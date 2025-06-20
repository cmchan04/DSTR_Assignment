//
// Created by Lim Beng Rhui on 11/06/2025.
//

// Make sure a header file is only included once in the program
#pragma once

// Imports
#include "../entities/Transaction.h"
#include "StringUtil.h"
#include <string>
#include <ranges>
#include <algorithm>

using namespace std;

struct Searcher{

    // Linear Searches
    static Transaction* linearSearchWithArray(Transaction* transactions, int size, const string& searchType, int& resultCount);


    //Binary Searches




};

