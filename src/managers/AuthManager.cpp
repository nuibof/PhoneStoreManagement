#include "managers/AuthManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

AuthManager::AuthManager()
{
    m_currentUsername = "";
}

bool AuthManager::login(const QString &username,
                        const QString &password)
{
    QSqlQuery query;

    query.prepare(
        "SELECT employee_id, position "
        "FROM employees "
        "WHERE username = :username "
        "AND password = :password"
    );

    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec())
    {
        qDebug() << "Login query failed:"
                 << query.lastError().text();
        return false;
    }

    if (!query.next())
    {
        return false;
    }

    m_currentUsername = username;
    m_currentPosition = query.value("position").toString();

    return true;
}

QString AuthManager::getCurrentPosition() const {
    return m_currentPosition;
}

QString AuthManager::getCurrentUsername() const
{
    return m_currentUsername;
}