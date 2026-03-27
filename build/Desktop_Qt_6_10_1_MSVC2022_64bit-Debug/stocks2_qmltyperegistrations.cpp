/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<BrowsePageHelper.hpp>)
#  include <BrowsePageHelper.hpp>
#endif
#if __has_include(<theme.hpp>)
#  include <theme.hpp>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_Stocks()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<BrowsePageHelper>("Stocks", 1);
    qmlRegisterTypesAndRevisions<Theme>("Stocks", 1);
    QT_WARNING_POP
    qmlRegisterModule("Stocks", 1, 0);
}

static const QQmlModuleRegistration stocksRegistration("Stocks", qml_register_types_Stocks);
