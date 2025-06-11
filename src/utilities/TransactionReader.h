//
// Created by cmchan04 on 6/8/2025.
//

// To make sure header file compiles only once
#pragma once

// Imports
#include <string>
#include "../entities/Transaction.h"
using namespace std;

/**
 * Used to read transactions into C++, either to an array or to a linked list
 */
struct TransactionReader {

    //Declaration of functions
    static Transaction* readCSVToArray(const string &filename, int &outSize);
    static bool stringToBool(const string &input);
};


