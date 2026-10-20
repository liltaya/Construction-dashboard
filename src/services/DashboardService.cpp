#include "construction/services/DashboardService.h"

#include <stdexcept>

namespace construction {

DashboardService::DashboardService(
    ConstructionRepository& repository
)
    : repository_(repository)
{
}

void DashboardService::createProject(
    const Project& project
)
{
    repository_.insertProject(project);
}

void DashboardService::updateProject(
    const Project& project
)
{
    repository_.updateProject(project);
}

void DashboardService::createTask(
    const Task& task
)
{
    repository_.insertTask(task);
}

void DashboardService::updateTask(
    const Task& task
)
{
    repository_.updateTask(task);
}

void DashboardService::createWorker(
    const Worker& worker
)
{
    repository_.insertWorker(worker);
}

void DashboardService::addCostEntry(
    const CostEntry& entry
)
{
    repository_.insertCostEntry(entry);
}

void DashboardService::addWorkLog(
    const WorkLog& workLog
)
{
    repository_.insertWorkLog(workLog);
}

std::optional<Project>
DashboardService::getProject(
    std::int64_t projectId
)
{
    return repository_.findProjectById(
        projectId
    );
}

std::vector<Project>
DashboardService::getProjects()
{
    return repository_.findAllProjects();
}

ProjectAnalytics
DashboardService::getProjectAnalytics(
    std::int64_t projectId,
    const QDate& currentDate
)
{
    const auto project =
        repository_.findProjectById(
            projectId
        );

    if (!project.has_value())
    {
        throw std::runtime_error(
            "Project not found."
        );
    }

    const auto tasks =
        repository_.findTasksByProject(
            projectId
        );

    const auto costs =
        repository_.findCostsByProject(
            projectId
        );

    const auto workLogs =
        repository_.findWorkLogsByProject(
            projectId
        );

    return AnalyticsEngine::calculate(
        *project,
        tasks,
        costs,
        workLogs,
        currentDate
    );
}

}
