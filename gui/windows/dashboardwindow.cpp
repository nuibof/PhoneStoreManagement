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

#include <iostream>
#include <ostream>

#include "loginwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QStyle>
#include <QDebug>

DashboardWindow::DashboardWindow(AuthManager *authManager, QWidget *parent) : QMainWindow(parent), ui(new Ui::DashboardWindow), authManager(authManager) {
    ui->setupUi(this);

    //Check position and hide buttons
    QString position = authManager->getCurrentPosition();
    std::cout << "Current position: " << position.toStdString() << std::endl;
    if (position == "Manager")
    {
        // hiện tất cả
    }
    else if (position == "Sales")
    {
        ui->btnStaff->hide();
    }
    else if (position == "Warehouse")
    {
        ui->btnCustomers->hide();
        ui->btnStaff->hide();
        ui->btnInvoices->hide();
        ui->btnOrders->hide();
    }

    // Add Staff Page
    StaffPage *staffPage = new StaffPage(authManager);
    int staffIndex =
        ui->stackedWidget->addWidget(staffPage);

    // Add Products Page
    ProductsPage *productsPage =
    new ProductsPage(
        authManager->getCurrentPosition()
    );
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

    auto setActiveButton = [this](QPushButton *activeButton)
    {
        QList<QPushButton *> buttons = {
            ui->btnProducts,
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

    // Products
    setActiveButton(ui->btnProducts);
    connect(ui->btnProducts, &QPushButton::clicked,
        this, [this, setActiveButton, productsIndex]()
{
    ui->stackedWidget->setCurrentIndex(productsIndex);
    setActiveButton(ui->btnProducts);
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