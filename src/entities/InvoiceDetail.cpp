//
// Created by Nam B on 9/15/2026.
//
#include "entities/InvoiceDetail.h"

InvoiceDetail::InvoiceDetail()
    : invoiceDetailId(0),
      quantity(0),
      unitPrice(0)
{
}

InvoiceDetail::InvoiceDetail(
    int invoiceDetailId,
    const ProductVariant& variant,
    int quantity,
    double unitPrice
)
    : invoiceDetailId(invoiceDetailId),
      variant(variant),
      quantity(quantity),
      unitPrice(unitPrice)
{
}

int InvoiceDetail::getInvoiceDetailId() const
{
    return invoiceDetailId;
}

ProductVariant InvoiceDetail::getVariant() const
{
    return variant;
}

int InvoiceDetail::getQuantity() const
{
    return quantity;
}

double InvoiceDetail::getUnitPrice() const
{
    return unitPrice;
}

void InvoiceDetail::setInvoiceDetailId(int id)
{
    invoiceDetailId = id;
}

void InvoiceDetail::setVariant(const ProductVariant& variant)
{
    this->variant = variant;
}

void InvoiceDetail::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void InvoiceDetail::setUnitPrice(double price)
{
    unitPrice = price;
}

double InvoiceDetail::getSubtotal() const
{
    return quantity * unitPrice;
}