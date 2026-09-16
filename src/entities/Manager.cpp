#include "entities/Manager.h"

Manager::Manager()
{
}

Manager::Manager(int id,
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

QString Manager::getPosition() const
{
    return "Manager";
}