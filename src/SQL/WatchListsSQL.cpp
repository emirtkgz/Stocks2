#include "WatchListsSQL.hpp"

#include <QDebug>

using json = nlohmann::json;

void WatchListsSQL::upsert(std::string_view username, std::string_view json_data) {
    upsertJSON(username, json_data,
                "INSERT INTO \"WatchLists\" (\"Username\", \"Data\") VALUES ($1, $2) \
                ON CONFLICT (\"Username\")                                           \
                DO UPDATE SET                                                        \
                \"Data\" = $2"
    );
}

nlohmann::json WatchListsSQL::query(std::string_view username) {
    return queryJSON(username, "SELECT \"Data\" FROM \"WatchLists\" WHERE \"Username\" = $1");
}
