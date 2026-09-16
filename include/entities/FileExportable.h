#pragma once

#include <QString>

// Lop truu tuong: dai dien cho cac doi tuong co the xuat noi dung ra file van ban
class FileExportable
{
public:
    virtual ~FileExportable();

    // Ham thuan ao - lop con dinh nghia noi dung can xuat ra file
    virtual QString toFileText() const = 0;

    // Ghi noi dung (sinh ra tu toFileText()) ra file van ban tai duong dan chi dinh
    bool exportToFile(const QString& filePath) const;
};
