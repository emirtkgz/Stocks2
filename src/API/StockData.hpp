#pragma once

#include <QtNumeric>

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <unordered_map>

namespace StockData {

    // Uses Yahoo Finance API to fetch data
    qreal getCurrentPrice(const std::string& code);
    // Use multi threaded approach to get data
    std::unordered_map<std::string, qreal> getCurrentPrices(const std::vector<std::string>& codes);
    std::unordered_map<std::string, qreal> getCurrentPrices(const nlohmann::json& portfolio);

}
