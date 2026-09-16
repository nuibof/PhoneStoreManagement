//
// Created by Nam B on 9/15/2026.
//
#include "../include/entities/OrderDetail.h"

OrderDetail::OrderDetail()
    : orderDetailId(0),
      quantity(0),
      unitPrice(0)
{
}

OrderDetail::OrderDetail(
    int orderDetailId,
    const ProductVariant& variant,
    int quantity,
    double unitPrice
)
    : orderDetailId(orderDetailId),
      variant(variant),
      quantity(quantity),
      unitPrice(unitPrice)
{
}

int OrderDetail::getOrderDetailId() const
{
    return orderDetailId;
}

ProductVariant OrderDetail::getVariant() const
{
    return variant;
}

int OrderDetail::getQuantity() const
{
    return quantity;
}

double OrderDetail::getUnitPrice() const
{
    return unitPrice;
}

void OrderDetail::setOrderDetailId(int id)
{
    orderDetailId = id;
}

void OrderDetail::setVariant(const ProductVariant& variant)
{
    this->variant = variant;
}

void OrderDetail::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void OrderDetail::setUnitPrice(double price)
{
    unitPrice = price;
}

double OrderDetail::getSubtotal() const
{
    return quantity * unitPrice;
}