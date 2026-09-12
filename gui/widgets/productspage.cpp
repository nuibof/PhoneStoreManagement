//
// Created by Nam B on 9/12/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ProductsPage.h" resolved

#include "productspage.h"
#include "ui_ProductsPage.h"
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidgetItem>

ProductsPage::ProductsPage(QWidget *parent) : QWidget(parent), ui(new Ui::ProductsPage) {
    ui->setupUi(this);

    setupTable();
    connect(ui->btnAdd, &QPushButton::clicked, this, &ProductsPage::onAddProduct);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &ProductsPage::onRefresh);
    loadProducts();
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

    ui->tblProducts->setAlternatingRowColors(false);

    ui->tblProducts->verticalHeader()->setVisible(false);

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

    struct ProductData
    {
        int id;
        QString name;
        QString brand;
        QString category;
        QString model;
        int warranty;
        QString description;
    };

    const QList<ProductData> products = {

        // =========================
        // APPLE - 7 PRODUCTS
        // =========================

        {
            1,
            "iPhone 15",
            "Apple",
            "Smartphone",
            "iPhone 15",
            12,
            "iPhone 15 with A16 Bionic"
        },

        {
            2,
            "iPhone 15 Pro",
            "Apple",
            "Smartphone",
            "iPhone 15 Pro",
            12,
            "iPhone 15 Pro with A17 Pro and titanium design"
        },

        {
            3,
            "iPhone 15 Pro Max",
            "Apple",
            "Smartphone",
            "iPhone 15 Pro Max",
            12,
            "Premium iPhone with A17 Pro"
        },

        {
            4,
            "iPhone 16",
            "Apple",
            "Smartphone",
            "iPhone 16",
            12,
            "iPhone 16 with A18 chip"
        },

        {
            5,
            "iPhone 16 Pro",
            "Apple",
            "Smartphone",
            "iPhone 16 Pro",
            12,
            "iPhone 16 Pro with A18 Pro chip"
        },

        {
            6,
            "iPhone 16 Pro Max",
            "Apple",
            "Smartphone",
            "iPhone 16 Pro Max",
            12,
            "Premium iPhone with A18 Pro chip"
        },

        {
            7,
            "iPhone 17",
            "Apple",
            "Smartphone",
            "iPhone 17",
            12,
            "iPhone 17 with A19 chip"
        },

        // =========================
        // SAMSUNG - 7 PRODUCTS
        // =========================

        {
            8,
            "Galaxy S23",
            "Samsung",
            "Smartphone",
            "Galaxy S23",
            12,
            "Samsung Galaxy S23 flagship smartphone"
        },

        {
            9,
            "Galaxy S23 Ultra",
            "Samsung",
            "Smartphone",
            "Galaxy S23 Ultra",
            12,
            "Samsung Galaxy S23 Ultra with S Pen"
        },

        {
            10,
            "Galaxy S24",
            "Samsung",
            "Smartphone",
            "Galaxy S24",
            12,
            "Samsung Galaxy S24 flagship smartphone"
        },

        {
            11,
            "Galaxy S24 Ultra",
            "Samsung",
            "Smartphone",
            "Galaxy S24 Ultra",
            12,
            "Samsung flagship smartphone with S Pen"
        },

        {
            12,
            "Galaxy S25",
            "Samsung",
            "Smartphone",
            "Galaxy S25",
            12,
            "Samsung Galaxy S25 flagship smartphone"
        },

        {
            13,
            "Galaxy S25 Ultra",
            "Samsung",
            "Smartphone",
            "Galaxy S25 Ultra",
            12,
            "Samsung premium flagship smartphone"
        },

        {
            14,
            "Galaxy S26 Ultra",
            "Samsung",
            "Smartphone",
            "Galaxy S26 Ultra",
            12,
            "Samsung latest premium flagship smartphone"
        },

        // =========================
        // XIAOMI - 6 PRODUCTS
        // =========================

        {
            15,
            "Xiaomi 13",
            "Xiaomi",
            "Smartphone",
            "Xiaomi 13",
            12,
            "Xiaomi flagship smartphone"
        },

        {
            16,
            "Xiaomi 13 Pro",
            "Xiaomi",
            "Smartphone",
            "Xiaomi 13 Pro",
            12,
            "Xiaomi premium flagship with Leica camera"
        },

        {
            17,
            "Xiaomi 13T",
            "Xiaomi",
            "Smartphone",
            "Xiaomi 13T",
            12,
            "Xiaomi T-series smartphone"
        },

        {
            18,
            "Xiaomi 14",
            "Xiaomi",
            "Smartphone",
            "Xiaomi 14",
            12,
            "Xiaomi flagship smartphone with Leica camera"
        },

        {
            19,
            "Xiaomi 14T Pro",
            "Xiaomi",
            "Smartphone",
            "Xiaomi 14T Pro",
            12,
            "Xiaomi premium T-series smartphone"
        },

        {
            20,
            "Xiaomi 15",
            "Xiaomi",
            "Smartphone",
            "Xiaomi 15",
            12,
            "Xiaomi flagship smartphone"
        }
    };

    for (const ProductData &product : products)
    {
        const int row = ui->tblProducts->rowCount();

        ui->tblProducts->insertRow(row);

        ui->tblProducts->setItem(
            row,
            0,
            new QTableWidgetItem(
                QString::number(product.id)
            )
        );

        ui->tblProducts->setItem(
            row,
            1,
            new QTableWidgetItem(product.name)
        );

        ui->tblProducts->setItem(
            row,
            2,
            new QTableWidgetItem(product.brand)
        );

        ui->tblProducts->setItem(
            row,
            3,
            new QTableWidgetItem(product.category)
        );

        ui->tblProducts->setItem(
            row,
            4,
            new QTableWidgetItem(product.model)
        );

        ui->tblProducts->setItem(
            row,
            5,
            new QTableWidgetItem(
                QString::number(product.warranty) + " months"
            )
        );

        ui->tblProducts->setItem(
            row,
            6,
            new QTableWidgetItem(product.description)
        );

        // =========================
        // ACTION BUTTONS
        // =========================

        auto *editButton = new QPushButton("Edit");
        auto *deleteButton = new QPushButton("Delete");

        editButton->setProperty(
            "productId",
            product.id
        );

        deleteButton->setProperty(
            "productId",
            product.id
        );

        auto *actionWidget = new QWidget();

        auto *actionLayout =
            new QHBoxLayout(actionWidget);

        actionLayout->setContentsMargins(
            4, 2, 4, 2
        );

        actionLayout->setSpacing(5);

        actionLayout->addWidget(editButton);
        actionLayout->addWidget(deleteButton);

        ui->tblProducts->setCellWidget(
            row,
            7,
            actionWidget
        );

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
}

void ProductsPage::onAddProduct()
{
    QMessageBox::information(
        this,
        "Add Product",
        "Add Product dialog will be implemented here."
    );
}

void ProductsPage::onEditProduct()
{
    auto *button = qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int productId =
        button->property("productId").toInt();

    QMessageBox::information(
        this,
        "Edit Product",
        QString("Edit product ID: %1")
            .arg(productId)
    );
}

void ProductsPage::onDeleteProduct()
{
    auto *button = qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int productId =
        button->property("productId").toInt();

    QMessageBox::StandardButton reply =
        QMessageBox::question(
            this,
            "Delete Product",
            QString(
                "Are you sure you want to delete product ID %1?"
            ).arg(productId),
            QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(
            this,
            "Delete Product",
            "Product deleted successfully."
        );
    }
}

void ProductsPage::onRefresh()
{
    loadProducts();
}

void ProductsPage::onSearch()
{
    QString searchTerm = ui->txtSearch->text().trimmed();

    if (searchTerm.isEmpty())
    {
        loadProducts();
        return;
    }

    for (int row = 0; row < ui->tblProducts->rowCount(); ++row)
    {
        bool matchFound = false;

        for (int col = 0; col < ui->tblProducts->columnCount() - 1; ++col)
        {
            QTableWidgetItem *item = ui->tblProducts->item(row, col);

            if (item && item->text().contains(searchTerm, Qt::CaseInsensitive))
            {
                matchFound = true;
                break;
            }
        }

        ui->tblProducts->setRowHidden(row, !matchFound);
    }
}