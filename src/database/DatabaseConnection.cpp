//
// Created by Nam B on 9/12/2026.
//

#include "../../include/database/DatabaseConnection.h"
#include <QDebug>
#include <QSqlError>

bool DatabaseConnection::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("phone_store_management");

    db.setUserName("postgres");
    db.setPassword("1234");

    if (!db.open())
    {
        qDebug() << "Database connection failed:";
        qDebug() << db.lastError().text();
        return false;
    }

    qDebug() << "Database connected successfully!";
    return true;
}

QSqlDatabase DatabaseConnection::database()
{
    return QSqlDatabase::database();
}