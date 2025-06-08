//
// Created by cmchan04 on 6/8/2025.
//

#include <string>
#include "../entities/Transaction.h"
#pragma once

using namespace std;

struct TransactionReader {

    //Declaration of functions
    static Transaction* readCSVToArray(const string &filename, int &outSize);

    static bool stringToBool(const string &input);

};


