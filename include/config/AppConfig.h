#pragma once

#include <QString>

// Doc cau hinh ung dung tu file van ban (thay vi hard-code trong code)
class AppConfig
{
public:
    struct DatabaseConfig
    {
        QString host = "localhost";
        int port = 5432;
        QString databaseName = "phone_store";
        QString userName = "postgres";
        QString password = "1234";
    };

    // Doc thong tin ket noi CSDL tu file dinh dang "key=value".
    // Neu khong mo duoc file, tra ve cau hinh mac dinh o tren.
    static DatabaseConfig loadDatabaseConfig(const QString& filePath = "config/database.txt");
};
