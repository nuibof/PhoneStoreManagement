//
// Created by Nam B on 9/9/2026.
//

#ifndef PHONESTOREMANAGEMENT_LOGINWINDOW_H
#define PHONESTOREMANAGEMENT_LOGINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE

namespace Ui {
    class LoginWindow;
}

QT_END_NAMESPACE

class LoginWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

    ~LoginWindow() override;

private:
    Ui::LoginWindow *ui;
};


#endif //PHONESTOREMANAGEMENT_LOGINWINDOW_H
