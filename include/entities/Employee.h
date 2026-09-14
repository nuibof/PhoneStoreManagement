#pragma once
#include <QString>

class Employee
{
protected:
    int id;
    QString fullName;
    QString phone;
    QString email;
    QString username;
    QString password;

public:
    Employee();

    Employee(int id,
            QString fullName,
            QString phone,
            QString email,
            QString username,
            QString password);

    virtual ~Employee();

    // Getter
    int getId() const;
    QString getFullName() const;
    QString getPhone() const;
    QString getEmail() const;
    QString getUsername() const;
    QString getPassword() const;

    // Setter
    void setId(int id);
    void setFullName(QString fullName);
    void setPhone(QString phone);
    void setEmail(QString email);
    void setUsername(QString username);
    void setPassword(QString password);

    // Hàm thuần ảo
    virtual QString getPosition() const = 0;

    // Quá tải toán tử
    bool operator==(const Employee& other) const;
};