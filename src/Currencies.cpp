#include "Currencies.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::unique_ptr<const nlohmann::json> Currencies::json_object;

Currencies::Currencies() {
    json_object = std::make_unique<json>("./data/currencies.json");
}

const nlohmann::json& Currencies::getInstance() {
    static Currencies instance;

    return *json_object;
}


