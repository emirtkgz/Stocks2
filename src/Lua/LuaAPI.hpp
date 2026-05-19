#pragma once

#include <sol/sol.hpp>

class LuaAPI {
public:
    static sol::state& getInstance();
private:
    sol::state state;

    LuaAPI();
};
