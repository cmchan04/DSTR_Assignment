//
// Created by Lim Beng Rhui on 17/06/2025.
//

#include "DoublyLinkedList.h"
#include <iostream>

using namespace std;

/**
 * Constructor to initialize a node.
 * @param data The pointer to the Transaction object
 * @param index The current size of the linked list. This acts as the index for the node (since no deletion is involved).
 */
Node::Node(const Transaction* data, const int index) {

    // First check if a valid object is passed into the method
    if (data == nullptr) throw invalid_argument("Data cannot be null.");

    // Initialize variables
    this -> transactionObject = data;
    this -> previousNode = nullptr;
    this -> nextNode = nullptr;
    this -> indexInList = index;
}

/**
 * The constructor to create an empty linked list.
 */
DoublyLinkedList::DoublyLinkedList() {

    // A new list does not have any nodes, hence both head and tail are nullptr
    this -> headNode = nullptr;
    this -> tailNode = nullptr;
}

/**
 * The destructor that removes all nodes from the linked list.
 */
DoublyLinkedList::~DoublyLinkedList() {

    // Has the same function as clear()
    clear();
}

/**
 * This method copies a new linked list without any overlapping components.
 * @param list The original linked list
 */
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& list): headNode(nullptr), tailNode(nullptr) {

    // Get the head node as the first node
    const Node* current = list.headNode;

    // Loop through each node
    while (current != nullptr) {

        // Add each transaction to the end of the list
        this -> insertAtEnd(current -> transactionObject);
        current = current -> nextNode;
    }
}

/**
 * The getter to get the first node of the list.
 * @return The first node of the list
 */
Node* DoublyLinkedList::getHeadNode() const {
    return this -> headNode;
}

/**
 * The getter to get the last node of the list.
 * @return The last node of the list
 */
Node* DoublyLinkedList::getTailNode() const {
    return this -> tailNode;
}

/**
 * The setter to set the new head node for the linked list
 * @param headNode The new head node of the linked list
 */
void DoublyLinkedList::setHeadNode(Node* headNode) {
    this -> headNode = headNode;
}

/**
 * The setter to set the new tail node for the linked list
 * @param tailNode The new tail node of the linked list
 */
void DoublyLinkedList::setTailNode(Node* tailNode) {
    this -> tailNode = tailNode;
}

/**
 * A method that adds a Transaction before a specified node.
 * @param node The node that will be placed after the new node
 * @param data The Transaction object
 */
void DoublyLinkedList::insertBefore(Node* node, const Transaction* data) {

    // Overall idea: Three nodes have to be set up. The specified node, the previous node of the specified node, and the new node.

    // First reject empty nodes or empty data
    if (node == nullptr || data == nullptr) throw invalid_argument("Input cannot be null.");

    // Retrieve the index of the specified node
    const int index = node -> indexInList;

    // Create a new node for the new Transaction object
    auto* newNode = new Node(data, index);

    // Set up the new node
    newNode -> nextNode = node;
    newNode -> previousNode = node->previousNode;

    // Handle the node before the specified node. Special case if the node is head node
    if (node -> previousNode == nullptr) headNode = newNode;

    // If not, reassign the pointer of the previous node
    else node -> previousNode -> nextNode = newNode;

    // Handle the specified node. Only the previous node is changed to the new node
    node -> previousNode = newNode;

    // Update the index of the later nodes
    for (Node* updateNodes = node; updateNodes != nullptr; updateNodes = updateNodes -> nextNode) {
        updateNodes -> indexInList++;
    }

    // Lastly, update the size of the linked list
    size++;
}

/**
 * The method to insert the Transaction object into the end of linked list.
 * @param data The Transaction object to be added.
 */
void DoublyLinkedList::insertAtEnd(const Transaction* data) {

    // First create a node for the data
    const auto newNode = new Node(data, ++size);

    // Case 1: The list is empty
    if (headNode == nullptr || tailNode == nullptr) {

        // The new node automatically becomes both the head and tail node
        headNode = tailNode = newNode;

        // End function here
        return;
    }

    // Case 2: The list already has nodes
    // The new node is located at the back of the tail node
    tailNode -> nextNode = newNode;

    // The new node's previous node will be the initial tail node
    newNode -> previousNode = tailNode;

    // And the new node is now the last node
    tailNode = newNode;
}

/**
 * The method to display all the information of all the nodes in the linked list.
 */
void DoublyLinkedList::printContents() const {

    // Get the first node
    const Node* currentNode = headNode;

    // Print header
    cout << "===== Printing Linked List Contents =====" << endl;

    // Special case: List is empty
    if (headNode == nullptr) {
        cout << "The doubly linked list is empty." << endl;
    }

    // Loop until the node points to nullptr (the last node)
    while (currentNode != nullptr) {

        // Print details
        cout << "[Node at position " << currentNode -> indexInList << "]" << endl;
        cout << "  ID        : " << currentNode -> transactionObject -> transactionId << endl;
        cout << "  Amount    : " << currentNode -> transactionObject -> amount << endl;
        cout << "  Type      : " << currentNode -> transactionObject -> transactionType << endl;
        cout << "  Channel   : " << currentNode -> transactionObject -> paymentChannel << endl;
        cout << "  Timestamp : " << currentNode -> transactionObject -> timestamp << endl;
        cout << "  Location  : " << currentNode -> transactionObject -> location << endl;
        cout << "-----------------------------" << endl;

        // Move to the next node
        currentNode = currentNode -> nextNode;
    }
}

/**
 * This method swaps two nodes in the linked list. This will be useful for later sorts.
 * @param firstNode The first node to be swapped
 * @param secondNode The other node to be swapped
 */
void DoublyLinkedList::swap(Node* firstNode, Node* secondNode) {

    // Reject null nodes
    if (firstNode == nullptr || secondNode == nullptr) throw invalid_argument("Node cannot be null.");

    // Do nothing for similar nodes
    if (firstNode == secondNode) return;

    // First exchange the index of both nodes
    const int firstNodeIndex = firstNode -> indexInList;
    firstNode -> indexInList = secondNode -> indexInList;
    secondNode -> indexInList = firstNodeIndex;

    // Special case: One of the nodes is the head node
    if (headNode == firstNode) headNode = secondNode;
    else if (headNode == secondNode) headNode = firstNode;

    // Special case: One of the nodes is the tail node
    if (tailNode == firstNode) tailNode = secondNode;
    else if (tailNode == secondNode) tailNode = firstNode;

    // Handle the special case: The next node of the second node is the first node. We swap both nodes here.
    if (secondNode -> nextNode == firstNode) {
        Node* tempNode = firstNode;
        firstNode = secondNode;
        secondNode = tempNode;
    }

    // Now can check for the special case: Adjacent nodes are handled separately
    if (firstNode -> nextNode == secondNode) {

        // Only need to handle the nodes before the first node and after the second node
        Node* beforeNode = firstNode -> previousNode;
        Node* afterNode = secondNode -> nextNode;

        // Change the linking nodes for the two neighboring nodes
        if (beforeNode) beforeNode -> nextNode = secondNode;
        if (afterNode) afterNode -> previousNode = firstNode;

        // Modify the current swapping nodes
        firstNode -> previousNode = secondNode;
        firstNode -> nextNode = afterNode;
        secondNode -> previousNode = beforeNode;
        secondNode -> nextNode = firstNode;

        // End operation here
        return;
    }

    // Retrieve the neighbor nodes
    Node* firstNodePrev = firstNode -> previousNode;
    Node* firstNodeNext = firstNode -> nextNode;
    Node* secondNodePrev = secondNode -> previousNode;
    Node* secondNodeNext = secondNode -> nextNode;

    // Reestablish connection of neighbor nodes to correct nodes
    if (firstNodePrev != nullptr) firstNodePrev -> nextNode = secondNode;
    if (firstNodeNext != nullptr) firstNodeNext -> previousNode = secondNode;
    if (secondNodePrev != nullptr) secondNodePrev -> nextNode = firstNode;
    if (secondNodeNext != nullptr) secondNodeNext -> previousNode = firstNode;

    // Swap the elements of the swapping node
    firstNode -> previousNode = secondNode -> previousNode;
    firstNode -> nextNode = secondNode -> nextNode;
    secondNode -> previousNode = firstNodePrev;
    secondNode -> nextNode = firstNodeNext;
}

/**
 * A method to remove all nodes in the linked list.
 */
void DoublyLinkedList::clear() {

    // Starting with head node
    Node* currentNode = headNode;

    // Travel through all later nodes until it reaches nullptr
    while (currentNode != nullptr) {

        // Get the location of the next node
        Node* nextNode = currentNode -> nextNode;

        // Remove everything in the current node
        delete currentNode;

        // And traverse to the next node (next pointer)
        currentNode = nextNode;
    }

    // And lastly, reset head and tail nodes with size
    headNode = nullptr;
    tailNode = nullptr;
    size = 0;
}

/**
 * A method to increment the recorded size of a linked list.
 */
void DoublyLinkedList::incrementSize() {
    this -> size++;
}

/**
 * A method that returns the size of the linked list
 * @return The size of the linked list in \code int\endcode.
 */
int DoublyLinkedList::getSize() const {

    // Return the size
    return size;
}

/**
 * A method that checks if a linked list has any nodes.
 * @return \code true\endcode if the list is empty, \code false\endcode otherwise
 */
bool DoublyLinkedList::isEmpty() const {

    // Check the size of the list
    return size == 0;
}
