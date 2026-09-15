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

QList<InvoiceDetail> Invoice::getDetails() const
{
    return details;
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

void Invoice::addDetail(const InvoiceDetail& detail)
{
    details.append(detail);
    totalAmount = calculateTotal();
}

void Invoice::removeDetail(int invoiceDetailId)
{
    for (int i = 0; i < details.size(); ++i)
    {
        if (details[i].getInvoiceDetailId() == invoiceDetailId)
        {
            details.removeAt(i);
            break;
        }
    }

    totalAmount = calculateTotal();
}

void Invoice::clearDetails()
{
    details.clear();
    totalAmount = 0;
}

double Invoice::calculateTotal() const
{
    double total = 0;

    for (const InvoiceDetail& detail : details)
    {
        total += detail.getSubtotal();
    }

    return total;
}

bool Invoice::operator==(const Invoice& other) const
{
    return invoiceId == other.invoiceId;
}