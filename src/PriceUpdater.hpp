#pragma once

#include <QtTypes>

#include <nlohmann/json.hpp>
#include <yfinance/hpp/symbols.h>

#include <string_view>
#include <mutex>

#include "SQL/PortfolioSQL.hpp"
#include "InvestmentType.hpp"

// No need to update bond data for periods of time less than 1 day
#ifndef ST_BOND_UPDATE_FREQ
#define ST_BOND_UPDATE_FREQ 1d
#endif

using namespace std::chrono_literals;

namespace PriceUpdater {
    namespace {
        std::mutex mutex;
    }

    // A function that will update lastPrice of each portfolio element in the database
    nlohmann::json updateLastPrice(std::string_view username) {
        // Lock between query and upsert so no data race
        std::unique_lock lock(mutex);
        // Get the current portfolio json
        nlohmann::json portfolio = PortfolioSQL::query(username);

        std::vector<std::string> codes;
        std::vector<std::string> bonds;

        // Get the symbol codes into 2 vectors (One for bonds and one for the rest)
        for(auto& entry : portfolio) {
            InvestmentType type = entry["type"];
            if(type == InvestmentType::BONDS) {
                bonds.push_back(entry["name"]);
            }
            else {
                codes.push_back(entry["name"]);
            }
        }

        // Get the current price of each symbol
        yfinance::Symbols symbols(codes);
        auto summaries = symbols.get_summaries("price");

        for(auto& summary : summaries) {
            // Skip if symbol could not be fetched
            if(summary.empty())
                continue;

            const std::string& name = summary["symbol"];
            time_t lastUpdated      = summary["regularMarketTime"];
            qreal price             = summary["regularMarketPrice"]["raw"];

            // Update the portfolio object
            for (auto& entry : portfolio) {
                if (entry["name"] == name) {
                    entry["lastPrice"]["price"]       = price;
                    entry["lastPrice"]["lastUpdated"] = lastUpdated;
                    break;
                }
            }
        }

        // Update the database
        PortfolioSQL::upsert(username, portfolio.dump());

        // Return the json for further use
        return portfolio;
    }
}
