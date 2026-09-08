//
// Created by Nam B on 9/8/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWindow.h" resolved

#include "loginwindow.h"
#include "ui_LoginWindow.h"


LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);
}

LoginWindow::~LoginWindow() {
    delete ui;
}
