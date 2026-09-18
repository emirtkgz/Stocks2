#pragma once

#include "Utils/Worker.hpp"

#include <nlohmann/json.hpp>

#include <QQmlApplicationEngine>
#include <QSystemTrayIcon>

#include <memory>

#ifndef ST_ALARM_CHECKER_FREQ
#define ST_ALARM_CHECKER_FREQ 30s
#endif

class AlarmChecker : public QObject {
    Q_OBJECT
public:
    AlarmChecker(QQmlApplicationEngine* engine);

    void getAlarmList();
    nlohmann::json fetchPrices();
public slots:
    void showNotification(const QString& title, const QString& message);
private:
    std::unique_ptr<Worker> worker;

    nlohmann::json alarm_list;
    nlohmann::json price_list;
    time_t last_updated;

    QQmlApplicationEngine* engine;
    QSystemTrayIcon* notification;
};
