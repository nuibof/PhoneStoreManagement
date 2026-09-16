#include "entities/Employee.h"

Employee::Employee()
{
    id = 0;
}

Employee::Employee(int id,
                   QString fullName,
                   QString phone,
                   QString email,
                   QString username,
                   QString password)
{
    this->id = id;
    this->fullName = fullName;
    this->phone = phone;
    this->email = email;
    this->username = username;
    this->password = password;
}

Employee::~Employee()
{
}

// Getter
int Employee::getId() const
{
    return id;
}

QString Employee::getFullName() const
{
    return fullName;
}

QString Employee::getPhone() const
{
    return phone;
}

QString Employee::getEmail() const
{
    return email;
}

QString Employee::getUsername() const
{
    return username;
}

QString Employee::getPassword() const
{
    return password;
}

// Setter
void Employee::setId(int id)
{
    this->id = id;
}

void Employee::setFullName(QString fullName)
{
    this->fullName = fullName;
}

void Employee::setPhone(QString phone)
{
    this->phone = phone;
}

void Employee::setEmail(QString email)
{
    this->email = email;
}

void Employee::setUsername(QString username)
{
    this->username = username;
}

void Employee::setPassword(QString password)
{
    this->password = password;
}

// Quá tải toán tử
bool Employee::operator==(const Employee& other) const
{
    return id == other.id;
}