#pragma once

#include "construction/models/CostEntry.h"
#include "construction/models/Project.h"
#include "construction/models/Task.h"
#include "construction/models/WorkLog.h"

#include <QDate>

#include <cstddef>
#include <vector>

namespace construction {

struct ProjectAnalytics
{
    double budget = 0.0;
    double actualCost = 0.0;
    double budgetVariance = 0.0;

    double completionPercent = 0.0;

    std::size_t overdueTasks = 0;

    double plannedCompletionPercent = 0.0;
    double scheduleVariance = 0.0;

    double laborHours = 0.0;
};

class AnalyticsEngine
{
public:
    static ProjectAnalytics calculate(
        const Project& project,
        const std::vector<Task>& tasks,
        const std::vector<CostEntry>& costs,
        const std::vector<WorkLog>& workLogs,
        const QDate& currentDate = QDate::currentDate()
    );

private:
    static double calculateCompletion(
        const std::vector<Task>& tasks
    );

    static std::size_t calculateOverdueTasks(
        const std::vector<Task>& tasks,
        const QDate& currentDate
    );

    static double calculatePlannedCompletion(
        const Project& project,
        const QDate& currentDate
    );
};

}

