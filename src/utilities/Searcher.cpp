//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include <iostream>
#include "Searcher.h"
#include "StringUtil.h"

using namespace std;

/**
 * This method searches for a specific transaction type
 * @param transactions array parsed in to search
 * @param size size of the parsed array
 * @param searchType transaction type to search
 * @param resultCount number of total results
 * @return The pointer to an array with only the transaction type searched
 */
Transaction** Searcher::linearSearchUsingArray(Transaction* transactions, const int size, const string &searchType,
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
        string nodeTransactionType = currentNode -> transactionObject -> transactionType;
        nodeTransactionType = toLowerCase(nodeTransactionType);

        // Check if the current node matches condition
        if (nodeTransactionType == transactionType) {

            // Add the transaction object to the array
            result[matchCount] = currentNode -> transactionObject;

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
 * A method that performs search for a specific transaction by using binary search.
 * @param transactions The array of transactions involved
 * @param size The total size of the array
 * @param searchType The transaction type to be searched
 * @param resultCount The final size of the result
 * @return A transaction list consisting of the filtered results
 */
Transaction** Searcher::binarySearchUsingArray(Transaction* transactions, const int size, const string &searchType,
                                              int &resultCount){
    // Initialize the counter
    resultCount = 0;

    // Convert search type input to lowercase
    const string type = toLowerCase(searchType);

    // Declare an array with maximum size to store results
    auto** result = new Transaction*[size];

    // Declare different indices to track the traversal process
    int sortIndex = 0, leftBoundary = 0, rightBoundary = size - 1, foundIndex = -1;

    // Continue the splitting process as long as the indices are still valid
    while (leftBoundary <= rightBoundary) {

        // Get the middle index
        const int median = (leftBoundary + rightBoundary) / 2;

        // Extract the transaction type associated with the middle index
        string midType = toLowerCase(transactions[median].transactionType);

        // If the type matches
        if (midType == type) {

            // The index where the result is found is recorded, and the loop ends
            foundIndex = median;
            break;
        }

        // If the type does not match (type is located at the right), move to the right section
        if (midType < type) leftBoundary = median + 1;

        // Otherwise, move to the left
        else if (midType > type) rightBoundary = median - 1;
    }

    // If no record matches, return null
    if (foundIndex == -1) {
        cout << "No records are found with transaction type (" << searchType << "). \n" << endl;
        return nullptr;
    }

    // Declare the starting index of matching results
    int leftStart = foundIndex, rightStart = foundIndex;

    // Decrement the start index until all matching transactions on the right are included
    while (leftStart > 0 && toLowerCase(transactions[leftStart - 1].transactionType) == type) {
        --leftStart;
    }

    // Increment the starting index until all matching transactions on the right are included
    while (rightStart < size - 1 && toLowerCase(transactions[rightStart + 1].transactionType) == type) {
        ++rightStart;
    }

    // Store array of pointers to matched results
    for (int i = leftStart; i <= rightStart; ++i) {
        result[sortIndex++] = &transactions[i];
    }

    // Trim the size of result array
    removeUnusedIndex(result, size, sortIndex);

    // Set result count and return it
    resultCount = sortIndex;

    return result;
}

/**
 * A method to search for Transaction objects using binary search.
 * @param list The overall list containing all data
 * @param transactionType The type of transaction (deposit, cash, etc.) that the method will search for
 * @param outputSize The size of the search
 * @return A list of Transaction pointers that matches the search criteria
 */
Transaction** Searcher::binarySearchUsingList(const DoublyLinkedList &list, string &transactionType, int &outputSize) {

    // Check if the list is empty
    if (list.isEmpty()) {

        // Return null without doing search
        outputSize = 0;
        return nullptr;
    }

    // First declare an output size of 0 to reset the variable's value
    outputSize = 0;

    // First create a list with maximum size
    const int maximumSize = list.getSize();
    auto** result = new Transaction*[maximumSize];

    // Preprocess the transaction type string to lower case
    toLowerCase(transactionType);

    // Retrieve the starting and ending node of the linked list
    Node* leftNode = list.getHeadNode();
    Node* rightNode = list.getTailNode();

    // Start looping
    while (true) {

        // Special case: The list only contains one or two nodes
        if (leftNode == rightNode || leftNode -> nextNode == rightNode) {

            // First retrieve the strings and convert them to lower case
            string leftNodeTransactionType = leftNode -> transactionObject -> transactionType;
            string rightNodeTransactionType;
            toLowerCase(leftNodeTransactionType);

            // Don't repeat the same process if two nodes are the same
            if (leftNode != rightNode) {
                rightNodeTransactionType = rightNode -> transactionObject -> transactionType;
                toLowerCase(rightNodeTransactionType);
            }

            // Declare a boolean to mark that index 0 is taken, and mark the output size
            bool indexZeroTaken = false;
            int listSize = 0;

            // Check condition for left node
            if (leftNodeTransactionType == transactionType) {

                // Add the result to the first index
                result[0] = leftNode -> transactionObject;
                indexZeroTaken = true;
                listSize++;
            }

            // Check condition for right node
            if (rightNodeTransactionType == transactionType) {

                // Get the index for the position to fill and insert the object if match
                const int indexToFill = indexZeroTaken ? 1 : 0;
                result[indexToFill] = rightNode -> transactionObject;
                listSize++;
            }

            // Since this is the last loop, we shall return the list size and end the loop here
            outputSize = listSize;
            break;
        }

        // Retrieve the middle node
        Node* middleNode = getMiddleNode(leftNode, rightNode);

        // If middle node is null then end the function
        if (middleNode == nullptr) return nullptr;

        // If not, we retrieve the transaction type for the middle node
        string retrievedType = middleNode -> transactionObject -> transactionType;

        // Now convert the associated transaction type to lower case
        toLowerCase(retrievedType);

        // Compare the types: If the correct node is at the right of the middle
        if (retrievedType < transactionType) {
            leftNode = middleNode -> nextNode;
            continue;
        }

        // If the correct node is at the left of the middle
        if (retrievedType > transactionType) {
            rightNode = middleNode -> previousNode;
            continue;
        }

        // If the middle is one of the correct nodes
        if (retrievedType == transactionType) {

            // First place the transaction object associated with the middle node into the list
            result[0] = middleNode -> transactionObject;

            // Create a counter to record the index
            int index = 1;

            // Traverse in two ways to pick up the associated transaction objects
            Node* traverseToFront = middleNode -> previousNode;
            Node* traverseToBack = middleNode -> nextNode;

            // Traverse to the front
            while (traverseToFront != nullptr) {

                // Since the linked list is already sorted, the loop ends once the transaction type does not match
                if (traverseToFront -> transactionObject -> transactionType != retrievedType) break;

                // If it matches, store the objects into the result list
                result[index] = traverseToFront -> transactionObject;

                // Move to the previous one
                traverseToFront = traverseToFront -> previousNode;
                index++;
            }

            // Traverse to the back, with similar logic with traverse to the front
            while (traverseToBack != nullptr) {

                // End once the transaction type does not tally
                if (traverseToBack -> transactionObject -> transactionType != retrievedType) break;

                // If it matches, store the objects into the result list
                result[index] = traverseToBack -> transactionObject;

                // Move to the previous one
                traverseToBack = traverseToBack -> nextNode;
                index++;
            }

            // Update the actual size of the array and exit
            outputSize = index;
            break;
        }
    }

    // If there is no result, null is returned
    if (outputSize == 0) {

        // Deallocate memory and return null
        delete[] result;
        return nullptr;
    }

    // Remove the unused spaces in the list
    removeUnusedIndex(result, maximumSize, outputSize);

    // Return the final result
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
 * A method to retrieve the middle node given a range of nodes.
 * @param startNode The beginning node
 * @param endNode The ending node
 * @return The middle node
 */
Node* Searcher::getMiddleNode(Node* startNode, const Node* endNode) {

    // Reject if the start node is null and start node is immediately followed by the end node
    if (startNode == nullptr || startNode -> nextNode == endNode) return nullptr;

    // Beginning with the start node, we go with two types of traversal
    Node* slow = startNode;
    const Node* fast = startNode;

    // Traversal begins here
    while (fast != endNode && fast -> nextNode != endNode) {

        // Fast node traverse for two steps
        fast = fast -> nextNode;
        if (fast != endNode) fast = fast -> nextNode;

        // Slow node traverse for one step
        slow = slow -> nextNode;
    }

    // The slow node (middle) is returned
    return slow;
}
