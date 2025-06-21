//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include "Sorter.h"

/**
 * This method is to sort a transaction array based on location or transaction type with BUBBLE SORTING algorithm
 * @param transactions transaction array to be sorted
 * @param size size of the array
 * @param column targeted column name
 * @param ascending sort in ascending or descending \codetrue\endcode indicates ascending, \codefalse\endcode indicates descending
 */
void Sorter::bubbleSortArray(Transaction *transactions, int size, const std::string &column, bool ascending) {

    // Convert the sort field to lower case
    string col = toLowerCase(column);

    // Start bubble sorting
    for (int i = 0; i < size; ++i) {

        // TODO - Remove after tested
        // Progress Counter
        if (i % 100 == 0){
            cout << "Processing row: " << i << endl;
        }

        // Avoid unnecessary swapping for completed indexes
        for (int j = 0; j < size - i - 1; ++j) {

            // A flag that indicates should swap or not
            bool shouldSwap = false;

            // String Comparison
            if (col == "type")
                shouldSwap = ascending ? transactions[j].transactionType >transactions[j + 1].transactionType
                                       : transactions[j].transactionType < transactions[j + 1].transactionType;
            else if (col == "location")
                shouldSwap = ascending ? transactions[j].location > transactions[j + 1].location
                                       : transactions[j].location < transactions[j + 1].location;

            if (shouldSwap) {
                transactions->swap(transactions[j], transactions[j + 1]);
            }

        }
    }
}

/**
 * This method is to sort a transaction array based on a location or transaction type with INSERTION SORTING algorithm
 * @param transactions transaction array to be sorted
 * @param size size of the array
 * @param column targeted column name
 * @param ascending sort in ascending or descending \codetrue\endcode indicates ascending, \codefalse\endcode indicates descending
 */
void Sorter::insertionSortArray(Transaction* transactions, int size, const std::string& column, bool ascending) {

    // Convert column name to lowercase
    string col = toLowerCase(column);

    // Start insertion sort
    for (int i = 1; i < size; ++i) {

        // TODO - Remove after tested
        // Progress Counter
        if (i % 100 == 0) {
            cout << "Processing row: " << i << endl;
        }

        // Create the key object to be compared in each iteration
        Transaction key = transactions[i];
        int j = i - 1;

        // Loop through previous sorted elements
        while (j >= 0) {
            bool shouldSwap = false;

            // Check target column
            if (col == "type")
                shouldSwap = ascending ? key.transactionType < transactions[j].transactionType
                                       : key.transactionType > transactions[j].transactionType;
            else if (col == "location")
                shouldSwap = ascending ? key.location < transactions[j].location
                                       : key.location > transactions[j].location;

            // Break when it reached the correct index (is larger / smaller than the previous index)
            if (!shouldSwap) break;

            // Swap with the previous object
            transactions[j + 1] = transactions[j];

            // Decrement to compare with the object at the following index
            --j;
        }

        // Replace the index object with the key object
        transactions[j + 1] = key;
    }
}
