#include "managers/OrderManager.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

namespace {
bool options(const QString &sql, QList<OrderOption> &result, QString &error) {
    result.clear(); error.clear();
    QSqlQuery query;
    if (!query.exec(sql)) { error = query.lastError().text(); return false; }
    while (query.next()) result.append({query.value(0).toInt(), query.value(1).toString()});
    return true;
}

QString friendlyError(const QSqlError &sqlError) {
    if (sqlError.nativeErrorCode() == "23503")
        return "This order has a related invoice and cannot be deleted.";
    return sqlError.text();
}
}

bool OrderManager::getOrders(QList<OrderRow> &orders, QString &error) const {
    orders.clear(); error.clear();
    QSqlQuery query;
    if (!query.exec(
        "SELECT o.order_id, o.customer_id, o.employee_id, o.order_date, o.status, "
        "o.total_amount, c.full_name, e.full_name "
        "FROM orders o JOIN customers c ON c.customer_id=o.customer_id "
        "JOIN employees e ON e.employee_id=o.employee_id ORDER BY o.order_id")) {
        error = query.lastError().text(); return false;
    }
    while (query.next()) {
        Order order(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(),
                    query.value(3).toDateTime(), query.value(4).toString());
        order.setTotalAmount(query.value(5).toDouble());
        orders.append({order, query.value(6).toString(), query.value(7).toString()});
    }
    return true;
}

bool OrderManager::getCustomers(QList<OrderOption> &result, QString &error) const {
    return options("SELECT customer_id, full_name FROM customers ORDER BY full_name", result, error);
}

bool OrderManager::getEmployees(QList<OrderOption> &result, QString &error) const {
    return options("SELECT employee_id, full_name FROM employees ORDER BY full_name", result, error);
}

bool OrderManager::getVariants(QList<OrderVariantOption> &result, QString &error) const {
    result.clear(); error.clear();
    QSqlQuery query;
    if (!query.exec(
        "SELECT v.variant_id, p.product_name || ' - ' || v.sku, v.selling_price, v.stock_quantity "
        "FROM product_variants v JOIN products p ON p.product_id=v.product_id "
        "WHERE v.stock_quantity > 0 ORDER BY p.product_name, v.sku")) {
        error = query.lastError().text(); return false;
    }
    while (query.next()) result.append({query.value(0).toInt(), query.value(1).toString(),
                                        query.value(2).toDouble(), query.value(3).toInt()});
    return true;
}

bool OrderManager::addOrder(int customerId, int employeeId, int variantId, int quantity,
                            const QString &status, QString &error) const {
    error.clear();
    if (customerId <= 0 || employeeId <= 0 || variantId <= 0 || quantity <= 0) {
        error = "Select a customer, employee and product variant."; return false;
    }
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction()) { error = db.lastError().text(); return false; }
    QSqlQuery stock(db);
    stock.prepare("SELECT selling_price, stock_quantity FROM product_variants WHERE variant_id=:id FOR UPDATE");
    stock.bindValue(":id", variantId);
    if (!stock.exec() || !stock.next()) { error = stock.lastError().isValid() ? stock.lastError().text() : "Variant not found."; db.rollback(); return false; }
    const double price = stock.value(0).toDouble();
    if (stock.value(1).toInt() < quantity) { error = "Not enough stock for the selected variant."; db.rollback(); return false; }
    QSqlQuery order(db);
    order.prepare("INSERT INTO orders(customer_id, employee_id, status, total_amount) VALUES(:customer,:employee,:status,:total) RETURNING order_id");
    order.bindValue(":customer", customerId); order.bindValue(":employee", employeeId);
    order.bindValue(":status", status); order.bindValue(":total", price * quantity);
    if (!order.exec() || !order.next()) { error = order.lastError().text(); db.rollback(); return false; }
    QSqlQuery detail(db);
    detail.prepare("INSERT INTO order_details(order_id, variant_id, quantity, unit_price) VALUES(:order,:variant,:quantity,:price)");
    detail.bindValue(":order", order.value(0)); detail.bindValue(":variant", variantId);
    detail.bindValue(":quantity", quantity); detail.bindValue(":price", price);
    if (!detail.exec()) { error = detail.lastError().text(); db.rollback(); return false; }
    QSqlQuery update(db);
    update.prepare("UPDATE product_variants SET stock_quantity=stock_quantity-:quantity WHERE variant_id=:variant");
    update.bindValue(":quantity", quantity); update.bindValue(":variant", variantId);
    if (!update.exec()) { error = update.lastError().text(); db.rollback(); return false; }
    if (!db.commit()) { error = db.lastError().text(); db.rollback(); return false; }
    return true;
}

bool OrderManager::updateOrder(const Order &order, QString &error) const {
    error.clear();
    QSqlQuery query;
    query.prepare("UPDATE orders SET customer_id=:customer, employee_id=:employee, status=:status WHERE order_id=:id");
    query.bindValue(":customer", order.getCustomerId()); query.bindValue(":employee", order.getEmployeeId());
    query.bindValue(":status", order.getStatus()); query.bindValue(":id", order.getOrderId());
    if (!query.exec()) { error = friendlyError(query.lastError()); return false; }
    if (query.numRowsAffected() != 1) { error = "This order no longer exists."; return false; }
    return true;
}

bool OrderManager::deleteOrder(int id, QString &error) const {
    error.clear();
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction()) { error = db.lastError().text(); return false; }
    QSqlQuery restore(db);
    restore.prepare("UPDATE product_variants v SET stock_quantity=v.stock_quantity+d.quantity FROM order_details d WHERE d.order_id=:id AND d.variant_id=v.variant_id");
    restore.bindValue(":id", id);
    if (!restore.exec()) { error = restore.lastError().text(); db.rollback(); return false; }
    QSqlQuery query(db);
    query.prepare("DELETE FROM orders WHERE order_id=:id"); query.bindValue(":id", id);
    if (!query.exec()) { error = friendlyError(query.lastError()); db.rollback(); return false; }
    if (query.numRowsAffected() != 1) { error = "This order no longer exists."; db.rollback(); return false; }
    if (!db.commit()) { error = db.lastError().text(); db.rollback(); return false; }
    return true;
}
