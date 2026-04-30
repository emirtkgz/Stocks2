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

void PortfolioSQL::set(std::string_view username, std::string_view json_data) {
    try {
        // Lock the connection so multiple threads won't try to access it at the same time
        std::unique_lock<std::mutex> lock(mutex);

        pqxx::work tx{*connection};

        tx.exec("UPDATE \"Portfolios\"        \
                SET \"Data\" = \"Data\" || $2 \
                WHERE \"Username\" = $1",

            pqxx::params(username, json_data)
        );

        tx.commit();
    } catch (std::exception exception) {
        qWarning() << "Warning: Failed to set element to database Portfolio (" << exception.what() << ")";
    }
}

void PortfolioSQL::remove(std::string_view username, intmax_t index) {
    try {
        // Lock the connection so multiple threads won't try to access it at the same time
        std::unique_lock<std::mutex> lock(mutex);

        pqxx::work tx{*connection};

        tx.exec("UPDATE \"Portfolios\"            \
                SET \"Data\" = \"Data\" - $2::int \
                WHERE \"Username\" = $1",

                pqxx::params(username, index)
        );

        tx.commit();
    } catch (std::exception exception) {
        qWarning() << "Warning: Failed to remove element at index" << index << "in database Portfolio (" << exception.what() << ")";
    }
}


