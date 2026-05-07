#pragma once

#include <ctime>
#include <cctype>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace StUtils {
    static time_t periodToSeconds(const std::string& period) {
        // Find where value ends and unit starts
        size_t unit_start = 0;

        while(std::isdigit(period[unit_start]))
            unit_start++;

        uint_fast32_t value = std::stoull(period.substr(0, unit_start));

        static const std::unordered_map<std::string, time_t> unitMap = {
            {"s",  1LL},
            {"m",  60LL},
            {"h",  3600LL},
            {"d",  86400LL},
            {"wk", 604800LL},
            {"mo", 2592000LL},
            {"y",  31536000LL}
        };

        // Find the corresponding seconds
        auto it = unitMap.find(period.substr(unit_start));
        if(it == unitMap.end())
            throw std::invalid_argument("Given interval is invalid!");

        return value * it->second;
    }
}
