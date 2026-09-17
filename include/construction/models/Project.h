#pragma once

#include <cstdint>
#include <string>

namespace construction {

struct Project
{
    std::int64_t id = 0;

    std::string name;
    std::string description;
    std::string location;

    std::string startDate;
    std::string endDate;

    std::string status = "planned";

    double budget = 0.0;
};

} // namespace construction
