#pragma once

#include <QObject>
#include <QQmlEngine>

class BackendHelper : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    BackendHelper();
};

