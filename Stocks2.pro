QT += quick
QT += charts
QT += gui

CONFIG += c++20
CONFIG += qmltypes

SOURCES += \
        src/API/DataFetchers.cpp \
        src/API/QuoteData.cpp \
        src/API/ServerAPI.cpp \
        src/Lua/LuaAPI.cpp \
        src/Pages/BrowsePageHelper.cpp \
        src/Currencies.cpp \
        src/Pages/PortfolioPageHelper.cpp \
        src/Pages/WatchListsPageHelper.cpp \
        src/SQL/PortfolioSQL.cpp \
        src/SQL/WatchListsSQL.cpp \
        src/Settings.cpp \
        src/main.cpp \
        src/theme.cpp \
        src/SQL/SQL.cpp

HEADERS += \
    src/API/DataFetchers.hpp \
    src/API/DataFetchers.hpp \
    src/API/QuoteData.hpp \
    src/API/ServerAPI.hpp \
    src/Lua/LuaAPI.hpp \
    src/Lua/LuaFunctions.hpp \
    src/Package.hpp \
    src/Pages/BrowsePageHelper.hpp \
    src/Currencies.hpp \
    src/InvestmentType.hpp \
    src/Pages/PortfolioPageHelper.hpp \
    src/Pages/WatchListsPageHelper.hpp \
    src/PriceUpdater.hpp \
    src/SQL/PortfolioSQL.hpp \
    src/SQL/WatchListsSQL.hpp \
    src/Settings.hpp \
    src/StQMLTypes.hpp \
    src/Utils/ISIN.hpp \
    src/Utils/JSON.hpp \
    src/Utils/Utils.hpp \
    src/Utils/Worker.hpp \
    src/theme.hpp \
    src/SQL/SQL.hpp

# -- Resources --
resources.files = \
        qml/main.qml

resources.prefix = /

RESOURCES += resources \
    qml.qrc

# ----------------

DISTFILES += \
    lua/StState.lua \
    src/Lua/StState.lua \

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Includes
INCLUDEPATH += src/
INCLUDEPATH += src/Pages
INCLUDEPATH += include/

# Libs
CONFIG(debug, debug|release) {
    LIBS += -L"$${PWD}/lib/debug" -llibcurl-d_imp
} else {
    LIBS += -L"$${PWD}/lib/release" -llibcurl-imp
}

LIBS += -lpqxx -lyfinance -llibpq -lcpr -llua-5.4.4

# WinAPI Libs
win32 {
    LIBS += -lAdvapi32 -lWS2_32
}

# QML Import
QML_IMPORT_NAME = Stocks
QML_IMPORT_MAJOR_VERSION = 1

# Preprocessor Definitions
win32 {
    DEFINES += NOMINMAX
}

