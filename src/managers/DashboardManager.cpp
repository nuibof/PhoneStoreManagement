//
// Created by Nam B on 9/12/2026.
//

#include "../../include/managers/DashboardManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int DashboardManager::getProductCount() {
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(*) FROM products")) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return 0;
    }
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int DashboardManager::getOrderCount() {
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(*) FROM orders")) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return 0;
    }
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int DashboardManager::getCustomerCount() {
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(*) FROM customers")) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return 0;
    }
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}