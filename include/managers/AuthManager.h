#pragma once

#include <QString>

class AuthManager
{
public:
    AuthManager();

    bool login(const QString &username,
               const QString &password);

    QString getCurrentUsername() const;
    QString getCurrentPosition() const;
private:
    QString m_currentUsername;
    QString m_currentPosition;
};