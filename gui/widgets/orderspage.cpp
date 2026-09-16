#include "../UiStyle.h"
#include "OrdersPage.h"
#include "ui_OrdersPage.h"
#include "managers/OrderManager.h"

#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLocale>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidgetItem>

namespace {
int senderId(QObject *sender) { return sender ? sender->property("orderId").toInt() : 0; }
void fillOptions(QComboBox *combo, const QList<OrderOption> &options) {
    for (const auto &option : options) combo->addItem(option.name, option.id);
}
void selectData(QComboBox *combo, int value) {
    const int index = combo->findData(value); if (index >= 0) combo->setCurrentIndex(index);
}
bool editHeader(QWidget *parent, Order &order, bool editing, int &variantId, int &quantity, QString &error) {
    OrderManager manager; QList<OrderOption> customers, employees;
    if (!manager.getCustomers(customers, error) || !manager.getEmployees(employees, error)) return false;
    QList<OrderVariantOption> variants;
    if (!editing && !manager.getVariants(variants, error)) return false;
    QDialog dialog(parent); dialog.setWindowTitle(editing ? "Edit Order" : "Add Order");
    auto *layout = new QFormLayout(&dialog); auto *customer = new QComboBox(&dialog);
    auto *employee = new QComboBox(&dialog); auto *status = new QComboBox(&dialog);
    status->addItems({"Pending", "Completed", "Cancelled"});
    fillOptions(customer, customers); fillOptions(employee, employees);
    selectData(customer, order.getCustomerId()); selectData(employee, order.getEmployeeId());
    status->setCurrentText(order.getStatus());
    layout->addRow("Customer", customer); layout->addRow("Employee", employee);
    if (!editing) {
        auto *variant = new QComboBox(&dialog);
        for (const auto &item : variants)
            variant->addItem(QString("%1 | %2 | Stock: %3").arg(item.name, QLocale().toCurrencyString(item.price)).arg(item.stock), item.id);
        auto *qty = new QSpinBox(&dialog); qty->setRange(1, 999);
        layout->addRow("Product variant", variant); layout->addRow("Quantity", qty);
        variantId = variant->currentData().toInt(); quantity = qty->value();
        QObject::connect(variant, &QComboBox::currentIndexChanged, &dialog, [variant, &variantId]{ variantId = variant->currentData().toInt(); });
        QObject::connect(qty, &QSpinBox::valueChanged, &dialog, [&quantity](int value){ quantity = value; });
    }
    layout->addRow("Status", status);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    UiStyle::form(buttons, editing); layout->addRow(buttons);
    QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() != QDialog::Accepted) { error.clear(); return false; }
    if (customer->currentIndex() < 0 || employee->currentIndex() < 0 || (!editing && variantId <= 0)) {
        error = "Customer, employee and product variant are required."; return false;
    }
    order.setCustomerId(customer->currentData().toInt()); order.setEmployeeId(employee->currentData().toInt());
    order.setStatus(status->currentText()); return true;
}
}

OrdersPage::OrdersPage(QWidget *parent) : QWidget(parent), ui(new Ui::OrdersPage) {
    ui->setupUi(this); UiStyle::page(this);
    ui->lblSubtitle->setText("Manage customer orders, stock and order status.");
    setupTable(); loadOrders();
    connect(ui->btnAdd, &QPushButton::clicked, this, &OrdersPage::onAdd);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &OrdersPage::onRefresh);
    connect(ui->txtSearch, &QLineEdit::textChanged, this, &OrdersPage::onSearch);
}
OrdersPage::~OrdersPage() { delete ui; }

void OrdersPage::setupTable() {
    ui->tblOrders->setColumnCount(7);
    ui->tblOrders->setHorizontalHeaderLabels({"ID", "Customer", "Employee", "Order Date", "Status", "Total Amount", "Actions"});
    UiStyle::table(ui->tblOrders, 6);
}

void OrdersPage::loadOrders() {
    ui->tblOrders->setRowCount(0); QList<OrderRow> orders; QString error;
    if (!OrderManager().getOrders(orders, error)) { QMessageBox::critical(this, "Orders", "Unable to load orders.\n" + error); return; }
    for (const auto &rowData : orders) {
        const Order &order = rowData.order; const int row = ui->tblOrders->rowCount(); ui->tblOrders->insertRow(row);
        ui->tblOrders->setItem(row, 0, new QTableWidgetItem(QString::number(order.getOrderId())));
        ui->tblOrders->setItem(row, 1, new QTableWidgetItem(rowData.customerName));
        ui->tblOrders->setItem(row, 2, new QTableWidgetItem(rowData.employeeName));
        ui->tblOrders->setItem(row, 3, new QTableWidgetItem(order.getOrderDate().toString("dd/MM/yyyy HH:mm")));
        ui->tblOrders->setItem(row, 4, new QTableWidgetItem(order.getStatus()));
        ui->tblOrders->setItem(row, 5, new QTableWidgetItem(QLocale().toCurrencyString(order.getTotalAmount(), "VND")));
        auto *widget = new QWidget; auto *layout = new QHBoxLayout(widget);
        auto *edit = new QPushButton("Edit"); auto *remove = new QPushButton("Delete");
        edit->setProperty("orderId", order.getOrderId());
        edit->setProperty("customerId", order.getCustomerId());
        edit->setProperty("employeeId", order.getEmployeeId());
        edit->setProperty("status", order.getStatus());
        remove->setProperty("orderId", order.getOrderId());
        connect(edit, &QPushButton::clicked, this, &OrdersPage::onEdit); connect(remove, &QPushButton::clicked, this, &OrdersPage::onDelete);
        layout->addWidget(edit); layout->addWidget(remove); UiStyle::actions(edit, remove, layout); ui->tblOrders->setCellWidget(row, 6, widget);
    }
}

void OrdersPage::onAdd() {
    Order order; int variantId = 0, quantity = 1; QString error;
    if (!editHeader(this, order, false, variantId, quantity, error)) { if (!error.isEmpty()) QMessageBox::warning(this, "Add Order", error); return; }
    if (!OrderManager().addOrder(order.getCustomerId(), order.getEmployeeId(), variantId, quantity, order.getStatus(), error)) {
        QMessageBox::critical(this, "Add Order", error); return;
    }
    QMessageBox::information(this, "Add Order", "Order added successfully."); loadOrders();
}

void OrdersPage::onEdit() {
    auto *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;
    Order order;
    order.setOrderId(button->property("orderId").toInt());
    order.setCustomerId(button->property("customerId").toInt());
    order.setEmployeeId(button->property("employeeId").toInt());
    order.setStatus(button->property("status").toString());
    QString error; OrderManager manager;
    int variant = 0, quantity = 1;
    if (!editHeader(this, order, true, variant, quantity, error)) { if (!error.isEmpty()) QMessageBox::warning(this, "Edit Order", error); return; }
    if (!manager.updateOrder(order, error)) { QMessageBox::critical(this, "Edit Order", error); return; }
    QMessageBox::information(this, "Edit Order", "Order updated successfully."); loadOrders();
}

void OrdersPage::onDelete() {
    const int id = senderId(sender());
    if (QMessageBox::question(this, "Delete Order", "Delete this order and return its items to stock?", QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) return;
    QString error; if (!OrderManager().deleteOrder(id, error)) { QMessageBox::critical(this, "Delete Order", error); return; }
    QMessageBox::information(this, "Delete Order", "Order deleted successfully."); loadOrders();
}
void OrdersPage::onRefresh() { loadOrders(); }
void OrdersPage::onSearch() {
    const QString keyword = ui->txtSearch->text().trimmed().toLower();
    for (int row = 0; row < ui->tblOrders->rowCount(); ++row) {
        bool match = keyword.isEmpty();
        for (int col = 0; !match && col < 6; ++col) { const auto *item = ui->tblOrders->item(row, col); match = item && item->text().toLower().contains(keyword); }
        ui->tblOrders->setRowHidden(row, !match);
    }
}
