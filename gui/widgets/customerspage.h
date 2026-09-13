//
// Created by Nam B on 9/13/2026.
//

#ifndef PHONESTOREMANAGEMENT_CUSTOMERSPAGE_H
#define PHONESTOREMANAGEMENT_CUSTOMERSPAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class CustomersPage;
}

QT_END_NAMESPACE

class CustomersPage : public QWidget {
    Q_OBJECT

public:
    explicit CustomersPage(QWidget *parent = nullptr);

    ~CustomersPage() override;
private slots:
    void onAddCustomer();
    void onEditCustomer();
    void onDeleteCustomer();
    void onRefresh();
    void onSearch();
private:
    Ui::CustomersPage *ui;
    void setupTable();
    void loadCustomers();
};


#endif //PHONESTOREMANAGEMENT_CUSTOMERSPAGE_H
