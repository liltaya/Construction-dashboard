#pragma once

#include <cstdint>
#include <string>

namespace construction {

struct WorkLog
{
    std::int64_t id = 0;
    std::int64_t projectId = 0;
    std::int64_t workerId = 0;

    double hours = 0.0;

    std::string workDate;
};

}
