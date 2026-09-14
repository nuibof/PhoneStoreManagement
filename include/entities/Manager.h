#pragma once
#include "Employee.h"

class Manager : public Employee
{
public:
    Manager();

    Manager(int id,
            QString fullName,
            QString phone,
            QString email,
            QString username,
            QString password);

    QString getPosition() const override;
};