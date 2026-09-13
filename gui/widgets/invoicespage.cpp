#include "InvoicesPage.h"
#include "ui_InvoicesPage.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QTableWidgetItem>

InvoicesPage::InvoicesPage(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::InvoicesPage)
{
    ui->setupUi(this);

    setupTable();
    loadInvoices();

    connect(ui->btnAdd, &QPushButton::clicked,
            this, &InvoicesPage::onAddInvoice);

    connect(ui->btnRefresh, &QPushButton::clicked,
            this, &InvoicesPage::onRefresh);

    connect(ui->txtSearch, &QLineEdit::textChanged,
            this, &InvoicesPage::onSearch);
}

InvoicesPage::~InvoicesPage()
{
    delete ui;
}

void InvoicesPage::setupTable()
{
    ui->tblInvoices->setColumnCount(7);

    QStringList headers = {
        "ID",
        "Order ID",
        "Invoice Date",
        "Payment Method",
        "Payment Status",
        "Total Amount",
        "Actions"
    };

    ui->tblInvoices->setHorizontalHeaderLabels(headers);

    ui->tblInvoices->setSelectionBehavior(
        QAbstractItemView::SelectRows);

    ui->tblInvoices->setSelectionMode(
        QAbstractItemView::SingleSelection);

    ui->tblInvoices->setEditTriggers(
        QAbstractItemView::NoEditTriggers);

    ui->tblInvoices->setAlternatingRowColors(true);
    ui->tblInvoices->setShowGrid(false);

    ui->tblInvoices->verticalHeader()->setVisible(false);
    ui->tblInvoices->verticalHeader()->setDefaultSectionSize(45);

    ui->tblInvoices->horizontalHeader()->setStretchLastSection(true);

    ui->tblInvoices->setColumnWidth(0, 60);
    ui->tblInvoices->setColumnWidth(1, 90);
    ui->tblInvoices->setColumnWidth(2, 130);
    ui->tblInvoices->setColumnWidth(3, 140);
    ui->tblInvoices->setColumnWidth(4, 140);
    ui->tblInvoices->setColumnWidth(5, 150);
    ui->tblInvoices->setColumnWidth(6, 150);
}

void InvoicesPage::loadInvoices()
{
    ui->tblInvoices->setRowCount(0);

    struct InvoiceData
    {
        int id;
        int orderId;
        QString invoiceDate;
        QString paymentMethod;
        QString paymentStatus;
        QString totalAmount;
    };

    QList<InvoiceData> invoices = {
        {1, 1, "2026-09-01", "Cash",
         "Paid", "24,990,000 VND"},

        {2, 2, "2026-09-03", "Bank Transfer",
         "Paid", "18,490,000 VND"},

        {3, 3, "2026-09-05", "Cash",
         "Paid", "32,980,000 VND"},

        {4, 5, "2026-09-08", "E-Wallet",
         "Pending", "21,490,000 VND"}
    };

    for (const auto &invoice : invoices)
    {
        int row = ui->tblInvoices->rowCount();
        ui->tblInvoices->insertRow(row);

        ui->tblInvoices->setItem(
            row, 0,
            new QTableWidgetItem(
                QString::number(invoice.id)));

        ui->tblInvoices->setItem(
            row, 1,
            new QTableWidgetItem(
                QString::number(invoice.orderId)));

        ui->tblInvoices->setItem(
            row, 2,
            new QTableWidgetItem(
                invoice.invoiceDate));

        ui->tblInvoices->setItem(
            row, 3,
            new QTableWidgetItem(
                invoice.paymentMethod));

        ui->tblInvoices->setItem(
            row, 4,
            new QTableWidgetItem(
                invoice.paymentStatus));

        ui->tblInvoices->setItem(
            row, 5,
            new QTableWidgetItem(
                invoice.totalAmount));

        // Actions
        QWidget *actionWidget = new QWidget();
        QHBoxLayout *actionLayout =
            new QHBoxLayout(actionWidget);

        actionLayout->setContentsMargins(5, 0, 5, 0);
        actionLayout->setSpacing(6);

        QPushButton *btnEdit =
            new QPushButton("Edit");

        QPushButton *btnDelete =
            new QPushButton("Delete");

        btnEdit->setProperty(
            "invoiceId", invoice.id);

        btnDelete->setProperty(
            "invoiceId", invoice.id);

        btnEdit->setFixedHeight(30);
        btnDelete->setFixedHeight(30);

        btnEdit->setStyleSheet(
            "QPushButton {"
            "background-color: #EAF1FF;"
            "color: #3478F6;"
            "border: none;"
            "border-radius: 6px;"
            "padding: 4px 10px;"
            "}"
            "QPushButton:hover {"
            "background-color: #DCE8FF;"
            "}"
        );

        btnDelete->setStyleSheet(
            "QPushButton {"
            "background-color: #FFF1F1;"
            "color: #D93025;"
            "border: none;"
            "border-radius: 6px;"
            "padding: 4px 8px;"
            "}"
            "QPushButton:hover {"
            "background-color: #FFE0E0;"
            "}"
        );

        connect(btnEdit, &QPushButton::clicked,
                this, &InvoicesPage::onEditInvoice);

        connect(btnDelete, &QPushButton::clicked,
                this, &InvoicesPage::onDeleteInvoice);

        actionLayout->addWidget(btnEdit);
        actionLayout->addWidget(btnDelete);

        ui->tblInvoices->setCellWidget(
            row, 6, actionWidget);
    }
}

void InvoicesPage::onAddInvoice()
{
    QMessageBox::information(
        this,
        "Add Invoice",
        "Add Invoice functionality is not implemented yet."
    );
}

void InvoicesPage::onEditInvoice()
{
    QPushButton *button =
        qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int invoiceId =
        button->property("invoiceId").toInt();

    QMessageBox::information(
        this,
        "Edit Invoice",
        QString("Edit invoice ID: %1")
            .arg(invoiceId)
    );
}

void InvoicesPage::onDeleteInvoice()
{
    QPushButton *button =
        qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    int invoiceId =
        button->property("invoiceId").toInt();

    QMessageBox::StandardButton reply =
        QMessageBox::question(
            this,
            "Delete Invoice",
            QString(
                "Are you sure you want to delete invoice ID %1?"
            ).arg(invoiceId),
            QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(
            this,
            "Delete Invoice",
            QString(
                "Invoice ID %1 deleted successfully."
            ).arg(invoiceId)
        );
    }
}

void InvoicesPage::onRefresh()
{
    loadInvoices();

    QMessageBox::information(
        this,
        "Refresh",
        "Invoice list refreshed."
    );
}

void InvoicesPage::onSearch()
{
    QString keyword =
        ui->txtSearch->text()
            .trimmed()
            .toLower();

    for (int row = 0;
         row < ui->tblInvoices->rowCount();
         ++row)
    {
        bool match = false;

        for (int col = 0; col < 6; ++col)
        {
            QTableWidgetItem *item =
                ui->tblInvoices->item(row, col);

            if (item &&
                item->text()
                    .toLower()
                    .contains(keyword))
            {
                match = true;
                break;
            }
        }

        ui->tblInvoices->setRowHidden(
            row, !match);
    }
}