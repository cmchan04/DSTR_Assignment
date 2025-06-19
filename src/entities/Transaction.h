//
// Created by cmchan04 on 6/2/2025.
//

// This is used to make sure that the header file loads only once
#pragma once

// Imports
#include <string>
#include <iostream>
using namespace std;

// The transaction struct (with public attributes)
struct Transaction {

    // Declaration of variables
    string transactionId;
    string timestamp;
    string senderAcc;
    string receiverAcc;
    double amount{};
    string transactionType;
    string merchantCategory;
    string location;
    string deviceUsed;
    bool isFraud{};
    string fraudType;
    double timeSinceLastTransaction{};
    double spendingDeviationScore{};
    int velocityScore{};
    double geoAnomalyScore{};
    string paymentChannel;
    string ipAddress;
    string deviceHash;

    // Constructor declaration
    Transaction() = default;
    explicit Transaction(const string* dataArray);

    // Print sample contents
    void printContents(int index = -1) const;

    // Basic swap - will be utilized in sorting
    void swap(Transaction& first, Transaction& second);
};

