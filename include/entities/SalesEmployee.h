#pragma once
#include "Employee.h"

class SalesEmployee : public Employee
{
public:
    SalesEmployee();

    SalesEmployee(int id,
        QString fullName,
        QString phone,
        QString email,
        QString username,
        QString password);
    QString getPosition() const override;
};