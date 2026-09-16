//
// Created by Nam B on 9/15/2026.
//
#pragma once

#include "ProductVariant.h"
#ifndef PHONESTOREMANAGEMENT_ORDERDETAIL_H
#define PHONESTOREMANAGEMENT_ORDERDETAIL_H
class OrderDetail
{
private:
    int orderDetailId;
    ProductVariant variant;
    int quantity;
    double unitPrice;

public:
    OrderDetail();

    OrderDetail(
        int orderDetailId,
        const ProductVariant& variant,
        int quantity,
        double unitPrice
    );

    int getOrderDetailId() const;
    ProductVariant getVariant() const;
    int getQuantity() const;
    double getUnitPrice() const;

    void setOrderDetailId(int id);
    void setVariant(const ProductVariant& variant);
    void setQuantity(int quantity);
    void setUnitPrice(double price);

    double getSubtotal() const;
};
#endif //PHONESTOREMANAGEMENT_ORDERDETAIL_H
