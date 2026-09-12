//
// Created by Nam B on 9/9/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWindow.h" resolved

#include "loginwindow.h"
#include "ui_LoginWindow.h"
#include "QPushButton"
#include "QMessageBox"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    //account for testing
    const QString testUsername = "test";
    const QString testPassword = "password";
    //click btnLogin ok show popup logged
    connect(ui->btnLogin, &QPushButton::clicked, this, [this, testUsername, testPassword]() {
        QString username = ui->txtUsername->text();
        QString password = ui->txtPassword->text();
        if (username == testUsername && password == testPassword) {
            QMessageBox::information(this, "Login", "Đăng nhập thành công!");
            // Open main window
            this->hide();
            // You can create and show your main window here
        } else {
            QMessageBox::warning(this, "Login", "Sai tài khoản hoặc mật khẩu!");
        }
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
