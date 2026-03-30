#pragma once

#include <nlohmann/json.hpp>

#include <memory>

// Singleton instance used to check global currencies
// Original json file: https://gist.github.com/ksafranski/2973986
class Currencies {
public:
    Currencies();
    ~Currencies() = default;

    static const nlohmann::json& getInstance();

    // Remove copy semantics
    Currencies(const Currencies& i)            = delete;
    Currencies& operator=(const Currencies& i) = delete;

    // Remove move semantics
    Currencies(Currencies&& i)            noexcept = delete;
    Currencies& operator=(Currencies&& i) noexcept = delete;
private:
    static std::unique_ptr<const nlohmann::json> json_object;
};
