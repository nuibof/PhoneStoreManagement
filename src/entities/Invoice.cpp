//
// Created by Nam B on 9/15/2026.
//
#include "entities/Invoice.h"

Invoice::Invoice()
    : invoiceId(0),
      orderId(0),
      invoiceDate(QDateTime::currentDateTime()),
      paymentMethod("Cash"),
      paymentStatus("Paid"),
      totalAmount(0)
{
}

Invoice::Invoice(
    int invoiceId,
    int orderId,
    const QDateTime& invoiceDate,
    const QString& paymentMethod,
    const QString& paymentStatus
)
    : invoiceId(invoiceId),
      orderId(orderId),
      invoiceDate(invoiceDate),
      paymentMethod(paymentMethod),
      paymentStatus(paymentStatus),
      totalAmount(0)
{
}

int Invoice::getInvoiceId() const
{
    return invoiceId;
}

int Invoice::getOrderId() const
{
    return orderId;
}

QDateTime Invoice::getInvoiceDate() const
{
    return invoiceDate;
}

QString Invoice::getPaymentMethod() const
{
    return paymentMethod;
}

QString Invoice::getPaymentStatus() const
{
    return paymentStatus;
}

double Invoice::getTotalAmount() const
{
    return totalAmount;
}

void Invoice::setInvoiceId(int id)
{
    invoiceId = id;
}

void Invoice::setOrderId(int id)
{
    orderId = id;
}

void Invoice::setInvoiceDate(const QDateTime& date)
{
    invoiceDate = date;
}

void Invoice::setPaymentMethod(const QString& method)
{
    paymentMethod = method;
}

void Invoice::setPaymentStatus(const QString& status)
{
    paymentStatus = status;
}

bool Invoice::operator==(const Invoice& other) const
{
    return invoiceId == other.invoiceId;
}

void Invoice::setTotalAmount(double amount)
{
    totalAmount = amount;
}
