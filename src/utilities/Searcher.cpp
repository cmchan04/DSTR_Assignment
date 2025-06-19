//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include <iostream>
#include "Searcher.h"

using namespace std;

Transaction** Searcher::linearSearchUsingList(const DoublyLinkedList &list, string &transactionType, int &outputSize) {

    // Checking: is the list empty?
    if (list.isEmpty()) {

        // Exit the program immediately
        outputSize = 0;
        return nullptr;
    }

    // First declare a new list to store results (with maximum size) with a counter
    auto** result = new Transaction*[list.getSize()];
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
    if (matchCount < list.getSize()) {

        // Create a new temporary list
        auto** tempList = new Transaction*[matchCount];

        // Move all search results into the temporary list
        for (int i = 0; i < matchCount; i++) {
            tempList[i] = result[i];
        }

        // Now replace the result with the temporary list
        delete[] result;
        result = tempList;
    }

    // Return the output size and search result
    outputSize = matchCount;
    return result;
}
