// A header to include all sorts of functions that are called by/calls other lua functions

#pragma once

#include <QtDebug>

#include <sol/sol.hpp>

#include <string>

#include "../API/QuoteData.hpp"
#include "Lua/LuaAPI.hpp"

inline QuoteData runFormula(sol::environment& env, const std::string& formula) {
    // Wrap the formula to a proper lua function that returns the result
    std::string wrapped = "return (function() return " + formula + " end)()";
    sol::object result = LuaAPI::getInstance().script(wrapped, env);

    return result.as<QuoteData>();
}

// Just a wrapper for QuoteData constructor in case more functionality needs to be added
inline QuoteData fetchSymbol(const std::string& symbol, const std::string& interval, time_t period) {
    return QuoteData(symbol, interval, period);
}
