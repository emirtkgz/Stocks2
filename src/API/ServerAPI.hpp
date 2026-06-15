#pragma once

#include <string_view>

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

#define ServerAPI _ServerAPI::getInstance()

class _ServerAPI {
public:
    static _ServerAPI& getInstance();

    static nlohmann::json get(const std::string& api_point, cpr::Parameters parameters = {});
    static nlohmann::json post(const std::string& api_point, cpr::Body body = {});
    static nlohmann::json login(const std::string& username, const std::string& password);

    static std::string JWT;
    static inline constexpr std::string_view base_url = "http://localhost:3000/";

    // Remove copy semantics
    _ServerAPI(const _ServerAPI& i)            = delete;
    _ServerAPI& operator=(const _ServerAPI& i) = delete;

    // Remove move semantics
    _ServerAPI(_ServerAPI&& i)            noexcept = delete;
    _ServerAPI& operator=(_ServerAPI&& i) noexcept = delete;
private:
    _ServerAPI();
};
