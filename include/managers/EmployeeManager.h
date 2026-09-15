#pragma once

#include "EmployeeData.h"
#include <QSqlDatabase>

class EmployeeManager
{
public:
    EmployeeManager();

    bool addEmployee(const EmployeeData &employee);
    bool updateEmployee(const EmployeeData &employee);
    bool deleteEmployee(int employeeId);

    QList<EmployeeData> getAllEmployees();
    EmployeeData getEmployeeById(int employeeId);

private:
    bool connectToDatabase();

    QSqlDatabase m_db;
};