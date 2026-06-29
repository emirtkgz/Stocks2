#pragma once

#include <QVariant>
#include <QJSValue>
#include <QJSValueIterator>

#include <nlohmann/json.hpp>

/*
 * A recursive function to convert nlohmann::json object to QVariant
 * Can be used in cases where a nlohmann::json object is needed to be parsed
 * into qml without string serialization/deserialization
*/
static QVariant nlohmannToQVariant(const nlohmann::json& j) {
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

/*
 * Same as before but in reverse
*/
static nlohmann::json qvariantToNlohmann(const QVariant& v) {
    switch (v.typeId()) {
    case QMetaType::QVariantMap: {
        nlohmann::json obj = nlohmann::json::object();
        const QVariantMap map = v.toMap();
        for (auto it = map.begin(); it != map.end(); ++it)
            obj[it.key().toStdString()] = qvariantToNlohmann(it.value());
        return obj;
    }
    case QMetaType::QVariantList: {
        nlohmann::json arr = nlohmann::json::array();
        for (const QVariant& item : v.toList())
            arr.push_back(qvariantToNlohmann(item));
        return arr;
    }
    case QMetaType::QString:
        return v.toString().toStdString();
    case QMetaType::Int:
    case QMetaType::Long:
    case QMetaType::LongLong:
        return v.toLongLong();
    case QMetaType::UInt:
    case QMetaType::ULong:
    case QMetaType::ULongLong:
        return v.toULongLong();
    case QMetaType::Double:
    case QMetaType::Float:
        return v.toDouble();
    case QMetaType::Bool:
        return v.toBool();
    case QMetaType::UnknownType:
    default:
        return nullptr;
    }
}

static nlohmann::json qjsvalueToNlohmann(const QJSValue& v) {
    if (v.isNull() || v.isUndefined())
        return nullptr;
    if (v.isBool())
        return v.toBool();
    if (v.isNumber())
        return v.toNumber();
    if (v.isString())
        return v.toString().toStdString();
    if (v.isArray()) {
        nlohmann::json arr = nlohmann::json::array();
        int length = v.property("length").toInt();
        for (int i = 0; i < length; ++i)
            arr.push_back(qjsvalueToNlohmann(v.property(i)));
        return arr;
    }
    if (v.isObject()) {
        nlohmann::json obj = nlohmann::json::object();
        QJSValueIterator it(v);
        while (it.hasNext()) {
            it.next();
            obj[it.name().toStdString()] = qjsvalueToNlohmann(it.value());
        }
        return obj;
    }
    return nullptr;
}
