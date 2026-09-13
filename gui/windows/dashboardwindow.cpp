//
// Created by Nam B on 9/12/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DashboardWindow.h" resolved

#include "../../include/managers/DashboardManager.h"
#include "../widgets/customerspage.h"
#include "../widgets/productspage.h"
#include "../widgets/invoicespage.h"
#include "../widgets/orderspage.h"
#include "../widgets/staffpage.h"
#include "ui_DashboardWindow.h"
#include "dashboardwindow.h"
#include "loginwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QStyle>
#include <QDebug>

DashboardWindow::DashboardWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::DashboardWindow) {
    ui->setupUi(this);

    // Add Staff Page
    StaffPage *staffPage = new StaffPage();
    int staffIndex =
        ui->stackedWidget->addWidget(staffPage);

    // Add Products Page
    ProductsPage *productsPage = new ProductsPage();
    int productsIndex =
        ui->stackedWidget->addWidget(productsPage);

    // Add Customers Page
    CustomersPage *customersPage = new CustomersPage();
    int customersIndex =
        ui->stackedWidget->addWidget(customersPage);

    // Add Orders Page
    OrdersPage *ordersPage = new OrdersPage();
    int ordersIndex =
        ui->stackedWidget->addWidget(ordersPage);

    // Add Invoices Page
    InvoicesPage *invoicesPage = new InvoicesPage();
    int invoicesIndex =
        ui->stackedWidget->addWidget(invoicesPage);

    // Make Dashboard the default page
    ui->stackedWidget->setCurrentWidget(ui->dashboardPage);

    // Load dashboard data
    loadDashboardData();

    auto setActiveButton = [this](QPushButton *activeButton)
    {
        QList<QPushButton *> buttons = {
            ui->btnDashboard,
            ui->btnProducts,
            ui->btnCategories,
            ui->btnCustomers,
            ui->btnStaff,
            ui->btnOrders,
            ui->btnInvoices
        };

        for (QPushButton *button : buttons)
        {
            button->setProperty("active", button == activeButton);
            button->style()->unpolish(button);
            button->style()->polish(button);
        }
    };
    // Dashboard (default) active button
    setActiveButton(ui->btnDashboard);
    connect(ui->btnDashboard, &QPushButton::clicked, this, [this, setActiveButton]()
    {
        ui->stackedWidget->setCurrentWidget(ui->dashboardPage);
        setActiveButton(ui->btnDashboard);
    });

    // Products
    connect(ui->btnProducts, &QPushButton::clicked,
        this, [this, setActiveButton, productsIndex]()
{
    ui->stackedWidget->setCurrentIndex(productsIndex);
    setActiveButton(ui->btnProducts);
});

    // Categories
    connect(ui->btnCategories, &QPushButton::clicked, this, [this, setActiveButton]()
    {
        ui->stackedWidget->setCurrentWidget(ui->categoriesPage);
        setActiveButton(ui->btnCategories);
    });

    // Customers
    connect(ui->btnCustomers, &QPushButton::clicked, this, [this, setActiveButton, customersIndex]()
    {
        ui->stackedWidget->setCurrentIndex(customersIndex);
        setActiveButton(ui->btnCustomers);
    });

    // Staff
    connect(ui->btnStaff, &QPushButton::clicked, this, [this, setActiveButton, staffIndex]()
    {
        ui->stackedWidget->setCurrentIndex(staffIndex);
        setActiveButton(ui->btnStaff);
    });

    // Orders
    connect(ui->btnOrders, &QPushButton::clicked, this, [this, setActiveButton, ordersIndex]()
    {
        ui->stackedWidget->setCurrentIndex(ordersIndex);
        setActiveButton(ui->btnOrders);
    });

    // Invoices
    connect(ui->btnInvoices, &QPushButton::clicked, this, [this, setActiveButton, invoicesIndex]()
    {
        ui->stackedWidget->setCurrentIndex(invoicesIndex);
        setActiveButton(ui->btnInvoices);
    });

    //click btnLogout show yes/no ok back to login window
    connect(ui->btnLogout, &QPushButton::clicked, this, [this]()
{
    QMessageBox::StandardButton reply =
        QMessageBox::question(
            this,
            "Logout",
            "Chắc chắn muốn đăng xuất?",
            QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes)
    {
        auto *loginWindow = new LoginWindow();
        loginWindow->show();
        close();
    }
});
}

DashboardWindow::~DashboardWindow() {
    delete ui;
}

void DashboardWindow::loadDashboardData()
{
    qDebug() << "=== Loading Dashboard Data ===";

    DashboardManager manager;

    int productCount = manager.getProductCount();
    int orderCount = manager.getOrderCount();
    int customerCount = manager.getCustomerCount();

    qDebug() << "Products:" << productCount;
    qDebug() << "Orders:" << orderCount;
    qDebug() << "Customers:" << customerCount;

    ui->productsValue->setText(QString::number(productCount));
    ui->ordersValue->setText(QString::number(orderCount));
    ui->customersValue->setText(QString::number(customerCount));
}