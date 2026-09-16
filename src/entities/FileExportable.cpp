#include "entities/FileExportable.h"

#include <QFile>
#include <QTextStream>

FileExportable::~FileExportable()
{
}

bool FileExportable::exportToFile(const QString& filePath) const
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);
    out << toFileText();

    file.close();

    return true;
}
