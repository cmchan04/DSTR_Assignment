//
// Created by Lim Beng Rhui on 17/06/2025.
//

#include "DoublyLinkedList.h"
#include <iostream>

using namespace std;

/**
 * Constructor to initialize a node.
 * @param data The pointer to the Transaction object
 */
DoublyLinkedList::Node::Node(const Transaction* data) {

    // First check if a valid object is passed into the method
    if (data == nullptr) throw invalid_argument("Data cannot be null.");

    // Initialize variables
    this -> transactionObject = *data;
    this -> previousNode = nullptr;
    this -> nextNode = nullptr;
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
 * The method to insert the Transaction object into the end of linked list.
 * @param data The Transaction object to be added.
 */
void DoublyLinkedList::insertAtEnd(const Transaction* data) {

    // First create a node for the data
    const auto newNode = new Node(data);

    // Case 1: The list is empty
    if (headNode == nullptr) {

        // The new node automatically becomes both the head and tail node
        headNode = tailNode = newNode;

        // Increment size count and end function here
        size++;
        return;
    }

    // Case 2: The list already has nodes
    // The new node is located at the back of the tail node
    tailNode -> nextNode = newNode;

    // The new node's previous node will be the initial tail node
    newNode -> previousNode = tailNode;

    // And the new node is now the last node, also increment size count
    tailNode = newNode;
    size++;
}

/**
 * The method to display all the information of all the nodes in the linked list.
 */
void DoublyLinkedList::printContents() const {

    // Get the first node
    const Node* currentNode = headNode;
    int index = 1;

    // Print header
    cout << "===== Printing Linked List Contents =====" << endl;

    // Special case: List is empty
    if (headNode == nullptr) {
        cout << "The doubly linked list is empty." << endl;
    }

    // Loop until the node points to nullptr (the last node)
    while (currentNode != nullptr) {

        // Print details
        cout << "[Node at position " << index << "]" << endl;
        cout << "  ID        : " << currentNode -> transactionObject.transactionId << endl;
        cout << "  Amount    : " << currentNode -> transactionObject.amount << endl;
        cout << "  Type      : " << currentNode -> transactionObject.transactionType << endl;
        cout << "  Channel   : " << currentNode -> transactionObject.paymentChannel << endl;
        cout << "  Timestamp : " << currentNode -> transactionObject.timestamp << endl;
        cout << "-----------------------------" << endl;

        // Move to the next node
        currentNode = currentNode -> nextNode;
        index++;
    }
}

/**
 * A method to remove all nodes in the linked list.
 */
void DoublyLinkedList::clear() {

    // Starting with head node
    const Node* currentNode = headNode;

    // Travel through all later nodes until it reaches nullptr
    while (currentNode != nullptr) {

        // Get the location of the next node
        const Node* nextNode = currentNode -> nextNode;

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
