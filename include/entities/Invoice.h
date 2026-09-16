//
// Created by Nam B on 9/15/2026.
//
#pragma once

#include <QDateTime>
#include <QString>
#include <vector>

#include "InvoiceDetail.h"
#include "FileExportable.h"
#ifndef PHONESTOREMANAGEMENT_INVOICE_H
#define PHONESTOREMANAGEMENT_INVOICE_H
class Invoice : public FileExportable
{
private:
    int invoiceId;
    int orderId;
    QDateTime invoiceDate;
    QString paymentMethod;
    QString paymentStatus;
    double totalAmount;

    std::vector<InvoiceDetail> details;

public:
    Invoice();

    Invoice(
        int invoiceId,
        int orderId,
        const QDateTime& invoiceDate,
        const QString& paymentMethod,
        const QString& paymentStatus
    );

    int getInvoiceId() const;
    int getOrderId() const;
    QDateTime getInvoiceDate() const;
    QString getPaymentMethod() const;
    QString getPaymentStatus() const;
    double getTotalAmount() const;

    std::vector<InvoiceDetail> getDetails() const;

    void setInvoiceId(int id);
    void setOrderId(int id);
    void setInvoiceDate(const QDateTime& date);
    void setPaymentMethod(const QString& method);
    void setPaymentStatus(const QString& status);

    void addDetail(const InvoiceDetail& detail);
    void removeDetail(int invoiceDetailId);
    void clearDetails();

    double calculateTotal() const;

    bool operator==(const Invoice& other) const;

    // Ghi de ham thuan ao cua FileExportable - sinh noi dung hoa don de xuat ra file
    QString toFileText() const override;
};
#endif //PHONESTOREMANAGEMENT_INVOICE_H
