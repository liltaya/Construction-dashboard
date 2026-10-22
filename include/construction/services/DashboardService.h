#pragma once

#include "construction/analytics/AnalyticsEngine.h"
#include "construction/repositories/ConstructionRepository.h"
#include "construction/csv/CsvImporter.h"

#include <cstdint>
#include <optional>
#include <vector>

namespace construction {

class DashboardService
{
public:
    explicit DashboardService(
        ConstructionRepository& repository
    );

    void createProject(const Project& project);
    void updateProject(const Project& project);

    void createTask(const Task& task);
    void updateTask(const Task& task);

    void createWorker(const Worker& worker);

    void addCostEntry(const CostEntry& entry);
    void addWorkLog(const WorkLog& workLog);

    void importProjectsFromCsv(const QString& filePath);

    std::optional<Project>
    getProject(std::int64_t projectId);

    std::vector<Project> getProjects();

    ProjectAnalytics getProjectAnalytics(
        std::int64_t projectId,
        const QDate& currentDate =
        QDate::currentDate()
            
    );

private:
    ConstructionRepository& repository_;
};

}
