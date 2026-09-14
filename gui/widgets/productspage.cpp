//
// Created by Nam B on 9/12/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ProductsPage.h" resolved

#include "productspage.h"
#include "ui_ProductsPage.h"

#include <QSqlQuery>
#include <QSqlError>

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
#include "QtAwesome.h"

ProductsPage::ProductsPage(QWidget* parent) : QWidget(parent), ui(new Ui::ProductsPage) {
    ui->setupUi(this);

    awesome = new fa::QtAwesome(this);
    awesome->initFontAwesome();

    setupTable();
    connect(ui->btnAdd, &QPushButton::clicked, this, &ProductsPage::onAddProduct);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &ProductsPage::onRefresh);
    connect(ui->txtSearch, &QLineEdit::textChanged, this, &ProductsPage::onSearch);

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

    QSqlQuery query;

    query.prepare(
        "SELECT "
        "p.product_id, "
        "p.product_name, "
        "b.brand_name, "
        "c.category_name, "
        "p.model, "
        "p.warranty_months, "
        "p.description "
        "FROM products p "
        "JOIN brands b ON p.brand_id = b.brand_id "
        "JOIN categories c ON p.category_id = c.category_id "
        "ORDER BY p.product_id"
    );

    if (!query.exec())
    {
        QMessageBox::critical(
            this,
            "Database Error",
            query.lastError().text()
        );

        return;
    }

    while (query.next())
    {
        const int row = ui->tblProducts->rowCount();

        ui->tblProducts->insertRow(row);

        ui->tblProducts->setItem(
            row,
            0,
            new QTableWidgetItem(
                QString::number(query.value("product_id").toInt())
            )
        );

        ui->tblProducts->setItem(
            row,
            1,
            new QTableWidgetItem(query.value("product_name").toString())
        );

        ui->tblProducts->setItem(
            row,
            2,
            new QTableWidgetItem(query.value("brand_name").toString())
        );

        ui->tblProducts->setItem(
            row,
            3,
            new QTableWidgetItem(query.value("category_name").toString())
        );

        ui->tblProducts->setItem(
            row,
            4,
            new QTableWidgetItem(query.value("model").toString())
        );

        ui->tblProducts->setItem(
            row,
            5,
            new QTableWidgetItem(
                QString::number(query.value("warranty_months").toInt()) + " months"
            )
        );

        ui->tblProducts->setItem(
            row,
            6,
            new QTableWidgetItem(query.value("description").toString())
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

        editButton->setIcon(awesome->icon(fa::fa_solid, fa::fa_pen));
        deleteButton->setIcon(awesome->icon(fa::fa_solid, fa::fa_trash));
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
            query.value("product_id").toInt()
        );

        deleteButton->setProperty(
            "productId",
            query.value("product_id").toInt()
        );

        editButton->setMinimumSize(60, 30);
        deleteButton->setMinimumSize(60, 30);

        editButton->setCursor(Qt::PointingHandCursor);
        deleteButton->setCursor(Qt::PointingHandCursor);

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
}

void ProductsPage::onAddProduct()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add Product");
    dialog.resize(450, 400);

    QFormLayout* layout = new QFormLayout(&dialog);

    QLineEdit* txtName = new QLineEdit();
    QComboBox* cbBrand = new QComboBox();
    QComboBox* cbCategory = new QComboBox();
    QLineEdit* txtModel = new QLineEdit();

    QSpinBox* spinWarranty = new QSpinBox();
    spinWarranty->setRange(0, 120);
    spinWarranty->setValue(12);

    QTextEdit* txtDescription = new QTextEdit();

    // Lấy Brand từ database
    QSqlQuery brandQuery;

    if (brandQuery.exec(
        "SELECT brand_id, brand_name "
        "FROM brands ORDER BY brand_name"))
    {
        while (brandQuery.next())
        {
            cbBrand->addItem(
                brandQuery.value("brand_name").toString(),
                brandQuery.value("brand_id")
            );
        }
    }

    // Lấy Category từ database
    QSqlQuery categoryQuery;

    if (categoryQuery.exec(
        "SELECT category_id, category_name "
        "FROM categories ORDER BY category_name"))
    {
        while (categoryQuery.next())
        {
            cbCategory->addItem(
                categoryQuery.value("category_name").toString(),
                categoryQuery.value("category_id")
            );
        }
    }

    layout->addRow("Product Name:", txtName);
    layout->addRow("Brand:", cbBrand);
    layout->addRow("Category:", cbCategory);
    layout->addRow("Model:", txtModel);
    layout->addRow("Warranty:", spinWarranty);
    layout->addRow("Description:", txtDescription);

    QDialogButtonBox* buttons =
        new QDialogButtonBox(
            QDialogButtonBox::Ok |
            QDialogButtonBox::Cancel
        );

    layout->addRow(buttons);

    connect(
        buttons,
        &QDialogButtonBox::accepted,
        &dialog,
        &QDialog::accept
    );

    connect(
        buttons,
        &QDialogButtonBox::rejected,
        &dialog,
        &QDialog::reject
    );

    // Người dùng bấm Cancel
    if (dialog.exec() != QDialog::Accepted)
        return;

    // Kiểm tra tên sản phẩm
    if (txtName->text().trimmed().isEmpty())
    {
        QMessageBox::warning(
            this,
            "Warning",
            "Product name cannot be empty."
        );

        return;
    }

    // Thêm vào database
    QSqlQuery query;

    query.prepare(
        "INSERT INTO products "
        "(category_id, brand_id, product_name, model, "
        "description, warranty_months) "
        "VALUES "
        "(:category, :brand, :name, :model, "
        ":description, :warranty)"
    );

    query.bindValue(
        ":category",
        cbCategory->currentData()
    );

    query.bindValue(
        ":brand",
        cbBrand->currentData()
    );

    query.bindValue(
        ":name",
        txtName->text().trimmed()
    );

    query.bindValue(
        ":model",
        txtModel->text().trimmed()
    );

    query.bindValue(
        ":description",
        txtDescription->toPlainText().trimmed()
    );

    query.bindValue(
        ":warranty",
        spinWarranty->value()
    );

    if (!query.exec())
    {
        QMessageBox::critical(
            this,
            "Database Error",
            query.lastError().text()
        );

        return;
    }

    QMessageBox::information(
        this,
        "Success",
        "Product added successfully."
    );

    loadProducts();
}

void ProductsPage::onEditProduct()
{
    auto* button = qobject_cast<QPushButton*>(sender());

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
    auto* button = qobject_cast<QPushButton*>(sender());

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
    ui->txtSearch->setText("");
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