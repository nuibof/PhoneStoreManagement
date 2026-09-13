//
// Created by Nam B on 9/13/2026.
//

#ifndef PHONESTOREMANAGEMENT_ORDERSPAGE_H
#define PHONESTOREMANAGEMENT_ORDERSPAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class OrdersPage;
}

QT_END_NAMESPACE

class OrdersPage : public QWidget {
    Q_OBJECT

public:
    explicit OrdersPage(QWidget *parent = nullptr);

    ~OrdersPage() override;
public slots:
    void onAdd();
    void onEdit();
    void onDelete();
    void onSearch();
    void onRefresh();
private:
    Ui::OrdersPage *ui;
    void setupTable();
    void loadOrders();
};


#endif //PHONESTOREMANAGEMENT_ORDERSPAGE_H
