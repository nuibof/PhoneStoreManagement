#pragma once

#include "entities/Invoice.h"
#include <QList>

struct InvoiceOrderOption {
    int id;
    QString name;
    double total;
};

class InvoiceManager {
public:
    bool getInvoices(QList<Invoice> &invoices, QString &error) const;
    bool getAvailableOrders(QList<InvoiceOrderOption> &orders, QString &error) const;
    bool addInvoice(int orderId, const QString &method, const QString &status, QString &error) const;
    bool updateInvoice(const Invoice &invoice, QString &error) const;
    bool deleteInvoice(int id, QString &error) const;
};
