#include <iostream>
#include "utilities/TransactionReader.h"
#include "utilities/ChannelSeperator.h"

using namespace std;

int main(){

    // Load CSV file
    const string FILE_PATH("../src/resources/financial_fraud_detection_dataset.csv");
    int totalRows;
    const Transaction* transactionsArray = TransactionReader::readCSVToArray(FILE_PATH, totalRows);

    // Declare new arrays and size
    Transaction *ach = nullptr, *card = nullptr, *upi = nullptr, *wireTransfer = nullptr;
    int achSize = 0, cardSize = 0, upiSize = 0, wireSize = 0;

    // Distribution of transaction records
    ChannelSeperator::splitToChannelArray(transactionsArray, totalRows,
                                          ach, achSize,
                                          card, cardSize,
                                          upi, upiSize,
                                          wireTransfer, wireSize);

    // Ensure all rows are distributed - Check if any missing
    cout << "ACH Transactions: " << achSize << endl;
    cout << "Card Transactions: " << cardSize << endl;
    cout << "UPI Transactions: " << upiSize << endl;
    cout << "Wire Transfers: " << wireSize << endl;

    // Show total rows read
    cout << "Total rows: " << totalRows << endl;

//    //To show sample rows
//    for (int i = 0; i < 20; ++i) {
//        const Transaction& t = transactionsArray[i];
//
//        cout << "Row " << i + 1 << ":\n";
//        cout << "  ID: " << t.transactionId << "\n";
//        cout << "  Timestamp: " << t.timestamp << "\n";
//        cout << "  Sender: " << t.senderAcc << "\n";
//        cout << "  Receiver: " << t.receiverAcc << "\n";
//        cout << "  Amount: " << t.amount << "\n";
//        cout << "  Type: " << t.transactionType << "\n";
//        cout << "  Merchant Category: " << t.merchantCategory << "\n";
//        cout << "  Location: " << t.location << "\n";
//        cout << "  Device: " << t.deviceUsed << "\n";
//        cout << "  Is Fraud: " << (t.isFraud ? "Yes" : "No") << "\n";
//        cout << "  Fraud Type: " << t.fraudType << "\n";
//        cout << "  Time Since Last Txn: " << t.timeSinceLastTransaction << "\n";
//        cout << "  Spending Deviation: " << t.spendingDeviationScore << "\n";
//        cout << "  Velocity: " << t.velocityScore << "\n";
//        cout << "  Geo Anomaly: " << t.geoAnomalyScore << "\n";
//        cout << "  Channel: " << t.paymentChannel << "\n";
//        cout << "  IP: " << t.ipAddress << "\n";
//        cout << "  Device Hash: " << t.deviceHash << "\n\n";
//    }

    // Release memory
    delete[] transactionsArray;
    delete[] ach;
    delete[] card;
    delete[] upi;
    delete[] wireTransfer;

    return 0;
};

