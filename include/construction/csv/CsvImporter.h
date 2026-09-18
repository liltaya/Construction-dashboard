#pragma once

#include "construction/models/CostEntry.h"
#include "construction/models/Incident.h"
#include "construction/models/Project.h"
#include "construction/models/Task.h"
#include "construction/models/Worker.h"

#include <QString>

#include <vector>

namespace construction {

class CsvImporter
{
public:
    template <typename T>
    struct ImportResult
    {
        std::vector<T> objects;
        std::vector<QString> errors;

        bool success() const
        {
            return errors.empty();
        }
    };

    static ImportResult<Project>
    importProjects(const QString& filePath);

    static ImportResult<Task>
    importTasks(const QString& filePath);

    static ImportResult<Worker>
    importWorkers(const QString& filePath);

    static ImportResult<CostEntry>
    importCostEntries(const QString& filePath);

    static ImportResult<Incident>
    importIncidents(const QString& filePath);
};

}
