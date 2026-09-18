#include "AlarmsPageHelper.hpp"

#include <nlohmann/json.hpp>

#include "API/ServerAPI.hpp"
#include "Utils/JSON.hpp"

using json = nlohmann::json;

enum AlarmListRoles {
    Ticker  = Qt::UserRole + 1,
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
        {AlarmListRoles::Ticker,  "ticker"},
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

    for(auto& entry : list_json["data"]) {
        QStandardItem* item = new QStandardItem();

        item->setData(QString::fromStdString(entry["Ticker"]), Ticker);
        item->setData(qreal(entry["Type"]), Type);
        item->setData(QString::fromStdString(entry["Value"]).toDouble(), Value);
        item->setData(QString::fromStdString(entry["Message"]), Message);
        item->setData(bool(entry["IsOn"]), IsOn);

        m_alarmsList->appendRow(item);
    }
}

void AlarmsPageHelper::postNewAlarm(QJSValue data) {
    auto json_data = qjsvalueToNlohmann(data);

    ServerAPI.post("api/alarms/data", cpr::Body{json_data.dump()});
    updateAlarmsList();
}

// ~~ Q_PROPERTY Setters/Getters ~~
QStandardItemModel* AlarmsPageHelper::alarmsList() const {
    return m_alarmsList;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
