//
// Created by cmchan04 on 6/8/2025.
//

// Imports
#include "TransactionReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ranges>

using namespace std;

/**
 * This function converts a string to bool
 * \code const\endcode keyword to avoid overwriting to the original string
 * Use reference for better performance
 *
 * @param input The string to store and convert input to lowerCase
 *
 * @return return \code TRUE\endcode if the converted result is "true"
 */
bool TransactionReader::stringToBool(const string &input) {
    string lower = input;
    ranges::transform(lower, lower.begin(), ::tolower);
    return lower == "true";
}

/**
 * Reads a CSV file and loads transactions into an array.
 *
 * Malformed rows are skipped.
 *
 * @param filename Path to the csv file
 * @param outSize Reference to variable to check how many rows read successfully in total
 *
 * @return ptr to an array storing the csv, can be nullptr when any error occurs
 */
Transaction* TransactionReader::readCSVToArray(const string &filename, int &outSize) {

    // Retrieve file
    ifstream file(filename);

    // Temporary location to store data row (unformatted)
    string line;

    // Counters to determine array size and data row entry index
    int rowCount = 0;
    int index = 0;

    // Return nullptr when the file is not found
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        outSize = 0;
        return nullptr;
    }

    // Skip header (first) line
    getline(file, line);

    // Count the number of rows to allocate a fixed-size array
    while (getline(file, line)) {
        rowCount++;
    }

    // Return nullptr when no rows detected
    if (rowCount == 0) {
        cerr << "No data rows in file.\n";
        outSize = 0;
        return nullptr;
    }

    // Create an array to store transactions
    auto* transactionsArray = new Transaction[rowCount];

    // Reset the file pointer to start again for data entry
    file.clear();
    file.seekg(0, ios::beg);

    // Skip the header again
    getline(file, line);

    // Loop for data entry
    while (getline(file, line)) {

        // Create a new transaction object and use method to convert line into transactions
        if (Transaction transaction; parseLineToTransaction(line, transaction)) {

            // Add the transaction object into the array if created successfully
            transactionsArray[index] = transaction;

        } else {

            // If the row cannot be converted, prnt error message
            cerr << "Error parsing row: " << line << endl;
        }

        // Go to the next position
        index++;
    }

    // Set the output size of the array and return
    outSize = index;
    return transactionsArray;
}

/**
 * This helper method generates the Transaction object from a line of string data.
 * @param line The string data consisting of Transaction information
 * @param transactionObject The Transaction object that has to be constructed from string data
 * @return \code true\endcode if the \code Transaction\endcode object is created successfully, else \code false\endcode
 */
bool TransactionReader::parseLineToTransaction(const string& line, Transaction &transactionObject) {

    // Save the content of the line
    stringstream ss(line);

    // Generate an array with 18 columns with an index counter
    string fields[18];
    int fieldIndex = 0;

    // Store data into fields array
    while (getline(ss, fields[fieldIndex], ',') && fieldIndex < 18) {
        fieldIndex++;
    }

    // Check for invalid rows (should be none)
    if (fieldIndex < 18) {
        cerr << "Skipping malformed row.\n";
        return false;
    }

    // Create the transaction object and exit
    try {
        transactionObject = Transaction(fields);
        return true;

    // If rows cannot be handled
    } catch (...) {

        // Print error message and return
        cerr << "Error parsing row: " << line << endl;
        return false;
    }
}

/**
 * Reads the CSV file right into the linked list
 * @param filename The name of the CSV file
 * @param list The doubly linked list that will be modified
 */
void TransactionReader::readCSVToList(const string& filename, DoublyLinkedList* list) {

    // Get the file and declare an empty line to store unprocessed information from the file
    ifstream file(filename);
    string line;

    // Print error message if the file cannot be opened
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // Skip header
    getline(file, line);

    // Loop through each data in the stored stream
    while (getline(file, line)) {

        // Create a transaction object from string data
        if (Transaction transaction; parseLineToTransaction(line, transaction)) {

            // The transaction object is copied so that it can still remain for the later iterations
            const auto* transactionTemp = new Transaction(transaction);
            list -> insertAtEnd(transactionTemp);

        // Error message printed if unsuccessful
        } else {
            cerr << "Skipping malformed row for line: " << line << endl;
        }
    }
}
