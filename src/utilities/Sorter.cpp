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
 * @param ascending sort in ascending or descending \code true\endcode indicates ascending, \code false\endcode indicates descending
 */
void Sorter::mergeSortInArray(Transaction *transactions, const int size, const string &column, const bool ascending) {

    // If the transaction is empty, return error
    if (transactions == nullptr) throw invalid_argument("Transaction array cannot be null.");

    // Do nothing if array size is too small
    if (size <= 1) return;

    // Perform recursive sorting otherwise
    mergeSortDivider(transactions, 0, size - 1, column, ascending);
}

/**
 * This helper method act as a divider to divide and sort each segment
 * @param transactions array to be sorted
 * @param left index of left boundary
 * @param right index of right boundary
 * @param column targeted column name
 * @param ascending sort in ascending or descending \code true\endcode indicates ascending, \code false\endcode indicates descending
 */
void Sorter::mergeSortDivider(Transaction *transactions, const int left, const int right,
                              const string &column, const bool ascending) {

    // Divide the array into two if input is valid
    if (left < right) {

        // Locate the central point
        const int median = (left + right) / 2;

        // Divide into left and right half
        mergeSortDivider(transactions, left, median, column, ascending);
        mergeSortDivider(transactions, median + 1, right, column, ascending);

        // Sort and merge
        mergeForArrayElements(transactions, left, median, right, column, ascending);
    }

    // Return or do nothing when the merge is completed, or the parameters are passed incorrectly
}

/**
 * This method includes the comparison and shifting of merge sort
 * @param transactions array to be sorted
 * @param left index for left boundary
 * @param median central index point between left and right boundary
 * @param right index for right boundary
 * @param column targeted column name
 * @param ascending sort in ascending or descending \code true\endcode indicates ascending, \code false\endcode indicates descending
 */
void Sorter::mergeForArrayElements(Transaction *transactions, const int left, const int median, const int right,
                                   const string &column, const bool ascending) {

    // Initialize size of the left and right array
    const int leftSize = median - left + 1;
    const int rightSize = right - median;

    // Create the left and right array
    auto* leftArr = new Transaction[leftSize];
    auto* rightArr = new Transaction[rightSize];

    // Load data into temporary arrays: Left array
    for (int i = 0; i < leftSize; ++i)
        leftArr[i] = transactions[left + i];

    // Right array
    for (int j = 0; j < rightSize; ++j)
        rightArr[j] = transactions[median + 1 + j];

    // Initialize index for parsing transactions
    int leftIndex = 0, rightIndex = 0, transactionIndex = left;

    // Perform comparison and swapping when there are still elements in both arrays
    while (leftIndex < leftSize && rightIndex < rightSize) {

        // Declare a boolean to determine if the element shall be obtained from the left array or the right array
        bool getFromLeft = false;

        // Get information from the left and right array
        string leftID = leftArr[leftIndex].transactionId;
        string leftType = toLowerCase(leftArr[leftIndex].transactionType);
        string leftLocation = toLowerCase(leftArr[leftIndex].location);

        string rightID = rightArr[rightIndex].transactionId;
        string rightType = toLowerCase(rightArr[rightIndex].transactionType);
        string rightLocation = toLowerCase(rightArr[rightIndex].location);

        // Sorting based on transaction type
        if (column == "type") {
            getFromLeft = ascending ?
                leftType < rightType || (leftType == rightType && leftID < rightID) :
                leftType > rightType || (leftType == rightType && leftID > rightID);

        // Sorting based on location
        } else if (column == "location") {
            getFromLeft = ascending ?
                leftLocation < rightLocation || (leftLocation == rightLocation && leftID < rightID) :
                leftLocation > rightLocation || (leftLocation == rightLocation && leftID > rightID);
        }

        // If the element has to be obtained from the left
        if (getFromLeft) {

            // Add to the transaction list and increase index
            transactions[transactionIndex++] = leftArr[leftIndex++];

        // Add elements from the right list into the sorted array and increment index
        } else {
            transactions[transactionIndex++] = rightArr[rightIndex++];
        }
    }

    // Copy extra records when either the left or right array does not have elements anymore
    // When the left array still has elements, copy them
    while (leftIndex < leftSize) {
        transactions[transactionIndex++] = leftArr[leftIndex++];
    }

    // The same goes for the right
    while (rightIndex < rightSize) {
        transactions[transactionIndex++] = rightArr[rightIndex++];
    }

    // Clean up to free memory
    delete[] leftArr;
    delete[] rightArr;
}
