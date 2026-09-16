#include "entities/WarehouseEmployee.h"

WarehouseEmployee::WarehouseEmployee()
{
}

WarehouseEmployee::WarehouseEmployee(int id,
                                    QString fullName,
                                    QString phone,
                                    QString email,
                                    QString username,
                                    QString password)
    : Employee(id,
               fullName,
               phone,
               email,
               username,
               password)
{
}

QString WarehouseEmployee::getPosition() const
{
    return "Warehouse";
}