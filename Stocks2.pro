QT += quick
QT += charts
QT += gui

CONFIG += c++20
CONFIG += qmltypes

SOURCES += \
        src/BrowsePageHelper.cpp \
        src/main.cpp \
        src/theme.cpp

HEADERS += \
    src/BrowsePageHelper.hpp \
    src/theme.hpp

resources.files = \
        qml/main.qml
        qml/Pages/WelcomePage.qml

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

CONFIG += qmltypes

QML_IMPORT_NAME = Stocks
QML_IMPORT_MAJOR_VERSION = 1
