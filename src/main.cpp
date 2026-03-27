#include <QApplication>
#include <QQmlApplicationEngine>

#include "theme.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

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
    mainTheme.setSecondColor(QColor(41, 41, 41));
    mainTheme.setIsDarkTheme(true);




    engine.load(url);

    return app.exec();
}
