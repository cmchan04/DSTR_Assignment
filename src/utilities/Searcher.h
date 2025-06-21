//
// Created by Lim Beng Rhui on 11/06/2025.
//

// Make sure the header file is only included once in the program
#pragma once

#include "../entities/Transaction.h"
#include "../entities/DoublyLinkedList.h"

class Searcher {

    public:

    // Linear search
    static Transaction** linearSearchUsingList(const DoublyLinkedList &list, string &transactionType, int &outputSize);

    // Utility methods
    // Shrinks the size of a list
    inline static void removeUnusedIndex(Transaction** &list, const int &currentListSize, const int &actualListSize);

};
