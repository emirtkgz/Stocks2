#pragma once

#include "SQL.hpp"

#include <string_view>

#include <nlohmann/json.hpp>

class PortfolioSQL : public SQL {
public:
    static void upsert(std::string_view username, std::string_view json_data);
    static nlohmann::json query(std::string_view username);
};

