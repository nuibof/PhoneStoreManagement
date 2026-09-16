//
// Created by Nam B on 9/15/2026.
//
#include "entities/Invoice.h"

#include <QTextStream>

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

std::vector<InvoiceDetail> Invoice::getDetails() const
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
    details.push_back(detail);
    totalAmount = calculateTotal();
}

void Invoice::removeDetail(int invoiceDetailId)
{
    for (auto it = details.begin(); it != details.end(); ++it)
    {
        if (it->getInvoiceDetailId() == invoiceDetailId)
        {
            details.erase(it);
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

QString Invoice::toFileText() const
{
    QString text;
    QTextStream stream(&text);

    stream << "===== HOA DON =====" << "\n";
    stream << "Ma hoa don: " << invoiceId << "\n";
    stream << "Ma don hang: " << orderId << "\n";
    stream << "Ngay lap: " << invoiceDate.toString("dd/MM/yyyy HH:mm:ss") << "\n";
    stream << "Phuong thuc thanh toan: " << paymentMethod << "\n";
    stream << "Trang thai: " << paymentStatus << "\n";
    stream << "--------------------------------" << "\n";

    for (const InvoiceDetail& detail : details)
    {
        stream << detail.getVariant().getSku()
               << " | SL: " << detail.getQuantity()
               << " | Don gia: " << detail.getUnitPrice()
               << " | Thanh tien: " << detail.getSubtotal()
               << "\n";
    }

    stream << "--------------------------------" << "\n";
    stream << "TONG CONG: " << totalAmount << "\n";

    return text;
}

void Invoice::setTotalAmount(double totalAmount)
{
    this->totalAmount = totalAmount;
}