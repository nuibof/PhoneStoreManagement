#pragma once
#include "entities/ProductVariant.h"
#include <QList>

struct VariantRow {
    ProductVariant variant;
    QString colorName;
    QString storageName;
    QString ramName; // rong neu bien the khong co RAM rieng
};
struct VariantOption {
    int id;
    QString name;
};

class VariantManager {
public:
    bool getVariants(int productId, QList<VariantRow> &variants, QString &error) const;
    bool getVariant(int id, ProductVariant &variant, QString &error) const;
    bool getColors(QList<VariantOption> &options, QString &error) const;
    bool getStorageOptions(QList<VariantOption> &options, QString &error) const;
    bool getRamOptions(QList<VariantOption> &options, QString &error) const;
    bool addVariant(const ProductVariant &variant, QString &error) const;
    bool updateVariant(const ProductVariant &variant, QString &error) const;
    bool deleteVariant(int id, QString &error) const;

    // quantityChange > 0: nhap them hang, < 0: ban hang (giam ton kho)
    bool adjustStock(int id, int quantityChange, QString &error) const;
};
