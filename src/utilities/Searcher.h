//
// Created by Lim Beng Rhui on 11/06/2025.
//

// Make sure header file is only included once in program
#pragma once

// Imports
#include "../entities/Transaction.h"
#include <string>
#include <iostream>
#include <ranges>
#include <algorithm>

using namespace std;

struct Searcher{

    // Utility
    string toLowerCase(const string& str);

    // Linear Searches
    Transaction* linearSearchWithArray(Transaction* transactions, int size, const string& searchType, int& resultCount);


    //Binary Searches

};

