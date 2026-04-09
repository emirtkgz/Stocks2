#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtLogging>

#include "theme.hpp"
#include "SQL/SQL.hpp"
#include "SQL/PortfolioSQL.hpp"
#include "Pages/PortfolioPageHelper.hpp"
#include "Pages/BrowsePageHelper.hpp"
#include "Package.hpp"

#include <yahoo-finance/quote.hpp>

#include <nlohmann/json.hpp>

#include <fstream>

using json = nlohmann::json;

void registerQMLTypes() {
    qmlRegisterType<PortfolioPageHelper>(StPackage::name, StPackage::majorVersion, StPackage::minorVersion, "PortfolioPageHelper");
    qmlRegisterType<BrowsePageHelper>   (StPackage::name, StPackage::majorVersion, StPackage::minorVersion, "BrowserPageHelper");
}

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

    // Register QML Types
    registerQMLTypes();

    // Connect to database
    {
        // Open the credentials file
        std::ifstream fs("./data/database.json");

        if(fs) {
            json database_cred = json::parse(fs);

            // Format the json into a suitable string
            std::string connStr;
            for (auto it = database_cred.begin(); it != database_cred.end(); it++) {
                if (!connStr.empty())
                    connStr += ' ';

                connStr += it.key() + "='" + it.value().get<std::string>() + "'";
            }

            SQL::connect(connStr);            
        }
        else {
            qCritical() << "Failed to open database credentials file!";
        }
    }

    std::ifstream test_fs("./data/test.json");
    json test_json = json::parse(test_fs);

    //PortfolioSQL::upsert("Emirtkgz", test_json.dump());

    // Set the theme colors
    Theme mainTheme("StTheme");
    mainTheme.setFirstColor(QColor(31, 31, 31));
    mainTheme.setSecondColor(QColor(41, 41, 41));
    mainTheme.setIsDarkTheme(true);


    engine.load(url);

    return app.exec();
}
