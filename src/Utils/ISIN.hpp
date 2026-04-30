#pragma once

#include <string_view>
#include <cctype>

namespace ISIN {
    /*
     *      US            912810FM5           4
     * Country Code(2) Security Code(9)  Check Digit(1)
    */
    bool validateFormat(std::string_view isin) noexcept {
        // Size has to be 12
        if(isin.size() != 12)
            return false;

        // First two digits are alphabetic characters
        if (!std::isalpha(isin[0]) || !std::isalpha(isin[1]))
            return false;

        // Digits [3, 11] are alphanumeric
        for (int i = 2; i < 11; i++) {
            if (!std::isalnum(isin[i]))
                return false;
        }

        // Last digit is a number from [0,9]
        if (!std::isdigit(isin[11]))
            return false;

        return true;
    }
}
