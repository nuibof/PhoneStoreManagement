//
// Created by Nam B on 9/12/2026.
//
#pragma once
#ifndef PHONESTOREMANAGEMENT_DATABASECONNECTION_H
#define PHONESTOREMANAGEMENT_DATABASECONNECTION_H
#include <QSqlDatabase>

class DatabaseConnection {
    public:
    static bool connect();
    static QSqlDatabase database();
};


#endif //PHONESTOREMANAGEMENT_DATABASECONNECTION_H
