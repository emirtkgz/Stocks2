#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "theme.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // Initialize engine
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:qml/main.qml"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    // Set the theme colors
    Theme mainTheme("StTheme");
    mainTheme.setFirstColor(QColor(31, 31, 31));
    mainTheme.setSecondColor(QColor(36, 36, 36));




    engine.load(url);

    return app.exec();
}
