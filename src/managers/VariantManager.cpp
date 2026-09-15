#include "managers/VariantManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

namespace {
ProductVariant readVariant(const QSqlQuery &q) {
    int ramId = q.value(4).isNull() ? 0 : q.value(4).toInt();
    return ProductVariant(q.value(0).toInt(), q.value(1).toInt(), q.value(2).toInt(), q.value(3).toInt(),
                           ramId, q.value(5).toString(), q.value(6).toDouble(), q.value(7).toDouble(),
                           q.value(8).toInt());
}
bool options(const QString &sql, QList<VariantOption> &result, QString &error) {
    result.clear(); error.clear();
    QSqlQuery q;
    if (!q.exec(sql)) { error = q.lastError().text(); return false; }
    while (q.next()) result.append({q.value(0).toInt(), q.value(1).toString()});
    if (q.lastError().isValid()) { error = q.lastError().text(); result.clear(); return false; }
    return true;
}
bool bindVariant(QSqlQuery &q, const ProductVariant &v, QString &error) {
    error.clear();
    if (v.getSku().trimmed().isEmpty()) { error = "SKU cannot be empty."; return false; }
    if (v.getSku().trimmed().size() > 100) { error = "SKU exceeds the allowed length."; return false; }
    if (v.getProductId() <= 0) { error = "Select a product."; return false; }
    if (v.getColorId() <= 0 || v.getStorageId() <= 0) { error = "Select a color and a storage option."; return false; }
    if (v.getCostPrice() < 0 || v.getSellingPrice() < 0) { error = "Price cannot be negative."; return false; }
    if (v.getStockQuantity() < 0) { error = "Stock quantity cannot be negative."; return false; }
    q.bindValue(":product", v.getProductId());
    q.bindValue(":color", v.getColorId());
    q.bindValue(":storage", v.getStorageId());
    if (v.getRamId() > 0) {
        q.bindValue(":ram", v.getRamId());
    } else {
        q.bindValue(":ram", QVariant()); // QVariant rong -> Qt gui SQL NULL cho cot ram_id
    }
    q.bindValue(":sku", v.getSku().trimmed());
    q.bindValue(":cost", v.getCostPrice());
    q.bindValue(":sell", v.getSellingPrice());
    q.bindValue(":stock", v.getStockQuantity());
    return true;
}
bool change(QSqlQuery &q, QString &error) {
    error.clear();
    if (!q.exec()) {
        QString code = q.lastError().nativeErrorCode();
        if (code == "23505") {
            error = "This SKU already exists.";
        } else if (code == "23503") {
            error = "This operation conflicts with related data (product/color/storage/ram, or existing orders).";
        } else {
            error = q.lastError().text();
        }
        return false;
    }
    if (q.numRowsAffected() != 1) { error = "This variant no longer exists. Refresh the list."; return false; }
    return true;
}
}

bool VariantManager::getVariants(int productId, QList<VariantRow> &variants, QString &error) const {
    variants.clear(); error.clear();
    QSqlQuery q;
    q.prepare(
        "SELECT v.variant_id, v.product_id, v.color_id, v.storage_id, v.ram_id, v.sku, "
        "       v.cost_price, v.selling_price, v.stock_quantity, "
        "       c.color_name, s.storage_name, r.ram_name "
        "FROM product_variants v "
        "LEFT JOIN colors c ON c.color_id = v.color_id "
        "LEFT JOIN storage_options s ON s.storage_id = v.storage_id "
        "LEFT JOIN ram_options r ON r.ram_id = v.ram_id "
        "WHERE v.product_id = :productId "
        "ORDER BY v.variant_id"
    );
    q.bindValue(":productId", productId);
    if (!q.exec()) { error = q.lastError().text(); return false; }
    while (q.next()) {
        VariantRow row;
        row.variant = readVariant(q);
        row.colorName = q.value(9).toString();
        row.storageName = q.value(10).toString();
        row.ramName = q.value(11).toString();
        variants.append(row);
    }
    if (q.lastError().isValid()) { error = q.lastError().text(); variants.clear(); return false; }
    return true;
}

bool VariantManager::getVariant(int id, ProductVariant &variant, QString &error) const {
    error.clear(); variant = ProductVariant();
    QSqlQuery q;
    q.prepare(
        "SELECT variant_id, product_id, color_id, storage_id, ram_id, sku, cost_price, selling_price, stock_quantity "
        "FROM product_variants WHERE variant_id = :id"
    );
    q.bindValue(":id", id);
    if (!q.exec()) { error = q.lastError().text(); return false; }
    if (!q.next()) { error = q.lastError().isValid() ? q.lastError().text() : "This variant no longer exists."; return false; }
    variant = readVariant(q);
    return true;
}

bool VariantManager::getColors(QList<VariantOption> &result, QString &error) const {
    return options("SELECT color_id, color_name FROM colors ORDER BY color_name", result, error);
}

bool VariantManager::getStorageOptions(QList<VariantOption> &result, QString &error) const {
    return options("SELECT storage_id, storage_name FROM storage_options ORDER BY storage_id", result, error);
}

bool VariantManager::getRamOptions(QList<VariantOption> &result, QString &error) const {
    return options("SELECT ram_id, ram_name FROM ram_options ORDER BY ram_id", result, error);
}

bool VariantManager::addVariant(const ProductVariant &v, QString &error) const {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO product_variants (product_id, color_id, storage_id, ram_id, sku, cost_price, selling_price, stock_quantity) "
        "VALUES (:product, :color, :storage, :ram, :sku, :cost, :sell, :stock)"
    );
    return bindVariant(q, v, error) && change(q, error);
}

bool VariantManager::updateVariant(const ProductVariant &v, QString &error) const {
    QSqlQuery q;
    q.prepare(
        "UPDATE product_variants "
        "SET product_id=:product, color_id=:color, storage_id=:storage, ram_id=:ram, "
        "    sku=:sku, cost_price=:cost, selling_price=:sell, stock_quantity=:stock "
        "WHERE variant_id=:id"
    );
    q.bindValue(":id", v.getVariantId());
    return bindVariant(q, v, error) && change(q, error);
}

bool VariantManager::deleteVariant(int id, QString &error) const {
    QSqlQuery q;
    q.prepare("DELETE FROM product_variants WHERE variant_id=:id");
    q.bindValue(":id", id);
    return change(q, error);
}

bool VariantManager::adjustStock(int id, int quantityChange, QString &error) const {
    error.clear();
    QSqlQuery q;
    // Dieu kien "stock_quantity + :delta >= 0" trong WHERE dam bao khong the ban vuot ton kho
    // ngay ca khi co nhieu request chay dong thoi (tranh race condition o muc DB).
    q.prepare(
        "UPDATE product_variants "
        "SET stock_quantity = stock_quantity + :delta "
        "WHERE variant_id = :id AND stock_quantity + :delta >= 0"
    );
    q.bindValue(":delta", quantityChange);
    q.bindValue(":id", id);
    if (!q.exec()) { error = q.lastError().text(); return false; }
    if (q.numRowsAffected() != 1) {
        error = "Stock update rejected (variant not found, or not enough stock to sell).";
        return false;
    }
    return true;
}
