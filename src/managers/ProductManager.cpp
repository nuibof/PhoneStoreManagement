#include "managers/ProductManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

namespace {
Product readProduct(const QSqlQuery &q) {
    return Product(q.value(0).toInt(), q.value(1).toInt(), q.value(2).toInt(),
                   q.value(3).toString(), q.value(4).toString(), q.value(5).toString(), q.value(6).toInt());
}
bool options(const QString &sql, QList<ProductOption> &result, QString &error) {
    result.clear(); error.clear();
    QSqlQuery q;
    if (!q.exec(sql)) { error = q.lastError().text(); return false; }
    while (q.next()) result.append({q.value(0).toInt(), q.value(1).toString()});
    if (q.lastError().isValid()) { error = q.lastError().text(); result.clear(); return false; }
    return true;
}
bool bindProduct(QSqlQuery &q, const Product &p, QString &error) {
    error.clear();
    if (p.getProductName().trimmed().isEmpty()) { error = "Product name cannot be empty."; return false; }
    if (p.getProductName().trimmed().size() > 150 || p.getModel().trimmed().size() > 100) {
        error = "Product name or model exceeds the allowed length."; return false;
    }
    if (p.getBrandId() <= 0 || p.getCategoryId() <= 0) { error = "Select a brand and category."; return false; }
    if (p.getWarrantyMonths() < 0) { error = "Warranty cannot be negative."; return false; }
    q.bindValue(":name", p.getProductName().trimmed());
    q.bindValue(":model", p.getModel().trimmed());
    q.bindValue(":description", p.getDescription().trimmed());
    q.bindValue(":brand", p.getBrandId());
    q.bindValue(":category", p.getCategoryId());
    q.bindValue(":warranty", p.getWarrantyMonths());
    return true;
}
bool change(QSqlQuery &q, QString &error) {
    error.clear();
    if (!q.exec()) {
        error = q.lastError().nativeErrorCode() == "23503"
            ? "This operation conflicts with related data. The product may have variants, or its brand/category no longer exists."
            : q.lastError().text();
        return false;
    }
    if (q.numRowsAffected() != 1) { error = "This product no longer exists. Refresh the list."; return false; }
    return true;
}
}
bool ProductManager::getProducts(QList<ProductRow> &products, QString &error) const {
    products.clear(); error.clear();
    QSqlQuery q;
    if (!q.exec("SELECT p.product_id, p.category_id, p.brand_id, p.product_name, p.model, p.description, p.warranty_months, b.brand_name, c.category_name FROM products p LEFT JOIN brands b ON b.brand_id=p.brand_id LEFT JOIN categories c ON c.category_id=p.category_id ORDER BY p.product_id")) {
        error = q.lastError().text(); return false;
    }
    while (q.next()) products.append({readProduct(q), q.value(7).toString(), q.value(8).toString()});
    if (q.lastError().isValid()) { error = q.lastError().text(); products.clear(); return false; }
    return true;
}
bool ProductManager::getProduct(int id, Product &product, QString &error) const {
    error.clear(); product = Product();
    QSqlQuery q;
    q.prepare("SELECT product_id, category_id, brand_id, product_name, model, description, warranty_months FROM products WHERE product_id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) { error = q.lastError().text(); return false; }
    if (!q.next()) { error = q.lastError().isValid() ? q.lastError().text() : "This product no longer exists."; return false; }
    product = readProduct(q); return true;
}
bool ProductManager::getBrands(QList<ProductOption> &result, QString &error) const {
    return options("SELECT brand_id, brand_name FROM brands ORDER BY brand_name", result, error);
}
bool ProductManager::getCategories(QList<ProductOption> &result, QString &error) const {
    return options("SELECT category_id, category_name FROM categories ORDER BY category_name", result, error);
}
bool ProductManager::addProduct(const Product &p, QString &error) const {
    QSqlQuery q;
    q.prepare("INSERT INTO products (category_id, brand_id, product_name, model, description, warranty_months) VALUES (:category, :brand, :name, :model, :description, :warranty)");
    return bindProduct(q, p, error) && change(q, error);
}
bool ProductManager::updateProduct(const Product &p, QString &error) const {
    QSqlQuery q;
    q.prepare("UPDATE products SET category_id=:category, brand_id=:brand, product_name=:name, model=:model, description=:description, warranty_months=:warranty WHERE product_id=:id");
    q.bindValue(":id", p.getProductId());
    return bindProduct(q, p, error) && change(q, error);
}
bool ProductManager::deleteProduct(int id, QString &error) const {
    QSqlQuery q;
    q.prepare("DELETE FROM products WHERE product_id=:id");
    q.bindValue(":id", id);
    return change(q, error);
}
