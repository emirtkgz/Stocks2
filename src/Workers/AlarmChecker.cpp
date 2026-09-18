#include "AlarmChecker.hpp"

#include "API/ServerAPI.hpp"
#include "Utils/Utils.hpp"
#include "Pages/AlarmsPageHelper.hpp"

#include <nlohmann/json.hpp>
#include <yfinance/hpp/symbols.h>

#include <QSystemTrayIcon>
#include <QtTypes>

#include <chrono>

using namespace std::chrono_literals;
using json = nlohmann::json;

AlarmChecker::AlarmChecker(QQmlApplicationEngine* engine)
    : engine(engine)
{
    // Create the system tray icon object
    notification = new QSystemTrayIcon(engine);
    notification->setIcon(QIcon(":/icons/icon.ico"));
    notification->show();

    getAlarmList();
    price_list = fetchPrices();

    worker = std::make_unique<Worker>(ST_ALARM_CHECKER_FREQ, [&]{
        auto new_price_list = fetchPrices();

        for(auto& alarm : alarm_list) {
            std::string ticker = alarm["Ticker"];
            AlarmTypes type    = static_cast<AlarmTypes>(alarm["Type"]);
            double alarm_value = std::stod(std::string(alarm["Value"]));
            QString message    = QString::fromStdString(alarm["Message"]);

            double new_price = new_price_list[ticker];
            double old_price = price_list[ticker];

            // Define a lambda here so no need to write invokeMethod(...) for every case
            auto notifyForNotification = [this, &message]() {
                // Invoke this function within the main thread since QT GUI elements cannot work on multiple threads
                QMetaObject::invokeMethod(
                    this, "showNotification",
                    Qt::QueuedConnection,
                    Q_ARG(QString, "Title"),
                    Q_ARG(QString, message)
                );
            };

            // Switch for every alarm type
            switch (type) {
            // Case for both up and down crosses
            case AlarmTypes::Cross:
                if(StUtils::isInRangeEx(alarm_value, old_price, new_price)) {
                    notifyForNotification();
                }
                break;
            case AlarmTypes::CrossUp:
                if(StUtils::isInBetweenEx(alarm_value, old_price, new_price)) {
                    notifyForNotification();
                }
                break;
            case AlarmTypes::CrossDown:
                if(StUtils::isInBetweenEx(alarm_value, new_price, old_price)) {
                    notifyForNotification();
                }
                break;
            }
        }

        // Update the old list with the new one
        price_list = new_price_list;
    });
}

void AlarmChecker::getAlarmList() {
    json list_json = ServerAPI.get("api/alarms/data");
    if(ServerAPI.checkErrors(list_json))
        return;

    alarm_list = list_json["data"];
}

nlohmann::json AlarmChecker::fetchPrices() {
    // TODO: Add formula support
    std::vector<std::string> tickers;

    for(auto& alarm : alarm_list) {
        tickers.push_back(alarm["Ticker"]);
    }

    nlohmann::json list{};
    nlohmann::json summaries;

    // Use try-catch since in case of an error whole thread exits
    try {
        yfinance::Symbols symbols(tickers);
        summaries = symbols.get_summaries("price");
    } catch(...) {
        return list;
    }

    for(auto& summary : summaries) {
        const std::string& name = summary["symbol"];
        double price            = summary["regularMarketPrice"]["raw"];
        list[name] = price;
    }

    return list;
}

void AlarmChecker::showNotification(const QString& title, const QString& message) {
    notification->showMessage(
        title,
        message,
        QSystemTrayIcon::Critical,
        5000
    );
}



