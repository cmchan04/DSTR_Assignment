//
// Created by Lim Beng Rhui on 11/06/2025.
//

// Make sure a header file is only included once in the program
#pragma once

// Imports
#include "../entities/Transaction.h"
#include "StringUtil.h"
#include <string>

using namespace std;

struct Sorter{

    // Bubble sort
    static void bubbleSortInArray(Transaction* transactions, int size, const string &column = "location", bool ascending = true);

    // Insertion sort
    static void insertionSortInArray(Transaction* transactions, int size, const string &column = "location", bool ascending = true);

    // Merge sort


};
