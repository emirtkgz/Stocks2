#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QAbstractItemModel>
#include <QStandardItemModel>

#include <memory>

class BrowsePageHelper : public QObject {
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
public:
    BrowsePageHelper();

public slots:
    void uploadSearchModel();


    QAbstractItemModel* getSearchModel();

private:
    std::unique_ptr<QStandardItemModel> searchModel;
};

