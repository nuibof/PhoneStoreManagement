//
// Created by Nam B on 9/12/2026.
//

#include "../../include/database/DatabaseConnection.h"
#include "config/AppConfig.h"
#include <QDebug>
#include <QSqlError>

bool DatabaseConnection::connect()
{
    AppConfig::DatabaseConfig config = AppConfig::loadDatabaseConfig();

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName(config.host);
    db.setPort(config.port);
    db.setDatabaseName(config.databaseName);

    db.setUserName(config.userName);
    db.setPassword(config.password);

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