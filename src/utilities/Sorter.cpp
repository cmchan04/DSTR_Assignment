//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include "Sorter.h"
#include "StringUtil.h"

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
 * This method sorts a linked list based on the transaction type in ascending order.
 * @param list The list to be sorted
 */
DoublyLinkedList Sorter::bubbleSortInList(const DoublyLinkedList &list) {

    // If the list has only one node or is empty, no sorting is required
    if (list.getSize() <= 1) return list;

    // Copy the list into a new one
    DoublyLinkedList sortedList = list;

    // Declare variables to mark if swapping has taken place
    bool swapped;

    // Have a tracker to improve performance
    const Node* stopNode = nullptr;

    // Start a do-while loop: This represents looping through the entire list
    do {

        // First reset the boolean and the last swap node
        swapped = false;
        const Node* lastSwap = sortedList.getTailNode();

        // Get the head node as the start of the list iteration
        Node* currentNode = sortedList.getHeadNode();

        // Go through each pair of nodes
        while (currentNode != stopNode && currentNode -> nextNode != stopNode) {

            // Get the two nodes
            Node* leftNode = currentNode;
            Node* rightNode = currentNode -> nextNode;

            // Get the information from the two nodes
            const string leftID = leftNode -> transactionObject.transactionId;
            string leftTransactionType = toLowerCase(leftNode -> transactionObject.transactionType);
            const string rightID = rightNode -> transactionObject.transactionId;
            string rightTransactionType = toLowerCase(rightNode -> transactionObject.transactionType);

            // Compare the information. If the criteria is not met, swapping is performed
            if (leftTransactionType > rightTransactionType ||
                (leftTransactionType == rightTransactionType && leftID > rightID)) {

                // Swapping occurs
                sortedList.swap(leftNode, rightNode);

                // Now the left becomes the right node, and vice versa. So, the rightmost one is actually the left node
                swapped = true;
                lastSwap = leftNode;
                currentNode = rightNode -> nextNode;

            // If no swapping is done
            } else {

                // Traverse to the next node
                currentNode = leftNode -> nextNode;
            }
        }

        // Declare the node where the loop shall stop
        stopNode = lastSwap;

    // The linked list is iterated again as long as swapping takes place between the process
    } while (swapped);

    // After done, return the list
    return sortedList;
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
 * This method performs an insertion sort on Transaction objects based on their transaction types.
 * @param list The list to be sorted
 * @return The sorted list without modifying the original list
 */
DoublyLinkedList Sorter::insertionSortInList(const DoublyLinkedList &list) {

    // If the list does not contain anything or only has one node, do nothing
    if (list.getSize() <= 1) return list;

    // Create a new linked list to store the sorted results
    auto* sortedList = new DoublyLinkedList();

    // Retrieve the first node and start the loop
    const Node* currentNode = list.getHeadNode();
    while (currentNode != nullptr) {

        // Retrieve the transaction ID and type of the object for the current node
        Transaction currentObject = currentNode -> transactionObject;
        string currentID = currentObject.transactionId;
        string currentType = toLowerCase(currentObject.transactionType);

        // If the sorted list is empty
        if (sortedList -> isEmpty()) {

            // Insert the transaction object to the node and go to the next iteration
            sortedList -> insertAtEnd(&currentObject);
            currentNode = currentNode -> nextNode;
            continue;
        }

        // Create a variable to record if insertion has taken place
        bool inserted = false;

        // If the list is not empty, we have to go through the sorted list linearly.
        // Start from tail and go backward (matching array insertion sort)
        const Node* currentSortedNode = sortedList -> getTailNode();
        while (currentSortedNode != nullptr) {

            // Retrieve the information of the current node in the sorted list
            string currentSortedType = toLowerCase(currentSortedNode->transactionObject.transactionType);
            string currentSortedID = currentSortedNode->transactionObject.transactionId;

            // Compare. Insertion shall take place if the node has a value greater than the sorted one
            if (currentType > currentSortedType ||
                (currentType == currentSortedType && currentID > currentSortedID)) {

                // Insert the node after this sorted node, i.e., before the next sorted node if there is a next
                if (currentSortedNode -> nextNode != nullptr) {
                    sortedList -> insertBefore(currentSortedNode -> nextNode, &currentObject);

                // If the sorted node is no next, the node is a tail
                } else {

                    // Add the node as a tail
                    sortedList -> insertAtEnd(&currentObject);
                }

                // Mark that an insertion has taken place, hence loop exits
                inserted = true;
                break;
            }

            // Move to the next previous node
            currentSortedNode = currentSortedNode->previousNode;
        }

        // If the node is not inserted, insert at the beginning
        if (!inserted) sortedList->insertBefore(sortedList -> getHeadNode(), &currentObject);

        // Move to the next node
        currentNode = currentNode -> nextNode;
    }

    // Return the sorted list once finished
    return *sortedList;
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
    mergeSortDividerInArray(transactions, 0, size - 1, column, ascending);
}

/**
 * This helper method act as a divider to divide and sort each segment
 * @param transactions array to be sorted
 * @param left index of left boundary
 * @param right index of right boundary
 * @param column targeted column name
 * @param ascending sort in ascending or descending \code true\endcode indicates ascending, \code false\endcode indicates descending
 */
void Sorter::mergeSortDividerInArray(Transaction *transactions, const int left, const int right,
                              const string &column, const bool ascending) {

    // Divide the array into two if input is valid
    if (left < right) {

        // Locate the central point
        const int median = (left + right) / 2;

        // Divide into left and right half
        mergeSortDividerInArray(transactions, left, median, column, ascending);
        mergeSortDividerInArray(transactions, median + 1, right, column, ascending);

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

/**
 * This method sorts a list based on the merge sort algorithm.
 * @param list The list to be sorted
 * @return A list sorted using the merge sort algorithm
 */
DoublyLinkedList Sorter::mergeSortInList(const DoublyLinkedList &list) {

    // Overall idea: Split each element individually, then sort while merge.

    // Do nothing if the list has one node or less
    if (list.getSize() <= 1) return list;

    // Create a new list and retrieve the first node
    DoublyLinkedList sortedList = list;
    Node* headNode = sortedList.getHeadNode();

    // Perform a recursive split and sort based on the head node
    headNode = recursiveSplitAndSortInList(headNode);

    // Reassign the tail node by traversing through the entire linked list
    Node* tailNode = headNode;
    while (tailNode != nullptr && tailNode -> nextNode != nullptr) {
        tailNode = tailNode -> nextNode;
    }

    // Set the head and tail node after sorting
    sortedList.setHeadNode(headNode);
    sortedList.setTailNode(tailNode);

    // Return the sorted list once done
    return sortedList;
}

/**
 * This is a recursive method that splits the linked list into individual nodes before sorting and combining them again.
 * @param headNode The head node for the linked list
 * @return The head node of a new linked list that is sorted
 */
Node* Sorter::recursiveSplitAndSortInList(Node* headNode) {

    // The base case: The head node cannot be split anymore
    if (headNode == nullptr || headNode -> nextNode == nullptr) return headNode;

    // First, find the middle node. The next node after the middle node marks the start of the second half part.
    Node* middle = getMiddleNodeForList(headNode);
    Node* secondHalfStart = middle -> nextNode;

    // Next, split the list into two halves by setting null pointers
    middle -> nextNode = nullptr;                      // First half
    secondHalfStart -> previousNode = nullptr;         // Second half

    // Both halves are split again recursively
    Node* leftHalf = recursiveSplitAndSortInList(headNode);
    Node* rightHalf = recursiveSplitAndSortInList(secondHalfStart);

    // Merge both halves
    return mergeNodesForList(leftHalf, rightHalf);
}

/**
 * This method retrieves the node located at the center of a linked list.
 * @param headNode The head node of the linked list
 * @return The node located at the center of the list
 */
Node* Sorter::getMiddleNodeForList(Node* headNode) {

    // If the list has no node or only one node, end the recursion
    if (headNode == nullptr || headNode->nextNode == nullptr) return headNode;

    // If not, we will have two types of traversals
    Node* slow = headNode;
    const Node* fast = headNode;

    // Make sure that after traversal there are still nodes
    while (fast -> nextNode != nullptr && fast -> nextNode -> nextNode != nullptr) {

        // Slow travels one step, fast travels two steps
        slow = slow -> nextNode;
        fast = fast -> nextNode -> nextNode;
    }

    // The slow (middle) node is returned
    return slow;
}

/**
 * This method combines two linked lists and returns the head node of the sorted linked list
 * @param nodeInLeft The head node in the first linked list
 * @param nodeInRight The head node in the second list
 * @return The head node in the combined and sorted linked list
 */
Node* Sorter::mergeNodesForList(Node* nodeInLeft, Node* nodeInRight) {

    // Show warning if the input is null
    if (nodeInLeft == nullptr && nodeInRight == nullptr) throw invalid_argument("Inputs cannot be null");

    // Declare pointers to help manage the merged list
    Node* head = nullptr;
    Node* tail = nullptr;

    // Declare a variable to store index
    int nodeIndex = 1;

    // When the first in left node, and the first in right node, are available.
    // Imagine: Left = [transaction1, transaction2], Right = [transaction3, transaction4]
    while (nodeInLeft != nullptr && nodeInRight != nullptr) {

        // Retrieve the objects in the first of both parts
        Transaction &leftObject = nodeInLeft -> transactionObject;
        Transaction &rightObject = nodeInRight -> transactionObject;

        // Declare a boolean to mark our choice
        bool chooseLeft = false;

        // First retrieve the transaction type to compare
        const string leftType = toLowerCase(leftObject.transactionType);
        const string rightType = toLowerCase(rightObject.transactionType);

        // If the type on the left is smaller than the right ("a" < "b"), choose the left
        if (leftType < rightType) {
            chooseLeft = true;

        // Another scenario, if both types match
        } else if (leftType == rightType) {

            // We compare ID. Choose left if the left ID is smaller
            chooseLeft = leftObject.transactionId < rightObject.transactionId;
        }

        // Retrieve the selected node
        Node* selectedNode = chooseLeft ? nodeInLeft : nodeInRight;
        Node* nextNode = selectedNode -> nextNode;

        // Break any linkages associated with the selected node
        selectedNode -> previousNode = nullptr;
        selectedNode -> nextNode = nullptr;

        // Set up the new sorted list: First node
        if (head == nullptr) {

            // The head and tail will be the selected node
            head = tail = selectedNode;
            selectedNode -> previousNode = nullptr;
            selectedNode -> nextNode = nullptr;
            selectedNode -> indexInList = nodeIndex++;

        // Following nodes
        } else if (tail != nullptr) {

            // Attach the node to the tail
            tail -> nextNode = selectedNode;
            selectedNode -> previousNode = tail;

            // And update its index
            selectedNode -> indexInList = nodeIndex++;

            // And the new node now becomes the tail
            tail = selectedNode;
        }

        // If the left is chosen (the left Transaction shall be arranged first)
        if (chooseLeft) {

            // Move on to the next node
            nodeInLeft = nextNode;

        // If the right is chosen
        } else {

            // Move to the next right node
            nodeInRight = nextNode;
        }
    }

    // If no comparisons are made (one side is already blank), attach it to the rightmost
    Node* remainingNode = nodeInLeft != nullptr ? nodeInLeft : nodeInRight;
    while (remainingNode != nullptr && tail != nullptr) {

        // Store the next node before breaking links
        Node* nextNode = remainingNode -> nextNode;

        // Add the node to the list
        tail -> nextNode = remainingNode;
        remainingNode -> previousNode = tail;
        tail = remainingNode;

        // Update the index of the node
        remainingNode -> indexInList = nodeIndex++;

        // Move on to the next node
        remainingNode = nextNode;
    }

    // The tail must point to null at the last
    if (tail != nullptr) tail -> nextNode = nullptr;

    // Return the first node in the list
    return head;
}

/**
 * This method sorts a list using the quick sort algorithm based on the transaction type.
 * @param list The list to be sorted
 * @return The sorted list based on the transaction type
 */
DoublyLinkedList Sorter::quickSortInList(const DoublyLinkedList& list) {

    // Overall idea: Pick a pivot, partition based on pivot, and sort recursively

    // First retrieve the head and tail node of the list
    Node* headNode = list.getHeadNode();
    Node* tailNode = list.getTailNode();

    // Perform recursive action on quick sort. This returns the head node of the sorted list.
    Node* sortedNode = quickSortRecursiveForList(headNode, tailNode);

    // Create a new linked list
    DoublyLinkedList sortedList;

    // Check if the sorted node is null. If no, sorting is successful
    if (sortedNode != nullptr) {

        // Set the index for the first node
        int index = 1;
        sortedNode -> indexInList = index++;

        // Set the head node for the new linked list and increase size record
        sortedList.setHeadNode(sortedNode);
        sortedList.incrementSize();

        // Find the tail node
        Node* endingNode = sortedNode;
        while (endingNode -> nextNode != nullptr) {

            // Get the next node, set index and increase size
            endingNode = endingNode -> nextNode;
            endingNode -> indexInList = index++;
            sortedList.incrementSize();
        }

        // Set the tail node
        sortedList.setTailNode(endingNode);
    }

    // Lastly, return the sorted list
    return sortedList;
}

/**
 * This method performs recursive actions to partition the list and perform sorting.
 * @param head The head node of a list
 * @param tail The tail node of a list
 * @return The head node of the sorted list
 */
Node* Sorter::quickSortRecursiveForList(Node* head, Node* tail) {

    // For empty inputs, or if the list cannot be partitioned anymore, return the node
    if (head == nullptr || head == tail) return head;

    // Declare variables to represent the new head and tail nodes
    Node* leftNodes = nullptr;
    Node* rightNodes = nullptr;

    // Partition the list into two based on the last node, returning three information: pivot node, the head of the left and tail of the right
    Node* pivot = quickSortPartitionForList(head, tail, &leftNodes, &rightNodes);

    // We'll assume the pivot belongs to the right part
    // If the left part exist
    if (leftNodes != pivot) {

        // Retrieve the node before the pivot
        Node* leftFinalNode = pivot -> previousNode;

        // Temporarily break the connection of the left part
        if (leftFinalNode != nullptr) leftFinalNode -> nextNode = nullptr;
        pivot -> previousNode = nullptr;

        // Recursively continue the recursive sort
        leftNodes = quickSortRecursiveForList(leftNodes, leftFinalNode);

        // Find the tail of the new sorted left part
        Node* leftEndingNode = leftNodes;
        while (leftEndingNode -> nextNode != nullptr) leftEndingNode = leftEndingNode -> nextNode;

        // Reattach the ending node to the pivot
        leftEndingNode -> nextNode = pivot;
        pivot -> previousNode = leftEndingNode;
    }

    // Taking care of the right part
    pivot -> nextNode = quickSortRecursiveForList(pivot -> nextNode, rightNodes);

    // If the pivot has a next node, reestablish the connection
    if (pivot -> nextNode) pivot -> nextNode -> previousNode = pivot;

    // Return the first node in the sorted list at last
    return leftNodes;
}

/**
 * This method arranges the nodes based on the pivot.
 * @param head The initial head node of the linked list
 * @param tail The initial tail node of the linked list
 * @param leftNodes The new head node of the left portion
 * @param rightNodes The new tail node of the right portion
 * @return The pivot assigned throughout the sorting process.
 */
Node* Sorter::quickSortPartitionForList(Node* head, Node* tail, Node** leftNodes, Node** rightNodes) {

    // First, let the tail node be the pivot
    Node* pivot = tail;

    // We use median-of-three value strategy here. We first retrieve the middle node
    Node* middleNode = getMiddleNodeForList(head);

    // We compare the values from the head, middle and tail nodes
    string headType = toLowerCase(head->transactionObject.transactionType);
    string headID = head->transactionObject.transactionId;

    string middleType = toLowerCase(middleNode->transactionObject.transactionType);
    string middleID = middleNode->transactionObject.transactionId;

    string tailType = toLowerCase(tail->transactionObject.transactionType);
    string tailID = tail->transactionObject.transactionId;

    // Perform comparison between different nodes
    bool headLessMiddle = (headType < middleType) || (headType == middleType && headID < middleID);
    bool middleLessTail = (middleType < tailType) || (middleType == tailType && middleID < tailID);
    bool headLessTail = (headType < tailType) || (headType == tailType && headID < tailID);

    // Declare a median node
    Node* medianNode;

    // Based on comparison, determine the median node. We have six possible combinations here (3! = 6).
    // Condition: head < middle
    if (headLessMiddle) {

        // head < middle < tail
        if (middleLessTail) medianNode = middleNode;

        // head < tail < middle
        else if (headLessTail) medianNode = tail;

        // tail < head < middle
        else medianNode = head;

    // Condition: middle < head
    } else {

        // middle < head < tail
        if (headLessTail) medianNode = head;

        // middle < tail < head
        else if (middleLessTail) medianNode = tail;

        // tail < middle < head
        else medianNode = middleNode;
    }

    // Swap the data (not swapping pointers) from the median to the tail
    if (medianNode != tail) {

        // Retrieve the transaction object from the median node
        Transaction tempTransaction = medianNode -> transactionObject;

        // Perform swapping
        medianNode -> transactionObject = tail -> transactionObject;
        tail -> transactionObject = tempTransaction;
    }

    // Median-of-three done. Now, get values from the pivot / tail
    const string pivotID = pivot -> transactionObject.transactionId;
    const string pivotType = toLowerCase(pivot -> transactionObject.transactionType);

    // Reset the variables to contain left and right nodes
    *leftNodes = nullptr;
    *rightNodes = nullptr;

    // Keep track of the original tail for right partition
    Node* rightTail = tail;

    // Starting with the leftmost and traverse to the pivot
    Node* currentNode = head;
    while (currentNode != pivot) {

        // Retrieve the next node before modifying the current node
        Node* nextNode = currentNode -> nextNode;

        // Retrieve the information associated
        const string currentID = currentNode -> transactionObject.transactionId;
        const string currentType = toLowerCase(currentNode -> transactionObject.transactionType);

        // Make comparisons on the transaction type
        if (currentType > pivotType ||
            (currentType == pivotType && currentID > pivotID)) {

            // Remove current node from its current position
            if (currentNode -> previousNode) {
                currentNode -> previousNode -> nextNode = currentNode -> nextNode;
            }
            if (currentNode -> nextNode) {
                currentNode -> nextNode -> previousNode = currentNode -> previousNode;
            }

            // Add to the right partition (after pivot)
            rightTail -> nextNode = currentNode;
            currentNode -> previousNode = rightTail;
            currentNode -> nextNode = nullptr;

            // Update right tail pointer
            rightTail = currentNode;

        // If no switching takes place
        } else {

            // Node stays in left partition
            if (*leftNodes == nullptr) {
                *leftNodes = currentNode;
            }
        }

        // Move on to the next node
        currentNode = nextNode;
    }

    // If no left nodes, pivot becomes the first node
    if (*leftNodes == nullptr) *leftNodes = pivot;

    // Set the right tail and return the pivot
    *rightNodes = rightTail;
    return pivot;
}

/**
 * This method get the pivot index by determining the median of three
 * @param transactions array to be sorted
 * @param leftIndex starting index of partition
 * @param rightIndex ending index of partition
 * @param column column name to be sorted on (location or transaction type (type))
 * @return returns the pivot index
 */
int getMedianIndex(Transaction* transactions, int leftIndex, int rightIndex, const string &column) {

    // Get the current median index (pivot index)
    int medianIndex = leftIndex + (rightIndex - leftIndex) / 2;

    // Retrieve location or transaction type based on column
    string left = toLowerCase(column == "type" ? transactions[leftIndex].transactionType : transactions[leftIndex].location);
    string median = toLowerCase(column == "type" ? transactions[medianIndex].transactionType : transactions[medianIndex].location);
    string right = toLowerCase(column == "type" ? transactions[rightIndex].transactionType : transactions[rightIndex].location);

    // Check which is the median of three objects and return as pivot
    if ((left <= median && median <= right) || (right <= median && median <= left))
        return medianIndex;
    else if ((median <= left && left <= right) || (right <= left && left <= median))
        return leftIndex;
    else
        return rightIndex;
}

