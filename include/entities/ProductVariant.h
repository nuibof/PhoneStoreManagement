#pragma once

#include <QString>

class ProductVariant
{
private:
    int variantId;
    int productId;
    int colorId;
    int storageId;
    int ramId; // 0 nghia la khong co RAM rieng (cot ram_id trong DB co the NULL)

    QString sku;

    double costPrice;
    double sellingPrice;
    int stockQuantity;

public:
    ProductVariant();

    ProductVariant(int variantId,
        int productId,
        int colorId,
        int storageId,
        int ramId,
        const QString& sku,
        double costPrice,
        double sellingPrice,
        int stockQuantity);

    int getVariantId() const;
    int getProductId() const;
    int getColorId() const;
    int getStorageId() const;
    int getRamId() const;
    QString getSku() const;
    double getCostPrice() const;
    double getSellingPrice() const;
    int getStockQuantity() const;

    void setVariantId(int variantId);
    void setProductId(int productId);
    void setColorId(int colorId);
    void setStorageId(int storageId);
    void setRamId(int ramId);
    void setSku(const QString& sku);
    void setCostPrice(double costPrice);
    void setSellingPrice(double sellingPrice);
    void setStockQuantity(int stockQuantity);
};
