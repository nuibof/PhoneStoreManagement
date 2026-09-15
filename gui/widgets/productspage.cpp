//
// Created by Nam B on 9/12/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ProductsPage.h" resolved

#include "productspage.h"
#include "ui_ProductsPage.h"

#include "VariantsDialog.h"
#include "managers/ProductManager.h"
#include <QHeaderView>
#include <QHBoxLayout>
#include <limits>

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QDialogButtonBox>

#include <QMessageBox>
#include <QPushButton>
#include <QVariant>
#include <QIcon>

ProductsPage::ProductsPage(const QString &position, QWidget* parent)
    : QWidget(parent),
      ui(new Ui::ProductsPage),
      position(position) {
    ui->setupUi(this);

    if (position == "Sales") {
        ui->btnAdd->setEnabled(false);
    }
    setupTable();
    connect(ui->btnAdd, &QPushButton::clicked, this, &ProductsPage::onAddProduct);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &ProductsPage::onRefresh);
    connect(ui->txtSearch, &QLineEdit::textChanged, this, &ProductsPage::onSearch);

    loadProducts();

    connect(ui->tblProducts, &QTableWidget::cellDoubleClicked,
        this, [this](int row, int column)
{
    Q_UNUSED(column);

    QTableWidgetItem *idItem = ui->tblProducts->item(row, 0);
    QTableWidgetItem *nameItem = ui->tblProducts->item(row, 1);

    if (!idItem || !nameItem)
        return;

    int productId = idItem->text().toInt();
    QString productName = nameItem->text();

    VariantsDialog dialog(
        productId,
        productName,
        this->position,
        this
    );

    dialog.exec();
});
}

ProductsPage::~ProductsPage() {
    delete ui;
}

void ProductsPage::setupTable()
{
    ui->tblProducts->setColumnCount(8);

    QStringList headers = {
        "ID",
        "Product Name",
        "Brand",
        "Category",
        "Model",
        "Warranty",
        "Description",
        "Actions"
    };

    ui->tblProducts->setHorizontalHeaderLabels(headers);

    ui->tblProducts->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );

    ui->tblProducts->setSelectionMode(
        QAbstractItemView::SingleSelection
    );

    ui->tblProducts->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );

    ui->tblProducts->setAlternatingRowColors(true);

    ui->tblProducts->verticalHeader()->setVisible(false);

    // Row height
    ui->tblProducts->verticalHeader()->setDefaultSectionSize(45);

    ui->tblProducts->horizontalHeader()
        ->setStretchLastSection(true);

    ui->tblProducts->horizontalHeader()
        ->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    ui->tblProducts->horizontalHeader()
        ->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->tblProducts->horizontalHeader()
        ->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ui->tblProducts->horizontalHeader()
        ->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    ui->tblProducts->horizontalHeader()
        ->setSectionResizeMode(4, QHeaderView::ResizeToContents);

    ui->tblProducts->horizontalHeader()
        ->setSectionResizeMode(5, QHeaderView::ResizeToContents);

    ui->tblProducts->horizontalHeader()
        ->setSectionResizeMode(6, QHeaderView::Stretch);

    ui->tblProducts->horizontalHeader()
        ->setSectionResizeMode(7, QHeaderView::ResizeToContents);
}

void ProductsPage::loadProducts()
{
    ui->tblProducts->setRowCount(0);
    ui->tblProducts->horizontalHeader()->setStretchLastSection(false);

    ProductManager manager;
    QList<ProductRow> products;
    QString error;
    if (!manager.getProducts(products, error)) {
        QMessageBox::critical(this, "Database Error", error);
        return;
    }
    for (const auto &entry : products)
    {
        const Product &product = entry.product;
        const int row = ui->tblProducts->rowCount();

        ui->tblProducts->insertRow(row);

        ui->tblProducts->setItem(
            row,
            0,
            new QTableWidgetItem(
                QString::number(product.getProductId())
            )
        );

        ui->tblProducts->setItem(
            row,
            1,
            new QTableWidgetItem(product.getProductName())
        );

        ui->tblProducts->setItem(
            row,
            2,
            new QTableWidgetItem(entry.brandName)
        );

        ui->tblProducts->setItem(
            row,
            3,
            new QTableWidgetItem(entry.categoryName)
        );

        ui->tblProducts->setItem(
            row,
            4,
            new QTableWidgetItem(product.getModel())
        );

        ui->tblProducts->setItem(
            row,
            5,
            new QTableWidgetItem(
                QString::number(product.getWarrantyMonths()) + " months"
            )
        );

        ui->tblProducts->setItem(
            row,
            6,
            new QTableWidgetItem(product.getDescription())
        );

        // =========================
        // ACTION BUTTONS
        // =========================

        auto* editButton = new QPushButton();
        auto* deleteButton = new QPushButton();
        editButton->setToolTip("Edit");
        deleteButton->setToolTip("Delete");
        editButton->setAccessibleName("Edit");
        deleteButton->setAccessibleName("Delete");

        editButton->setIcon(QIcon(":/icons/edit.svg"));
        deleteButton->setIcon(QIcon(":/icons/delete.svg"));
        editButton->setIconSize(QSize(18, 18));
        deleteButton->setIconSize(QSize(18, 18));

        const QString actionStyle =
            "QPushButton { padding: 4px 8px; color: #3478F6; "
            "background-color: #FFFFFF; border: 1px solid #D0D0D0; "
            "border-radius: 4px; text-align: center; }"
            "QPushButton:hover { background-color: #EAF1FF; }";
        editButton->setStyleSheet(actionStyle);
        deleteButton->setStyleSheet(actionStyle);

        // Let QSS from ProductsPage.ui control the appearance
        editButton->setProperty("action", "edit");
        deleteButton->setProperty("action", "delete");

        editButton->setProperty(
            "productId",
            product.getProductId()
        );

        deleteButton->setProperty(
            "productId",
            product.getProductId()
        );

        editButton->setMinimumSize(60, 30);
        deleteButton->setMinimumSize(60, 30);

        editButton->setCursor(Qt::PointingHandCursor);
        deleteButton->setCursor(Qt::PointingHandCursor);
        if (position == "Sales")
        {
            editButton->setEnabled(false);
            deleteButton->setEnabled(false);
        }

        auto *actionWidget = new QWidget();
        actionWidget->setObjectName("actionWidget");

        auto* actionLayout =
            new QHBoxLayout(actionWidget);

        actionLayout->setContentsMargins(
            4, 2, 4, 2
        );

        actionLayout->setSpacing(6);

        actionLayout->addWidget(editButton);
        actionLayout->addWidget(deleteButton);



        ui->tblProducts->setCellWidget(
            row,
            7,
            actionWidget
        );
        actionWidget->ensurePolished();
        editButton->ensurePolished();
        deleteButton->ensurePolished();
        editButton->setMinimumSize(editButton->sizeHint());
        deleteButton->setMinimumSize(deleteButton->sizeHint());
        ui->tblProducts->setRowHeight(row, actionLayout->sizeHint().height() + 20);

        connect(
            editButton,
            &QPushButton::clicked,
            this,
            &ProductsPage::onEditProduct
        );

        connect(
            deleteButton,
            &QPushButton::clicked,
            this,
            &ProductsPage::onDeleteProduct
        );
    }
    onSearch();
}

void ProductsPage::onAddProduct()
{
    showProductDialog(0);
}

void ProductsPage::onEditProduct()
{
    auto *button = qobject_cast<QPushButton *>(sender());
    if (button)
        showProductDialog(button->property("productId").toInt());
}

void ProductsPage::showProductDialog(int productId)
{
    ProductManager manager;
    Product product;
    QString error;
    if (productId != 0 && !manager.getProduct(productId, product, error)) {
        QMessageBox::warning(this, "Product", error);
        loadProducts();
        return;
    }
    QList<ProductOption> brands, categories;
    if (!manager.getBrands(brands, error) || !manager.getCategories(categories, error)) {
        QMessageBox::critical(this, "Database Error", error);
        return;
    }
    if (brands.isEmpty() || categories.isEmpty()) {
        QMessageBox::warning(this, "Product", "Create a brand and category before adding or editing a product.");
        return;
    }
    QDialog dialog(this);
    dialog.setWindowTitle(productId == 0 ? "Add Product" : "Edit Product");
    dialog.resize(450, 400);
    auto *layout = new QFormLayout(&dialog);
    auto *txtName = new QLineEdit(product.getProductName());
    auto *cbBrand = new QComboBox();
    auto *cbCategory = new QComboBox();
    auto *txtModel = new QLineEdit(product.getModel());
    auto *spinWarranty = new QSpinBox();
    auto *txtDescription = new QTextEdit();
    txtName->setObjectName("txtProductName");
    cbBrand->setObjectName("cbBrand");
    cbCategory->setObjectName("cbCategory");
    txtModel->setObjectName("txtModel");
    spinWarranty->setObjectName("spinWarranty");
    txtDescription->setObjectName("txtDescription");
    txtName->setMaxLength(150);
    txtModel->setMaxLength(100);
    spinWarranty->setRange(0, std::numeric_limits<int>::max());
    spinWarranty->setValue(productId == 0 ? 12 : product.getWarrantyMonths());
    txtDescription->setPlainText(product.getDescription());
    for (const auto &brand : brands) cbBrand->addItem(brand.name, brand.id);
    for (const auto &category : categories) cbCategory->addItem(category.name, category.id);
    if (productId != 0) {
        cbBrand->setCurrentIndex(cbBrand->findData(product.getBrandId()));
        cbCategory->setCurrentIndex(cbCategory->findData(product.getCategoryId()));
    }
    layout->addRow("Product Name:", txtName);
    layout->addRow("Brand:", cbBrand);
    layout->addRow("Category:", cbCategory);
    layout->addRow("Model:", txtModel);
    layout->addRow("Warranty:", spinWarranty);
    layout->addRow("Description:", txtDescription);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addRow(buttons);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, [&]() {
        product.setProductName(txtName->text());
        product.setBrandId(cbBrand->currentData().toInt());
        product.setCategoryId(cbCategory->currentData().toInt());
        product.setModel(txtModel->text());
        product.setWarrantyMonths(spinWarranty->value());
        product.setDescription(txtDescription->toPlainText());
        const bool saved = productId == 0 ? manager.addProduct(product, error)
                                          : manager.updateProduct(product, error);
        if (!saved) {
            QMessageBox::warning(&dialog, "Product", error);
            return;
        }
        dialog.accept();
    });
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Success", productId == 0
            ? "Product added successfully." : "Product updated successfully.");
    }
    loadProducts();
}

void ProductsPage::onDeleteProduct()
{
    auto *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;
    const int productId = button->property("productId").toInt();
    if (QMessageBox::question(this, "Delete Product",
            QString("Are you sure you want to delete product ID %1?").arg(productId),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes)
        return;
    ProductManager manager;
    QString error;
    if (!manager.deleteProduct(productId, error)) {
        QMessageBox::warning(this, "Product", error);
        return;
    }
    QMessageBox::information(this, "Success", "Product deleted successfully.");
    loadProducts();
}


void ProductsPage::onRefresh()
{
    loadProducts();

}

void ProductsPage::onSearch()
{
    QString searchTerm =
        ui->txtSearch->text().trimmed();

    for (int row = 0;
         row < ui->tblProducts->rowCount();
         ++row)
    {
        bool match = false;

        for (int col = 0;
             col < 7;
             ++col)
        {
            QTableWidgetItem *item =
                ui->tblProducts->item(row, col);

            if (item &&
                item->text().contains(
                    searchTerm,
                    Qt::CaseInsensitive))
            {
                match = true;
                break;
            }
        }

        ui->tblProducts->setRowHidden(
            row,
            !match
        );
    }
}
