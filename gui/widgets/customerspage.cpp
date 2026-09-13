//
// Created by Nam B on 9/13/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CustomersPage.h" resolved

#include "customerspage.h"
#include "ui_CustomersPage.h"
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidgetItem>


CustomersPage::CustomersPage(QWidget *parent) : QWidget(parent), ui(new Ui::CustomersPage) {
    ui->setupUi(this);

    setupTable();

    connect(ui->btnAdd, &QPushButton::clicked, this, &CustomersPage::onAddCustomer);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &CustomersPage ::onRefresh);
    connect(ui->txtSearch, &QLineEdit::textChanged, this, &CustomersPage::onSearch);

    loadCustomers();
}

CustomersPage::~CustomersPage() {
    delete ui;
}

void CustomersPage::setupTable()
{
    ui->tblCustomers->setColumnCount(7);

    QStringList headers = {
        "ID",
        "Full Name",
        "Phone",
        "Email",
        "Address",
        "Created At",
        "Actions"
    };

    ui->tblCustomers->setHorizontalHeaderLabels(headers);

    ui->tblCustomers->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );

    ui->tblCustomers->setSelectionMode(
        QAbstractItemView::SingleSelection
    );

    ui->tblCustomers->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );

    ui->tblCustomers->verticalHeader()->setVisible(false);

    ui->tblCustomers->horizontalHeader()->setStretchLastSection(true);
}

void CustomersPage::loadCustomers()
{
    ui->tblCustomers->setRowCount(0);

    struct CustomerData
    {
        int id;
        QString name;
        QString phone;
        QString email;
        QString address;
        QString createdAt;
    };

    const QList<CustomerData> customers = {
        {
            1,
            "John Doe",
            "123-456-7890",
            "john.doe@example.com",
            "123 Main St",
            "2023-01-01 10:00:00"
        },
        {
            2,
            "Jane Smith",
            "098-765-4321",
            "jane.smith@example.com",
            "456 Oak Ave",
            "2023-01-02 11:00:00"
        },
        {
            3,
            "Alice Johnson",
            "555-1234",
            "alice.johnson@example.com",
            "789 Pine Rd",
            "2023-01-03 12:00:00"
        },
        {
            4,
            "Bob Brown",
            "555-5678",
            "bob.brown@example.com",
            "321 Elm St",
            "2023-01-04 13:00:00"
        },
        {
            5,
            "Charlie Davis",
            "555-9012",
            "charlie.davis@example.com",
            "654 Cedar Ln",
            "2023-01-05 14:00:00"
        }
    };

    for (const auto &customer : customers)
    {
        int row = ui->tblCustomers->rowCount();
        ui->tblCustomers->insertRow(row);

        // ID
        ui->tblCustomers->setItem(
            row,
            0,
            new QTableWidgetItem(
                QString::number(customer.id)
            )
        );

        // Full Name
        ui->tblCustomers->setItem(
            row,
            1,
            new QTableWidgetItem(
                customer.name
            )
        );

        // Phone
        ui->tblCustomers->setItem(
            row,
            2,
            new QTableWidgetItem(
                customer.phone
            )
        );

        // Email
        ui->tblCustomers->setItem(
            row,
            3,
            new QTableWidgetItem(
                customer.email
            )
        );

        // Address
        ui->tblCustomers->setItem(
            row,
            4,
            new QTableWidgetItem(
                customer.address
            )
        );

        // Created At
        ui->tblCustomers->setItem(
            row,
            5,
            new QTableWidgetItem(
                customer.createdAt
            )
        );

        // Actions
        QWidget *actionWidget = new QWidget();

        QHBoxLayout *actionLayout =
            new QHBoxLayout(actionWidget);

        actionLayout->setContentsMargins(5, 3, 5, 3);
        actionLayout->setSpacing(6);

        QPushButton *btnEdit =
            new QPushButton("Edit");

        QPushButton *btnDelete =
            new QPushButton("Delete");

        btnEdit->setFixedSize(55, 30);
        btnDelete->setFixedSize(60, 30);

        btnEdit->setProperty(
            "customerId",
            customer.id
        );

        btnDelete->setProperty(
            "customerId",
            customer.id
        );

        connect(
            btnEdit,
            &QPushButton::clicked,
            this,
            &CustomersPage::onEditCustomer
        );

        connect(
            btnDelete,
            &QPushButton::clicked,
            this,
            &CustomersPage::onDeleteCustomer
        );

        actionLayout->addWidget(btnEdit);
        actionLayout->addWidget(btnDelete);

        ui->tblCustomers->setCellWidget(
            row,
            6,
            actionWidget
        );
    }
}

void CustomersPage::onAddCustomer()
{
    QMessageBox::information(
        this,
        "Add Customer",
        "Add customer functionality is not implemented yet."
    );
}

void CustomersPage::onEditCustomer()
{
    auto *button = qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int customerId = button->property("customerId").toInt();

    QMessageBox::information(
        this,
        "Edit Customer",
        QString("Edit customer ID: %1").arg(customerId)
    );
}

void CustomersPage::onDeleteCustomer() {
    auto *button = qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int customerId = button->property("customerId").toInt();

    QMessageBox::StandardButton reply =
        QMessageBox::question(
            this,
            "Delete Customer",
            QString("Are you sure you want to delete customer ID %1?").arg(customerId),
            QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(
            this,
            "Delete Customer",
            "Customer deleted successfully."
        );
    }
}

void CustomersPage::onRefresh() {
    loadCustomers();
}

void CustomersPage::onSearch() {
    QString searchTerm = ui->txtSearch->text().trimmed();

    if (searchTerm.isEmpty()) {
        loadCustomers();
        return;
    }

    for (int row = 0; row < ui->tblCustomers->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < ui->tblCustomers->columnCount() - 1; ++col) {
            QTableWidgetItem *item = ui->tblCustomers->item(row, col);
            if (item && item->text().contains(searchTerm, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tblCustomers->setRowHidden(row, !match);
    }
}