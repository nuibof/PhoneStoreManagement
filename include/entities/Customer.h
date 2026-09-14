#pragma once
#include <QString>
#include <QDateTime>

class Customer {
public:
    Customer() = default;
    int getCustomerId() const;
    void setCustomerId(int value);
    QString getFullName() const;
    void setFullName(QString value);
    QString getPhone() const;
    void setPhone(QString value);
    QString getEmail() const;
    void setEmail(QString value);
    QString getAddress() const;
    void setAddress(QString value);
    QDateTime getCreatedAt() const;
    void setCreatedAt(QDateTime value);
private:
    int customerId = 0;
    QString fullName, phone, email, address;
    QDateTime createdAt;
};

