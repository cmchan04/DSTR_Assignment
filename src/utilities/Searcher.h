//
// Created by Lim Beng Rhui on 11/06/2025.
//

// Make sure the header file is only included once in the program
#pragma once

// Imports
#include "../entities/Transaction.h"
#include "../entities/DoublyLinkedList.h"
#include "StringUtil.h"
#include <string>

using namespace std;

struct Searcher{

    // Linear search
    static Transaction** linearSearchUsingArray(Transaction* transactions, int size, const string &searchType, int &resultCount);
    static Transaction** linearSearchUsingList(const DoublyLinkedList &list, string &transactionType, int &outputSize);

    // Binary search
    static Transaction** binarySearchUsingArray(Transaction* transactions, int size, const string &searchType, int &resultCount);
    static Transaction** binarySearchUsingList(const DoublyLinkedList &list, string &transactionType, int &outputSize);

    // Utility methods
    // Shrinks the size of a list
    inline static void removeUnusedIndex(Transaction** &list, const int &currentListSize, const int &actualListSize);

    // Retrieve the middle node of a linked list, given the beginning and ending nodes
    static Node* getMiddleNode(Node* startNode, const Node* endNode);
};
