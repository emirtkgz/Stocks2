#include "AlarmsPageHelper.hpp"

#include <nlohmann/json.hpp>

#include "API/ServerAPI.hpp"
#include "Utils/JSON.hpp"

using json = nlohmann::json;

enum AlarmListRoles {
    Code    = Qt::UserRole + 1,
    Type    = Qt::UserRole + 2,
    Value   = Qt::UserRole + 3,
    Message = Qt::UserRole + 4,
    IsOn    = Qt::UserRole + 5
};

AlarmsPageHelper::AlarmsPageHelper(QObject *parent)
    : QObject{parent}
{
    m_alarmsList = new QStandardItemModel();
    m_alarmsList->setItemRoleNames({
        {AlarmListRoles::Code,    "code"},
        {AlarmListRoles::Type,    "type"},
        {AlarmListRoles::Value,   "value"},
        {AlarmListRoles::Message, "message"},
        {AlarmListRoles::IsOn,    "is_on"}
    });
}

void AlarmsPageHelper::updateAlarmsList() {
    json list_json = ServerAPI.get("api/alarms/data");
    if(ServerAPI.checkErrors(list_json))
        return;

    // Clear the previous list data
    m_alarmsList->clear();

    for(auto& entry : list_json["Data"]) {
        QStandardItem* item = new QStandardItem();

        item->setData(QString::fromStdString(entry["code"]), Code);
        item->setData(qreal(entry["type"]), Type);
        item->setData(qreal(entry["value"]), Value);
        item->setData(QString::fromStdString(entry["message"]), Message);
        item->setData(bool(entry["is_on"]), IsOn);

        m_alarmsList->appendRow(item);
    }
}

void AlarmsPageHelper::postNewAlarm(QJSValue data) {
    auto string_data = qjsvalueToNlohmann(data).dump();

    ServerAPI.post("api/alarms/data", cpr::Body{string_data});
    updateAlarmsList();
}

// ~~ Q_PROPERTY Setters/Getters ~~
QStandardItemModel* AlarmsPageHelper::alarmsList() const {
    return m_alarmsList;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
