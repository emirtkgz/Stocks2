#pragma once

#include <QObject>
#include <QQmlEngine>

#include <memory>

class WatchListsPageHelper : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QVariantList* watchLists READ watchLists FINAL)
public:
    WatchListsPageHelper();

    // ~~ Q_PROPERTY Setters/Getters ~~
    QVariantList* watchLists() const;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public slots:
    void updateWatchLists();
private:
    std::unique_ptr<QVariantList> m_watchLists;
};

