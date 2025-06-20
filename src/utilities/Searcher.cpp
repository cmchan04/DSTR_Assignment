//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include "Searcher.h"

/**
 * A method to convert string to lower case
 * @param str string to be converted to lower case
 * @return lower case input
 */
string toLowerCase(const string& str){
    string lowerStr = str;
    ranges::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}


