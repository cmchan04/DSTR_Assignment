//
// Created by Lim Beng Rhui on 17/06/2025.
//

#pragma once

#include "Transaction.h"

/**
 * A struct to represent nodes in the linked list
 */
struct Node {

    // A doubly linked list has three elements: data, pointer of previous and next node
    Transaction* transactionObject;
    int indexInList;
    Node* previousNode;
    Node* nextNode;

    // Constructor: Explicit to ensure no implicit conversions take place
    explicit Node(Transaction* data, int index);
};

/**
 * This is the class for representing a doubly linked list.
 */
class DoublyLinkedList {

    // Member attributes to keep track of the linked list
    Node* headNode;
    Node* tailNode;

    // Counter to retrieve the size of linked list
    int size = 0;

public:

    // Constructor, destructor and copy constructor
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList &list);

    // Getters and setters
    [[nodiscard]] Node* getHeadNode() const;
    [[nodiscard]] Node* getTailNode() const;
    void setHeadNode(Node* headNode);
    void setTailNode(Node* tailNode);

    // Insertion methods
    void insertBefore(Node* node, Transaction* data);
    void insertAtEnd(Transaction* data);

    // Print contents
    void printContents() const;

    // Swap between nodes
    void swap(Node* firstNode, Node* secondNode);

    // Other utility methods
    void clear();
    void incrementSize();
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;
};
