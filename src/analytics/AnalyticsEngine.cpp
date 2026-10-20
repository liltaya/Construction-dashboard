#include "construction/analytics/AnalyticsEngine.h"

#include <algorithm>
#include <numeric>

namespace construction {

ProjectAnalytics AnalyticsEngine::calculate(
    const Project& project,
    const std::vector<Task>& tasks,
    const std::vector<CostEntry>& costs,
    const std::vector<WorkLog>& workLogs,
    const QDate& currentDate
)
{
    ProjectAnalytics analytics;

    analytics.budget = project.budget;

    analytics.actualCost =
        std::accumulate(
            costs.begin(),
            costs.end(),
            0.0,
            [](double total, const CostEntry& entry)
            {
                return total + entry.amount;
            }
        );

    analytics.budgetVariance =
        analytics.budget -
        analytics.actualCost;

    analytics.completionPercent =
        calculateCompletion(tasks);

    analytics.overdueTasks =
        calculateOverdueTasks(
            tasks,
            currentDate
        );

    analytics.plannedCompletionPercent =
        calculatePlannedCompletion(
            project,
            currentDate
        );

    analytics.scheduleVariance =
        analytics.completionPercent -
        analytics.plannedCompletionPercent;

    analytics.laborHours =
        std::accumulate(
            workLogs.begin(),
            workLogs.end(),
            0.0,
            [](double total, const WorkLog& log)
            {
                return total + log.hours;
            }
        );

    return analytics;
}

double AnalyticsEngine::calculateCompletion(
    const std::vector<Task>& tasks
)
{
    if (tasks.empty())
    {
        return 0.0;
    }

    const auto completed =
        std::count_if(
            tasks.begin(),
            tasks.end(),
            [](const Task& task)
            {
                return task.status == "completed";
            }
        );

    return (
        static_cast<double>(completed) /
        static_cast<double>(tasks.size())
    ) * 100.0;
}

std::size_t AnalyticsEngine::calculateOverdueTasks(
    const std::vector<Task>& tasks,
    const QDate& currentDate
)
{
    return static_cast<std::size_t>(
        std::count_if(
            tasks.begin(),
            tasks.end(),
            [&currentDate](const Task& task)
            {
                if (
                    task.status == "completed" ||
                    task.status == "cancelled"
                )
                {
                    return false;
                }

                const QDate dueDate =
                    QDate::fromString(
                        QString::fromStdString(task.dueDate),
                        Qt::ISODate
                    );

                return (
                    dueDate.isValid() &&
                    dueDate < currentDate
                );
            }
        )
    );
}

double AnalyticsEngine::calculatePlannedCompletion(
    const Project& project,
    const QDate& currentDate
)
{
    const QDate startDate =
        QDate::fromString(
            QString::fromStdString(project.startDate),
            Qt::ISODate
        );

    const QDate endDate =
        QDate::fromString(
            QString::fromStdString(project.endDate),
            Qt::ISODate
        );

    if (
        !startDate.isValid() ||
        !endDate.isValid() ||
        endDate <= startDate
    )
    {
        return 0.0;
    }

    if (currentDate <= startDate)
    {
        return 0.0;
    }

    if (currentDate >= endDate)
    {
        return 100.0;
    }

    const qint64 totalDays =
        startDate.daysTo(endDate);

    const qint64 elapsedDays =
        startDate.daysTo(currentDate);

    return (
        static_cast<double>(elapsedDays) /
        static_cast<double>(totalDays)
    ) * 100.0;
}

}
