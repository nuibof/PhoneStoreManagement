#include "config/AppConfig.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

AppConfig::DatabaseConfig AppConfig::loadDatabaseConfig(const QString& filePath)
{
    DatabaseConfig config;

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Khong tim thay file cau hinh:" << filePath
                 << "- su dung cau hinh CSDL mac dinh.";
        return config;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.isEmpty() || line.startsWith('#'))
        {
            continue;
        }

        int separatorIndex = line.indexOf('=');

        if (separatorIndex == -1)
        {
            continue;
        }

        QString key = line.left(separatorIndex).trimmed().toLower();
        QString value = line.mid(separatorIndex + 1).trimmed();

        if (key == "host")
        {
            config.host = value;
        }
        else if (key == "port")
        {
            config.port = value.toInt();
        }
        else if (key == "database")
        {
            config.databaseName = value;
        }
        else if (key == "username")
        {
            config.userName = value;
        }
        else if (key == "password")
        {
            config.password = value;
        }
    }

    file.close();

    qDebug() << "Da doc cau hinh CSDL tu file:" << filePath;

    return config;
}
