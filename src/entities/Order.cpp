//
// Created by Nam B on 9/15/2026.
//
#include "../include/entities/Order.h"

Order::Order()
    : orderId(0),
      customerId(0),
      employeeId(0),
      orderDate(QDateTime::currentDateTime()),
      status("Pending"),
      totalAmount(0)
{
}

Order::Order(
    int orderId,
    int customerId,
    int employeeId,
    const QDateTime& orderDate,
    const QString& status
)
    : orderId(orderId),
      customerId(customerId),
      employeeId(employeeId),
      orderDate(orderDate),
      status(status),
      totalAmount(0)
{
}

int Order::getOrderId() const
{
    return orderId;
}

int Order::getCustomerId() const
{
    return customerId;
}

int Order::getEmployeeId() const
{
    return employeeId;
}

QDateTime Order::getOrderDate() const
{
    return orderDate;
}

QString Order::getStatus() const
{
    return status;
}

double Order::getTotalAmount() const
{
    return totalAmount;
}

std::vector<OrderDetail> Order::getDetails() const
{
    return details;
}

void Order::setOrderId(int id)
{
    orderId = id;
}

void Order::setCustomerId(int id)
{
    customerId = id;
}

void Order::setEmployeeId(int id)
{
    employeeId = id;
}

void Order::setOrderDate(const QDateTime& date)
{
    orderDate = date;
}

void Order::setStatus(const QString& status)
{
    this->status = status;
}

void Order::addDetail(const OrderDetail& detail)
{
    details.push_back(detail);
    totalAmount = calculateTotal();
}

void Order::removeDetail(int orderDetailId)
{
    for (auto it = details.begin(); it != details.end(); ++it)
    {
        if (it->getOrderDetailId() == orderDetailId)
        {
            details.erase(it);
            break;
        }
    }

    totalAmount = calculateTotal();
}

void Order::clearDetails()
{
    details.clear();
    totalAmount = 0;
}

double Order::calculateTotal() const
{
    double total = 0;

    for (const OrderDetail& detail : details)
    {
        total += detail.getSubtotal();
    }

    return total;
}
//qttt
bool Order::operator==(const Order& other) const
{
    return orderId == other.orderId;
}