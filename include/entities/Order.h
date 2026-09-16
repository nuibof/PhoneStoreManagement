//
// Created by Nam B on 9/15/2026.
//
#pragma once

#include <QDateTime>
#ifndef PHONESTOREMANAGEMENT_ORDER_H
#define PHONESTOREMANAGEMENT_ORDER_H
class Order
{
private:
    int orderId;
    int customerId;
    int employeeId;
    QDateTime orderDate;
    QString status;
    double totalAmount;

public:
    Order();

    Order(
        int orderId,
        int customerId,
        int employeeId,
        const QDateTime& orderDate,
        const QString& status
    );

    int getOrderId() const;
    int getCustomerId() const;
    int getEmployeeId() const;
    QDateTime getOrderDate() const;
    QString getStatus() const;
    double getTotalAmount() const;

    void setOrderId(int id);
    void setCustomerId(int id);
    void setEmployeeId(int id);
    void setOrderDate(const QDateTime& date);
    void setStatus(const QString& status);
    void setTotalAmount(double amount);

    bool operator==(const Order& other) const;
};
#endif //PHONESTOREMANAGEMENT_ORDER_H
