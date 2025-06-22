//
// Created by Lim Beng Rhui on 11/06/2025.
//

// Make sure a header file is only included once in the program
#pragma once

// Imports
#include "../entities/Transaction.h"
#include "../entities/DoublyLinkedList.h"
#include "StringUtil.h"
#include <string>

using namespace std;

struct Searcher{

    // Linear Searches
    static Transaction* linearSearchWithArray(Transaction* transactions, int size, const string& searchType, int& resultCount);
  
    static Transaction** linearSearchUsingList(const DoublyLinkedList &list, string &transactionType, int &outputSize);


    //Binary Searches
    static Transaction** binarySearchWithArray(Transaction* transactions, int size, const string& searchType, int& resultCount);

  
    // Utility methods
    // Shrinks the size of a list
    inline static void removeUnusedIndex(Transaction** &list, const int &currentListSize, const int &actualListSize);

};
