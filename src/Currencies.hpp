#pragma once

#include <nlohmann/json.hpp>

#include <memory>

#define Currencies _Currencies::getInstance()

// Singleton instance used to check global currencies
// Original json file: https://gist.github.com/ksafranski/2973986
class _Currencies {
public:
    _Currencies();
    ~_Currencies() = default;

    static const nlohmann::json& getInstance();

    // Remove copy semantics
    _Currencies(const _Currencies& i)            = delete;
    _Currencies& operator=(const _Currencies& i) = delete;

    // Remove move semantics
    _Currencies(_Currencies&& i)            noexcept = delete;
    _Currencies& operator=(_Currencies&& i) noexcept = delete;
private:
    static std::unique_ptr<const nlohmann::json> json_object;
};
