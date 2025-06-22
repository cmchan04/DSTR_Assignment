//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include "Sorter.h"

/**
 * This method is to sort a transaction array based on location or transaction type with BUBBLE SORTING algorithm
 * @param transactions transaction array to be sorted
 * @param size size of the array
 * @param column targeted column name
 * @param ascending sort in ascending or descending \code true\endcode indicates ascending, \code false\endcode indicates descending
 */
void Sorter::bubbleSortInArray(Transaction* transactions, const int size, const string &column, const bool ascending) {

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
 * @param ascending sort in ascending or descending \code true\endcode indicates ascending, \code false\endcode indicates descending
 */
void Sorter::insertionSortInArray(Transaction* transactions, const int size, const string &column, const bool ascending) {

    // Convert column name to lowercase
    const string col = toLowerCase(column);

    // The overall traversal throughout the array
    for (int i = 1; i < size; ++i) {

        // Create the key object to be compared in each iteration and retrieve its information
        Transaction key = transactions[i];
        string keyID = key.transactionId;
        string keyType = toLowerCase(key.transactionType);
        string keyLocation = toLowerCase(key.location);

        // Start looping from the location before the key (backward traversal)
        int j = i - 1;
        while (j >= 0) {

            // Retrieve the information of the node being looped
            string previousID = transactions[j].transactionId;
            string previousType = toLowerCase(transactions[j].transactionType);
            string previousLocation = toLowerCase(transactions[j].location);

            // Declare a boolean to determine if insertion should take place
            bool shouldInsert = false;

            // Check target column
            if (col == "type")
                shouldInsert = ascending ?
                    keyType > previousType || (keyType == previousType && keyID > previousID) :
                    keyType < previousType || (keyType == previousType && keyID < previousID);

            // Swapping based on the location
            else if (col == "location")
                shouldInsert = ascending ?
                    keyLocation > previousLocation || (keyLocation == previousLocation && keyID > previousID) :
                    keyLocation < previousLocation || (keyLocation == previousLocation && keyID < previousID);

            // Break when it reached the correct index (is larger / smaller than the previous index)
            if (shouldInsert) break;

            // Move the object one step back
            transactions[j + 1] = transactions[j];

            // Decrement to compare with the object at the following index
            --j;
        }

        // Replace the index object with the key object
        transactions[j + 1] = key;
    }
}

/**
 * This method is to sort a transaction array based on a location or transaction type with MERGE SORTING algorithm
 * @param transactions transaction array to be sorted
 * @param size size of the array
 * @param column targeted column name
 * @param ascending sort in ascending or descending \codetrue\endcode indicates ascending, \codefalse\endcode indicates descending
 */
void Sorter::mergeSortArray(Transaction *transactions, int size, const std::string &column, bool ascending) {
    if (size <= 1) return;
    mergeSortDivider(transactions, 0, size - 1, column, ascending);
}

/**
 * This helper method act as a divider to divide and sort each segment
 * @param transactions array to be sorted
 * @param left index of left boundary
 * @param right index of right boundary
 * @param column targeted column name
 * @param ascending sort in ascending or descending \codetrue\endcode indicates ascending, \codefalse\endcode indicates descending
 */
void Sorter::mergeSortDivider(Transaction *transactions, int left, int right, const std::string &column,
                              bool ascending) {

    if (left < right) {

        // Locate central point
        int median = left + (right - left) / 2;

        // Divide into left and right half
        mergeSortDivider(transactions, left, median, column, ascending);
        mergeSortDivider(transactions, median + 1, right, column, ascending);

        // Sort and merge
        merge(transactions, left, median, right, column, ascending);

    } else if (left >= right) {

        // Return when the merge is completed or param parsed incorrectly
        return;
    }

}

/**
 * This method include the comparison and shifting of merge sort
 * @param transactions array to be sorted
 * @param left index for left boundary
 * @param median central index point between left and right boundary
 * @param right index for right boundary
 * @param column targeted column name
 * @param ascending sort in ascending or descending \codetrue\endcode indicates ascending, \codefalse\endcode indicates descending
 */
void Sorter::merge(Transaction *transactions, int left, int median, int right, const std::string &column,
                   bool ascending) {

    // Initialize size of the left and right array
    int leftSize = median - left + 1;
    int rightSize = right - median;

    // Create the left and right array
    Transaction* leftArr = new Transaction[leftSize];
    Transaction* rightArr = new Transaction[rightSize];

    // Load data into temp arrays
    for (int i = 0; i < leftSize; ++i)
        leftArr[i] = transactions[left + i];
    for (int j = 0; j < rightSize; ++j)
        rightArr[j] = transactions[median + 1 + j];

    // Initialize index for parsing transactions
    int leftIndex = 0, rightIndex = 0, transactionIndex = left;

    // Comparison and swapping
    while (leftIndex < leftSize && rightIndex < rightSize) {
        bool getFromLeft = false;

        if (column == "type") {
            getFromLeft = ascending ? leftArr[leftIndex].transactionType <= rightArr[rightIndex].transactionType
                                    : leftArr[leftIndex].transactionType >= rightArr[rightIndex].transactionType;
        } else if (column == "location") {
            getFromLeft = ascending ? leftArr[leftIndex].location <= rightArr[rightIndex].location
                                    : leftArr[leftIndex].location >= rightArr[rightIndex].location;
        }

        if (getFromLeft) {
            transactions[transactionIndex++] = leftArr[leftIndex++];
        } else {
            transactions[transactionIndex++] = rightArr[rightIndex++];
        }
    }

    // Copy extra records when left and right arrays are not balanced
    while (leftIndex < leftSize) {
        transactions[transactionIndex++] = leftArr[leftIndex++];
    }
    while (rightIndex < rightSize) {
        transactions[transactionIndex++] = rightArr[rightIndex++];
    }

    // Clean up
    delete[] leftArr;
    delete[] rightArr;

}
