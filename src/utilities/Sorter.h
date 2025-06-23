//
// Created by Lim Beng Rhui on 11/06/2025.
//

// Make sure the header file is only included once in the program
#pragma once

// Imports
#include "../entities/Transaction.h"
#include "../entities/DoublyLinkedList.h"
#include <string>

using namespace std;

struct Sorter{

    // Bubble sort
    static void bubbleSortInArray(Transaction* transactions, int size, const string &column = "location", bool ascending = true);
    static DoublyLinkedList bubbleSortInList(const DoublyLinkedList &list);

    // Insertion sort
    static void insertionSortInArray(Transaction* transactions, int size, const string &column = "location", bool ascending = true);
    static DoublyLinkedList insertionSortInList(const DoublyLinkedList &list);

    // Merge sort
    static void mergeSortInArray(Transaction* transactions, int size, const string& column = "location", bool ascending = true);
    static void mergeSortDividerInArray(Transaction* transactions, int left, int right, const string& column = "location", bool ascending = true);
    static void mergeForArrayElements(Transaction* transactions, int left, int median, int right, const string& column = "location", bool ascending = true);

    static DoublyLinkedList mergeSortInList(const DoublyLinkedList &list);
    static Node* recursiveSplitAndSortInList(Node* headNode);
    static Node* getMiddleNodeForList(Node* headNode);
    static Node* mergeNodesForList(Node* nodeInLeft, Node* nodeInRight);

    // Quick sort with utility functions (Linked List)
    static DoublyLinkedList quickSortInList(const DoublyLinkedList& list);
    static Node* quickSortRecursiveForList(Node* head, Node* tail);
    static Node* quickSortPartitionForList(Node* head, Node* tail, Node** leftNodes, Node** rightNodes);

    // Quick sort with utility functions (Array)
    static int getMedianIndex(Transaction* arr, int left, int right, const string &column);
    static int quickSortPartitionForArray(Transaction* arr, int left, int right, const string &column = "location", bool ascending = true);
    static void quickSortInArray(Transaction* arr, int left, int right, const string &column = "location", bool ascending = true);
};
