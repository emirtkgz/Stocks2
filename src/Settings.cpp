#include "Settings.hpp"

#include <QDebug>

namespace Settings {
    // Make sure these variables cannot be access and modified from outside
    namespace {
        std::string _username;
        std::string _currency;
        std::string _language;
    };

    // Define const references for outside use
    const std::string& username = _username;
    const std::string& currency = _currency;
    const std::string& language = _language;

    void loadSettings(const std::string& path) {
        // Load the settings json
        std::ifstream fs(path);
        if(!fs) {
            qCritical() << "Failed to open settings.json!";
            return;
        }

        nlohmann::json settings_json = nlohmann::json::parse(fs);

        // Set the internal variables
        _username = settings_json["username"];
        _currency = settings_json["currency"];
        _language = settings_json["language"];
    }
}
