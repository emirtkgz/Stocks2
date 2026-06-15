#include "QuoteData.hpp"

#include <yfinance/hpp/base.h>

using namespace yfinance;

// Put the initialization of inherited Quotes class here in order to fit it into initializer list of QuoteData
Structures::Quotes _initQuotes(const std::string& symbol, std::string interval, time_t period) {
    // Initialize a yfinance ticker object
    Symbol symbol_obj(symbol);

    const time_t time_now = std::time(nullptr);
    return symbol_obj.get_quotes(std::move(interval), time_now - period, time_now * 1); // Multiply by 1 because for some reason library asks for rvalue reference
}

QuoteData::QuoteData(const std::string& symbol, std::string interval, time_t period) :
    Structures::Quotes(_initQuotes(symbol, interval, period)),
    symbol(symbol),
    interval(interval),
    period(period)
{}

QuoteData::QuoteData() :
    period{0}
{}

// Reserve space for QuoteData vectors
void QuoteData::reserve(size_t size) {
    m_close.reserve(size);
    m_open.reserve(size);
    m_low.reserve(size);
    m_high.reserve(size);
    m_unix.reserve(size);
    m_volume.reserve(size);
}

QuoteData QuoteData::interpolate(const QuoteData &data, const std::string &new_interval) {
    return QuoteData();
}


QuoteData::QuoteData(size_t size) {
    reserve(size);
}
