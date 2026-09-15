//
// Created by Nam B on 9/9/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWindow.h" resolved

#include "loginwindow.h"
#include "ui_LoginWindow.h"
#include "QPushButton"
#include "QMessageBox"
#include "dashboardwindow.h"
#include "managers/AuthManager.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    AuthManager AM;

    //click btnLogin ok open dashboard window
    connect(ui->btnLogin, &QPushButton::clicked, this, [this]() {
        onLogin();
    });

    //click Enter key on txtPassword or txtUsername ok open dashboard window
    connect(ui->txtUsername, &QLineEdit::returnPressed, this, [this]() {
        ui->btnLogin->click();
    });
    connect(ui->txtPassword, &QLineEdit::returnPressed, this, [this]() {
        ui->btnLogin->click();
    });
    //click btnExit show yes no popup
    connect(ui->btnExit, &QPushButton::clicked, this, [this]() {
        if (QMessageBox::question(this, "Exit", "Chắc chắn muốn thoát?") == QMessageBox::Yes) {
            QApplication::quit();
        }
    });
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::onLogin()
{
    QString username = ui->txtUsername->text();
    QString password = ui->txtPassword->text();

    if (authManager.login(username, password))
    {
        DashboardWindow *dashboard =
            new DashboardWindow(&authManager);

        dashboard->show();
        this->hide();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Login",
            "Invalid username or password."
        );
    }
}
