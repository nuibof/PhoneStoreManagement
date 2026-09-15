#include "managers/EmployeeManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

EmployeeManager::EmployeeManager()
{
    connectToDatabase();
}

bool EmployeeManager::connectToDatabase()
{
    if (!QSqlDatabase::contains())
    {
        qDebug() << "Database connection not found.";
        return false;
    }

    m_db = QSqlDatabase::database();

    if (!m_db.isOpen())
    {
        qDebug() << "Database is not open.";
        return false;
    }

    return true;
}

bool EmployeeManager::addEmployee(const EmployeeData &employee)
{
    QSqlQuery query(m_db);

    query.prepare(
        "INSERT INTO employees "
        "(full_name, phone, email, position, username, password) "
        "VALUES "
        "(:full_name, :phone, :email, :position, :username, :password)"
    );

    query.bindValue(":full_name", employee.fullName);
    query.bindValue(":phone", employee.phone);
    query.bindValue(":email", employee.email);
    query.bindValue(":position", employee.position);
    query.bindValue(":username", employee.username);
    query.bindValue(":password", employee.password);

    if (!query.exec())
    {
        qDebug() << "Add employee failed:"
                 << query.lastError().text();

        return false;
    }

    qDebug() << "Employee added successfully:"
             << employee.username;

    return true;
}

bool EmployeeManager::updateEmployee(const EmployeeData &employee)
{
    QSqlQuery query(m_db);

    query.prepare(
        "UPDATE employees "
        "SET full_name = :full_name, "
        "phone = :phone, "
        "email = :email, "
        "position = :position, "
        "username = :username, "
        "password = :password "
        "WHERE employee_id = :id"
    );

    query.bindValue(":id", employee.id);
    query.bindValue(":full_name", employee.fullName);
    query.bindValue(":phone", employee.phone);
    query.bindValue(":email", employee.email);
    query.bindValue(":position", employee.position);
    query.bindValue(":username", employee.username);
    query.bindValue(":password", employee.password);

    if (!query.exec())
    {
        qDebug() << "Update employee failed:"
                 << query.lastError().text();
        return false;
    }

    return true;
}

bool EmployeeManager::deleteEmployee(int employeeId)
{
    QSqlQuery query(m_db);

    query.prepare(
        "DELETE FROM employees "
        "WHERE employee_id = :id"
    );

    query.bindValue(":id", employeeId);

    if (!query.exec())
    {
        qDebug() << "Delete employee failed:"
                 << query.lastError().text();
        return false;
    }

    return true;
}

QList<EmployeeData> EmployeeManager::getAllEmployees()
{
    QList<EmployeeData> employees;

    QSqlQuery query(m_db);

    if (!query.exec(
        "SELECT employee_id, full_name, phone, email, "
        "position, username "
        "FROM employees "
        "ORDER BY employee_id"
    ))
    {
        qDebug() << "Get employees failed:"
                 << query.lastError().text();
        return employees;
    }

    while (query.next())
    {
        EmployeeData employee;

        employee.id = query.value("employee_id").toInt();
        employee.fullName = query.value("full_name").toString();
        employee.phone = query.value("phone").toString();
        employee.email = query.value("email").toString();
        employee.position = query.value("position").toString();
        employee.username = query.value("username").toString();

        employees.append(employee);
    }

    return employees;
}

EmployeeData EmployeeManager::getEmployeeById(int employeeId)
{
    EmployeeData employee{};

    QSqlQuery query(m_db);

    query.prepare(
        "SELECT employee_id, full_name, phone, email, "
        "position, username, password "
        "FROM employees "
        "WHERE employee_id = :id"
    );

    query.bindValue(":id", employeeId);

    if (!query.exec())
    {
        qDebug() << "Get employee failed:"
                 << query.lastError().text();
        return employee;
    }

    if (query.next())
    {
        employee.id = query.value("employee_id").toInt();
        employee.fullName = query.value("full_name").toString();
        employee.phone = query.value("phone").toString();
        employee.email = query.value("email").toString();
        employee.position = query.value("position").toString();
        employee.username = query.value("username").toString();
        employee.password = query.value("password").toString();
    }

    return employee;
}