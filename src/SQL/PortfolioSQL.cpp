#include "PortfolioSQL.hpp"

#include <yfinance/hpp/symbols.h>

#include <pqxx/pqxx>

#include <QtDebug>

using json = nlohmann::json;

// Thread Safe
void PortfolioSQL::upsert(std::string_view username, std::string_view json_data) {
    try {
        // Lock the connection so multiple threads won't try to access it at the same time
        std::unique_lock<std::mutex> lock(mutex);

        pqxx::work tx{*connection};

        tx.exec("INSERT INTO \"Portfolios\" (\"Username\", \"Data\") VALUES ($1, $2) \
                ON CONFLICT (\"Username\")                                           \
                DO UPDATE SET                                                        \
                \"Data\" = $2",

            pqxx::params(username, json_data)
        );

        tx.commit();

    } catch(std::exception exception) {
        qWarning() << "Warning: Failed to upsert database Portfolio (" << exception.what() << ")";
    }
}

// Thread Safe
nlohmann::json PortfolioSQL::query(std::string_view username) {
    try {
        pqxx::row row;
        {
            // Lock the connection so multiple threads won't try to access it at the same time
            std::unique_lock<std::mutex> lock(mutex);

            pqxx::work tx{*connection};

            row = tx.exec("SELECT \"Data\" FROM \"Portfolios\" WHERE \"Username\" = $1",
                          pqxx::params(username)
                  ).one_row();

            tx.commit();
        }

        return json::parse(row[0].c_str());

    } catch (std::exception exception) {
        qWarning() << "Warning: Failed to query database Portfolio (" << exception.what() << ")";
        return json();
    }
}

nlohmann::json PortfolioSQL::updateLastPrice(std::string_view username) {
    // Get the current portfolio json
    json portfolio = query(username);

    std::vector<std::string> codes;
    // Get the symbol codes into a vector
    for(auto& entry : portfolio) {
        codes.push_back(entry["name"]);
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
    upsert(username, portfolio.dump());

    // Return the json for further use
    return portfolio;
}

