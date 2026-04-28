QT += quick
QT += charts
QT += gui
QT += sql

CONFIG += c++20
CONFIG += qmltypes

SOURCES += \
        src/API/StockData.cpp \
        src/Pages/BrowsePageHelper.cpp \
        src/Currencies.cpp \
        src/Pages/PortfolioPageHelper.cpp \
        src/SQL/PortfolioSQL.cpp \
        src/Settings.cpp \
        src/main.cpp \
        src/theme.cpp \
        src/SQL/SQL.cpp

HEADERS += \
    src/API/StockData.hpp \
    src/Package.hpp \
    src/Pages/BrowsePageHelper.hpp \
    src/Currencies.hpp \
    src/InvestmentType.hpp \
    src/Pages/PortfolioPageHelper.hpp \
    src/SQL/PortfolioSQL.hpp \
    src/Settings.hpp \
    src/StQMLTypes.hpp \
    src/Utils/Worker.hpp \
    src/theme.hpp \
    src/SQL/SQL.hpp \
    src/API/StockData.hpp

resources.files = \
        qml/main.qml

resources.prefix = /

RESOURCES += resources \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Import

INCLUDEPATH += src/
INCLUDEPATH += src/Pages
INCLUDEPATH += include/

CONFIG(debug, debug|release) {
    LIBS += -L"$${PWD}/lib/debug" -llibcurl-d_imp
} else {
    LIBS += -L"$${PWD}/lib/release" -llibcurl-imp
}

LIBS += -lpqxx -lyfinance -llibpq -lWS2_32 -lcpr

QML_IMPORT_NAME = Stocks
QML_IMPORT_MAJOR_VERSION = 1

DISTFILES += \
    data/database.json \
    test.json
