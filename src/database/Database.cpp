#include "construction/database/Database.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QUuid>

#include <stdexcept>

namespace construction {

Database::Database(const QString& databasePath)
    : connectionName_(
          QString("construction_%1")
              .arg(QUuid::createUuid().toString(QUuid::WithoutBraces))
      ),
      database_(
          QSqlDatabase::addDatabase(
              "QSQLITE",
              connectionName_
          )
      )
{
    database_.setDatabaseName(databasePath);

    if (!database_.open())
    {
        throw std::runtime_error(
            database_.lastError().text().toStdString()
        );
    }

    execute("PRAGMA foreign_keys = ON;");

    createSchema();
}

Database::~Database()
{
    if (database_.isOpen())
    {
        database_.close();
    }

    database_ = QSqlDatabase();

    QSqlDatabase::removeDatabase(connectionName_);
}

QSqlDatabase& Database::connection()
{
    return database_;
}

void Database::execute(const QString& sql)
{
    QSqlQuery query(database_);

    if (!query.exec(sql))
    {
        throw std::runtime_error(
            query.lastError().text().toStdString()
        );
    }
}

void Database::createSchema()
{
    execute(R"(
        CREATE TABLE IF NOT EXISTS projects (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            description TEXT NOT NULL,
            location TEXT NOT NULL,
            start_date TEXT NOT NULL,
            end_date TEXT NOT NULL,
            status TEXT NOT NULL,
            budget REAL NOT NULL CHECK (budget >= 0)
        );
    )");

    execute(R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY,
            project_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            description TEXT NOT NULL,
            status TEXT NOT NULL,
            priority TEXT NOT NULL,
            start_date TEXT NOT NULL,
            due_date TEXT NOT NULL,
            completed_at TEXT NOT NULL,
            estimated_cost REAL NOT NULL CHECK (estimated_cost >= 0),

            FOREIGN KEY (project_id)
                REFERENCES projects(id)
                ON DELETE CASCADE
        );
    )");

    execute(R"(
        CREATE TABLE IF NOT EXISTS workers (
            id INTEGER PRIMARY KEY,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL,
            phone TEXT NOT NULL,
            role TEXT NOT NULL,
            hourly_rate REAL NOT NULL CHECK (hourly_rate >= 0),
            active INTEGER NOT NULL DEFAULT 1
        );
    )");

    execute(R"(
        CREATE TABLE IF NOT EXISTS cost_entries (
            id INTEGER PRIMARY KEY,
            project_id INTEGER NOT NULL,
            task_id INTEGER,
            category TEXT NOT NULL,
            description TEXT NOT NULL,
            amount REAL NOT NULL CHECK (amount >= 0),
            entry_date TEXT NOT NULL,

            FOREIGN KEY (project_id)
                REFERENCES projects(id)
                ON DELETE CASCADE,

            FOREIGN KEY (task_id)
                REFERENCES tasks(id)
                ON DELETE SET NULL
        );
    )");

    execute(R"(
        CREATE TABLE IF NOT EXISTS work_logs (
            id INTEGER PRIMARY KEY,
            project_id INTEGER NOT NULL,
            worker_id INTEGER NOT NULL,
            hours REAL NOT NULL CHECK (hours >= 0),
            work_date TEXT NOT NULL,

            FOREIGN KEY (project_id)
                REFERENCES projects(id)
                ON DELETE CASCADE,

            FOREIGN KEY (worker_id)
                REFERENCES workers(id)
                ON DELETE CASCADE
        );
    )");
}

}
