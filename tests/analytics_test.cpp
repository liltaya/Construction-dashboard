#include "construction/analytics/AnalyticsEngine.h"

#include <gtest/gtest.h>

TEST(AnalyticsEngineTest, CalculatesMetrics)
{
    construction::Project project;

    project.id = 1;
    project.startDate = "2026-01-01";
    project.endDate = "2026-12-31";
    project.budget = 1000000.0;

    //First task: completed
    construction::Task task1;

    task1.id = 1;
    task1.projectId = 1;
    task1.status = "completed";
    task1.dueDate = "2026-03-01";

    //Second task: in progress and overdue
    construction::Task task2;

    task2.id = 2;
    task2.projectId = 1;
    task2.status = "in_progress";
    task2.dueDate = "2026-04-01";

    std::vector<construction::Task> tasks{
        task1,
        task2
    };

    //Project cost
    construction::CostEntry cost;

    cost.id = 1;
    cost.projectId = 1;
    cost.amount = 250000.0;

    std::vector<construction::CostEntry> costs{
        cost
    };

    //Labor hours
    construction::WorkLog log;

    log.id = 1;
    log.projectId = 1;
    log.workerId = 1;
    log.hours = 40.0;

    std::vector<construction::WorkLog> workLogs{
        log
    };

    //Calculate all analytics
    const auto analytics =
        construction::AnalyticsEngine::calculate(
            project,
            tasks,
            costs,
            workLogs,
            QDate(2026, 7, 1)
        );

    //Verify actual cost
    EXPECT_DOUBLE_EQ(
        analytics.actualCost,
        250000.0
    );

    //Verify budget variance
    EXPECT_DOUBLE_EQ(
        analytics.budgetVariance,
        750000.0
    );

    //Verify completion percentage
    EXPECT_DOUBLE_EQ(
        analytics.completionPercent,
        50.0
    );

    //Verify overdue tasks
    EXPECT_EQ(
        analytics.overdueTasks,
        1
    );

    //Verify labor hours
    EXPECT_DOUBLE_EQ(
        analytics.laborHours,
        40.0
    );

    //Verify planned completion
    EXPECT_NEAR(
        analytics.plannedCompletionPercent,
        49.7,
        0.1
    );

    //Verify schedule variance
    EXPECT_NEAR(
        analytics.scheduleVariance,
        0.3,
        0.1
    );
}
