#include "construction/csv/CsvParser.h"

#include <QFile>
#include <QTextStream>

namespace construction {

CsvParser::Result CsvParser::parseFile(const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return {
            {},
            QString("Could not open CSV file: %1").arg(filePath)
        };
    }

    QTextStream stream(&file);

    std::vector<Row> rows;

    while (!stream.atEnd())
    {
        const QString line = stream.readLine();

        if (line.trimmed().isEmpty())
        {
            continue;
        }

        rows.push_back(parseLine(line));
    }

    return {
        rows,
        {}
    };
}


CsvParser::Row CsvParser::parseLine(const QString& line)
{
    Row fields;

    QString currentField;
    bool insideQuotes = false;

    for (int i = 0; i < line.size(); ++i)
    {
        const QChar character = line[i];

        if (character == '"')
        {
            if (
                insideQuotes &&
                i + 1 < line.size() &&
                line[i + 1] == '"'
            )
            {
                currentField += '"';
                ++i;
            }
            else
            {
                insideQuotes = !insideQuotes;
            }
        }
        else if (character == ',' && !insideQuotes)
        {
            fields.append(currentField.trimmed());
            currentField.clear();
        }
        else
        {
            currentField += character;
        }
    }

    fields.append(currentField.trimmed());

    return fields;
}

}
