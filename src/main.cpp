#include <iostream>
#include "utilities/TransactionReader.h"
#include "utilities/ChannelSeparator.h"
#include "utilities/PerformanceTracker.h"
#include "utilities/Searcher.h"
#include "utilities/Sorter.h"

using namespace std;

int main(){

    // Initialize performance tracker for loading datasets into arrays.
    PerformanceTracker loadDataToArrayTracker{};
    loadDataToArrayTracker.start();

    // Load CSV file
    const string FILE_PATH("../src/resources/financial_fraud_detection_dataset.csv");
    int totalRows;
    Transaction* transactionsArray = TransactionReader::readCSVToArray(FILE_PATH, totalRows);

    // Check resources used in loading data into arrays
    loadDataToArrayTracker.stop();
    loadDataToArrayTracker.report("Performance for Loading CSV into Array");

    // Split based on payment channels
    // Create an empty list to store Transaction data
    auto* list = new DoublyLinkedList();

    // Create a performance tracker for tracking loading performance for the linked list
    PerformanceTracker loadDataToListTracker{};
    loadDataToListTracker.start();

    // Load data into a linked list
    TransactionReader::readCSVToList(FILE_PATH, list);

    // End performance tracking and print results
    loadDataToListTracker.stop();
    loadDataToListTracker.report("Performance for Loading CSV into Linked List");
    cout << "Size is: " << list -> getSize() << endl;

    // Declare new arrays and size
    Transaction *ach = nullptr, *card = nullptr, *upi = nullptr, *wireTransfer = nullptr;
    int achSize = 0, cardSize = 0, upiSize = 0, wireSize = 0;

    // Start performance tracker to check performance of the payment channel split in arrays
    PerformanceTracker arrayTrackerSplit{};
    arrayTrackerSplit.start();

    // Distribution of transaction records into arrays
    ChannelSeparator::splitToChannelArray(transactionsArray, totalRows,
                                          ach, achSize,
                                          card, cardSize,
                                          upi, upiSize,
                                          wireTransfer, wireSize);

    // Stop the tracker
    arrayTrackerSplit.stop();

    // Ensure all rows are distributed - Check if any missing
    cout << "ACH Transactions: " << achSize << endl;
    cout << "Card Transactions: " << cardSize << endl;
    cout << "UPI Transactions: " << upiSize << endl;
    cout << "Wire Transfers: " << wireSize << endl;

    // Check resources used in splitting data
    arrayTrackerSplit.report("Performance for Splitting Data based on Payment Channel in Array");

    // Show total rows read
    cout << "Total rows: " << totalRows << endl;

    //Release memory for splitting data
    delete[] ach;
    delete[] card;
    delete[] upi;
    delete[] wireTransfer;

    // Create a performance tracker for tracking linear searching in arrays
    PerformanceTracker linearSearchArrayTracker{};
    linearSearchArrayTracker.start();

    // Test: linear search for arrays
    // Initialize target type, result counter, and result array
    string searchType = "Deposit";
    int matchCount = 0;
    Transaction** results = Searcher::linearSearchUsingArray(transactionsArray, totalRows, searchType, matchCount);

    // Stop the tracker
    linearSearchArrayTracker.stop();

    // Short summary
    cout << "Found " << matchCount << " transactions with type: " << searchType << "\n" << endl;

    // Print at most 10 sample records
    for (int i = 0; i < min(10, matchCount); ++i) {
        results[i] -> printContents(i);
    }

    linearSearchArrayTracker.report("Performance for Linear Search in Array for \"Deposit\" transaction type");

    // Release memory
    delete[] results;
    
    // Create a Performance Tracker for Merge Sort in arrays
    PerformanceTracker mergeSortTracker{};
    mergeSortTracker.start();

    // Test: Merge sort in arrays based on transaction type
    // Initialize target type
    string sortType = "type";

    // Start sorting
    Sorter::mergeSortInArray(transactionsArray, totalRows, sortType, true);

    // Stop the tracker
    mergeSortTracker.stop();

    //Print 30 sample records
    for (int i = 0; i < 30; ++i) {
        transactionsArray[i].printContents(i);
    }

    // Print performance summary
    mergeSortTracker.report("Performance for Merge Sort in Array for \"Transaction Type\"");

    // Create a performance tracker for tracking binary searching in arrays
    PerformanceTracker binarySearchArrayTracker{};
    binarySearchArrayTracker.start();

    // Reinitialize search type and result array for binary search
    searchType = "Deposit";
    results = Searcher::binarySearchUsingArray(transactionsArray, totalRows, searchType, matchCount);

    // Stop the tracker
    binarySearchArrayTracker.stop();

    // Short summary
    cout << "Found " << matchCount << " transactions with type: " << searchType << "\n" << endl;

    // Print at most 10 sample records
    for (int i = 0; i < min(10, matchCount); ++i) {
        results[i] -> printContents(i);
    }

    // Print performance summary
    binarySearchArrayTracker.report("Performance for Binary Search in Array for \"Deposit\" transaction type");

    // Release memory
    delete[] results;

    // Release memory
    delete[] transactionsArray;
    delete[] list;

    // Program ends!
    return 0;
}
