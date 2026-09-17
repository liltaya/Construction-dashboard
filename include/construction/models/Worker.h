#pragma once

#include <cstdint>
#include <string>

namespace construction {

struct Worker
{
    std::int64_t id = 0;

    std::string firstName;
    std::string lastName;

    std::string email;
    std::string phone;

    std::string role;

    double hourlyRate = 0.0;

    bool active = true;
};

}
