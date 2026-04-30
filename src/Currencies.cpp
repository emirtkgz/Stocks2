#include "Currencies.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

using json = nlohmann::json;

std::unique_ptr<const nlohmann::json> _Currencies::json_object;

_Currencies::_Currencies() {
    std::ifstream fs("./data/currencies.json");

    json_object = std::make_unique<json>(json::parse(fs));
}

const nlohmann::json& _Currencies::getInstance() {
    static _Currencies instance;

    return *json_object;
}


