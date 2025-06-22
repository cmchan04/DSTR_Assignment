//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include <iostream>
#include "Searcher.h"

#include "StringUtil.h"

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
    ranges::transform(transactionType, transactionType.begin(), ::tolower);

    // Retrieve the starting and ending node of the linked list
    Node* leftNode = list.getHeadNode();
    Node* rightNode = list.getTailNode();

    // Start looping
    while (true) {

        // Special case: The list only contains one or two nodes
        if (leftNode == rightNode || leftNode -> nextNode == rightNode) {

            // First retrieve the strings and convert them to lower case
            string leftNodeTransactionType = leftNode -> transactionObject.transactionType;
            string rightNodeTransactionType;
            ranges::transform(leftNodeTransactionType, leftNodeTransactionType.begin(), ::tolower);

            // Don't repeat the same process if two nodes are the same
            if (leftNode != rightNode) {
                rightNodeTransactionType = rightNode -> transactionObject.transactionType;
                ranges::transform(rightNodeTransactionType, rightNodeTransactionType.begin(), ::tolower);
            }

            // Declare a boolean to mark that index 0 is taken, and mark the output size
            bool indexZeroTaken = false;
            int listSize = 0;

            // Check condition for left node
            if (leftNodeTransactionType == transactionType) {

                // Add the result to the first index
                result[0] = &leftNode -> transactionObject;
                indexZeroTaken = true;
                listSize++;
            }

            // Check condition for right node
            if (rightNodeTransactionType == transactionType) {

                // Get the index for the position to fill and insert the object if match
                const int indexToFill = indexZeroTaken ? 1 : 0;
                result[indexToFill] = &rightNode -> transactionObject;
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
        string retrievedType = middleNode -> transactionObject.transactionType;

        // Now convert the associated transaction type to lower case
        ranges::transform(retrievedType, retrievedType.begin(), ::tolower);

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
            result[0] = &middleNode -> transactionObject;

            // Create a counter to record the index
            int index = 1;

            // Traverse in two ways to pick up the associated transaction objects
            Node* traverseToFront = middleNode -> previousNode;
            Node* traverseToBack = middleNode -> nextNode;

            // Traverse to the front
            while (traverseToFront != nullptr) {

                // Since the linked list is already sorted, the loop ends once the transaction type does not match
                if (traverseToFront -> transactionObject.transactionType != retrievedType) break;

                // If it matches, store the objects into the result list
                result[index] = &traverseToFront -> transactionObject;

                // Move to the previous one
                traverseToFront = traverseToFront -> previousNode;
                index++;
            }

            // Traverse to the back, with similar logic with traverse to the front
            while (traverseToBack != nullptr) {

                // End once the transaction type does not tally
                if (traverseToBack -> transactionObject.transactionType != retrievedType) break;

                // If it matches, store the objects into the result list
                result[index] = &traverseToBack -> transactionObject;

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
