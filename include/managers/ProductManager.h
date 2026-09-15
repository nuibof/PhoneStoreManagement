#pragma once
#include "entities/Product.h"
#include <QList>

struct ProductRow {
    Product product;
    QString brandName;
    QString categoryName;
};
struct ProductOption {
    int id;
    QString name;
};
class ProductManager {
public:
    bool getProducts(QList<ProductRow> &products, QString &error) const;
    bool getProduct(int id, Product &product, QString &error) const;
    bool getBrands(QList<ProductOption> &options, QString &error) const;
    bool getCategories(QList<ProductOption> &options, QString &error) const;
    bool addProduct(const Product &product, QString &error) const;
    bool updateProduct(const Product &product, QString &error) const;
    bool deleteProduct(int id, QString &error) const;
};
