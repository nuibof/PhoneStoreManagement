#pragma once

#include <QDialog>
#include "entities/ProductVariant.h"
#include "managers/VariantManager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class VariantsDialog;
}
QT_END_NAMESPACE

// Dialog quan ly cac bien the (mau/dung luong/RAM/gia/ton kho) cua MOT san pham.
// Duoc mo tu ProductsPage (module Product+Customer) bang cach truyen vao productId
// va productName cua dong san pham dang chon - VariantsDialog khong tu tra cuu
// danh sach san pham, giu module Variant doc lap voi cach ProductManager cai dat.
class VariantsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VariantsDialog(
        int productId,
        const QString& productName,
        const QString& position,
        QWidget *parent = nullptr
    );
    ~VariantsDialog();

private slots:
    void onSaveClicked();
    void onClearClicked();
    void onEditVariant();
    void onDeleteVariant();

private:
    Ui::VariantsDialog *ui;
    VariantManager manager;

    int productId;
    int editingVariantId; // 0 = dang o che do them moi, > 0 = dang sua bien the co id nay

    QString position;

    void setupTable();
    void loadColorOptions();
    void loadStorageOptions();
    void loadRamOptions();
    void loadVariants();
    void fillFormFromVariant(const ProductVariant &variant);
    void clearForm();
    void setFormMode(bool editing);
};
