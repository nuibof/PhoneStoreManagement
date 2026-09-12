//
// Created by Nam B on 9/9/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWindow.h" resolved

#include "loginwindow.h"
#include "ui_LoginWindow.h"
#include "QPushButton"
#include "QMessageBox"
#include "dashboardwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    //account for testing
    const QString testUsername = "test";
    const QString testPassword = "password";
    //add test user for txtUsername and txtPassword
    ui->txtUsername->setText(testUsername);
    ui->txtPassword->setText(testPassword);
    //click btnLogin ok open dashboard window
    connect(ui->btnLogin, &QPushButton::clicked, this, [this, testUsername, testPassword]() {
        QString username = ui->txtUsername->text();
        QString password = ui->txtPassword->text();
        if (username == testUsername && password == testPassword) {
            //open dashboard window
            auto *dashboardWindow = new DashboardWindow();
            dashboardWindow->show();
            this->close();
        } else {
            QMessageBox::warning(this, "Login Failed", "Sai tên đăng nhập hoặc mật khẩu.");
        }
    });
    //click Enter key on txtPassword or txtUsername ok open dashboard window
    connect(ui->txtPassword, &QLineEdit::returnPressed, this, [this, testUsername, testPassword]() {
        ui->btnLogin->click();
    });
    connect(ui->txtUsername, &QLineEdit::returnPressed, this, [this, testUsername, testPassword]() {
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
