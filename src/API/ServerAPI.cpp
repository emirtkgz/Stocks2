#include "ServerAPI.hpp"

#include <QDebug>

#define JWT_HEADER cpr::Header{{"Authorization", "Bearer " + JWT}}

using nlohmann::json;

std::string _ServerAPI::JWT{};

_ServerAPI::_ServerAPI() {}

_ServerAPI& _ServerAPI::getInstance() {
    static _ServerAPI instance;

    return instance;
}

nlohmann::json _ServerAPI::get(const std::string& api_point, cpr::Parameters parameters) {
    cpr::Url api_url = std::string(base_url) + api_point;

    cpr::Response r = cpr::Get(api_url, parameters, JWT_HEADER);

    if((r.status_code != 200) || r.text.empty()) {
        qWarning() << "GET request to server API failed! (" << api_url.c_str() << ")";
        return json{};
    }

    return json::parse(r.text);
}

nlohmann::json _ServerAPI::post(const std::string& api_point, cpr::Body body) {
    cpr::Url api_url = std::string(base_url) + api_point;

    cpr::Response r = cpr::Post(api_url, body, cpr::Header{{"Content-Type", "application/json"}}, JWT_HEADER);

    if((r.status_code != 200) || r.text.empty()) {
        qWarning() << "POST request to server API failed! (" << api_url.c_str() << ")";
        return json{};
    }

    return json::parse(r.text);
}

nlohmann::json _ServerAPI::login(const std::string& username, const std::string& password) {
    json r = post("auth/login",
                  cpr::Body{json{
                    {"username", username},
                    {"password", password}
                }.dump()}
            );

    if(r.contains("accessToken")) {
        JWT = r["accessToken"];
    }

    return r;
}


