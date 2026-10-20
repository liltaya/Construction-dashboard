#pragma once

#include <QSqlDatabase>
#include <QString>

namespace construction {

class Database
{
public:
    explicit Database(const QString& databasePath);
    ~Database();

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    Database(Database&&) = delete;
    Database& operator=(Database&&) = delete;

    QSqlDatabase& connection();

private:
    void createSchema();
    void execute(const QString& sql);

    QString connectionName_;
    QSqlDatabase database_;
};

}
