//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include <iostream>
#include "Searcher.h"

using namespace std;

/**
 * The method to search for a specific transaction type using linear search.
 * @param list The overall list of data
 * @param transactionType The type of transaction (deposit, cash, etc.) to be searched for
 * @param outputSize The final size of the output
 * @return The list of Transaction pointers that each points to the Transaction object
 */
Transaction** Searcher::linearSearchUsingList(const DoublyLinkedList &list, string &transactionType, int &outputSize) {

    // Checking: is the list empty?
    if (list.isEmpty()) {

        // Exit the method immediately
        outputSize = 0;
        return nullptr;
    }

    // First declare a new list to store results (with maximum size) with a counter
    const int maximumSize = list.getSize();
    auto** result = new Transaction*[maximumSize];
    int matchCount = 0;

    // Convert the string input to lower case
    transactionType = toLowerCase(transactionType);

    // Get the head node
    Node* currentNode = list.getHeadNode();

    // Loop through each node
    while (currentNode != nullptr) {

        // Get the lower case version of the transaction type for each node
        string nodeTransactionType = currentNode -> transactionObject.transactionType;
        nodeTransactionType = toLowerCase(nodeTransactionType);

        // Check if the current node matches condition
        if (nodeTransactionType == transactionType) {

            // Add the transaction object to the array
            result[matchCount] = &currentNode -> transactionObject;

            // Increment match count for the next iteration
            matchCount++;
        }

        // Continue to the next iteration
        currentNode = currentNode -> nextNode;
    }

    // Special case: if there is no matching search
    if (matchCount == 0) {

        // Free up the allocated memory to store the result list
        delete[] result;

        // Return the output size and nullptr
        outputSize = 0;
        return nullptr;
    }

    // Perform shrinking of the resulting array (which will definitely happen)
    removeUnusedIndex(result, maximumSize, matchCount);

    // Return the output size and search result
    outputSize = matchCount;
    return result;
}

/**
 * A utility method to clear any unused spaces in a list.
 * @param list The list with blank spaces
 * @param currentListSize The current size of the list
 * @param actualListSize The size that the list should shrink down to
 */
inline void Searcher::removeUnusedIndex(Transaction** &list, const int &currentListSize, const int &actualListSize) {

    // Compare the intended size of the list with its actual size
    if (actualListSize < currentListSize) {

        // Create a new temporary list
        auto** tempList = new Transaction*[actualListSize];

        // Move all search results into the temporary list
        for (int i = 0; i < actualListSize; i++) {
            tempList[i] = list[i];
        }

        // Now replace the result with the temporary list
        delete[] list;
        list = tempList;
    }
}

/**
 * This method searches for a specific transaction type
 * @param transactions array parsed in to search
 * @param size size of the parsed array
 * @param searchType transaction type to search
 * @param resultCount number of total results
 * @return The pointer to an array with only the transaction type searched
 */
Transaction** Searcher::linearSearchWithArray(Transaction* transactions, const int size, const string &searchType,
                                              int &resultCount) {

    // Initialize the counter
    resultCount = 0;

    // Convert the search type to lower case
    const string type = toLowerCase(searchType);

    // Create a large array to store results
    auto** result = new Transaction*[size];

    // Index for data insertion
    int index = 0;

    // Loop through the transactions
    for (int i = 0; i < size; i++) {

        // Add the matching results into the array
        if (toLowerCase(transactions[i].transactionType) == type) result[index++] = &transactions[i];
    }

    // Trim the size of the resulting array
    removeUnusedIndex(result, size, index);

    // Set results count and return the array
    resultCount = index;
    return result;
}

Transaction** Searcher::binarySearchWithArray(Transaction* transactions, const int size, const string &searchType,
                                              int &resultCount){
    // Initialize the counter
    resultCount = 0;

    // Convert search type input to lowercase
    const string type = toLowerCase(searchType);

    // Declare an array with maximum size to store results
    auto** result = new Transaction*[size];
    int sortIndex = 0;

    // Declare boundary index and target found index
    int leftBoundary = 0, rightBoundary = size - 1, foundIndex = -1;

    // Locate the transaction object at median
    while (leftBoundary <= rightBoundary) {
        int median = leftBoundary + (rightBoundary - leftBoundary) / 2;

        // Extract the transaction type
        string midType = toLowerCase(transactions[median].transactionType);

        // Binary Search
        if (midType == type) {
            foundIndex = median;
            break;
        } else if (midType < type) { // if the target transaction type is larger (later alphabet), move to the right half
            leftBoundary = median + 1;
        } else if (midType > type){ // if the target transaction type is smaller (earlier alphabet), move to the left half
            rightBoundary = median - 1;
        }
    }

    // If no record matches, return null
    if (foundIndex == -1) {
        cout << "No records are found with transaction type (" << searchType << "). \n" << endl;
        return nullptr;
    }

    // Expand leftBoundary
    // Declare the starting index of matching results
    int start = foundIndex;

    // Decrement the start index until all matching transactions are included
    while (start > 0 && toLowerCase(transactions[start - 1].transactionType) == type) {
        --start;
    }

    // Expand rightBoundary
    // Declare the ending index of matching results
    int end = foundIndex;

    // Increment the end index until all matching transactions are included
    while (end < size - 1 && toLowerCase(transactions[end + 1].transactionType) == type) {
        ++end;
    }

    // Store array of pointers to matched results
    for (int i = start; i <= end; ++i) {
        result[sortIndex++] = &transactions[i];
    }

    // Trim the size of result array
    removeUnusedIndex(result, size, sortIndex);

    // Set result count and return it
    resultCount = sortIndex;
    return result;
}