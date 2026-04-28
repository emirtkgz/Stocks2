#pragma once

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

namespace Settings {
    // Declare const references for outside use
    extern const std::string& username;
    extern const std::string& currency;
    extern const std::string& language;

    // Function for loading the settings
    void loadSettings(const std::string& path);
};
