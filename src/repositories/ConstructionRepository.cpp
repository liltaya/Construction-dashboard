#include "construction/repositories/ConstructionRepository.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

#include <stdexcept>

namespace construction {

namespace {

void throwIfFailed(const QSqlQuery& query)
{
    throw std::runtime_error(
        query.lastError().text().toStdString()
    );
}

} 

ConstructionRepository::ConstructionRepository(
    Database& database
)
    : database_(database)
{
}

void ConstructionRepository::insertProject(
    const Project& project
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        INSERT INTO projects (
            id,
            name,
            description,
            location,
            start_date,
            end_date,
            status,
            budget
        )
        VALUES (?, ?, ?, ?, ?, ?, ?, ?);
    )");

    query.addBindValue(static_cast<qlonglong>(project.id));
    query.addBindValue(QString::fromStdString(project.name));
    query.addBindValue(QString::fromStdString(project.description));
    query.addBindValue(QString::fromStdString(project.location));
    query.addBindValue(QString::fromStdString(project.startDate));
    query.addBindValue(QString::fromStdString(project.endDate));
    query.addBindValue(QString::fromStdString(project.status));
    query.addBindValue(project.budget);

    if (!query.exec())
    {
        throwIfFailed(query);
    }
}

std::optional<Project>
ConstructionRepository::findProjectById(
    std::int64_t id
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        SELECT
            id,
            name,
            description,
            location,
            start_date,
            end_date,
            status,
            budget
        FROM projects
        WHERE id = ?;
    )");

    query.addBindValue(
        static_cast<qlonglong>(id)
    );

    if (!query.exec())
    {
        throwIfFailed(query);
    }

    if (!query.next())
    {
        return std::nullopt;
    }

    Project project;

    project.id = query.value(0).toLongLong();
    project.name = query.value(1).toString().toStdString();
    project.description = query.value(2).toString().toStdString();
    project.location = query.value(3).toString().toStdString();
    project.startDate = query.value(4).toString().toStdString();
    project.endDate = query.value(5).toString().toStdString();
    project.status = query.value(6).toString().toStdString();
    project.budget = query.value(7).toDouble();

    return project;
}

std::vector<Project>
ConstructionRepository::findAllProjects()
{
    QSqlQuery query(database_.connection());

    if (!query.exec(R"(
        SELECT
            id,
            name,
            description,
            location,
            start_date,
            end_date,
            status,
            budget
        FROM projects
        ORDER BY id;
    )"))
    {
        throwIfFailed(query);
    }

    std::vector<Project> projects;

    while (query.next())
    {
        Project project;

        project.id = query.value(0).toLongLong();
        project.name = query.value(1).toString().toStdString();
        project.description = query.value(2).toString().toStdString();
        project.location = query.value(3).toString().toStdString();
        project.startDate = query.value(4).toString().toStdString();
        project.endDate = query.value(5).toString().toStdString();
        project.status = query.value(6).toString().toStdString();
        project.budget = query.value(7).toDouble();

        projects.push_back(project);
    }

    return projects;
}

void ConstructionRepository::updateProject(
    const Project& project
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        UPDATE projects
        SET
            name = ?,
            description = ?,
            location = ?,
            start_date = ?,
            end_date = ?,
            status = ?,
            budget = ?
        WHERE id = ?;
    )");

    query.addBindValue(QString::fromStdString(project.name));
    query.addBindValue(QString::fromStdString(project.description));
    query.addBindValue(QString::fromStdString(project.location));
    query.addBindValue(QString::fromStdString(project.startDate));
    query.addBindValue(QString::fromStdString(project.endDate));
    query.addBindValue(QString::fromStdString(project.status));
    query.addBindValue(project.budget);
    query.addBindValue(static_cast<qlonglong>(project.id));

    if (!query.exec())
    {
        throwIfFailed(query);
    }
}

void ConstructionRepository::insertTask(
    const Task& task
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        INSERT INTO tasks (
            id,
            project_id,
            name,
            description,
            status,
            priority,
            start_date,
            due_date,
            completed_at,
            estimated_cost
        )
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    )");

    query.addBindValue(static_cast<qlonglong>(task.id));
    query.addBindValue(static_cast<qlonglong>(task.projectId));
    query.addBindValue(QString::fromStdString(task.name));
    query.addBindValue(QString::fromStdString(task.description));
    query.addBindValue(QString::fromStdString(task.status));
    query.addBindValue(QString::fromStdString(task.priority));
    query.addBindValue(QString::fromStdString(task.startDate));
    query.addBindValue(QString::fromStdString(task.dueDate));
    query.addBindValue(QString::fromStdString(task.completedAt));
    query.addBindValue(task.estimatedCost);

    if (!query.exec())
    {
        throwIfFailed(query);
    }
}

std::vector<Task>
ConstructionRepository::findTasksByProject(
    std::int64_t projectId
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        SELECT
            id,
            project_id,
            name,
            description,
            status,
            priority,
            start_date,
            due_date,
            completed_at,
            estimated_cost
        FROM tasks
        WHERE project_id = ?
        ORDER BY id;
    )");

    query.addBindValue(
        static_cast<qlonglong>(projectId)
    );

    if (!query.exec())
    {
        throwIfFailed(query);
    }

    std::vector<Task> tasks;

    while (query.next())
    {
        Task task;

        task.id = query.value(0).toLongLong();
        task.projectId = query.value(1).toLongLong();
        task.name = query.value(2).toString().toStdString();
        task.description = query.value(3).toString().toStdString();
        task.status = query.value(4).toString().toStdString();
        task.priority = query.value(5).toString().toStdString();
        task.startDate = query.value(6).toString().toStdString();
        task.dueDate = query.value(7).toString().toStdString();
        task.completedAt = query.value(8).toString().toStdString();
        task.estimatedCost = query.value(9).toDouble();

        tasks.push_back(task);
    }

    return tasks;
}

void ConstructionRepository::updateTask(
    const Task& task
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        UPDATE tasks
        SET
            project_id = ?,
            name = ?,
            description = ?,
            status = ?,
            priority = ?,
            start_date = ?,
            due_date = ?,
            completed_at = ?,
            estimated_cost = ?
        WHERE id = ?;
    )");

    query.addBindValue(static_cast<qlonglong>(task.projectId));
    query.addBindValue(QString::fromStdString(task.name));
    query.addBindValue(QString::fromStdString(task.description));
    query.addBindValue(QString::fromStdString(task.status));
    query.addBindValue(QString::fromStdString(task.priority));
    query.addBindValue(QString::fromStdString(task.startDate));
    query.addBindValue(QString::fromStdString(task.dueDate));
    query.addBindValue(QString::fromStdString(task.completedAt));
    query.addBindValue(task.estimatedCost);
    query.addBindValue(static_cast<qlonglong>(task.id));

    if (!query.exec())
    {
        throwIfFailed(query);
    }
}

void ConstructionRepository::insertWorker(
    const Worker& worker
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        INSERT INTO workers (
            id,
            first_name,
            last_name,
            email,
            phone,
            role,
            hourly_rate,
            active
        )
        VALUES (?, ?, ?, ?, ?, ?, ?, ?);
    )");

    query.addBindValue(static_cast<qlonglong>(worker.id));
    query.addBindValue(QString::fromStdString(worker.firstName));
    query.addBindValue(QString::fromStdString(worker.lastName));
    query.addBindValue(QString::fromStdString(worker.email));
    query.addBindValue(QString::fromStdString(worker.phone));
    query.addBindValue(QString::fromStdString(worker.role));
    query.addBindValue(worker.hourlyRate);
    query.addBindValue(worker.active ? 1 : 0);

    if (!query.exec())
    {
        throwIfFailed(query);
    }
}

void ConstructionRepository::insertCostEntry(
    const CostEntry& entry
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        INSERT INTO cost_entries (
            id,
            project_id,
            task_id,
            category,
            description,
            amount,
            entry_date
        )
        VALUES (?, ?, ?, ?, ?, ?, ?);
    )");

    query.addBindValue(static_cast<qlonglong>(entry.id));
    query.addBindValue(static_cast<qlonglong>(entry.projectId));

    if (entry.taskId.has_value())
    {
        query.addBindValue(
            static_cast<qlonglong>(*entry.taskId)
        );
    }
    else
    {
        query.addBindValue(QVariant());
    }

    query.addBindValue(QString::fromStdString(entry.category));
    query.addBindValue(QString::fromStdString(entry.description));
    query.addBindValue(entry.amount);
    query.addBindValue(QString::fromStdString(entry.entryDate));

    if (!query.exec())
    {
        throwIfFailed(query);
    }
}


std::vector<CostEntry>
ConstructionRepository::findCostsByProject(
    std::int64_t projectId
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        SELECT
            id,
            project_id,
            task_id,
            category,
            description,
            amount,
            entry_date
        FROM cost_entries
        WHERE project_id = ?;
    )");

    query.addBindValue(
        static_cast<qlonglong>(projectId)
    );

    if (!query.exec())
    {
        throwIfFailed(query);
    }

    std::vector<CostEntry> entries;

    while (query.next())
    {
        CostEntry entry;

        entry.id = query.value(0).toLongLong();
        entry.projectId = query.value(1).toLongLong();

        if (!query.value(2).isNull())
        {
            entry.taskId = query.value(2).toLongLong();
        }

        entry.category =
            query.value(3).toString().toStdString();

        entry.description =
            query.value(4).toString().toStdString();

        entry.amount = query.value(5).toDouble();

        entry.entryDate =
            query.value(6).toString().toStdString();

        entries.push_back(entry);
    }

    return entries;
}

std::int64_t
ConstructionRepository::countIncidentsByProject(
    std::int64_t projectId
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        SELECT COUNT(*)
        FROM incidents
        WHERE project_id = ?;
    )");

    query.addBindValue(
        static_cast<qlonglong>(projectId)
    );

    if (!query.exec())
    {
        throwIfFailed(query);
    }

    if (query.next())
    {
        return query.value(0).toLongLong();
    }

    return 0;
}

void ConstructionRepository::insertWorkLog(
    const WorkLog& workLog
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        INSERT INTO work_logs (
            id,
            project_id,
            worker_id,
            hours,
            work_date
        )
        VALUES (?, ?, ?, ?, ?);
    )");

    query.addBindValue(static_cast<qlonglong>(workLog.id));
    query.addBindValue(static_cast<qlonglong>(workLog.projectId));
    query.addBindValue(static_cast<qlonglong>(workLog.workerId));
    query.addBindValue(workLog.hours);
    query.addBindValue(QString::fromStdString(workLog.workDate));

    if (!query.exec())
    {
        throwIfFailed(query);
    }
}

std::vector<WorkLog>
ConstructionRepository::findWorkLogsByProject(
    std::int64_t projectId
)
{
    QSqlQuery query(database_.connection());

    query.prepare(R"(
        SELECT
            id,
            project_id,
            worker_id,
            hours,
            work_date
        FROM work_logs
        WHERE project_id = ?;
    )");

    query.addBindValue(
        static_cast<qlonglong>(projectId)
    );

    if (!query.exec())
    {
        throwIfFailed(query);
    }

    std::vector<WorkLog> workLogs;

    while (query.next())
    {
        WorkLog log;

        log.id = query.value(0).toLongLong();
        log.projectId = query.value(1).toLongLong();
        log.workerId = query.value(2).toLongLong();
        log.hours = query.value(3).toDouble();
        log.workDate = query.value(4).toString().toStdString();

        workLogs.push_back(log);
    }

    return workLogs;
}

} 
