#include "entities/Customer.h"

int Customer::getCustomerId() const { return customerId; }
void Customer::setCustomerId(int value) { customerId = value; }
QString Customer::getFullName() const { return fullName; }
void Customer::setFullName(QString value) { fullName = value; }
QString Customer::getPhone() const { return phone; }
void Customer::setPhone(QString value) { phone = value; }
QString Customer::getEmail() const { return email; }
void Customer::setEmail(QString value) { email = value; }
QString Customer::getAddress() const { return address; }
void Customer::setAddress(QString value) { address = value; }
QDateTime Customer::getCreatedAt() const { return createdAt; }
void Customer::setCreatedAt(QDateTime value) { createdAt = value; }

