#pragma once

#include <QtQmlTypeRegistrar/QtQmlTypeRegistrar>

#include "Package.hpp"

// --- Types ---
#include "Pages/BrowsePageHelper.hpp"
#include "PortfolioPageHelper.hpp"
// -------------

#define ST_QML_REGISTER_TYPE(Type, Name) \
    qmlRegisterType<Type>(StPackage::name, StPackage::majorVersion, StPackage::minorVersion, Name)

#define ST_QML_REGISTER_SINGLETON_INSTANCE(Type, Name, Instance) \
    qmlRegisterSingletonInstance<Type>(StPackage::name, StPackage::majorVersion, StPackage::minorVersion, Name, Instance)

inline void registerQMLTypes() {
    ST_QML_REGISTER_TYPE(PortfolioPageHelper, "PortfolioPageHelper");
    ST_QML_REGISTER_TYPE(BrowsePageHelper,    "BrowsePageHelper");
}
