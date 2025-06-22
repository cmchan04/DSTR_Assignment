//
// Created by Lim Beng Rhui on 11/06/2025.
//

// Make sure the header file is only included once in the program
#pragma once

#include "../entities/DoublyLinkedList.h"

class Sorter {

public:

    // Bubble sort
    static DoublyLinkedList bubbleSortInList(const DoublyLinkedList &list);

    // Insertion sort
    static DoublyLinkedList insertionSortInList(const DoublyLinkedList &list);

    // Merge sort with utility functions
    static DoublyLinkedList mergeSortInList(const DoublyLinkedList &list);
    static Node* recursiveSplitAndSort(Node* headNode);
    static Node* getMiddleNode(Node* headNode);
    static Node* mergeNodes(Node* nodeInLeft, Node* nodeInRight);

    // Quick sort with utility functions
    static DoublyLinkedList quickSortInList(const DoublyLinkedList& list);
    static Node* quickSortRecursive(Node* head, Node* tail);
    static Node* partition(Node* head, Node* tail, Node** leftNodes, Node** rightNodes);
};
