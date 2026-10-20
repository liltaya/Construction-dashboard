
#include "construction/MainWindow.h"
#include "construction/database/Database.h"
#include "construction/repositories/ConstructionRepository.h"
#include "construction/services/DashboardService.h"

#include <QApplication>
#include <QDebug>
#include <QDate>

#include <optional>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    construction::Database database("construction.db");
    construction::ConstructionRepository repository(database);
    construction::DashboardService service(repository);

    //Set true for the first run only.
    //Change to false after inserting the sample data.
    const bool seedDemoData = false;

    if (seedDemoData)
    {
        //ADD TASKS

        construction::Task task1;
        task1.id = 1;
        task1.projectId = 1;
        task1.name = "Foundation";
        task1.description = "Complete foundation";
        task1.status = "completed";
        task1.priority = "high";
        task1.startDate = "2026-01-01";
        task1.dueDate = "2026-03-01";
        task1.completedAt = "2026-02-25";
        task1.estimatedCost = 200000.0;

        service.createTask(task1);

        construction::Task task2;
        task2.id = 2;
        task2.projectId = 1;
        task2.name = "Framing";
        task2.description = "Structural framing";
        task2.status = "in_progress";
        task2.priority = "high";
        task2.startDate = "2026-03-01";
        task2.dueDate = "2026-06-01";
        task2.completedAt = "";
        task2.estimatedCost = 300000.0;

        service.createTask(task2);

        //ADD COSTS

        construction::CostEntry cost1;
        cost1.id = 1;
        cost1.projectId = 1;
        cost1.taskId = 1;
        cost1.category = "materials";
        cost1.description = "Concrete";
        cost1.amount = 150000.0;
        cost1.entryDate = "2026-02-10";

        service.addCostEntry(cost1);

        construction::CostEntry cost2;
        cost2.id = 2;
        cost2.projectId = 1;
        cost2.taskId = std::nullopt;
        cost2.category = "permit";
        cost2.description = "Building permit";
        cost2.amount = 25000.0;
        cost2.entryDate = "2026-01-10";

        service.addCostEntry(cost2);

        //ADD WORKER

        construction::Worker worker;
        worker.id = 1;
        worker.firstName = "John";
        worker.lastName = "Smith";
        worker.email = "john@test.com";
        worker.phone = "604-555-1234";
        worker.role = "Carpenter";
        worker.hourlyRate = 42.0;
        worker.active = true;

        service.createWorker(worker);

        //ADD LABOR HOURS

        construction::WorkLog log1;
        log1.id = 1;
        log1.projectId = 1;
        log1.workerId = 1;
        log1.hours = 8.0;
        log1.workDate = "2026-05-01";

        service.addWorkLog(log1);

        construction::WorkLog log2;
        log2.id = 2;
        log2.projectId = 1;
        log2.workerId = 1;
        log2.hours = 7.5;
        log2.workDate = "2026-05-02";

        service.addWorkLog(log2);

        qDebug() << "Sample data inserted successfully!";
    }

    //RUN ANALYTICS

    const auto analytics =
        service.getProjectAnalytics(
            1,
            QDate(2026, 7, 1)
        );

    qDebug() << "----------------------------";
    qDebug() << "PROJECT ANALYTICS";
    qDebug() << "----------------------------";

    qDebug() << "Budget:"
             << analytics.budget;

    qDebug() << "Actual cost:"
             << analytics.actualCost;

    qDebug() << "Budget variance:"
             << analytics.budgetVariance;

    qDebug() << "Completion:"
             << analytics.completionPercent << "%";

    qDebug() << "Overdue tasks:"
             << analytics.overdueTasks;

    qDebug() << "Planned completion:"
             << analytics.plannedCompletionPercent << "%";

    qDebug() << "Schedule variance:"
             << analytics.scheduleVariance;

    qDebug() << "Labor hours:"
             << analytics.laborHours;

    //Open dashboard window
    construction::MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
