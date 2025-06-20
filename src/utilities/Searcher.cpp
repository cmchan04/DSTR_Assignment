//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include "Searcher.h"

/**
 * A method to convert string to lower case
 * @param str string to be converted to lower case
 * @return lower case input
 */
string Searcher::toLowerCase(const std::string &str) {

    string lowerStr = str;
    ranges::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}


Transaction* Searcher::linearSearchWithArray(Transaction* transactions, int size, const string& searchType,
                                             int& resultCount) {

    // Initialize the counter
    resultCount = 0;

    //Convert searchType to lower case
    string type = toLowerCase(searchType);

    // Loop to check the total number of results
    for (int i = 0; i < size; i++){
        if (toLowerCase(transactions[i].transactionType) == type){
            resultCount++;
        }
    }

    // Create an array to store results
    auto* result = new Transaction[resultCount];

    // Index for data insertion
    int index = 0;

    // Copy matched transactions into the result array
    for (int i = 0; i < size; i++) {
        if (toLowerCase(transactions[i].transactionType) == type){
            result[index++] = transactions[i];
        }
    }

    return result;
}