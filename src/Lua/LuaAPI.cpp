#include "LuaAPI.hpp"

#include "../API/QuoteData.hpp"
#include "LuaFunctions.hpp"

#include <QDebug>

#include <fstream>
#include <sstream>

sol::state& LuaAPI::getInstance() {
    static LuaAPI luaAPI;

    return luaAPI.state;
}

LuaAPI::LuaAPI() :
    state{}
{
    // Open standard lua libraries
    state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);

    // Register functions
    state.set_function("fetchSymbol", fetchSymbol);

    // Register QuoteData class to lua
    state.new_usertype<QuoteData>(
        // Constructors
        sol::constructors<
            QuoteData(std::string, std::string, time_t),
            QuoteData()
        >(),

        // Members
        "symbol",   &QuoteData::symbol,
        "period",   &QuoteData::period,
        "interval", &QuoteData::interval,
        "close",    &QuoteData::m_close,
        "open",     &QuoteData::m_open,
        "high",     &QuoteData::m_high,
        "low",      &QuoteData::m_low,

        // Operator overloads
        sol::meta_function::addition, sol::overload(
            [](const QuoteData& a, double b)            { return a + b; },
            [](const QuoteData& a, const QuoteData& b)  { return a + b; }
        ),
        sol::meta_function::subtraction, sol::overload(
            [](const QuoteData& a, double b)            { return a - b; },
            [](const QuoteData& a, const QuoteData& b)  { return a - b; }
        ),
        sol::meta_function::multiplication, sol::overload(
            [](const QuoteData& a, double b)            { return a * b; },
            [](const QuoteData& a, const QuoteData& b)  { return a * b; }
        ),
        sol::meta_function::division, sol::overload(
            [](const QuoteData& a, double b)            { return a / b; },
            [](const QuoteData& a, const QuoteData& b)  { return a / b; }
        )
    );

    // Set the script to be used for global state
    {
        // Open the file
        std::ifstream fs("./lua/StState.lua");
        if(!fs) {
            qWarning() << "Failed to open StState.lua!";
        }

        // Read the content into string stream
        std::stringstream ss;
        ss << fs.rdbuf();

        // Run the script
        state.script(ss.str());
    }

    #ifdef _DEBUG
    state.script("print('Debug: Initialized lua API')");
    #endif
}
