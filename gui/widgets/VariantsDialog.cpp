#include "VariantsDialog.h"
#include "ui_VariantsDialog.h"
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidgetItem>

VariantsDialog::VariantsDialog(int productId, const QString& productName, const QString& position, QWidget *parent)
    : QDialog(parent), ui(new Ui::VariantsDialog), productId(productId), editingVariantId(0), position(position)
{
    ui->setupUi(this);

    // Sales chỉ được xem variant
    if (position == "Sales")
    {
        ui->btnSave->setEnabled(false);
        ui->btnClear->setEnabled(false);
    }

    ui->lblProductName->setText(productName);

    setupTable();
    loadColorOptions();
    loadStorageOptions();
    loadRamOptions();
    loadVariants();

    connect(ui->btnSave, &QPushButton::clicked, this, &VariantsDialog::onSaveClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &VariantsDialog::onClearClicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::accept);
}

VariantsDialog::~VariantsDialog()
{
    delete ui;
}

void VariantsDialog::setupTable()
{
    ui->tblVariants->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblVariants->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblVariants->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tblVariants->verticalHeader()->setVisible(false);
    ui->tblVariants->verticalHeader()->setDefaultSectionSize(42);

    ui->tblVariants->horizontalHeader()->setStretchLastSection(true);
    ui->tblVariants->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

void VariantsDialog::loadColorOptions()
{
    ui->cboColor->clear();

    QList<VariantOption> colors;
    QString error;
    if (!manager.getColors(colors, error)) {
        QMessageBox::warning(this, "Load Colors", error);
        return;
    }
    for (const VariantOption &option : colors) {
        ui->cboColor->addItem(option.name, option.id);
    }
}

void VariantsDialog::loadStorageOptions()
{
    ui->cboStorage->clear();

    QList<VariantOption> options;
    QString error;
    if (!manager.getStorageOptions(options, error)) {
        QMessageBox::warning(this, "Load Storage Options", error);
        return;
    }
    for (const VariantOption &option : options) {
        ui->cboStorage->addItem(option.name, option.id);
    }
}

void VariantsDialog::loadRamOptions()
{
    ui->cboRam->clear();
    ui->cboRam->addItem("(No RAM option)", 0);

    QList<VariantOption> options;
    QString error;
    if (!manager.getRamOptions(options, error)) {
        QMessageBox::warning(this, "Load RAM Options", error);
        return;
    }
    for (const VariantOption &option : options) {
        ui->cboRam->addItem(option.name, option.id);
    }
}

void VariantsDialog::loadVariants()
{
    ui->tblVariants->setRowCount(0);

    QList<VariantRow> variants;
    QString error;
    if (!manager.getVariants(productId, variants, error)) {
        QMessageBox::warning(this, "Load Variants", error);
        return;
    }

    for (const VariantRow &row : variants) {
        const int r = ui->tblVariants->rowCount();
        ui->tblVariants->insertRow(r);

        ui->tblVariants->setItem(r, 0, new QTableWidgetItem(row.variant.getSku()));
        ui->tblVariants->setItem(r, 1, new QTableWidgetItem(row.colorName));
        ui->tblVariants->setItem(r, 2, new QTableWidgetItem(row.storageName));
        ui->tblVariants->setItem(r, 3, new QTableWidgetItem(row.ramName.isEmpty() ? QString("-") : row.ramName));
        ui->tblVariants->setItem(r, 4, new QTableWidgetItem(QString::number(row.variant.getCostPrice(), 'f', 0)));
        ui->tblVariants->setItem(r, 5, new QTableWidgetItem(QString::number(row.variant.getSellingPrice(), 'f', 0)));
        ui->tblVariants->setItem(r, 6, new QTableWidgetItem(QString::number(row.variant.getStockQuantity())));

        auto *editButton = new QPushButton("Edit");
        auto *deleteButton = new QPushButton("Delete");

        editButton->setProperty("action", "edit");
        deleteButton->setProperty("action", "delete");
        editButton->setProperty("variantId", row.variant.getVariantId());
        deleteButton->setProperty("variantId", row.variant.getVariantId());

        editButton->setMinimumSize(55, 28);
        deleteButton->setMinimumSize(55, 28);
        editButton->setCursor(Qt::PointingHandCursor);
        deleteButton->setCursor(Qt::PointingHandCursor);

        auto *actionWidget = new QWidget();
        actionWidget->setObjectName("actionWidget");

        auto *actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->setContentsMargins(4, 2, 4, 2);
        actionLayout->setSpacing(6);
        actionLayout->addWidget(editButton);
        actionLayout->addWidget(deleteButton);

        ui->tblVariants->setCellWidget(r, 7, actionWidget);

        connect(editButton, &QPushButton::clicked, this, &VariantsDialog::onEditVariant);
        connect(deleteButton, &QPushButton::clicked, this, &VariantsDialog::onDeleteVariant);
    }
}

void VariantsDialog::fillFormFromVariant(const ProductVariant &variant)
{
    int colorIndex = ui->cboColor->findData(variant.getColorId());
    if (colorIndex >= 0) ui->cboColor->setCurrentIndex(colorIndex);

    int storageIndex = ui->cboStorage->findData(variant.getStorageId());
    if (storageIndex >= 0) ui->cboStorage->setCurrentIndex(storageIndex);

    int ramIndex = ui->cboRam->findData(variant.getRamId());
    if (ramIndex >= 0) ui->cboRam->setCurrentIndex(ramIndex);

    ui->txtSku->setText(variant.getSku());
    ui->spinCostPrice->setValue(variant.getCostPrice());
    ui->spinSellingPrice->setValue(variant.getSellingPrice());
    ui->spinStock->setValue(variant.getStockQuantity());
}

void VariantsDialog::clearForm()
{
    ui->cboColor->setCurrentIndex(0);
    ui->cboStorage->setCurrentIndex(0);
    ui->cboRam->setCurrentIndex(0);
    ui->txtSku->clear();
    ui->spinCostPrice->setValue(0);
    ui->spinSellingPrice->setValue(0);
    ui->spinStock->setValue(0);

    editingVariantId = 0;
    setFormMode(false);
}

void VariantsDialog::setFormMode(bool editing)
{
    ui->btnSave->setText(editing ? "Update Variant" : "+ Add Variant");
}

void VariantsDialog::onSaveClicked()
{
    ProductVariant variant;
    variant.setVariantId(editingVariantId);
    variant.setProductId(productId);
    variant.setColorId(ui->cboColor->currentData().toInt());
    variant.setStorageId(ui->cboStorage->currentData().toInt());
    variant.setRamId(ui->cboRam->currentData().toInt());
    variant.setSku(ui->txtSku->text());
    variant.setCostPrice(ui->spinCostPrice->value());
    variant.setSellingPrice(ui->spinSellingPrice->value());
    variant.setStockQuantity(ui->spinStock->value());

    QString error;
    bool ok = (editingVariantId > 0)
        ? manager.updateVariant(variant, error)
        : manager.addVariant(variant, error);

    if (!ok) {
        QMessageBox::warning(this, "Save Variant", error);
        return;
    }

    clearForm();
    loadVariants();
}

void VariantsDialog::onClearClicked()
{
    clearForm();
}

void VariantsDialog::onEditVariant()
{
    auto *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    int variantId = button->property("variantId").toInt();

    ProductVariant variant;
    QString error;
    if (!manager.getVariant(variantId, variant, error)) {
        QMessageBox::warning(this, "Edit Variant", error);
        return;
    }

    editingVariantId = variantId;
    fillFormFromVariant(variant);
    setFormMode(true);
}

void VariantsDialog::onDeleteVariant()
{
    auto *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    int variantId = button->property("variantId").toInt();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Delete Variant",
        QString("Are you sure you want to delete variant ID %1?").arg(variantId),
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply != QMessageBox::Yes) {
        return;
    }

    QString error;
    if (!manager.deleteVariant(variantId, error)) {
        QMessageBox::warning(this, "Delete Variant", error);
        return;
    }

    if (editingVariantId == variantId) {
        clearForm();
    }
    loadVariants();
}
