// A header to include all sorts of functions that are called by/calls other lua functions

#pragma once

#include <QtDebug>

#include <sol/sol.hpp>

#include <string>

#include "../API/QuoteData.hpp"
#include "Lua/LuaAPI.hpp"
#include "Currencies.hpp"

inline QuoteData runFormula(sol::environment& env, const std::string& formula) {
    // Wrap the formula to a proper lua function that returns the result
    std::string wrapped = "return (function() return " + formula + " end)()";
    sol::object result = LuaAPI::getInstance().script(wrapped, env);

    return result.as<QuoteData>();
}

inline std::string formatSymbol(const std::string& symbol) {
    // Formatter
    const static std::string BIST = "BIST_";

    std::string new_symbol = symbol;

    // Format BIST_SYMBOL to SYMBOL.IS
    if(symbol.starts_with(BIST)) {
        new_symbol = symbol.substr(BIST.size(), symbol.size());
        new_symbol += ".IS";
    }
    // Format XAG to SI=F
    else if(symbol.starts_with("XAG")) {
        new_symbol = "SI=F";
    }
    // Format XAU to GC=F
    else if(symbol.starts_with("XAU")) {
        new_symbol = "GC=F";
    }
    // Format XPT to PL=F
    else if(symbol.starts_with("XPT")) {
        new_symbol = "PL=F";
    }
    // Format currencies
    else if(symbol.size() == 6) {
        auto curr1 = symbol.substr(0, 3);
        auto curr2 = symbol.substr(3, 3);

        // TODO: Can be optimized to a single loop
        if(Currencies.contains(curr1) && Currencies.contains(curr2)) {
            // yfinance omits USD if it is at the start (eg. USDEUR -> EUR=X)
            if(curr1 == "USD") {
                new_symbol = curr2 + "=X";
            } else {
                new_symbol += "=X";
            }
        }
    }

    return new_symbol;
}

// Just a wrapper for QuoteData constructor in case more functionality needs to be added
inline QuoteData fetchSymbol(const std::string& symbol, const std::string& interval, time_t period) {
    // NOTE: Maybe instead of formatting each variable to the suitable code, yfinance search functionality can be used
    return QuoteData(formatSymbol(symbol), interval, period);
}
