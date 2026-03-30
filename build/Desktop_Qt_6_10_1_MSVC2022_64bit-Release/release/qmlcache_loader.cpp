#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qml_main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qml_Pages_WelcomePage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qml_Menu_StMenuBar_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qml_Menu_MenuAction_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qml_Pages_Portfolio_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qml_Pages_Browse_Browse_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qml_Pages_Browse_BrowseSearchField_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qml_StyleObjects_StChartView_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qml_main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qml/main.qml"), &QmlCacheGeneratedCode::_qml_main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qml/Pages/WelcomePage.qml"), &QmlCacheGeneratedCode::_qml_Pages_WelcomePage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qml/Menu/StMenuBar.qml"), &QmlCacheGeneratedCode::_qml_Menu_StMenuBar_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qml/Menu/MenuAction.qml"), &QmlCacheGeneratedCode::_qml_Menu_MenuAction_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qml/Pages/Portfolio.qml"), &QmlCacheGeneratedCode::_qml_Pages_Portfolio_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qml/Pages/Browse/Browse.qml"), &QmlCacheGeneratedCode::_qml_Pages_Browse_Browse_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qml/Pages/Browse/BrowseSearchField.qml"), &QmlCacheGeneratedCode::_qml_Pages_Browse_BrowseSearchField_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qml/StyleObjects/StChartView.qml"), &QmlCacheGeneratedCode::_qml_StyleObjects_StChartView_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qml/main.qml"), &QmlCacheGeneratedCode::_qml_main_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(qml_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    Q_CLEANUP_RESOURCE(qml_qmlcache);
    return 1;
}
int QT_MANGLE_NAMESPACE(qInitResources_qmake_resources)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(build_Desktop_Qt_6_10_1_MSVC2022_64bit_Release_release_qmake_resources_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmake_resources))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmake_resources)() {
    Q_CLEANUP_RESOURCE(build_Desktop_Qt_6_10_1_MSVC2022_64bit_Release_release_qmake_resources_qmlcache);
    return 1;
}
