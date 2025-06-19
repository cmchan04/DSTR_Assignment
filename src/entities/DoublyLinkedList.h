//
// Created by Lim Beng Rhui on 17/06/2025.
//

#pragma once

#include "Transaction.h"

/**
 * This is the class for representing a doubly linked list.
 */
class DoublyLinkedList {

    // A private struct to represent nodes in the linked list
    struct Node {

        // A doubly linked list has three elements: data, pointer of previous and next node
        Transaction transactionObject;
        int indexInList;
        Node* previousNode;
        Node* nextNode;

        // Constructor: Explicit to ensure no implicit conversions take place
        explicit Node(const Transaction* data, int index);
    };

    // Member attributes to keep track of the linked list
    Node* headNode;
    Node* tailNode;

    // Counter to retrieve the size of linked list
    int size = 0;

public:

    // Constructor and destructor
    DoublyLinkedList();
    ~DoublyLinkedList();

    // Insertion methods
    void insertAtEnd(const Transaction* data);

    // Print contents
    void printContents() const;

    // Swap between nodes
    void swap(Node* firstNode, Node* secondNode);

    // The swap with Transaction (below) can be removed if not used (bur remained for testing as for now)
    void swap(const Transaction* firstTransaction, const Transaction* secondTransaction);

    // Other utility methods
    void clear();
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;
};
