#ifndef PHONESTOREMANAGEMENT_STAFFPAGE_H
#define PHONESTOREMANAGEMENT_STAFFPAGE_H

#include <QWidget>

class AuthManager;

QT_BEGIN_NAMESPACE

namespace Ui {
    class StaffPage;
}

QT_END_NAMESPACE

class StaffPage : public QWidget {
    Q_OBJECT

public:
    explicit StaffPage(AuthManager *authManager,
                       QWidget *parent = nullptr);

    ~StaffPage() override;

public slots:
    void onAddStaff();
    void onEditStaff();
    void onDeleteStaff();
    void onRefresh();
    void onSearch();

private:
    Ui::StaffPage *ui;
    AuthManager *authManager;

    void setupTable();
    void loadStaff();
};

#endif