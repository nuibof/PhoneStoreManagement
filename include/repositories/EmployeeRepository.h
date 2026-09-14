#pragma once
#include <QSqlDatabase>
#include <QVector>
#include "entities/Employee.h"

class EmployeeRepository
{
private:
    QSqlDatabase db;

public:
    // Constructor
    EmployeeRepository(QSqlDatabase database);

    // CREATE
    bool add(Employee* employee);

    // READ
    QVector<Employee*> getAll();

    Employee* getById(int id);

    Employee* findByUsername(QString username);

    // UPDATE
    bool update(Employee* employee);

    // DELETE
    bool remove(int id);
};