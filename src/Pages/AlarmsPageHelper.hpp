#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QStandardItemModel>

enum AlarmTypes {
    Cross              = 0,
    CrossUp            = 1,
    CrossDown          = 2,
    ChangeDaily        = 3,
    ChangeDailyPercent = 4
};

class AlarmsPageHelper : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QStandardItemModel* alarmsList READ alarmsList)
public:
    explicit AlarmsPageHelper(QObject* parent = nullptr);

    // ~~ Q_PROPERTY Setters/Getters ~~
    QStandardItemModel* alarmsList() const;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public slots:
    void updateAlarmsList();
    void postNewAlarm(QJSValue data);
private:
    QStandardItemModel* m_alarmsList = nullptr;
};
