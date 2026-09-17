#pragma once

#include <cstdint>
#include <string>

namespace construction {

struct Task
{
    std::int64_t id = 0;
    std::int64_t projectId = 0;

    std::string name;
    std::string description;

    std::string status = "todo";
    std::string priority = "medium";

    std::string startDate;
    std::string dueDate;
    std::string completedAt;

    double estimatedCost = 0.0;
};

}
