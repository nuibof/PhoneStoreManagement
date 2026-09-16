//
// Created by Nam B on 9/15/2026.
//

#include "OrderInvoiceTest.h"

#include "entities/ProductVariant.h"
#include "entities/OrderDetail.h"
#include "entities/Order.h"
#include "entities/InvoiceDetail.h"
#include "entities/Invoice.h"

#include <QDebug>
#include <QDateTime>

void OrderInvoiceTest::run()
{
    qDebug() << "========================================";
    qDebug() << "       ORDER & INVOICE LOGIC TEST";
    qDebug() << "========================================";


    // =====================================================
    // 1. CREATE PRODUCT VARIANTS FOR TEST
    // =====================================================

    qDebug() << "\n[1] Testing ProductVariant data";

    ProductVariant variant1(
        1,              // variantId
        1,              // productId
        1,              // colorId
        1,              // storageId
        1,              // ramId
        "IP15-BLK-128",
        18000000,       // cost
        22000000,       // selling
        10              // stock
    );

    ProductVariant variant2(
        2,
        2,
        2,
        2,
        1,
        "SSS24-BLU-256",
        20000000,
        25000000,
        8
    );

    qDebug() << "Variant 1 SKU:" << variant1.getSku();
    qDebug() << "Variant 1 selling price:" << variant1.getSellingPrice();

    qDebug() << "Variant 2 SKU:" << variant2.getSku();
    qDebug() << "Variant 2 selling price:" << variant2.getSellingPrice();


    // =====================================================
    // 2. ORDER DETAIL
    // =====================================================

    qDebug() << "\n[2] Testing OrderDetail";

    OrderDetail orderDetail1(
        1,
        variant1,
        2,
        22000000
    );

    OrderDetail orderDetail2(
        2,
        variant2,
        1,
        25000000
    );

    qDebug() << "OrderDetail 1 subtotal:"
             << orderDetail1.getSubtotal();

    qDebug() << "OrderDetail 2 subtotal:"
             << orderDetail2.getSubtotal();


    // =====================================================
    // 3. ORDER
    // =====================================================

    qDebug() << "\n[3] Testing Order";

    Order order(
        1,
        1,                          // customerId
        1,                          // employeeId
        QDateTime::currentDateTime(),
        "Pending"
    );

    qDebug() << "Order ID:" << order.getOrderId();
    qDebug() << "Customer ID:" << order.getCustomerId();
    qDebug() << "Employee ID:" << order.getEmployeeId();
    qDebug() << "Status:" << order.getStatus();

    // Add detail
    order.addDetail(orderDetail1);
    order.addDetail(orderDetail2);

    qDebug() << "Number of order details:"
             << order.getDetails().size();

    qDebug() << "Order total:"
             << order.calculateTotal();

    qDebug() << "Stored total:"
             << order.getTotalAmount();


    // =====================================================
    // 4. ORDER REMOVE DETAIL
    // =====================================================

    qDebug() << "\n[4] Testing Order removeDetail";

    order.removeDetail(1);

    qDebug() << "Number of order details after remove:"
             << order.getDetails().size();

    qDebug() << "Order total after remove:"
             << order.calculateTotal();


    // =====================================================
    // 5. ORDER CLEAR DETAILS
    // =====================================================

    qDebug() << "\n[5] Testing Order clearDetails";

    order.clearDetails();

    qDebug() << "Number of order details after clear:"
             << order.getDetails().size();

    qDebug() << "Order total after clear:"
             << order.calculateTotal();


    // =====================================================
    // 6. ORDER OPERATOR ==
    // =====================================================

    qDebug() << "\n[6] Testing Order operator==";

    Order orderA(
        100,
        1,
        1,
        QDateTime::currentDateTime(),
        "Pending"
    );

    Order orderB(
        100,
        2,
        2,
        QDateTime::currentDateTime(),
        "Completed"
    );

    Order orderC(
        200,
        1,
        1,
        QDateTime::currentDateTime(),
        "Pending"
    );

    qDebug() << "orderA == orderB:"
             << (orderA == orderB);

    qDebug() << "orderA == orderC:"
             << (orderA == orderC);


    // =====================================================
    // 7. INVOICE DETAIL
    // =====================================================

    qDebug() << "\n[7] Testing InvoiceDetail";

    InvoiceDetail invoiceDetail1(
        1,
        variant1,
        2,
        22000000
    );

    InvoiceDetail invoiceDetail2(
        2,
        variant2,
        1,
        25000000
    );

    qDebug() << "InvoiceDetail 1 subtotal:"
             << invoiceDetail1.getSubtotal();

    qDebug() << "InvoiceDetail 2 subtotal:"
             << invoiceDetail2.getSubtotal();


    // =====================================================
    // 8. INVOICE
    // =====================================================

    qDebug() << "\n[8] Testing Invoice";

    Invoice invoice(
        1,
        1,                      // orderId
        QDateTime::currentDateTime(),
        "Cash",
        "Paid"
    );

    qDebug() << "Invoice ID:"
             << invoice.getInvoiceId();

    qDebug() << "Order ID:"
             << invoice.getOrderId();

    qDebug() << "Payment method:"
             << invoice.getPaymentMethod();

    qDebug() << "Payment status:"
             << invoice.getPaymentStatus();

    // Add details
    invoice.addDetail(invoiceDetail1);
    invoice.addDetail(invoiceDetail2);

    qDebug() << "Number of invoice details:"
             << invoice.getDetails().size();

    qDebug() << "Invoice total:"
             << invoice.calculateTotal();

    qDebug() << "Stored invoice total:"
             << invoice.getTotalAmount();


    // =====================================================
    // 9. INVOICE REMOVE DETAIL
    // =====================================================

    qDebug() << "\n[9] Testing Invoice removeDetail";

    invoice.removeDetail(1);

    qDebug() << "Number of invoice details after remove:"
             << invoice.getDetails().size();

    qDebug() << "Invoice total after remove:"
             << invoice.calculateTotal();


    // =====================================================
    // 10. INVOICE CLEAR DETAILS
    // =====================================================

    qDebug() << "\n[10] Testing Invoice clearDetails";

    invoice.clearDetails();

    qDebug() << "Number of invoice details after clear:"
             << invoice.getDetails().size();

    qDebug() << "Invoice total after clear:"
             << invoice.calculateTotal();


    // =====================================================
    // 11. INVOICE OPERATOR ==
    // =====================================================

    qDebug() << "\n[11] Testing Invoice operator==";

    Invoice invoiceA(
        100,
        1,
        QDateTime::currentDateTime(),
        "Cash",
        "Paid"
    );

    Invoice invoiceB(
        100,
        2,
        QDateTime::currentDateTime(),
        "Bank Transfer",
        "Pending"
    );

    Invoice invoiceC(
        200,
        1,
        QDateTime::currentDateTime(),
        "Cash",
        "Paid"
    );

    qDebug() << "invoiceA == invoiceB:"
             << (invoiceA == invoiceB);

    qDebug() << "invoiceA == invoiceC:"
             << (invoiceA == invoiceC);


    // =====================================================
    // FINISHED
    // =====================================================

    qDebug() << "\n========================================";
    qDebug() << "       TEST FINISHED";
    qDebug() << "========================================";
}