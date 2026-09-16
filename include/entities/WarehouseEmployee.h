#pragma once
#include "Employee.h"

class WarehouseEmployee : public Employee
{
public:
    WarehouseEmployee();

    WarehouseEmployee(int id,
                      QString fullName,
                      QString phone,
                      QString email,
                      QString username,
                      QString password);

    QString getPosition() const override;
};