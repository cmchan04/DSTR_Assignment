#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "entities/transaction.h"

using namespace std;

/**
 * This function converts a string to bool
 * const keyword to avoid overwrite to the original string
 * Use reference for better performance
 * @param lower - The string to store and convert input to lowerCase
 * @return return TRUE if the converted results is "true"
 */
bool stringToBool(const string &input)
{
    string lower = input;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower == "true";
}

/**
 * Reads a CSV file and loads transactions into array.
 *
 * Malformed rows are skipped.
 *
 * @param filename - path to the csv file
 * @param outSize - reference to variable to check how many rows read successfully in total
 *
 * @var line - temp location to store data row
 * @var rowCount - counter to determine size of array
 * @var index - counter for data row entry index
 * @return ptr to an array storing the csv, can be nullptr when error occurs
 */

Transaction* readCSVToArray(const string &filename, int &outSize)
{
    ifstream file(filename);
    string line;
    int rowCount = 0;
    int index = 0;

    /**
     * @return nullptr when file not found.
     */
    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        outSize = 0;
        return nullptr;
    }

    getline(file, line); //skip the first line

    //Count the number of rows to allocate a fixed-size array
    while (getline(file, line))
    {
        rowCount++;
    }

    /**
     * @return nullptr when no rows detected
     */
    if (rowCount == 0)
    {
        cerr << "No data rows in file.\n";
        outSize = 0;
        return nullptr;
    }

    //Create Array to store transactions
    Transaction* transactionsArray = new Transaction[rowCount];

    //Reset the file pointer to start again for data entry
    file.clear();
    file.seekg(0, ios::beg);

    //Skip the header again
    getline(file, line);

    //Loop for data entry
    while (getline(file, line))
    {
        /**
         * @var ss - save content in [line]
         * @var fields - array having 18 columns for data parsing purpose
         * @var fieldIndex - loop the index during input to match [Transaction] attributes
         */
        stringstream ss(line);
        string fields[18];
        int fieldIndex = 0;

        //This loop read and store value into fields[index] and continue next loop when a "," is read
        while (getline(ss, fields[fieldIndex], ',') && fieldIndex < 18)
        {
            fieldIndex++;
        }

        if (fieldIndex < 18)
        {
            cerr << "Skipping malformed row.\n";
            continue;
        }

        //Load each row into transactionsArray
        try
        {
            Transaction t;
            t.transactionId = fields[0];
            t.timestamp = fields[1];
            t.senderAcc = fields[2];
            t.receiverAcc = fields[3];
            t.amount = fields[4].empty()?0.0: stod(fields[4]);
            t.transactionType = fields[5];
            t.merchantCategory = fields[6];
            t.location = fields[7];
            t.deviceUsed = fields[8];
            t.isFraud = stringToBool(fields[9]);
            t.fraudType = fields[10];
            t.timeSinceLastTransaction = fields[11].empty()?0.0: stod(fields[11]);
            t.spendingDeviationScore = fields[12].empty()?0.0: stod(fields[12]);
            t.velocityScore = stoi(fields[13]);
            t.geoAnomalyScore = fields[14].empty()?0.0: stod(fields[14]);
            t.paymentChannel = fields[15];
            t.ipAddress = fields[16];
            t.deviceHash = fields[17];

            transactionsArray[index] = t;
            index++;
        }
        catch (...)
        {
            cerr << "Error parsing row: " << line << endl;
        }
    }

    outSize = index;
    return transactionsArray;
}


int main(){

    //Your csv should locate in this file path
    const string FILE_PATH("../src/resources/financial_fraud_detection_dataset.csv");
    int totalRows;
    Transaction* transactionsArray = readCSVToArray(FILE_PATH, totalRows);

    //Show total rows read
    cout << "Total rows: " << totalRows << endl;

    //To show sample rows
    for (int i = 0; i < 20; ++i) {
        const Transaction& t = transactionsArray[i];

        cout << "Row " << i + 1 << ":\n";
        cout << "  ID: " << t.transactionId << "\n";
        cout << "  Timestamp: " << t.timestamp << "\n";
        cout << "  Sender: " << t.senderAcc << "\n";
        cout << "  Receiver: " << t.receiverAcc << "\n";
        cout << "  Amount: " << t.amount << "\n";
        cout << "  Type: " << t.transactionType << "\n";
        cout << "  Merchant Category: " << t.merchantCategory << "\n";
        cout << "  Location: " << t.location << "\n";
        cout << "  Device: " << t.deviceUsed << "\n";
        cout << "  Is Fraud: " << (t.isFraud ? "Yes" : "No") << "\n";
        cout << "  Fraud Type: " << t.fraudType << "\n";
        cout << "  Time Since Last Txn: " << t.timeSinceLastTransaction << "\n";
        cout << "  Spending Deviation: " << t.spendingDeviationScore << "\n";
        cout << "  Velocity: " << t.velocityScore << "\n";
        cout << "  Geo Anomaly: " << t.geoAnomalyScore << "\n";
        cout << "  Channel: " << t.paymentChannel << "\n";
        cout << "  IP: " << t.ipAddress << "\n";
        cout << "  Device Hash: " << t.deviceHash << "\n\n";
    }

    //Release memory
    delete[] transactionsArray;

    return 0;
};

