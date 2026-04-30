#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtLogging>

#include "theme.hpp"
#include "SQL/SQL.hpp"
#include "SQL/PortfolioSQL.hpp"
#include "API/StockData.hpp"
#include "Settings.hpp"
#include "API/StockData.hpp"
#include "StQMLTypes.hpp"
#include "Utils/Worker.hpp"
#include "PriceUpdater.hpp"

#include <yfinance/hpp/base.h>
#include <yfinance/hpp/symbols.h>

#include <nlohmann/json.hpp>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <fstream>

#define ST_PRICE_UPDATER_FREQ 30s

using json = nlohmann::json;

using namespace std::chrono_literals;

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
        Qt::QueuedConnection
    );

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

    // Load the user settings
    Settings::loadSettings("./data/settings.json");


    {
        std::ifstream test_fs("./data/test.json");
        json test_json = json::parse(test_fs);

        //PortfolioSQL::upsert("Emirtkgz", test_json.dump());
    }
    {
        std::ifstream fs("./data/test2.json");
        json test_json = json::parse(fs);

        //PortfolioSQL::set(Settings::username, test_json.dump());
        //PortfolioSQL::remove(Settings::username, -1);
    }

    // Timer loop to update the portfolio
    Worker priceUpdater(ST_PRICE_UPDATER_FREQ, []{
        qDebug() << "Updated portfolio";
        PriceUpdater::updateLastPrice(Settings::username);
    });

    // Set the theme colors
    Theme mainTheme("StTheme");
    mainTheme.setFirstColor(QColor(31, 31, 31));
    mainTheme.setSecondColor(QColor(41, 41, 41));
    mainTheme.setIsDarkTheme(true);

    // Lua demo
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package);
    lua.script("print('bark bark bark!')");

    engine.load(url);

    return app.exec();
}
