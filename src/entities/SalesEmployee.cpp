#include "entities/SalesEmployee.h"

SalesEmployee::SalesEmployee()
{
}

SalesEmployee::SalesEmployee(int id,
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

QString SalesEmployee::getPosition() const
{
    return "Sales";
}