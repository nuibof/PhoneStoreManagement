#pragma once
#include "entities/Customer.h"
#include <QList>

class CustomerManager {
public:
    bool getCustomers(QList<Customer> &customers, QString &error) const;
    bool getCustomer(int id, Customer &customer, QString &error) const;
    bool addCustomer(const Customer &customer, QString &error) const;
    bool updateCustomer(const Customer &customer, QString &error) const;
    bool deleteCustomer(int id, QString &error) const;
};
