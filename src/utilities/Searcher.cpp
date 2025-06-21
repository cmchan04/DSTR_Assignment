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
    ranges::transform(transactionType, transactionType.begin(), ::tolower);

    // Get the head node
    Node* currentNode = list.getHeadNode();

    // Loop through each node
    while (currentNode != nullptr) {

        // Get the lower case version of the transaction type for each node
        string nodeTransactionType = currentNode -> transactionObject.transactionType;
        ranges::transform(nodeTransactionType, nodeTransactionType.begin(), ::tolower);

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
 * @return
 */
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