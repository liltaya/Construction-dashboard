
#pragma once

#include <QString>
#include <QStringList>
#include <QVector>

namespace construction {

struct CsvValidationResult
{
    bool valid = false;
    QString error;
    QStringList headers;
    QVector<QStringList> rows;
};

class CsvValidator
{
public:
    static CsvValidationResult validate(
        const QString& content
    );
};

}
