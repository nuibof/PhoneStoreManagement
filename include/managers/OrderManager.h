#pragma once

#include "entities/Order.h"
#include <QList>

struct OrderOption {
    int id;
    QString name;
};

struct OrderVariantOption {
    int id;
    QString name;
    double price;
    int stock;
};

struct OrderRow {
    Order order;
    QString customerName;
    QString employeeName;
};

class OrderManager {
public:
    bool getOrders(QList<OrderRow> &orders, QString &error) const;
    bool getCustomers(QList<OrderOption> &options, QString &error) const;
    bool getEmployees(QList<OrderOption> &options, QString &error) const;
    bool getVariants(QList<OrderVariantOption> &options, QString &error) const;
    bool addOrder(int customerId, int employeeId, int variantId, int quantity,
                  const QString &status, QString &error) const;
    bool updateOrder(const Order &order, QString &error) const;
    bool deleteOrder(int id, QString &error) const;
};
