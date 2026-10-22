#include "construction/analytics/AnalyticsEngine.h"

#include <gtest/gtest.h>
#include <QDate>

using namespace construction;

TEST(AnalyticsTest, BudgetVariance)
{
    Project project;

    project.budget = 1000000.0;
    project.startDate = "2026-01-01";
    project.endDate = "2026-12-31";

    CostEntry cost1;
    cost1.amount = 150000.0;

    CostEntry cost2;
    cost2.amount = 25000.0;

    const auto result = AnalyticsEngine::calculate(
        project,
        {},
        {cost1, cost2},
        {},
        QDate(2026, 7, 1)
    );

    EXPECT_DOUBLE_EQ(result.actualCost, 175000.0);
    EXPECT_DOUBLE_EQ(result.budgetVariance, 825000.0);
}

TEST(AnalyticsTest, CompletionPercentage)
{
    Project project;

    Task task1;
    task1.status = "completed";

    Task task2;
    task2.status = "in_progress";

    const auto result = AnalyticsEngine::calculate(
        project,
        {task1, task2},
        {},
        {},
        QDate(2026, 7, 1)
    );

    EXPECT_DOUBLE_EQ(result.completionPercent, 50.0);
}

TEST(AnalyticsTest, OverdueTasks)
{
    Project project;

    Task task1;
    task1.status = "in_progress";
    task1.dueDate = "2026-03-01";

    Task task2;
    task2.status = "completed";
    task2.dueDate = "2026-02-01";

    const auto result = AnalyticsEngine::calculate(
        project,
        {task1, task2},
        {},
        {},
        QDate(2026, 7, 1)
    );

    EXPECT_EQ(result.overdueTasks, 1);
}

TEST(AnalyticsTest, LaborHours)
{
    Project project;

    WorkLog first;
    first.hours = 8.0;

    WorkLog second;
    second.hours = 7.5;

    const auto result = AnalyticsEngine::calculate(
        project,
        {},
        {},
        {first, second},
        QDate(2026, 7, 1)
    );

    EXPECT_DOUBLE_EQ(result.laborHours, 15.5);
}

TEST(AnalyticsTest, EmptyData)
{
    Project project;
    project.budget = 500000.0;

    const auto result = AnalyticsEngine::calculate(
        project,
        {},
        {},
        {},
        QDate(2026, 7, 1)
    );

    EXPECT_DOUBLE_EQ(result.actualCost, 0.0);
    EXPECT_DOUBLE_EQ(result.completionPercent, 0.0);
    EXPECT_EQ(result.overdueTasks, 0);
    EXPECT_DOUBLE_EQ(result.laborHours, 0.0);
}
