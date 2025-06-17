//
// Created by Lim Beng Rhui on 17/06/2025.
//

#pragma once
#include <utility>

#include "Transaction.h"

/**
 * This is the class for representing a doubly linked list.
 */
class DoublyLinkedList {

    // A private struct to represent nodes in the linked list
    struct Node {

        // A doubly linked list has three elements: data, pointer of previous and next node
        Transaction transactionObject;
        Node* previousNode;
        Node* nextNode;

        // Constructor: Explicit to ensure no implicit conversions take place
        explicit Node(const Transaction* data);
    };

    // Member attributes to keep track of the linked list
    Node* headNode;
    Node* tailNode;

    // Counter to retrieve the size of linked list
    int size = 0;

public:

    // Constructor and destructor, with copy constructor prevented
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList&) = delete;

    // Insertion methods
    void insertAtEnd(const Transaction* data);

    // Print contents
    void printContents() const;

    // Other utility methods
    void clear();
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;
};
