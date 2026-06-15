#pragma once

#include <QVariant>
#include <nlohmann/json.hpp>

/*
 * A recursive function to convert nlohmann::json object to QVariant
 * Can be used in cases where a nlohmann::json object is needed to be parsed
 * into qml without string serialization/deserialization
*/
QVariant nlohmannToQVariant(const nlohmann::json& j) {
    switch (j.type()) {
    case nlohmann::json::value_t::object: {
        QVariantMap map;
        for (auto& [key, val] : j.items())
            map[QString::fromStdString(key)] = nlohmannToQVariant(val);
        return map;
    }
    case nlohmann::json::value_t::array: {
        QVariantList list;
        for (const auto& val : j)
            list.append(nlohmannToQVariant(val));
        return list;
    }
    case nlohmann::json::value_t::string:
        return QString::fromStdString(j.get<std::string>());
    case nlohmann::json::value_t::number_integer:
        return QVariant(j.get<int64_t>());
    case nlohmann::json::value_t::number_unsigned:
        return QVariant(j.get<uint64_t>());
    case nlohmann::json::value_t::number_float:
        return QVariant(j.get<double>());
    case nlohmann::json::value_t::boolean:
        return QVariant(j.get<bool>());
    case nlohmann::json::value_t::null:
    default:
        return QVariant();
    }
}
