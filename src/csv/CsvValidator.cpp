#include "construction/csv/CsvValidator.h"

namespace construction {

CsvValidationResult CsvValidator::validate(
    const QString& content)
{
    CsvValidationResult result;

    if (content.trimmed().isEmpty())
    {
        result.error = "CSV is empty.";
        return result;
    }

    const QString text = QString(content)
        .replace("\r\n", "\n")
        .replace('\r', '\n');

    QVector<QStringList> records;
    QStringList fields;
    QString field;

    bool quoted = false;
    bool closedQuote = false;
    bool fieldStart = true;

    int line = 1;

    auto finishRow = [&]()
    {
        fields.append(field);
        records.append(fields);

        fields.clear();
        field.clear();
        fieldStart = true;
        closedQuote = false;
    };

    for (int i = 0; i < text.size(); ++i)
    {
        const QChar ch = text.at(i);

        if (quoted)
        {
            if (ch == '"')
            {
                if (i + 1 < text.size()
                    && text.at(i + 1) == '"')
                {
                    field += '"';
                    ++i;
                }
                else
                {
                    quoted = false;
                    closedQuote = true;
                }
            }
            else
            {
                field += ch;
                if (ch == '\n')
                    ++line;
            }

            continue;
        }

        if (closedQuote)
        {
            if (ch == ',')
            {
                fields.append(field);
                field.clear();
                fieldStart = true;
                closedQuote = false;
            }
            else if (ch == '\n')
            {
                finishRow();
                ++line;
            }
            else
            {
                result.error = QString(
                    "Unexpected text after quote at line %1"
                ).arg(line);
                return result;
            }
            continue;
        }

        if (ch == '"')
        {
            if (!fieldStart)
            {
                result.error =
                    QString("Unexpected quote at line %1")
                        .arg(line);
                return result;
            }

            quoted = true;
            fieldStart = false;
        }
        else if (ch == ',')
        {
            fields.append(field);
            field.clear();
            fieldStart = true;
        }
        else if (ch == '\n')
        {
            finishRow();
            ++line;
        }
        else
        {
            field += ch;
            fieldStart = false;
        }
    }

    if (quoted)
    {
        result.error = "Unterminated quoted field.";
        return result;
    }

    if (!fields.isEmpty() ||
        !field.isEmpty() ||
        closedQuote)
    {
        finishRow();
    }

    if (records.isEmpty())
    {
        result.error = "No CSV records found.";
        return result;
    }

    result.headers = records.takeFirst();

    for (const auto& header : result.headers)
    {
        if (header.trimmed().isEmpty())
        {
            result.error = "Empty CSV header.";
            return result;
        }
    }

    for (int i = 0; i < records.size(); ++i)
    {
        if (records[i].size() != result.headers.size())
        {
            result.error = QString(
                "Record %1 has %2 columns; expected %3."
            )
                .arg(i + 2)
                .arg(records[i].size())
                .arg(result.headers.size());

            return result;
        }
    }

    result.rows = records;
    result.valid = true;

    return result;
}

}
