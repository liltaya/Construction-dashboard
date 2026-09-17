#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace construction {

struct Incident
{
    std::int64_t id = 0;

    std::int64_t projectId = 0;

    std::optional<std::int64_t> taskId;
    std::optional<std::int64_t> workerId;

    std::string title;
    std::string description;

    std::string type;
    std::string severity;

    std::string incidentDate;

    bool resolved = false;

    std::string resolutionNotes;
};

} 
