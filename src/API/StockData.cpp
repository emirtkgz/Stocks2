#include "StockData.hpp"

#include <yfinance/base.h>

#include <memory>

qreal StockData::getCurrentPrice(const std::string& code) {
    // Create a ticker object
    auto tk = std::make_unique<yfinance::Symbol>(code);

    // Loading quotes into struct:
    auto quoteSummary = tk->get_summary("financialData");

    return quoteSummary["currentPrice"]["raw"];
}
