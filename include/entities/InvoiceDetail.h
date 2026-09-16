//
// Created by Nam B on 9/15/2026.
//
#pragma once

#ifndef PHONESTOREMANAGEMENT_INVOICEDETAIL_H
#define PHONESTOREMANAGEMENT_INVOICEDETAIL_H
#include "ProductVariant.h"

class InvoiceDetail
{
private:
    int invoiceDetailId;
    ProductVariant variant;
    int quantity;
    double unitPrice;

public:
    InvoiceDetail();

    InvoiceDetail(
        int invoiceDetailId,
        const ProductVariant& variant,
        int quantity,
        double unitPrice
    );

    int getInvoiceDetailId() const;
    ProductVariant getVariant() const;
    int getQuantity() const;
    double getUnitPrice() const;

    void setInvoiceDetailId(int id);
    void setVariant(const ProductVariant& variant);
    void setQuantity(int quantity);
    void setUnitPrice(double price);

    double getSubtotal() const;
};
#endif //PHONESTOREMANAGEMENT_INVOICEDETAIL_H
