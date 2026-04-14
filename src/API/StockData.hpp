#pragma once

#include <QtNumeric>

#include <string>

namespace StockData {

    // Uses Yahoo Finance API to fetch data
    qreal getCurrentPrice(const std::string& code);
}
