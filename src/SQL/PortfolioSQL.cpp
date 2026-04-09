#include "PortfolioSQL.hpp"

#include <pqxx/pqxx>

#include <QtDebug>

using json = nlohmann::json;

void PortfolioSQL::upsert(std::string_view username, std::string_view json_data) {
    try {
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

nlohmann::json PortfolioSQL::query(std::string_view username) {
    try {
        pqxx::work tx{*connection};

        pqxx::row row = tx.exec("SELECT \"Data\" FROM \"Portfolios\" WHERE \"Username\" = $1",
            pqxx::params(username)
        ).one_row();

        tx.commit();

        return json::parse(row[0].c_str());

    } catch (std::exception exception) {
        qWarning() << "Warning: Failed to query database Portfolio (" << exception.what() << ")";
        return json();
    }
}

