#include "../UiStyle.h"
#include "OrdersPage.h"
#include "ui_OrdersPage.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QTableWidgetItem>

OrdersPage::OrdersPage(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OrdersPage)
{
    ui->setupUi(this);
    UiStyle::page(this);
    ui->lblSubtitle->setText("Sample data — this page is a preview. Changes are not saved.");

    setupTable();
    loadOrders();

    connect(ui->btnAdd, &QPushButton::clicked,
            this, &OrdersPage::onAdd);

    connect(ui->btnRefresh, &QPushButton::clicked,
            this, &OrdersPage::onRefresh);

    connect(ui->txtSearch, &QLineEdit::textChanged,
            this, &OrdersPage::onSearch);
}

OrdersPage::~OrdersPage()
{
    delete ui;
}

void OrdersPage::setupTable()
{
    ui->tblOrders->setColumnCount(7);

    QStringList headers = {
        "ID",
        "Customer",
        "Employee",
        "Order Date",
        "Status",
        "Total Amount",
        "Actions"
    };

    ui->tblOrders->setHorizontalHeaderLabels(headers);

    ui->tblOrders->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblOrders->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblOrders->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tblOrders->setAlternatingRowColors(true);
    ui->tblOrders->setShowGrid(false);

    ui->tblOrders->verticalHeader()->setVisible(false);
    ui->tblOrders->verticalHeader()->setDefaultSectionSize(45);

    ui->tblOrders->horizontalHeader()->setStretchLastSection(true);

    ui->tblOrders->setColumnWidth(0, 60);
    ui->tblOrders->setColumnWidth(1, 180);
    ui->tblOrders->setColumnWidth(2, 160);
    ui->tblOrders->setColumnWidth(3, 120);
    ui->tblOrders->setColumnWidth(4, 110);
    ui->tblOrders->setColumnWidth(5, 130);
    ui->tblOrders->setColumnWidth(6, 150);
    UiStyle::table(ui->tblOrders, 6);
}

void OrdersPage::loadOrders()
{
    ui->tblOrders->setRowCount(0);

    struct OrderData
    {
        int id;
        QString customer;
        QString employee;
        QString orderDate;
        QString status;
        QString totalAmount;
    };

    QList<OrderData> orders = {
        {1, "Nguyen Van An", "Tran Thi Binh",
         "2026-09-01", "Completed", "24,990,000 VND"},

        {2, "Le Van Cuong", "Pham Thi Dung",
         "2026-09-03", "Pending", "18,490,000 VND"},

        {3, "Pham Thi Dung", "Hoang Van Em",
         "2026-09-05", "Completed", "32,980,000 VND"},

        {4, "Hoang Van Em", "Tran Thi Binh",
         "2026-09-07", "Cancelled", "15,990,000 VND"},

        {5, "Tran Minh Khoa", "Pham Thi Dung",
         "2026-09-08", "Pending", "21,490,000 VND"}
    };

    for (const auto &order : orders)
    {
        int row = ui->tblOrders->rowCount();
        ui->tblOrders->insertRow(row);

        ui->tblOrders->setItem(
            row, 0,
            new QTableWidgetItem(QString::number(order.id)));

        ui->tblOrders->setItem(
            row, 1,
            new QTableWidgetItem(order.customer));

        ui->tblOrders->setItem(
            row, 2,
            new QTableWidgetItem(order.employee));

        ui->tblOrders->setItem(
            row, 3,
            new QTableWidgetItem(order.orderDate));

        ui->tblOrders->setItem(
            row, 4,
            new QTableWidgetItem(order.status));

        ui->tblOrders->setItem(
            row, 5,
            new QTableWidgetItem(order.totalAmount));

        // Actions
        QWidget *actionWidget = new QWidget();
        QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);

        actionLayout->setContentsMargins(5, 0, 5, 0);
        actionLayout->setSpacing(6);

        QPushButton *btnEdit = new QPushButton("Edit");
        QPushButton *btnDelete = new QPushButton("Delete");

        btnEdit->setProperty("orderId", order.id);
        btnDelete->setProperty("orderId", order.id);

        btnEdit->setFixedHeight(30);
        btnDelete->setFixedHeight(30);

        connect(btnEdit, &QPushButton::clicked,
                this, &OrdersPage::onEdit);

        connect(btnDelete, &QPushButton::clicked,
                this, &OrdersPage::onDelete);

        actionLayout->addWidget(btnEdit);
        actionLayout->addWidget(btnDelete);
        UiStyle::actions(btnEdit, btnDelete, actionLayout);


        ui->tblOrders->setCellWidget(row, 6, actionWidget);
    }
    onSearch();
}

void OrdersPage::onAdd()
{
    QMessageBox::information(
        this,
        "Add Order",
        "Add Order functionality is not implemented yet."
    );
}

void OrdersPage::onEdit()
{
    QMessageBox::information(this, "Order", "This page shows sample data. Editing and deletion are not available yet.");
}

void OrdersPage::onDelete()
{
    QMessageBox::information(this, "Order", "This page shows sample data. Editing and deletion are not available yet.");
}

void OrdersPage::onRefresh()
{
    loadOrders();
}

void OrdersPage::onSearch()
{
    QString keyword =
        ui->txtSearch->text().trimmed().toLower();

    for (int row = 0; row < ui->tblOrders->rowCount(); ++row)
    {
        bool match = false;

        for (int col = 0; col < 6; ++col)
        {
            QTableWidgetItem *item =
                ui->tblOrders->item(row, col);

            if (item &&
                item->text().toLower().contains(keyword))
            {
                match = true;
                break;
            }
        }

        ui->tblOrders->setRowHidden(row, !match);
    }
}