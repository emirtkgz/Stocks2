#include "StockData.hpp"

#include <yfinance/hpp/base.h>
#include <yfinance/hpp/symbols.h>

#include <memory>

#include <QDebug>

qreal StockData::getCurrentPrice(const std::string& code) {
    // Create a ticker object
    auto tk = std::make_unique<yfinance::Symbol>(code);

    // Loading quotes into struct:
    auto quoteSummary = tk->get_summary("price");

    return quoteSummary["regularMarketPrice"]["raw"];
}

std::unordered_map<std::string, qreal> StockData::getCurrentPrices(const std::vector<std::string>& codes) {
    yfinance::Symbols symbols(codes);

    auto quoteSummaries = symbols.get_summaries("price");

    std::unordered_map<std::string, qreal> data;
    for(size_t i = 0; i < quoteSummaries.size(); i++) {
        // Fetch the code and price from json
        const std::string& code  = quoteSummaries[i]["symbol"];
        qreal              price = quoteSummaries[i]["regularMarketPrice"]["raw"];

        data.insert({code, price});
    }

    return data;
}

std::unordered_map<std::string, qreal> StockData::getCurrentPrices(const nlohmann::json& portfolio) {
    std::vector<std::string> codes;

    for(const auto& entry: portfolio) {
        codes.push_back(entry["name"]);
    }

    return getCurrentPrices(codes);
}
