#include "managers/InvoiceManager.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

bool InvoiceManager::getInvoices(QList<Invoice> &invoices, QString &error) const {
    invoices.clear(); error.clear();
    QSqlQuery query;
    if (!query.exec("SELECT invoice_id, order_id, invoice_date, payment_method, payment_status, total_amount FROM invoices ORDER BY invoice_id")) {
        error = query.lastError().text(); return false;
    }
    while (query.next()) {
        Invoice invoice(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toDateTime(),
                        query.value(3).toString(), query.value(4).toString());
        invoice.setTotalAmount(query.value(5).toDouble());
        invoices.append(invoice);
    }
    return true;
}

bool InvoiceManager::getAvailableOrders(QList<InvoiceOrderOption> &orders, QString &error) const {
    orders.clear(); error.clear();
    QSqlQuery query;
    if (!query.exec(
        "SELECT o.order_id, '#' || o.order_id || ' - ' || c.full_name, o.total_amount "
        "FROM orders o JOIN customers c ON c.customer_id=o.customer_id "
        "LEFT JOIN invoices i ON i.order_id=o.order_id WHERE i.invoice_id IS NULL "
        "ORDER BY o.order_id")) {
        error = query.lastError().text(); return false;
    }
    while (query.next()) orders.append({query.value(0).toInt(), query.value(1).toString(), query.value(2).toDouble()});
    return true;
}

bool InvoiceManager::addInvoice(int orderId, const QString &method, const QString &status, QString &error) const {
    error.clear();
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction()) { error = db.lastError().text(); return false; }
    QSqlQuery order(db);
    order.prepare("SELECT total_amount FROM orders WHERE order_id=:id"); order.bindValue(":id", orderId);
    if (!order.exec() || !order.next()) { error = order.lastError().isValid() ? order.lastError().text() : "Order not found."; db.rollback(); return false; }
    QSqlQuery invoice(db);
    invoice.prepare("INSERT INTO invoices(order_id,payment_method,payment_status,total_amount) VALUES(:order,:method,:status,:total) RETURNING invoice_id");
    invoice.bindValue(":order", orderId); invoice.bindValue(":method", method);
    invoice.bindValue(":status", status); invoice.bindValue(":total", order.value(0));
    if (!invoice.exec() || !invoice.next()) { error = invoice.lastError().text(); db.rollback(); return false; }
    QSqlQuery details(db);
    details.prepare("INSERT INTO invoice_details(invoice_id,variant_id,quantity,unit_price) SELECT :invoice,variant_id,quantity,unit_price FROM order_details WHERE order_id=:order");
    details.bindValue(":invoice", invoice.value(0)); details.bindValue(":order", orderId);
    if (!details.exec()) { error = details.lastError().text(); db.rollback(); return false; }
    if (!db.commit()) { error = db.lastError().text(); db.rollback(); return false; }
    return true;
}

bool InvoiceManager::updateInvoice(const Invoice &invoice, QString &error) const {
    error.clear();
    QSqlQuery query;
    query.prepare("UPDATE invoices SET payment_method=:method,payment_status=:status WHERE invoice_id=:id");
    query.bindValue(":method", invoice.getPaymentMethod()); query.bindValue(":status", invoice.getPaymentStatus());
    query.bindValue(":id", invoice.getInvoiceId());
    if (!query.exec()) { error = query.lastError().text(); return false; }
    if (query.numRowsAffected() != 1) { error = "This invoice no longer exists."; return false; }
    return true;
}

bool InvoiceManager::deleteInvoice(int id, QString &error) const {
    error.clear();
    QSqlQuery query;
    query.prepare("DELETE FROM invoices WHERE invoice_id=:id"); query.bindValue(":id", id);
    if (!query.exec()) { error = query.lastError().text(); return false; }
    if (query.numRowsAffected() != 1) { error = "This invoice no longer exists."; return false; }
    return true;
}
