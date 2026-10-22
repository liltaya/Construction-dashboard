#include "construction/csv/CsvImporter.h"
#include "construction/csv/CsvParser.h"
#include "construction/csv/CsvValidator.h"
#include "construction/utils/Logger.h"

#include <QFile>
#include <QIODevice>
#include <QSet>

#include <cstdint>
#include <stdexcept>

namespace construction {

namespace {

// Validate the complete CSV before parsing.
bool validateCsvFile(
    const QString& filePath,
    QString& error
)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        error = file.errorString();
        return false;
    }

    const QString csvContent =
        QString::fromUtf8(file.readAll());

    const auto validation =
        CsvValidator::validate(csvContent);

    if (!validation.valid)
    {
        Logger::instance().warning(
            "CSV rejected: " + validation.error
        );

        error = validation.error;
        return false;
    }

    return true;
}

// Parse a non-negative integer ID.
bool parseId(
    const QString& value,
    std::int64_t& destination
)
{
    bool ok = false;

    const qlonglong parsed = value.toLongLong(&ok);

    if (!ok || parsed < 0)
    {
        return false;
    }

    destination = static_cast<std::int64_t>(parsed);
    return true;
}

// Parse a non-negative decimal number.
bool parsePositiveDouble(
    const QString& value,
    double& destination
)
{
    bool ok = false;

    const double parsed = value.toDouble(&ok);

    if (!ok || parsed < 0.0)
    {
        return false;
    }

    destination = parsed;
    return true;
}

// Parse supported boolean values.
bool parseBoolean(
    const QString& value,
    bool& destination
)
{
    const QString normalized =
        value.trimmed().toLower();

    if (
        normalized == "1" ||
        normalized == "true" ||
        normalized == "yes"
    )
    {
        destination = true;
        return true;
    }

    if (
        normalized == "0" ||
        normalized == "false" ||
        normalized == "no"
    )
    {
        destination = false;
        return true;
    }

    return false;
}

bool validProjectStatus(const QString& status)
{
    static const QSet<QString> allowed {
        "planned",
        "active",
        "on_hold",
        "completed",
        "cancelled"
    };

    return allowed.contains(status);
}

bool validTaskStatus(const QString& status)
{
    static const QSet<QString> allowed {
        "todo",
        "in_progress",
        "blocked",
        "completed",
        "cancelled"
    };

    return allowed.contains(status);
}

bool validPriority(const QString& priority)
{
    static const QSet<QString> allowed {
        "low",
        "medium",
        "high",
        "critical"
    };

    return allowed.contains(priority);
}

bool validCostCategory(const QString& category)
{
    static const QSet<QString> allowed {
        "labor",
        "material",
        "equipment",
        "subcontractor",
        "permit",
        "transportation",
        "other"
    };

    return allowed.contains(category);
}

bool validIncidentType(const QString& type)
{
    static const QSet<QString> allowed {
        "injury",
        "safety",
        "equipment",
        "property_damage",
        "near_miss",
        "other"
    };

    return allowed.contains(type);
}

bool validSeverity(const QString& severity)
{
    static const QSet<QString> allowed {
        "low",
        "medium",
        "high",
        "critical"
    };

    return allowed.contains(severity);
}

} // anonymous namespace

CsvImporter::ImportResult<Project>
CsvImporter::importProjects(const QString& filePath)
{
    ImportResult<Project> result;

    QString validationError;

    if (!validateCsvFile(filePath, validationError))
    {
        result.errors.push_back(validationError);
        return result;
    }

    const auto parsed = CsvParser::parseFile(filePath);

    if (!parsed.success())
    {
        result.errors.push_back(parsed.error);
        return result;
    }

    if (parsed.rows.empty())
    {
        result.errors.push_back("Project CSV is empty.");
        return result;
    }

    const QStringList expectedHeader {
        "id",
        "name",
        "description",
        "location",
        "start_date",
        "end_date",
        "status",
        "budget"
    };

    if (parsed.rows.front() != expectedHeader)
    {
        result.errors.push_back(
            "Invalid project CSV header."
        );
        return result;
    }

    for (
        std::size_t index = 1;
        index < parsed.rows.size();
        ++index
    )
    {
        const auto& row = parsed.rows[index];

        const int rowNumber =
            static_cast<int>(index + 1);

        if (row.size() != expectedHeader.size())
        {
            result.errors.push_back(
                QString("Row %1: expected %2 fields but found %3.")
                    .arg(rowNumber)
                    .arg(expectedHeader.size())
                    .arg(row.size())
            );
            continue;
        }

        Project project;

        if (!parseId(row[0], project.id))
        {
            result.errors.push_back(
                QString("Row %1: invalid project id.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (row[1].trimmed().isEmpty())
        {
            result.errors.push_back(
                QString("Row %1: project name is required.")
                    .arg(rowNumber)
            );
            continue;
        }

        project.name = row[1].toStdString();
        project.description = row[2].toStdString();
        project.location = row[3].toStdString();

        project.startDate = row[4].toStdString();
        project.endDate = row[5].toStdString();

        const QString status =
            row[6].trimmed().toLower();

        if (!validProjectStatus(status))
        {
            result.errors.push_back(
                QString("Row %1: invalid project status '%2'.")
                    .arg(rowNumber)
                    .arg(row[6])
            );
            continue;
        }

        project.status = status.toStdString();

        if (!parsePositiveDouble(row[7], project.budget))
        {
            result.errors.push_back(
                QString("Row %1: invalid project budget.")
                    .arg(rowNumber)
            );
            continue;
        }

        result.objects.push_back(project);
    }

    return result;
}

CsvImporter::ImportResult<Task>
CsvImporter::importTasks(const QString& filePath)
{
    ImportResult<Task> result;

    QString validationError;

    if (!validateCsvFile(filePath, validationError))
    {
        result.errors.push_back(validationError);
        return result;
    }

    const auto parsed = CsvParser::parseFile(filePath);

    if (!parsed.success())
    {
        result.errors.push_back(parsed.error);
        return result;
    }

    if (parsed.rows.empty())
    {
        result.errors.push_back("Task CSV is empty.");
        return result;
    }

    const QStringList expectedHeader {
        "id",
        "project_id",
        "name",
        "description",
        "status",
        "priority",
        "start_date",
        "due_date",
        "completed_at",
        "estimated_cost"
    };

    if (parsed.rows.front() != expectedHeader)
    {
        result.errors.push_back(
            "Invalid task CSV header."
        );
        return result;
    }

    for (
        std::size_t index = 1;
        index < parsed.rows.size();
        ++index
    )
    {
        const auto& row = parsed.rows[index];

        const int rowNumber =
            static_cast<int>(index + 1);

        if (row.size() != expectedHeader.size())
        {
            result.errors.push_back(
                QString("Row %1: incorrect number of task fields.")
                    .arg(rowNumber)
            );
            continue;
        }

        Task task;

        if (!parseId(row[0], task.id))
        {
            result.errors.push_back(
                QString("Row %1: invalid task id.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (!parseId(row[1], task.projectId))
        {
            result.errors.push_back(
                QString("Row %1: invalid project id.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (row[2].trimmed().isEmpty())
        {
            result.errors.push_back(
                QString("Row %1: task name is required.")
                    .arg(rowNumber)
            );
            continue;
        }

        task.name = row[2].toStdString();
        task.description = row[3].toStdString();

        const QString status =
            row[4].trimmed().toLower();

        if (!validTaskStatus(status))
        {
            result.errors.push_back(
                QString("Row %1: invalid task status.")
                    .arg(rowNumber)
            );
            continue;
        }

        task.status = status.toStdString();

        const QString priority =
            row[5].trimmed().toLower();

        if (!validPriority(priority))
        {
            result.errors.push_back(
                QString("Row %1: invalid task priority.")
                    .arg(rowNumber)
            );
            continue;
        }

        task.priority = priority.toStdString();

        task.startDate = row[6].toStdString();
        task.dueDate = row[7].toStdString();
        task.completedAt = row[8].toStdString();

        if (
            !parsePositiveDouble(
                row[9],
                task.estimatedCost
            )
        )
        {
            result.errors.push_back(
                QString("Row %1: invalid estimated cost.")
                    .arg(rowNumber)
            );
            continue;
        }

        result.objects.push_back(task);
    }

    return result;
}

CsvImporter::ImportResult<Worker>
CsvImporter::importWorkers(const QString& filePath)
{
    ImportResult<Worker> result;

    QString validationError;

    if (!validateCsvFile(filePath, validationError))
    {
        result.errors.push_back(validationError);
        return result;
    }

    const auto parsed = CsvParser::parseFile(filePath);

    if (!parsed.success())
    {
        result.errors.push_back(parsed.error);
        return result;
    }

    if (parsed.rows.empty())
    {
        result.errors.push_back("Worker CSV is empty.");
        return result;
    }

    const QStringList expectedHeader {
        "id",
        "first_name",
        "last_name",
        "email",
        "phone",
        "role",
        "hourly_rate",
        "active"
    };

    if (parsed.rows.front() != expectedHeader)
    {
        result.errors.push_back(
            "Invalid worker CSV header."
        );
        return result;
    }

    for (
        std::size_t index = 1;
        index < parsed.rows.size();
        ++index
    )
    {
        const auto& row = parsed.rows[index];

        const int rowNumber =
            static_cast<int>(index + 1);

        if (row.size() != expectedHeader.size())
        {
            result.errors.push_back(
                QString("Row %1: incorrect number of worker fields.")
                    .arg(rowNumber)
            );
            continue;
        }

        Worker worker;

        if (!parseId(row[0], worker.id))
        {
            result.errors.push_back(
                QString("Row %1: invalid worker id.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (
            row[1].trimmed().isEmpty() ||
            row[2].trimmed().isEmpty()
        )
        {
            result.errors.push_back(
                QString("Row %1: worker first and last name are required.")
                    .arg(rowNumber)
            );
            continue;
        }

        worker.firstName = row[1].toStdString();
        worker.lastName = row[2].toStdString();

        worker.email = row[3].toStdString();
        worker.phone = row[4].toStdString();
        worker.role = row[5].toStdString();

        if (
            !parsePositiveDouble(
                row[6],
                worker.hourlyRate
            )
        )
        {
            result.errors.push_back(
                QString("Row %1: invalid hourly rate.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (!parseBoolean(row[7], worker.active))
        {
            result.errors.push_back(
                QString("Row %1: active must be true/false, yes/no, or 1/0.")
                    .arg(rowNumber)
            );
            continue;
        }

        result.objects.push_back(worker);
    }

    return result;
}

CsvImporter::ImportResult<CostEntry>
CsvImporter::importCostEntries(const QString& filePath)
{
    ImportResult<CostEntry> result;

    QString validationError;

    if (!validateCsvFile(filePath, validationError))
    {
        result.errors.push_back(validationError);
        return result;
    }

    const auto parsed = CsvParser::parseFile(filePath);

    if (!parsed.success())
    {
        result.errors.push_back(parsed.error);
        return result;
    }

    if (parsed.rows.empty())
    {
        result.errors.push_back("Cost CSV is empty.");
        return result;
    }

    const QStringList expectedHeader {
        "id",
        "project_id",
        "task_id",
        "category",
        "description",
        "amount",
        "entry_date"
    };

    if (parsed.rows.front() != expectedHeader)
    {
        result.errors.push_back(
            "Invalid cost CSV header."
        );
        return result;
    }

    for (
        std::size_t index = 1;
        index < parsed.rows.size();
        ++index
    )
    {
        const auto& row = parsed.rows[index];

        const int rowNumber =
            static_cast<int>(index + 1);

        if (row.size() != expectedHeader.size())
        {
            result.errors.push_back(
                QString("Row %1: incorrect number of cost fields.")
                    .arg(rowNumber)
            );
            continue;
        }

        CostEntry cost;

        if (!parseId(row[0], cost.id))
        {
            result.errors.push_back(
                QString("Row %1: invalid cost id.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (!parseId(row[1], cost.projectId))
        {
            result.errors.push_back(
                QString("Row %1: invalid project id.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (!row[2].trimmed().isEmpty())
        {
            std::int64_t taskId = 0;

            if (!parseId(row[2], taskId))
            {
                result.errors.push_back(
                    QString("Row %1: invalid task id.")
                        .arg(rowNumber)
                );
                continue;
            }

            cost.taskId = taskId;
        }

        const QString category =
            row[3].trimmed().toLower();

        if (!validCostCategory(category))
        {
            result.errors.push_back(
                QString("Row %1: invalid cost category.")
                    .arg(rowNumber)
            );
            continue;
        }

        cost.category = category.toStdString();
        cost.description = row[4].toStdString();

        if (!parsePositiveDouble(row[5], cost.amount))
        {
            result.errors.push_back(
                QString("Row %1: invalid cost amount.")
                    .arg(rowNumber)
            );
            continue;
        }

        cost.entryDate = row[6].toStdString();

        result.objects.push_back(cost);
    }

    return result;
}

CsvImporter::ImportResult<Incident>
CsvImporter::importIncidents(const QString& filePath)
{
    ImportResult<Incident> result;

    QString validationError;

    if (!validateCsvFile(filePath, validationError))
    {
        result.errors.push_back(validationError);
        return result;
    }

    const auto parsed = CsvParser::parseFile(filePath);

    if (!parsed.success())
    {
        result.errors.push_back(parsed.error);
        return result;
    }

    if (parsed.rows.empty())
    {
        result.errors.push_back("Incident CSV is empty.");
        return result;
    }

    const QStringList expectedHeader {
        "id",
        "project_id",
        "task_id",
        "worker_id",
        "title",
        "description",
        "incident_type",
        "severity",
        "incident_date",
        "resolved",
        "resolution_notes"
    };

    if (parsed.rows.front() != expectedHeader)
    {
        result.errors.push_back(
            "Invalid incident CSV header."
        );
        return result;
    }

    for (
        std::size_t index = 1;
        index < parsed.rows.size();
        ++index
    )
    {
        const auto& row = parsed.rows[index];

        const int rowNumber =
            static_cast<int>(index + 1);

        if (row.size() != expectedHeader.size())
        {
            result.errors.push_back(
                QString("Row %1: incorrect number of incident fields.")
                    .arg(rowNumber)
            );
            continue;
        }

        Incident incident;

        if (!parseId(row[0], incident.id))
        {
            result.errors.push_back(
                QString("Row %1: invalid incident id.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (!parseId(row[1], incident.projectId))
        {
            result.errors.push_back(
                QString("Row %1: invalid project id.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (!row[2].trimmed().isEmpty())
        {
            std::int64_t taskId = 0;

            if (!parseId(row[2], taskId))
            {
                result.errors.push_back(
                    QString("Row %1: invalid task id.")
                        .arg(rowNumber)
                );
                continue;
            }

            incident.taskId = taskId;
        }

        if (!row[3].trimmed().isEmpty())
        {
            std::int64_t workerId = 0;

            if (!parseId(row[3], workerId))
            {
                result.errors.push_back(
                    QString("Row %1: invalid worker id.")
                        .arg(rowNumber)
                );
                continue;
            }

            incident.workerId = workerId;
        }

        if (row[4].trimmed().isEmpty())
        {
            result.errors.push_back(
                QString("Row %1: incident title is required.")
                    .arg(rowNumber)
            );
            continue;
        }

        if (row[5].trimmed().isEmpty())
        {
            result.errors.push_back(
                QString("Row %1: incident description is required.")
                    .arg(rowNumber)
            );
            continue;
        }

        incident.title = row[4].toStdString();
        incident.description = row[5].toStdString();

        const QString type =
            row[6].trimmed().toLower();

        if (!validIncidentType(type))
        {
            result.errors.push_back(
                QString("Row %1: invalid incident type.")
                    .arg(rowNumber)
            );
            continue;
        }

        incident.type = type.toStdString();

        const QString severity =
            row[7].trimmed().toLower();

        if (!validSeverity(severity))
        {
            result.errors.push_back(
                QString("Row %1: invalid incident severity.")
                    .arg(rowNumber)
            );
            continue;
        }

        incident.severity = severity.toStdString();

        incident.incidentDate =
            row[8].toStdString();

        if (!parseBoolean(row[9], incident.resolved))
        {
            result.errors.push_back(
                QString("Row %1: invalid resolved value.")
                    .arg(rowNumber)
            );
            continue;
        }

        incident.resolutionNotes =
            row[10].toStdString();

        result.objects.push_back(incident);
    }

    return result;
}

} 
