#include "Currencies.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

using json = nlohmann::json;

std::unique_ptr<const nlohmann::json> Currencies::json_object;

Currencies::Currencies() {
    std::ifstream fs("./data/currencies.json");

    json_object = std::make_unique<json>(json::parse(fs));
}

const nlohmann::json& Currencies::getInstance() {
    static Currencies instance;

    return *json_object;
}


