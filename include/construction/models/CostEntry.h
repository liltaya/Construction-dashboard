#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace construction {

struct CostEntry
{
    std::int64_t id = 0;

    std::int64_t projectId = 0;
    std::optional<std::int64_t> taskId;

    std::string category;
    std::string description;

    double amount = 0.0;

    std::string entryDate;
};

}
