#pragma once

#include <QString>

class Product
{
private:
    int productId;
    int categoryId;
    int brandId;

    QString productName;
    QString model;
    QString description;

    int warrantyMonths;

public:
    Product();

    Product(int productId,
        int categoryId,
        int brandId,
        const QString& productName,
        const QString& model,
        const QString& description,
        int warrantyMonths);

    int getProductId() const;
    int getCategoryId() const;
    int getBrandId() const;
    QString getProductName() const;
    QString getModel() const;
    QString getDescription() const;
    int getWarrantyMonths() const;

    void setProductId(int productId);
    void setCategoryId(int categoryId);
    void setBrandId(int brandId);
    void setProductName(const QString& productName);
    void setModel(const QString& model);
    void setDescription(const QString& description);
    void setWarrantyMonths(int warrantyMonths);
};