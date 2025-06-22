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
void Sorter::bubbleSortArray(Transaction* transactions, const int size, const string &column, const bool ascending) {

    // Convert the sort field to lower case
    const string col = toLowerCase(column);

    // Start bubble sorting
    for (int i = 0; i < size; ++i) {

        // Declare a variable to check if any swapping takes place in this traversal
        bool swapped = false;

        // Avoid unnecessary swapping for completed indexes
        for (int j = 0; j < size - i - 1; ++j) {

            // A flag that indicates should swap or not
            bool shouldSwap = false;

            // Get details for the left and right transactions
            const string leftID = transactions[j].transactionId;
            const string leftType = toLowerCase(transactions[j].transactionType);
            const string leftLocation = toLowerCase(transactions[j].location);

            const string rightID = transactions[j + 1].transactionId;
            const string rightType = toLowerCase(transactions[j + 1].transactionType);
            const string rightLocation = toLowerCase(transactions[j + 1].location);

            // Swapping based on the transaction type
            if (col == "type")
                shouldSwap = ascending ?
                    leftType > rightType || (leftType == rightType && leftID > rightID) :
                    leftType < rightType || (leftType == rightType && leftID < rightID);

            // Swapping based on the location
            else if (col == "location")
                shouldSwap = ascending ?
                    leftLocation > rightLocation || (leftLocation == rightLocation && leftID > rightID) :
                    leftLocation < rightLocation || (leftLocation == rightLocation && leftID < rightID);

            // Perform swapping if swapping condition is fulfilled
            if (shouldSwap) {
                Transaction::swap(transactions[j], transactions[j + 1]);
                swapped = true;
            }
        }

        // If no swapping takes place, then everything ends early
        if (!swapped) break;
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
