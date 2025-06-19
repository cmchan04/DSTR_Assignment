//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include "Transaction.h"
#include "../utilities/TransactionReader.h"

/**
 * Constructor to create Transaction objects from an array <br>
 *
 * @param dataArray The array consisting of data retrieved from the text file
 */
Transaction::Transaction(const string* dataArray) {

    // Add data to the Transaction object
    this -> transactionId = dataArray[0];
    this -> timestamp = dataArray[1];
    this -> senderAcc = dataArray[2];
    this -> receiverAcc = dataArray[3];
    this -> amount = dataArray[4].empty() ? 0.0 : stod(dataArray[4]);
    this -> transactionType = dataArray[5];
    this -> merchantCategory = dataArray[6];
    this -> location = dataArray[7];
    this -> deviceUsed = dataArray[8];
    this -> isFraud = TransactionReader::stringToBool(dataArray[9]);
    this -> fraudType = dataArray[10];
    this -> timeSinceLastTransaction = dataArray[11].empty() ? 0.0 : stod(dataArray[11]);
    this -> spendingDeviationScore = dataArray[12].empty() ? 0.0 : stod(dataArray[12]);
    this -> velocityScore = stoi(dataArray[13]);
    this -> geoAnomalyScore = dataArray[14].empty()?0.0: stod(dataArray[14]);
    this -> paymentChannel = dataArray[15];
    this -> ipAddress = dataArray[16];
    this -> deviceHash = dataArray[17];
}


/**
 * This function prints sample rows of the array
 * @param index number of rows to be shown
 * @note Use for loops to print samples
 */
 void Transaction::printContents(int index) const {

    // Show header
    cout << "=== Printing Array Contents ===" << endl;

    // Reject negative index
    if (index >= 0) {
        cout << "Row " << index + 1 << ":\n";
    }

    // Print contents
    cout << "  ID: " << transactionId << "\n";
    cout << "  Transaction Type: " << transactionType << "\n";
    cout << "  Location: " << location << "\n";
    cout << "  Is Fraud: " << (isFraud ? "Yes" : "No") << "\n";
    cout << "  Channel: " << paymentChannel << "\n";

 }

 /**
  * This function is to swap two transactions index in the array
  * @param first
  * @param second
  */
void Transaction::swap(Transaction &first, Transaction &second) {

     Transaction temp = first;
     first = second;
     second = temp;

 }
