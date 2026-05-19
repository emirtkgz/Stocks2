#pragma once

#include <yfinance/hpp/structures.h>

#include <string>

// A handy macro for QuoteData op float operation overloads
#define _NEW_QUOTEDATA_OP_FLOAT(OP)                          \
inline QuoteData operator OP (float num) const noexcept {    \
    const size_t size = m_unix.size();                       \
                                                             \
    QuoteData new_data(size);                                \
    new_data.symbol   = this->symbol;                        \
    new_data.interval = this->interval;                      \
    new_data.period   = this->period;                        \
                                                             \
    for(size_t i = 0; i < m_unix.size(); i++) {              \
        new_data.m_unix.push_back(this->m_unix[i]);          \
        new_data.m_volume.push_back(this->m_volume[i]);      \
                                                             \
        new_data.m_close.push_back(this->m_close[i] OP num); \
        new_data.m_open.push_back (this->m_open[i]  OP num); \
        new_data.m_high.push_back (this->m_high[i]  OP num); \
        new_data.m_low.push_back  (this->m_low[i]   OP num); \
    }                                                        \
                                                             \
    return new_data;                                         \
}                                                            \

// TODO: Test this macro
// A handy macro for QuoteData op QuoteData operation overloads
#define _NEW_QUOTEDATA_OP_QUOTEDATA(OP)                                                        \
inline QuoteData operator OP (const QuoteData& data) const noexcept {                          \
    /* Return this if intervals do not match */                                                \
    if(this->interval != data.interval)                                                        \
        return *this;                                                                          \
                                                                                               \
    /* Initialize the new data */                                                              \
    QuoteData new_data;                                                                        \
    new_data.interval = this->interval;                                                        \
    new_data.symbol   = this->symbol + #OP + data.symbol;                                      \
                                                                                               \
    /* Find the common start and end date */                                                   \
    const time_t start = std::max(this->m_unix.front(), data.m_unix.front());                  \
    const time_t end   = std::min(this->m_unix.back(), data.m_unix.back());                    \
                                                                                               \
    /* Case when,                                                                              \
     * Data1    |--------|                                                                     \
     * Data2                |--------------------|                                             \
     * Result   (Empty)                                                                        \
    */                                                                                         \
    if(start > end)                                                                            \
        return new_data;                                                                       \
                                                                                               \
    /* Other cases such as,                                                                    \
     * Data1    |---------------|               |------------------|                           \
     * Data2         |--------------------|         |---------|                                \
     * Result        |----------|                   |---------|                                \
    */                                                                                         \
    else {                                                                                     \
        /* Set the period of the new_data */                                                   \
        new_data.period = end - start;                                                         \
                                                                                               \
        /* Even if intervals are equal, two datas can be off by seconds, so use lower_bound */ \
        auto start1 = std::lower_bound(this->m_unix.begin(), this->m_unix.end(), start);       \
        auto start2 = std::lower_bound(data.m_unix.begin(),  data.m_unix.end(),  start);       \
        auto end1   = std::lower_bound(this->m_unix.begin(), this->m_unix.end(), end);         \
                                                                                               \
        /* Get indices from iterators */                                                       \
        size_t index1 = std::distance(this->m_unix.begin(), start1);                           \
        size_t index2 = std::distance(data.m_unix.begin(), start2);                            \
                                                                                               \
        /* Reserve the size so push_back wont need to resize */                                \
        const size_t size = std::distance(start1, end1);                                       \
        new_data.reserve(size);                                                                \
                                                                                               \
        for(size_t i = 0; i < size; i++) {                                                     \
            new_data.m_unix.push_back(this->m_unix[index1 + i]);                               \
            new_data.m_volume.push_back(this->m_volume[index1 + i]);                           \
                                                                                               \
            new_data.m_close.push_back(this->m_close[index1 + i] OP data.m_close[index2 + i]); \
            new_data.m_open.push_back (this->m_open[index1 + i]  OP data.m_open[index2 + i]);  \
            new_data.m_high.push_back (this->m_high[index1 + i]  OP data.m_high[index2 + i]);  \
            new_data.m_low.push_back  (this->m_low[index1 + i]   OP data.m_low[index2 + i]);   \
        }                                                                                      \
                                                                                               \
        return new_data;                                                                       \
    }                                                                                          \
                                                                                               \
}


// A class to handle all sorts of historical quote price data
class QuoteData : public Structures::Quotes {
public:
    QuoteData(const std::string& symbol, std::string interval, time_t period);
    QuoteData();

    void reserve(size_t size);

    // QuoteData (op) float overloads
    _NEW_QUOTEDATA_OP_FLOAT(+)
    _NEW_QUOTEDATA_OP_FLOAT(-)
    _NEW_QUOTEDATA_OP_FLOAT(/)
    _NEW_QUOTEDATA_OP_FLOAT(*)

    // QuoteData (op) QuoteData overloads
    _NEW_QUOTEDATA_OP_QUOTEDATA(+)
    _NEW_QUOTEDATA_OP_QUOTEDATA(-)
    _NEW_QUOTEDATA_OP_QUOTEDATA(/)
    _NEW_QUOTEDATA_OP_QUOTEDATA(*)

    // Members
    std::string symbol;
    std::string interval;
    time_t period;
private:
    QuoteData(size_t size);
};

#undef _NEW_QUOTEDATA_OP_FLOAT
#undef _NEW_QUOTEDATA_OP_QUOTEDATA
