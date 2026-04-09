#pragma once

#include <unordered_map>
#include <string>

enum InvestmentType {
    CASH        = 0,
    SAVINGS     = 1,
    BONDS       = 2,
    COMMODITIES = 3,
    STOCKS      = 4,
    FUNDS       = 5,
    CRYPTOS     = 6,
    DERIVATIVES = 7
};

#define InvestmentTypeLookup(x) (const std::string&)m_InvestmentTypeLookup.at(x)

const std::unordered_map<InvestmentType, std::string> m_InvestmentTypeLookup {
    {CASH, "Cash"},
    {SAVINGS, "Savings"},
    {BONDS, "Bonds"},
    {COMMODITIES, "Commodities"},
    {STOCKS, "Stocks"},
    {FUNDS, "Funds"},
    {CRYPTOS, "Cryptos"},
    {DERIVATIVES, "Derivatives"}
};
