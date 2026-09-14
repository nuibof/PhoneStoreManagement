#include "entities/Product.h"

Product::Product()
{
    productId = 0;
    categoryId = 0;
    brandId = 0;
    warrantyMonths = 0;
}

Product::Product(int productId,
    int categoryId,
    int brandId,
    const QString& productName,
    const QString& model,
    const QString& description,
    int warrantyMonths)
{
    this->productId = productId;
    this->categoryId = categoryId;
    this->brandId = brandId;
    this->productName = productName;
    this->model = model;
    this->description = description;
    this->warrantyMonths = warrantyMonths;
}

int Product::getProductId() const
{
    return productId;
}

int Product::getCategoryId() const
{
    return categoryId;
}

int Product::getBrandId() const
{
    return brandId;
}

QString Product::getProductName() const
{
    return productName;
}

QString Product::getModel() const
{
    return model;
}

QString Product::getDescription() const
{
    return description;
}

int Product::getWarrantyMonths() const
{
    return warrantyMonths;
}

void Product::setProductId(int productId)
{
    this->productId = productId;
}

void Product::setCategoryId(int categoryId)
{
    this->categoryId = categoryId;
}

void Product::setBrandId(int brandId)
{
    this->brandId = brandId;
}

void Product::setProductName(const QString& productName)
{
    this->productName = productName;
}

void Product::setModel(const QString& model)
{
    this->model = model;
}

void Product::setDescription(const QString& description)
{
    this->description = description;
}

void Product::setWarrantyMonths(int warrantyMonths)
{
    this->warrantyMonths = warrantyMonths;
}