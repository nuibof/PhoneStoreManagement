//
// Created by Nam B on 9/12/2026.
//

#ifndef PHONESTOREMANAGEMENT_DASHBOARDWINDOW_H
#define PHONESTOREMANAGEMENT_DASHBOARDWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE

#include <QMainWindow>

class AuthManager;

QT_BEGIN_NAMESPACE

namespace Ui {
    class DashboardWindow;
}

QT_END_NAMESPACE

class DashboardWindow : public QMainWindow {
    Q_OBJECT

QT_END_NAMESPACE
public:
    explicit DashboardWindow(AuthManager *authManager,
                             QWidget *parent = nullptr);

    ~DashboardWindow() override;

private:
    Ui::DashboardWindow *ui;
    AuthManager *authManager;

    void loadDashboardData();
};

#endif
