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
#include <QIcon>
#include "managers/CustomerManager.h"

#include <QDateTime>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>


CustomersPage::CustomersPage(QWidget *parent) : QWidget(parent), ui(new Ui::CustomersPage) {
    ui->setupUi(this);

    setupTable();

    connect(ui->btnAdd, &QPushButton::clicked, this, &CustomersPage::onAddCustomer);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &CustomersPage::onRefresh);
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

    ui->tblCustomers->setAlternatingRowColors(true);
    ui->tblCustomers->setShowGrid(false);

    ui->tblCustomers->verticalHeader()->setVisible(false);
    ui->tblCustomers->verticalHeader()->setDefaultSectionSize(45);

    auto *header = ui->tblCustomers->horizontalHeader();
    header->setStretchLastSection(false);
    header->setSectionResizeMode(QHeaderView::ResizeToContents);
    header->setResizeContentsPrecision(-1);
    header->setSectionResizeMode(6, QHeaderView::Fixed);
    ui->tblCustomers->setColumnWidth(6, 88);
    ui->tblCustomers->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tblCustomers->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
}

void CustomersPage::loadCustomers()
{
    ui->tblCustomers->setRowCount(0);

    CustomerManager manager;
    QList<Customer> customers;
    QString error;
    if (!manager.getCustomers(customers, error)) {
        QMessageBox::critical(this, "Database Error", error);
        return;
    }
    for (const Customer &customer : customers)
    {
        int row = ui->tblCustomers->rowCount();
        ui->tblCustomers->insertRow(row);

        // ID
        ui->tblCustomers->setItem(
            row,
            0,
            new QTableWidgetItem(
                QString::number(customer.getCustomerId())
            )
        );

        // Full Name
        ui->tblCustomers->setItem(
            row,
            1,
            new QTableWidgetItem(
                customer.getFullName()
            )
        );

        // Phone
        ui->tblCustomers->setItem(
            row,
            2,
            new QTableWidgetItem(
                customer.getPhone()
            )
        );

        // Email
        ui->tblCustomers->setItem(
            row,
            3,
            new QTableWidgetItem(
                customer.getEmail()
            )
        );

        // Address
        ui->tblCustomers->setItem(
            row,
            4,
            new QTableWidgetItem(
                customer.getAddress()
            )
        );

        // Created At
        ui->tblCustomers->setItem(
            row,
            5,
            new QTableWidgetItem(
                customer.getCreatedAt().toString("yyyy-MM-dd HH:mm:ss")
            )
        );

        // =========================
        // ACTION BUTTONS
        // =========================

        auto* btnEdit = new QPushButton();
        auto* btnDelete = new QPushButton();
        btnEdit->setToolTip("Edit");
        btnDelete->setToolTip("Delete");
        btnEdit->setAccessibleName("Edit");
        btnDelete->setAccessibleName("Delete");

        btnEdit->setIcon(QIcon(":/icons/edit.svg"));
        btnDelete->setIcon(QIcon(":/icons/delete.svg"));
        btnEdit->setIconSize(QSize(18, 18));
        btnDelete->setIconSize(QSize(18, 18));

        const QString actionStyle =
            "QPushButton { padding: 0px; color: #3478F6; "
            "background-color: #FFFFFF; border: 1px solid #D0D0D0; "
            "border-radius: 4px; text-align: center; }"
            "QPushButton:hover { background-color: #EAF1FF; }";
        btnEdit->setStyleSheet(actionStyle);
        btnDelete->setStyleSheet(actionStyle);

        // Let QSS from CustomersPage.ui control the appearance
        btnEdit->setProperty("action", "edit");
        btnDelete->setProperty("action", "delete");

        btnEdit->setProperty(
            "customerId",
            customer.getCustomerId()
        );

        btnDelete->setProperty(
            "customerId",
            customer.getCustomerId()
        );

        btnEdit->setFixedSize(30, 30);
        btnDelete->setFixedSize(30, 30);

        btnEdit->setCursor(Qt::PointingHandCursor);
        btnDelete->setCursor(Qt::PointingHandCursor);

        auto *actionWidget = new QWidget();
        actionWidget->setObjectName("actionWidget");

        auto *actionLayout =
            new QHBoxLayout(actionWidget);

        actionLayout->setContentsMargins(
            4, 2, 4, 2
        );

        actionLayout->setSpacing(6);
        actionLayout->setAlignment(Qt::AlignCenter);

        actionLayout->addWidget(btnEdit);
        actionLayout->addWidget(btnDelete);

        ui->tblCustomers->setCellWidget(
            row,
            6,
            actionWidget
        );
        actionWidget->ensurePolished();
        btnEdit->ensurePolished();
        btnDelete->ensurePolished();
        ui->tblCustomers->setRowHeight(row, 45);

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
    }
    onSearch();
}

void CustomersPage::onAddCustomer()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add Customer");
    dialog.resize(450, 250);
    auto *layout = new QFormLayout(&dialog);
    auto *txtName = new QLineEdit();
    auto *txtPhone = new QLineEdit();
    auto *txtEmail = new QLineEdit();
    auto *txtAddress = new QLineEdit();
    txtName->setMaxLength(150);
    txtPhone->setMaxLength(20);
    txtEmail->setMaxLength(150);
    layout->addRow("Full Name:", txtName);
    layout->addRow("Phone:", txtPhone);
    layout->addRow("Email:", txtEmail);
    layout->addRow("Address:", txtAddress);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addRow(buttons);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, [&]() {
        if (txtName->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dialog, "Customer", "Full name cannot be empty.");
            txtName->setFocus();
            return;
        }
        Customer customer;
        customer.setFullName(txtName->text());
        customer.setPhone(txtPhone->text());
        customer.setEmail(txtEmail->text());
        customer.setAddress(txtAddress->text());
        CustomerManager manager;
        QString error;
        if (!manager.addCustomer(customer, error)) {
            QMessageBox::critical(&dialog, "Customer", error);
            return;
        }
        dialog.accept();
    });
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Success", "Customer added successfully.");
        loadCustomers();
    }
}

void CustomersPage::onEditCustomer()
{
    auto *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;
    const int customerId = button->property("customerId").toInt();
    CustomerManager manager;
    Customer current;
    QString error;
    if (!manager.getCustomer(customerId, current, error)) {
        QMessageBox::warning(this, "Customer", error);
        loadCustomers();
        return;
    }
    QDialog dialog(this);
    dialog.setWindowTitle("Edit Customer");
    dialog.resize(450, 250);
    auto *layout = new QFormLayout(&dialog);
    auto *txtName = new QLineEdit();
    auto *txtPhone = new QLineEdit();
    auto *txtEmail = new QLineEdit();
    auto *txtAddress = new QLineEdit();
    txtName->setMaxLength(150);
    txtPhone->setMaxLength(20);
    txtEmail->setMaxLength(150);
    layout->addRow("Full Name:", txtName);
    layout->addRow("Phone:", txtPhone);
    layout->addRow("Email:", txtEmail);
    layout->addRow("Address:", txtAddress);
    txtName->setText(current.getFullName());
    txtPhone->setText(current.getPhone());
    txtEmail->setText(current.getEmail());
    txtAddress->setText(current.getAddress());

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addRow(buttons);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, [&]() {
        if (txtName->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dialog, "Customer", "Full name cannot be empty.");
            txtName->setFocus();
            return;
        }
        Customer customer;
        customer.setFullName(txtName->text());
        customer.setPhone(txtPhone->text());
        customer.setEmail(txtEmail->text());
        customer.setAddress(txtAddress->text());
        customer.setCustomerId(customerId);
        CustomerManager manager;
        QString error;
        if (!manager.updateCustomer(customer, error)) {
            QMessageBox::critical(&dialog, "Customer", error);
            return;
        }
        dialog.accept();
    });
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Success", "Customer updated successfully.");
        loadCustomers();
    }
}

void CustomersPage::onDeleteCustomer() {
    auto *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;
    const int customerId = button->property("customerId").toInt();
    if (QMessageBox::question(this, "Delete Customer",
            QString("Are you sure you want to delete customer ID %1?").arg(customerId),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes)
        return;

    CustomerManager manager;
    QString error;
    if (!manager.deleteCustomer(customerId, error)) {
        QMessageBox::warning(this, "Customer", error);
        return;
    }
    QMessageBox::information(this, "Success", "Customer deleted successfully.");
    loadCustomers();
}

void CustomersPage::onRefresh() {
    loadCustomers();
}

void CustomersPage::onSearch()
{
    QString searchTerm =
        ui->txtSearch->text().trimmed();

    for (int row = 0;
         row < ui->tblCustomers->rowCount();
         ++row)
    {
        bool match = false;

        // Search ID -> Created At
        // Do not search Actions
        for (int col = 0;
             col < 6;
             ++col)
        {
            QTableWidgetItem *item =
                ui->tblCustomers->item(row, col);

            if (item &&
                item->text().contains(
                    searchTerm,
                    Qt::CaseInsensitive))
            {
                match = true;
                break;
            }
        }

        ui->tblCustomers->setRowHidden(
            row,
            !match
        );
    }
}
