#include "repositories/EmployeeRepository.h"
#include "entities/Manager.h"
#include "entities/SalesEmployee.h"
#include "entities/WarehouseEmployee.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

// Constructor
EmployeeRepository::EmployeeRepository(QSqlDatabase database)
{
    db = database;
}

// Create Thêm nhân viên
bool EmployeeRepository::add(Employee* employee)
{
    QSqlQuery query(db);

    query.prepare(
        "INSERT INTO employees "
        "(full_name, phone, email, position, username, password) "
        "VALUES "
        "(:fullName, :phone, :email, :position, :username, :password)"
    );

    query.bindValue(
        ":fullName",
        employee->getFullName()
    );

    query.bindValue(
        ":phone",
        employee->getPhone()
    );

    query.bindValue(
        ":email",
        employee->getEmail()
    );

    query.bindValue(
        ":position",
        employee->getPosition()
    );

    query.bindValue(
        ":username",
        employee->getUsername()
    );

    query.bindValue(
        ":password",
        employee->getPassword()
    );

    if (query.exec())
    {
        qDebug() << "Thêm nhân viên thành công";
        return true;
    }

    qDebug() << "Lỗi khi thêm nhân viên:";
    qDebug() << query.lastError().text();

    return false;
}

// Read Lấy tất cả nhân viên
QVector<Employee*> EmployeeRepository::getAll()
{
    QVector<Employee*> employees;

    QSqlQuery query(db);

    bool success = query.exec(
        "SELECT * "
        "FROM employees "
        "ORDER BY employee_id"
    );

    if (!success)
    {
        qDebug() << "Lỗi khi lấy danh sách nhân viên:";
        qDebug() << query.lastError().text();

        return employees;
    }

    while (query.next())
    {
        int id =
            query.value("employee_id").toInt();

        QString fullName =
            query.value("full_name").toString();

        QString phone =
            query.value("phone").toString();

        QString email =
            query.value("email").toString();

        QString position =
            query.value("position").toString();

        QString username =
            query.value("username").toString();

        QString password =
            query.value("password").toString();

        Employee* employee = nullptr;

        if (position == "Manager")
        {
            employee = new Manager(
                id,
                fullName,
                phone,
                email,
                username,
                password
            );
        }
        else if (position == "Sales")
        {
            employee = new SalesEmployee(
                id,
                fullName,
                phone,
                email,
                username,
                password
            );
        }
        else if (position == "Warehouse")
        {
            employee = new WarehouseEmployee(
                id,
                fullName,
                phone,
                email,
                username,
                password
            );
        }

        if (employee != nullptr)
        {
            employees.push_back(employee);
        }
    }

    qDebug() << "Lấy danh sách nhân viên thành công";

    return employees;
}

// Read Tìm nv theo ID
Employee* EmployeeRepository::getById(int id)
{
    QSqlQuery query(db);

    query.prepare(
        "SELECT * "
        "FROM employees "
        "WHERE employee_id = :id"
    );

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Lỗi khi tìm nhân viên theo ID:";
        qDebug() << query.lastError().text();

        return nullptr;
    }

    if (!query.next())
    {
        qDebug() << "Không tìm thấy nhân viên có ID:" << id;

        return nullptr;
    }

    QString fullName =
        query.value("full_name").toString();

    QString phone =
        query.value("phone").toString();

    QString email =
        query.value("email").toString();

    QString position =
        query.value("position").toString();

    QString username =
        query.value("username").toString();

    QString password =
        query.value("password").toString();

    if (position == "Manager")
    {
        return new Manager(
            id,
            fullName,
            phone,
            email,
            username,
            password
        );
    }

    if (position == "Sales")
    {
        return new SalesEmployee(
            id,
            fullName,
            phone,
            email,
            username,
            password
        );
    }

    if (position == "Warehouse")
    {
        return new WarehouseEmployee(
            id,
            fullName,
            phone,
            email,
            username,
            password
        );
    }
    qDebug() << "Chức vụ nhân viên không hợp lệ";

    return nullptr;
}

// Read Tìm theo username
Employee* EmployeeRepository::findByUsername(QString username)
{
    QSqlQuery query(db);

    query.prepare(
        "SELECT * "
        "FROM employees "
        "WHERE username = :username"
    );

    query.bindValue(
        ":username",
        username
    );

    if (!query.exec())
    {
        qDebug() << "Lỗi khi tìm nhân viên theo tên đăng nhập:";
        qDebug() << query.lastError().text();

        return nullptr;
    }

    if (!query.next())
    {
        qDebug() << "Không tìm thấy tài khoản:" << username;

        return nullptr;
    }

    int id =
        query.value("employee_id").toInt();

    QString fullName =
        query.value("full_name").toString();

    QString phone =
        query.value("phone").toString();

    QString email =
        query.value("email").toString();

    QString position =
        query.value("position").toString();

    QString password =
        query.value("password").toString();

    if (position == "Manager")
    {
        return new Manager(
            id,
            fullName,
            phone,
            email,
            username,
            password
        );
    }

    if (position == "Sales")
    {
        return new SalesEmployee(
            id,
            fullName,
            phone,
            email,
            username,
            password
        );
    }

    if (position == "Warehouse")
    {
        return new WarehouseEmployee(
            id,
            fullName,
            phone,
            email,
            username,
            password
        );
    }

    qDebug() << "Chức vụ nhân viên không hợp lệ";

    return nullptr;
}

// Update
bool EmployeeRepository::update(Employee* employee)
{
    QSqlQuery query(db);

    query.prepare(
        "UPDATE employees "
        "SET full_name = :fullName, "
        "phone = :phone, "
        "email = :email, "
        "position = :position, "
        "username = :username, "
        "password = :password "
        "WHERE employee_id = :id"
    );

    query.bindValue(
        ":fullName",
        employee->getFullName()
    );

    query.bindValue(
        ":phone",
        employee->getPhone()
    );

    query.bindValue(
        ":email",
        employee->getEmail()
    );

    query.bindValue(
        ":position",
        employee->getPosition()
    );

    query.bindValue(
        ":username",
        employee->getUsername()
    );

    query.bindValue(
        ":password",
        employee->getPassword()
    );

    query.bindValue(
        ":id",
        employee->getId()
    );

    if (query.exec())
    {
        qDebug() << "Cập nhật nhân viên thành công";
        return true;
    }

    qDebug() << "Lỗi khi cập nhật nhân viên:";
    qDebug() << query.lastError().text();

    return false;
}

// Delete
bool EmployeeRepository::remove(int id)
{
    QSqlQuery query(db);

    query.prepare(
        "DELETE FROM employees "
        "WHERE employee_id = :id"
    );

    query.bindValue(
        ":id",
        id
    );

    if (query.exec())
    {
        qDebug() << "Xóa nhân viên thành công";
        return true;
    }

    qDebug() << "Lỗi khi xóa nhân viên:";
    qDebug() << query.lastError().text();

    return false;
}