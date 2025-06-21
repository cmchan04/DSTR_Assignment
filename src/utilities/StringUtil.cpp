//
// Created by User on 6/20/2025.
//

#include "StringUtil.h"

/**
 * A method to convert string to lower case
 * @param str string to be converted to lower case
 * @return lower case input
 */
string toLowerCase(const std::string &str) {

    // Retrieve the string
    string lowerStr = str;

    // Convert to lower case using ranges::transform, then return the string
    ranges::transform(lowerStr, lowerStr.begin(), ::tolower);
    return lowerStr;
}
