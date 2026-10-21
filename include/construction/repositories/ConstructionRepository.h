#pragma once

#include "construction/database/Database.h"
#include "construction/models/CostEntry.h"
#include "construction/models/Project.h"
#include "construction/models/Task.h"
#include "construction/models/Worker.h"
#include "construction/models/WorkLog.h"

#include <cstdint>
#include <optional>
#include <vector>

namespace construction {

class ConstructionRepository
{
public:
    explicit ConstructionRepository(Database& database);

    void insertProject(const Project& project);
    std::optional<Project> findProjectById(std::int64_t id);
    std::vector<Project> findAllProjects();
    void updateProject(const Project& project);

    void insertTask(const Task& task);
    std::vector<Task> findTasksByProject(std::int64_t projectId);
    void updateTask(const Task& task);

    void insertWorker(const Worker& worker);

    void insertCostEntry(const CostEntry& entry);
    std::vector<CostEntry> findCostsByProject(std::int64_t projectId);

    void insertWorkLog(const WorkLog& workLog);
    std::vector<WorkLog> findWorkLogsByProject(std::int64_t projectId);

    std::int64_t countIncidentsByProject(
    std::int64_t projectId);

private:
    Database& database_;
};

}
