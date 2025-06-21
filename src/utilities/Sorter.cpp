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
        if (i % 1000 == 0) {
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
