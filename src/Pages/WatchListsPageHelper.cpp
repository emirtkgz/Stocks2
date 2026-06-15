#include "WatchListsPageHelper.hpp"

#include "SQL/WatchListsSQL.hpp"
#include "Settings.hpp"
#include "Utils/JSON.hpp"

WatchListsPageHelper::WatchListsPageHelper() {}


void WatchListsPageHelper::updateWatchLists() {
    m_watchLists = std::make_unique<QVariantList>(nlohmannToQVariant(WatchListsSQL::query(Settings::username)).toList());
}

// ~~ Q_PROPERTY Setters/Getters ~~
QVariantList* WatchListsPageHelper::watchLists() const {
    return m_watchLists.get();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
