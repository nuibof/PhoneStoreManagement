#include "managers/CustomerManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

namespace {
Customer readCustomer(const QSqlQuery &query) {
    Customer customer;
    customer.setCustomerId(query.value(0).toInt());
    customer.setFullName(query.value(1).toString());
    customer.setPhone(query.value(2).toString());
    customer.setEmail(query.value(3).toString());
    customer.setAddress(query.value(4).toString());
    customer.setCreatedAt(query.value(5).toDateTime());
    return customer;
}
bool executeChange(QSqlQuery &query, QString &error) {
    error.clear();
    if (!query.exec()) { error = query.lastError().text(); return false; }
    if (query.numRowsAffected() != 1) {
        error = "This customer no longer exists. Refresh the list.";
        return false;
    }
    return true;
}
bool bindCustomer(QSqlQuery &query, const Customer &customer, QString &error) {
    error.clear();
    const auto name = customer.getFullName().trimmed();
    const auto phone = customer.getPhone().trimmed();
    const auto email = customer.getEmail().trimmed();
    if (name.isEmpty()) { error = "Full name cannot be empty."; return false; }
    if (name.size() > 150 || phone.size() > 20 || email.size() > 150) {
        error = "Customer information exceeds the allowed length.";
        return false;
    }
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":address", customer.getAddress().trimmed());
    return true;
}
}

bool CustomerManager::getCustomers(QList<Customer> &customers, QString &error) const {
    error.clear();
    customers.clear();
    QSqlQuery query;
    if (!query.exec("SELECT customer_id, full_name, phone, email, address, created_at FROM customers ORDER BY customer_id")) {
        error = query.lastError().text(); return false;
    }
    while (query.next()) customers.append(readCustomer(query));
    if (query.lastError().isValid()) { error = query.lastError().text(); customers.clear(); return false; }
    return true;
}
bool CustomerManager::getCustomer(int id, Customer &customer, QString &error) const {
    error.clear();
    customer = Customer();
    QSqlQuery query;
    query.prepare("SELECT customer_id, full_name, phone, email, address, created_at FROM customers WHERE customer_id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) { error = query.lastError().text(); return false; }
    if (!query.next()) { error = query.lastError().isValid() ? query.lastError().text() : "This customer no longer exists."; return false; }
    customer = readCustomer(query);
    return true;
}
bool CustomerManager::addCustomer(const Customer &customer, QString &error) const {
    QSqlQuery query;
    query.prepare("INSERT INTO customers (full_name, phone, email, address) VALUES (:name, NULLIF(:phone, ''), NULLIF(:email, ''), :address)");
    return bindCustomer(query, customer, error) && executeChange(query, error);
}
bool CustomerManager::updateCustomer(const Customer &customer, QString &error) const {
    QSqlQuery query;
    query.prepare("UPDATE customers SET full_name = :name, phone = NULLIF(:phone, ''), email = NULLIF(:email, ''), address = :address WHERE customer_id = :id");
    query.bindValue(":id", customer.getCustomerId());
    return bindCustomer(query, customer, error) && executeChange(query, error);
}
bool CustomerManager::deleteCustomer(int id, QString &error) const {
    QSqlQuery query;
    query.prepare("DELETE FROM customers WHERE customer_id = :id");
    query.bindValue(":id", id);
    return executeChange(query, error);
}
