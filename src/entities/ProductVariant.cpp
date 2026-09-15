#include "entities/ProductVariant.h"

ProductVariant::ProductVariant()
{
    variantId = 0;
    productId = 0;
    colorId = 0;
    storageId = 0;
    ramId = 0;
    costPrice = 0;
    sellingPrice = 0;
    stockQuantity = 0;
}

ProductVariant::ProductVariant(int variantId,
    int productId,
    int colorId,
    int storageId,
    int ramId,
    const QString& sku,
    double costPrice,
    double sellingPrice,
    int stockQuantity)
{
    this->variantId = variantId;
    this->productId = productId;
    this->colorId = colorId;
    this->storageId = storageId;
    this->ramId = ramId;
    this->sku = sku;
    this->costPrice = costPrice;
    this->sellingPrice = sellingPrice;
    this->stockQuantity = stockQuantity;
}

int ProductVariant::getVariantId() const
{
    return variantId;
}

int ProductVariant::getProductId() const
{
    return productId;
}

int ProductVariant::getColorId() const
{
    return colorId;
}

int ProductVariant::getStorageId() const
{
    return storageId;
}

int ProductVariant::getRamId() const
{
    return ramId;
}

QString ProductVariant::getSku() const
{
    return sku;
}

double ProductVariant::getCostPrice() const
{
    return costPrice;
}

double ProductVariant::getSellingPrice() const
{
    return sellingPrice;
}

int ProductVariant::getStockQuantity() const
{
    return stockQuantity;
}

void ProductVariant::setVariantId(int variantId)
{
    this->variantId = variantId;
}

void ProductVariant::setProductId(int productId)
{
    this->productId = productId;
}

void ProductVariant::setColorId(int colorId)
{
    this->colorId = colorId;
}

void ProductVariant::setStorageId(int storageId)
{
    this->storageId = storageId;
}

void ProductVariant::setRamId(int ramId)
{
    this->ramId = ramId;
}

void ProductVariant::setSku(const QString& sku)
{
    this->sku = sku;
}

void ProductVariant::setCostPrice(double costPrice)
{
    this->costPrice = costPrice;
}

void ProductVariant::setSellingPrice(double sellingPrice)
{
    this->sellingPrice = sellingPrice;
}

void ProductVariant::setStockQuantity(int stockQuantity)
{
    this->stockQuantity = stockQuantity;
}
