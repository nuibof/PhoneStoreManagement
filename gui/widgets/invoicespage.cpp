#include "../UiStyle.h"
#include "InvoicesPage.h"
#include "ui_InvoicesPage.h"
#include "managers/InvoiceManager.h"

#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLocale>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>

namespace {
int senderId(QObject *sender) { return sender ? sender->property("invoiceId").toInt() : 0; }

bool editInvoice(QWidget *parent, Invoice &invoice, bool editing, QString &error) {
    QDialog dialog(parent); dialog.setWindowTitle(editing ? "Edit Invoice" : "Add Invoice");
    auto *layout = new QFormLayout(&dialog); auto *order = new QComboBox(&dialog);
    if (!editing) {
        QList<InvoiceOrderOption> orders;
        if (!InvoiceManager().getAvailableOrders(orders, error)) return false;
        for (const auto &item : orders)
            order->addItem(QString("%1 | %2").arg(item.name, QLocale().toCurrencyString(item.total, "VND")), item.id);
        layout->addRow("Order", order);
    }
    auto *method = new QComboBox(&dialog); method->addItems({"Cash", "Bank Transfer", "E-Wallet", "Card"});
    auto *status = new QComboBox(&dialog); status->addItems({"Pending", "Paid", "Cancelled"});
    method->setCurrentText(invoice.getPaymentMethod()); status->setCurrentText(invoice.getPaymentStatus());
    layout->addRow("Payment method", method); layout->addRow("Payment status", status);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    UiStyle::form(buttons, editing); layout->addRow(buttons);
    QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() != QDialog::Accepted) { error.clear(); return false; }
    if (!editing && order->currentIndex() < 0) { error = "There are no orders available for a new invoice."; return false; }
    if (!editing) invoice.setOrderId(order->currentData().toInt());
    invoice.setPaymentMethod(method->currentText()); invoice.setPaymentStatus(status->currentText()); return true;
}
}

InvoicesPage::InvoicesPage(QWidget *parent) : QWidget(parent), ui(new Ui::InvoicesPage) {
    ui->setupUi(this); UiStyle::page(this);
    ui->lblSubtitle->setText("Manage invoices and payment information.");
    setupTable(); loadInvoices();
    connect(ui->btnAdd, &QPushButton::clicked, this, &InvoicesPage::onAddInvoice);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &InvoicesPage::onRefresh);
    connect(ui->txtSearch, &QLineEdit::textChanged, this, &InvoicesPage::onSearch);
}
InvoicesPage::~InvoicesPage() { delete ui; }

void InvoicesPage::setupTable() {
    ui->tblInvoices->setColumnCount(7);
    ui->tblInvoices->setHorizontalHeaderLabels({"ID", "Order ID", "Invoice Date", "Payment Method", "Payment Status", "Total Amount", "Actions"});
    UiStyle::table(ui->tblInvoices, 6);
}

void InvoicesPage::loadInvoices() {
    ui->tblInvoices->setRowCount(0); QList<Invoice> invoices; QString error;
    if (!InvoiceManager().getInvoices(invoices, error)) { QMessageBox::critical(this, "Invoices", "Unable to load invoices.\n" + error); return; }
    for (const auto &invoice : invoices) {
        const int row = ui->tblInvoices->rowCount(); ui->tblInvoices->insertRow(row);
        ui->tblInvoices->setItem(row, 0, new QTableWidgetItem(QString::number(invoice.getInvoiceId())));
        ui->tblInvoices->setItem(row, 1, new QTableWidgetItem(QString::number(invoice.getOrderId())));
        ui->tblInvoices->setItem(row, 2, new QTableWidgetItem(invoice.getInvoiceDate().toString("dd/MM/yyyy HH:mm")));
        ui->tblInvoices->setItem(row, 3, new QTableWidgetItem(invoice.getPaymentMethod()));
        ui->tblInvoices->setItem(row, 4, new QTableWidgetItem(invoice.getPaymentStatus()));
        ui->tblInvoices->setItem(row, 5, new QTableWidgetItem(QLocale().toCurrencyString(invoice.getTotalAmount(), "VND")));
        auto *widget = new QWidget; auto *layout = new QHBoxLayout(widget);
        auto *edit = new QPushButton("Edit"); auto *remove = new QPushButton("Delete");
        edit->setProperty("invoiceId", invoice.getInvoiceId());
        edit->setProperty("orderId", invoice.getOrderId());
        edit->setProperty("method", invoice.getPaymentMethod());
        edit->setProperty("status", invoice.getPaymentStatus());
        remove->setProperty("invoiceId", invoice.getInvoiceId());
        connect(edit, &QPushButton::clicked, this, &InvoicesPage::onEditInvoice);
        connect(remove, &QPushButton::clicked, this, &InvoicesPage::onDeleteInvoice);
        layout->addWidget(edit); layout->addWidget(remove); UiStyle::actions(edit, remove, layout); ui->tblInvoices->setCellWidget(row, 6, widget);
    }
}

void InvoicesPage::onAddInvoice() {
    Invoice invoice; QString error;
    if (!editInvoice(this, invoice, false, error)) { if (!error.isEmpty()) QMessageBox::warning(this, "Add Invoice", error); return; }
    if (!InvoiceManager().addInvoice(invoice.getOrderId(), invoice.getPaymentMethod(), invoice.getPaymentStatus(), error)) {
        QMessageBox::critical(this, "Add Invoice", error); return;
    }
    QMessageBox::information(this, "Add Invoice", "Invoice added successfully."); loadInvoices();
}

void InvoicesPage::onEditInvoice() {
    auto *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;
    Invoice invoice;
    invoice.setInvoiceId(button->property("invoiceId").toInt());
    invoice.setOrderId(button->property("orderId").toInt());
    invoice.setPaymentMethod(button->property("method").toString());
    invoice.setPaymentStatus(button->property("status").toString());
    QString error; InvoiceManager manager;
    if (!editInvoice(this, invoice, true, error)) { if (!error.isEmpty()) QMessageBox::warning(this, "Edit Invoice", error); return; }
    if (!manager.updateInvoice(invoice, error)) { QMessageBox::critical(this, "Edit Invoice", error); return; }
    QMessageBox::information(this, "Edit Invoice", "Invoice updated successfully."); loadInvoices();
}

void InvoicesPage::onDeleteInvoice() {
    const int id = senderId(sender());
    if (QMessageBox::question(this, "Delete Invoice", "Delete this invoice?", QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) return;
    QString error; if (!InvoiceManager().deleteInvoice(id, error)) { QMessageBox::critical(this, "Delete Invoice", error); return; }
    QMessageBox::information(this, "Delete Invoice", "Invoice deleted successfully."); loadInvoices();
}
void InvoicesPage::onRefresh() { loadInvoices(); }
void InvoicesPage::onSearch() {
    const QString keyword = ui->txtSearch->text().trimmed().toLower();
    for (int row = 0; row < ui->tblInvoices->rowCount(); ++row) {
        bool match = keyword.isEmpty();
        for (int col = 0; !match && col < 6; ++col) { const auto *item = ui->tblInvoices->item(row, col); match = item && item->text().toLower().contains(keyword); }
        ui->tblInvoices->setRowHidden(row, !match);
    }
}
