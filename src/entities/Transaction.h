//
// Created by cmchan04 on 6/2/2025.
//

#include <string>
#pragma once

using namespace std;

struct Transaction {

    //Declaration of variables
    string transactionId;
    string timestamp;
    string senderAcc;
    string receiverAcc;
    double amount;
    string transactionType;
    string merchantCategory;
    string location;
    string deviceUsed;
    bool isFraud;
    string fraudType;
    double timeSinceLastTransaction;
    double spendingDeviationScore;
    int velocityScore;
    double geoAnomalyScore;
    string paymentChannel;
    string ipAddress;
    string deviceHash;

};

