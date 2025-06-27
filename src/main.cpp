#include <iostream>

#include "utilities/TransactionReader.h"
#include "utilities/ChannelSeparator.h"
#include "utilities/JsonExport.h"
#include "utilities/PerformanceTracker.h"
#include "utilities/Searcher.h"
#include "utilities/Sorter.h"

using namespace std;

#define FILE_PATH "../src/resources/financial_fraud_detection_dataset.csv"
#define SAMPLING_SIZE 50000

// Methods to break down tasks
PerformanceTracker* loadDataToArray(Transaction* &array, int &size);
PerformanceTracker* loadDataToList(DoublyLinkedList* &list);
PerformanceTracker* storeArrayToJson(Transaction* &array, const int &size);
PerformanceTracker* storeLinkedListToJson(DoublyLinkedList* &list);

PerformanceTracker* separateArrayData(const Transaction* array, const int &size,
                                      Transaction* &ach, Transaction* &card, Transaction* &upi, Transaction* &wireTransfer,
                                      int &achSize, int &cardSize, int &upiSize, int &wireSize);

PerformanceTracker* separateListData(const DoublyLinkedList* list,
                                     DoublyLinkedList* &achList,
                                     DoublyLinkedList* &cardList,
                                     DoublyLinkedList* &upiList,
                                     DoublyLinkedList* &wireList);

void copyArray(const Transaction* mainArray, const int &arraySize, Transaction* &array1);

PerformanceTracker* arrayBubbleSort(Transaction* &array, int &size, const string &searchType, const bool &sample = false);
PerformanceTracker* arrayInsertionSort(Transaction* &array, int &size, const string &searchType, const bool &sample = false);
PerformanceTracker* arrayMergeSort(Transaction* &array, int &size, const string &searchType, const bool &sample = false);
PerformanceTracker* arrayQuickSort(Transaction* &array, int &size, const string &searchType, const bool &sample = false);

PerformanceTracker* listBubbleSort(DoublyLinkedList &list, const string &searchType, const bool &sample = false);
PerformanceTracker* listInsertionSort(DoublyLinkedList &list, const string &searchType, const bool &sample = false);
PerformanceTracker* listMergeSort(DoublyLinkedList &list, const string &searchType, const bool &sample = false);
PerformanceTracker* listQuickSort(DoublyLinkedList &list, const string &searchType, const bool &sample = false);

PerformanceTracker* arrayLinearSearch(Transaction* array, int size, Transaction** &result, const string &searchType, int &matchCount);
PerformanceTracker* arrayBinarySearch(Transaction* array, int size, Transaction** &result, const string &searchType, int &matchCount);

PerformanceTracker* listLinearSearch(const DoublyLinkedList &list, Transaction** &outputList, string &searchType, int &outputSize);
PerformanceTracker* listBinarySearch(const DoublyLinkedList &list, Transaction** &outputList, string &searchType, int &outputSize);

int main() {

    // Task 0: Import data
    cout << endl << "--------Task 0: Importing data into program--------" << endl;
    cout << endl << "Loading data from file to array ... " << endl;

    // Load data into array
    Transaction* overallTransactionArray = nullptr;
    int totalArrayRow;
    const PerformanceTracker* tracker = nullptr;

    tracker = loadDataToArray(overallTransactionArray, totalArrayRow);
    tracker -> report("Performance for loading CSV to array");
    delete tracker;

    // Load data into a linked list
    cout << "Loading data from file to linked list ... " << endl;
    DoublyLinkedList* overallTransactionList = nullptr;
    tracker = loadDataToList(overallTransactionList);
    tracker -> report("Performance for loading CSV to linked list");
    delete tracker;

    // Check performance for JSON
    cout << "Exporting array results to JSON ... " << endl;
    tracker = storeArrayToJson(overallTransactionArray, totalArrayRow);
    tracker -> report("Performance for loading array to JSON");
    delete tracker;

    cout << "Exporting linked list results to JSON ... " << endl;
    tracker = storeLinkedListToJson(overallTransactionList);
    tracker -> report("Performance for loading linked list to JSON");
    delete tracker;

    // ---------------------------------------------------------------------------------------------------------
    // Task 1: Separate data based on different channels.
    // Goal: Compare performance of the normal read and write between arrays and linked lists
    cout << "--------Task 1: Separate data into different channels--------" << endl;
    cout << endl << "Separating data from the overall array ... " << endl;

    // Array
    Transaction *achArray = nullptr, *cardArray = nullptr, *upiArray = nullptr, *wireTransferArray = nullptr;
    int achSize = 0, cardSize = 0, upiSize = 0, wireSize = 0;
    tracker = separateArrayData(overallTransactionArray, totalArrayRow,
                      achArray, cardArray, upiArray, wireTransferArray,
                      achSize, cardSize, upiSize, wireSize);
    tracker -> report("Performance for Splitting Data based on Payment Channel in Array");
    delete tracker;

    cout << "Exporting results to JSON ... " << endl;
    JsonExport::convertToJson(achArray,           achSize,  "ACH_Payment_Array.json");
    JsonExport::convertToJson(cardArray,          cardSize, "Card_Payment_Array.json");
    JsonExport::convertToJson(upiArray,           upiSize,  "UPI_Payment_Array.json");
    JsonExport::convertToJson(wireTransferArray,  wireSize, "Wire_Transfer_Payment_Array.json");

    // Release memory for splitting data
    delete[] achArray;
    delete[] cardArray;
    delete[] upiArray;
    delete[] wireTransferArray;

    // Linked list
    cout << endl << "Separating data from the overall linked list ... " << endl;
    DoublyLinkedList *achList = nullptr, *cardList = nullptr, *upiList = nullptr, *wireList = nullptr;
    tracker = separateListData(overallTransactionList,
                  achList, cardList,
                  upiList, wireList);
    tracker -> report("Performance for splitting data in linked list");
    delete tracker;

    cout << "Exporting results to JSON ... " << endl;
    JsonExport::convertToJson(achList,  "ACH_Payment_Linked_List.json");
    JsonExport::convertToJson(cardList, "Card_Payment_Linked_List.json");
    JsonExport::convertToJson(upiList,  "UPI_Payment_Linked_List.json");
    JsonExport::convertToJson(wireList, "Wire_Transfer_Payment_Linked_List.json");

    // Release memory once done
    delete achList;
    delete cardList;
    delete upiList;
    delete wireList;

    // ---------------------------------------------------------------------------------------------------------
    // Task 2: Perform sorting on transactions based on location
    // Goal: Compare the performance of different sorts in arrays and linked list
    // Note: Bubble sort and insertion sort are too inefficient, takes hours to days to run everything!
    cout << endl << "--------Task 2: Sorting based on location--------" << endl;

    // Perform sorting on merge sort and quick sort
    // Array
    const string locationSortKey = "location";
    Transaction *locationMergeSortArray = nullptr,
                *locationQuickSortArray = nullptr;

    int mergeSortSize = totalArrayRow;
    int quickSortSize = totalArrayRow;

    copyArray(overallTransactionArray, totalArrayRow, locationMergeSortArray);
    copyArray(overallTransactionArray, totalArrayRow, locationQuickSortArray);

    cout << endl << "Sorting data from array using merge sort ... " << endl;
    tracker = arrayMergeSort(locationMergeSortArray, mergeSortSize, locationSortKey);
    tracker -> report("Performance for Merge Sort in Array");
    delete tracker;

    cout << "Sorting data from array using quick sort ... " << endl;
    tracker = arrayQuickSort(locationQuickSortArray, quickSortSize, locationSortKey);
    tracker -> report("Performance for Quick Sort in Array");
    delete tracker;

    cout << "Exporting results to JSON ... " << endl;
    JsonExport::convertToJson(locationMergeSortArray, mergeSortSize,  "Merge_Sort_Full_Array.json");
    JsonExport::convertToJson(locationQuickSortArray, quickSortSize,  "Quick_Sort_Full_Array.json");

    // Release memory after use
    delete[] locationMergeSortArray;
    delete[] locationQuickSortArray;

    // Linked list
    auto* mergeSortList = new DoublyLinkedList(*overallTransactionList);
    auto* quickSortList = new DoublyLinkedList(*overallTransactionList);

    cout << endl << "Sorting data from linked list using merge sort ... " << endl;
    tracker = listMergeSort(*mergeSortList, locationSortKey);
    tracker -> report("Performance for Merge Sort in Linked List");
    delete tracker;

    cout << "Sorting data from linked list using quick sort ... " << endl;
    tracker = listQuickSort(*quickSortList, locationSortKey);
    tracker -> report("Performance for Quick Sort in Linked List");
    delete tracker;

    cout << "Exporting results to JSON ... " << endl;
    JsonExport::convertToJson(mergeSortList, "Merge_Sort_Full_Linked_List.json");
    JsonExport::convertToJson(quickSortList, "Quick_Sort_Full_Linked_List.json");

    // Release memory
    delete mergeSortList;
    delete quickSortList;

    // To compare the performances for all sorting algorithms, the dataset is sampled down.
    Transaction *sampledBubbleSortArray = nullptr,
                *sampledInsertionSortArray = nullptr,
                *sampledMergeSortArray = nullptr,
                *sampledQuickSortArray = nullptr;

    int sampledBubbleSortSize = totalArrayRow;
    int sampledInsertionSortSize = totalArrayRow;
    int sampledMergeSortSize = totalArrayRow;
    int sampledQuickSortSize = totalArrayRow;

    copyArray(overallTransactionArray, totalArrayRow, sampledBubbleSortArray);
    copyArray(overallTransactionArray, totalArrayRow, sampledInsertionSortArray);
    copyArray(overallTransactionArray, totalArrayRow, sampledMergeSortArray);
    copyArray(overallTransactionArray, totalArrayRow, sampledQuickSortArray);

    auto* sampledBubbleSortList = new DoublyLinkedList(*overallTransactionList);
    auto* sampledInsertionSortList = new DoublyLinkedList(*overallTransactionList);
    auto* sampledMergeSortList = new DoublyLinkedList(*overallTransactionList);
    auto* sampledQuickSortList = new DoublyLinkedList(*overallTransactionList);

    // Sampled-down array
    cout << endl << "Sorting sampled data from array using bubble sort ... " << endl;
    tracker = arrayBubbleSort(sampledBubbleSortArray, sampledBubbleSortSize, locationSortKey, true);
    tracker -> report("Performance of Bubble Sort for Sampled Array");
    delete tracker;

    cout << "Sorting sampled data from array using insertion sort ... " << endl;
    tracker = arrayInsertionSort(sampledInsertionSortArray, sampledInsertionSortSize, locationSortKey, true);
    tracker -> report("Performance of Insertion Sort for Sampled Array");
    delete tracker;

    cout << "Sorting sampled data from array using merge sort ... " << endl;
    tracker = arrayMergeSort(sampledMergeSortArray, sampledMergeSortSize, locationSortKey, true);
    tracker -> report("Performance of Merge Sort for Sampled Array");
    delete tracker;

    cout << "Sorting sampled data from array using quick sort ... " << endl;
    tracker = arrayQuickSort(sampledQuickSortArray, sampledQuickSortSize, locationSortKey, true);
    tracker -> report("Performance of Quick Sort for Sampled Array");
    delete tracker;

    cout << "Exporting results to JSON ... " << endl;
    JsonExport::convertToJson(sampledBubbleSortArray,    sampledBubbleSortSize,     "Bubble_Sort_Sampled_Array.json");
    JsonExport::convertToJson(sampledInsertionSortArray, sampledInsertionSortSize,  "Insertion_Sort_Sampled_Array.json");
    JsonExport::convertToJson(sampledMergeSortArray,     sampledMergeSortSize,      "Merge_Sort_Sampled_Array.json");
    JsonExport::convertToJson(sampledQuickSortArray,     sampledQuickSortSize,      "Quick_Sort_Sampled_Array.json");

    // Release memory
    delete[] sampledBubbleSortArray;
    delete[] sampledInsertionSortArray;
    delete[] sampledMergeSortArray;
    delete[] sampledQuickSortArray;

    // Sampled down linked list
    cout << endl << "Sorting sampled data from linked list using bubble sort ... " << endl;
    tracker = listBubbleSort(*sampledBubbleSortList, locationSortKey, true);
    tracker -> report("Performance of Bubble Sort for Sampled Linked List");
    delete tracker;

    cout << "Sorting sampled data from linked list using insertion sort ... " << endl;
    tracker = listInsertionSort(*sampledInsertionSortList, locationSortKey, true);
    tracker -> report("Performance of Insertion Sort for Sampled Linked List");
    delete tracker;

    cout << "Sorting sampled data from linked list using merge sort ... " << endl;
    tracker = listMergeSort(*sampledMergeSortList, locationSortKey, true);
    tracker -> report("Performance of Merge Sort for Sampled Linked List");
    delete tracker;

    cout << "Sorting sampled data from linked list using quick sort ... " << endl;
    tracker = listQuickSort(*sampledQuickSortList, locationSortKey, true);
    tracker -> report("Performance of Quick Sort for Sampled Linked List");
    delete tracker;

    cout << "Exporting results to JSON ... " << endl;
    JsonExport::convertToJson(sampledBubbleSortList,    "Bubble_Sort_Sampled_Linked_List.json");
    JsonExport::convertToJson(sampledInsertionSortList, "Insertion_Sampled_Full_Linked_List.json");
    JsonExport::convertToJson(sampledMergeSortList,     "Merge_Sort_Sampled_Linked_List.json");
    JsonExport::convertToJson(sampledQuickSortList,     "Quick_Sort_Sampled_Linked_List.json");

    // Release memory
    delete sampledBubbleSortList;
    delete sampledInsertionSortList;
    delete sampledMergeSortList;
    delete sampledQuickSortList;

    // ---------------------------------------------------------------------------------------------------------
    // Task 3: Search for specific transaction types
    // Goal: To perform and compare different searching algorithms between arrays and linked lists.
    cout << endl << "--------Task 3: Search transaction based on types--------" << endl;
    string searchType = "Deposit";
    quickSortSize = totalArrayRow;

    // First perform the fastest sort to sort based on the transaction type
    cout << endl << "First sort the data based on location (for binary search) ... " << endl;
    Transaction* typeSortedArray = nullptr;
    copyArray(overallTransactionArray, totalArrayRow, typeSortedArray);

    tracker = arrayQuickSort(typeSortedArray, quickSortSize, "type");
    delete tracker;

    auto* typeSortedList = new DoublyLinkedList(*overallTransactionList);
    tracker = listQuickSort(*typeSortedList, "type");
    delete tracker;

    // Linear search
    cout << endl << "Sorting done! Now begin linear search for array ... " << endl;
    Transaction** linearSearchArray = nullptr;
    int linearSearchArrayCount = 0;
    tracker = arrayLinearSearch(overallTransactionArray, totalArrayRow, linearSearchArray, searchType, linearSearchArrayCount);
    tracker -> report("Performance of Linear Search for Array");
    delete tracker;

    cout << "Begin linear search for linked list ... " << endl;
    Transaction** linearSearchList = nullptr;
    int linearSearchListCount = 0;
    tracker = listLinearSearch(*overallTransactionList, linearSearchList, searchType, linearSearchListCount);
    tracker -> report("Performance of Linear Search for Linked List");
    delete tracker;

    cout << "Exporting results to JSON ... " << endl;
    JsonExport::convertToJson(linearSearchArray, linearSearchArrayCount,"Linear_Search_Array.json");
    JsonExport::convertToJson(linearSearchList, linearSearchListCount, "Linear_Search_List.json");

    // Release memory
    delete[] linearSearchArray;
    delete[] linearSearchList;

    // Binary search
    cout << endl << "Begin binary search for array ... " << endl;
    Transaction** binarySearchArray = nullptr;
    int binarySearchArrayCount = 0;
    tracker = arrayBinarySearch(typeSortedArray, totalArrayRow, binarySearchArray, searchType, binarySearchArrayCount);
    tracker -> report("Performance of Binary Search for Array");
    delete tracker;

    cout << "Begin binary search for linked list ... " << endl;
    Transaction** binarySearchList = nullptr;
    int binarySearchListCount = 0;
    tracker = listBinarySearch(*typeSortedList, binarySearchList, searchType, binarySearchListCount);
    tracker -> report("Performance of Binary Search for Linked List");
    delete tracker;

    cout << "Exporting results to JSON ... " << endl;
    JsonExport::convertToJson(binarySearchArray, binarySearchArrayCount, "Binary_Search_Array.json");
    JsonExport::convertToJson(binarySearchList, binarySearchListCount, "Binary_Search_Linked_List.json");

    // Delete memory
    delete[] binarySearchArray;
    delete[] binarySearchList;

    // Final cleanup
    delete[] overallTransactionArray;
    delete overallTransactionList;
    delete[] typeSortedArray;
    delete typeSortedList;

    // Program ends!
    cout << endl << "Done! Our program ends here." << endl;
    return 0;
}

PerformanceTracker* loadDataToArray(Transaction* &array, int &size) {

    // Initialize performance tracker for loading datasets into arrays.
    auto* loadDataToArrayTracker = new PerformanceTracker();
    loadDataToArrayTracker -> start();

    // Load CSV file
    array = TransactionReader::readCSVToArray(FILE_PATH, size);

    // Check resources used in loading data into arrays
    loadDataToArrayTracker -> stop();
    return loadDataToArrayTracker;
}

PerformanceTracker* loadDataToList(DoublyLinkedList* &list) {

    // Create a performance tracker for tracking loading performance for the linked list
    auto* loadDataToListTracker = new PerformanceTracker();
    loadDataToListTracker -> start();

    // Load data into a linked list
    TransactionReader::readCSVToList(FILE_PATH, list);

    // End performance tracking and print results
    loadDataToListTracker -> stop();
    return loadDataToListTracker;
}

PerformanceTracker* storeArrayToJson(Transaction* &array, const int &size) {

    // Create a tracker
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform conversion
    JsonExport::convertToJson(array, size, "Output_Array.json");

    // Stop and return tracker
    tracker -> stop();
    return tracker;
}

PerformanceTracker* storeLinkedListToJson(DoublyLinkedList* &list) {

    // Create a tracker
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform conversion to JSON
    JsonExport::convertToJson(list, "Output_Linked_List.json");

    // Stop and return tracker
    tracker -> stop();
    return tracker;
}

PerformanceTracker* separateArrayData(const Transaction* array, const int &size,
                                      Transaction* &ach, Transaction* &card, Transaction* &upi, Transaction* &wireTransfer,
                                      int &achSize, int &cardSize, int &upiSize, int &wireSize) {

    // Reset the arrays and counters
    ach = card = upi = wireTransfer = nullptr;
    achSize = cardSize = upiSize = wireSize = 0;

    // Start performance tracker to check performance of the payment channel split in arrays
    auto* tracker = new PerformanceTracker{};
    tracker -> start();

    // Distribution of transaction records into arrays
    ChannelSeparator::splitToChannelArray(array, size,
                                          ach, achSize,
                                          card, cardSize,
                                          upi, upiSize,
                                          wireTransfer, wireSize);

    // Stop the tracker
    tracker -> stop();
    return tracker;
}

PerformanceTracker* separateListData(const DoublyLinkedList* list,
                                     DoublyLinkedList* &achList,
                                     DoublyLinkedList* &cardList,
                                     DoublyLinkedList* &upiList,
                                     DoublyLinkedList* &wireList) {

    // Start performance tracker to check performance for dividing the overall linked list into different channels
    auto* tracker = new PerformanceTracker{};
    tracker -> start();

    // Perform the splitting process
    ChannelSeparator::splitToChannelList(list, achList, cardList, upiList, wireList);

    // Stop the tracker
    tracker -> stop();
    return tracker;
}

void copyArray(const Transaction* mainArray, const int &arraySize, Transaction* &array1) {

    // Create the new array
    array1 = new Transaction[arraySize];

    // Loop through the main array
    for (int i = 0; i < arraySize; i ++) {

        // Retrieve the associated transaction object
        const Transaction object = mainArray[i];

        // Assign to the arrays
        array1[i] = object;
    }
}

PerformanceTracker* arrayBubbleSort(Transaction* &array, int &size, const string &searchType, const bool &sample) {

    // Declare variables to store the information of the sampled array
    Transaction* workingArray;
    int workingSize;
    bool shouldCopyBack = false;

    // If sampling is needed, we sample for 100 records
    if (sample) {

        // Create a new array and copy the first 100 data into it
        workingArray = new Transaction[SAMPLING_SIZE];
        for (int i = 0; i < SAMPLING_SIZE; i++) workingArray[i] = array[i];

        // Set other values
        workingSize = SAMPLING_SIZE;
        shouldCopyBack = true;

    // If sampling is not required, maintain everything
    } else {
        workingArray = array;
        workingSize = size;
    }

    // Start performance tracker for bubble sort
    auto* tracker = new PerformanceTracker{};
    tracker -> start();

    // Perform the sorting process
    Sorter::bubbleSortInArray(workingArray, workingSize, searchType, true);

    // Stop the tracker
    tracker -> stop();

    // Copy sorted data back to the original array if sampling takes place
    if (shouldCopyBack) {

        // Clean the original array and return the working array
        delete[] array;
        array = workingArray;
        size = workingSize;
    }

    // Lastly, return the performance tracker
    return tracker;
}

PerformanceTracker* arrayInsertionSort(Transaction* &array, int &size, const string &searchType, const bool &sample) {

    // Declare variables to store the information of the sampled array
    Transaction* workingArray;
    int workingSize;
    bool shouldCopyBack = false;

    // If sampling is needed, we sample for 100 records
    if (sample) {

        // Create a new array and copy the first 100 data into it
        workingArray = new Transaction[SAMPLING_SIZE];
        for (int i = 0; i < SAMPLING_SIZE; i++) workingArray[i] = array[i];

        // Set other values
        workingSize = SAMPLING_SIZE;
        shouldCopyBack = true;

    // If sampling is not required, maintain everything
    } else {
        workingArray = array;
        workingSize = size;
    }

    // Start performance tracker for insertion sort
    auto* tracker = new PerformanceTracker{};
    tracker -> start();

    // Perform the sorting process
    Sorter::insertionSortInArray(workingArray, workingSize, searchType, true);

    // Stop the tracker
    tracker -> stop();

    // Copy sorted data back to the original array if sampling takes place
    if (shouldCopyBack) {

        // Clean the original array and return the working array
        delete[] array;
        array = workingArray;
        size = workingSize;
    }

    // Lastly, return the performance tracker
    return tracker;
}

PerformanceTracker* arrayMergeSort(Transaction* &array, int &size, const string &searchType, const bool &sample) {

    // Declare variables to store the information of the sampled array
    Transaction* workingArray;
    int workingSize;
    bool shouldCopyBack = false;

    // If sampling is needed, we sample for 100 records
    if (sample) {

        // Create a new array and copy the first 100 data into it
        workingArray = new Transaction[SAMPLING_SIZE];
        for (int i = 0; i < SAMPLING_SIZE; i++) workingArray[i] = array[i];

        // Set other values
        workingSize = SAMPLING_SIZE;
        shouldCopyBack = true;

    // If sampling is not required, maintain everything
    } else {
        workingArray = array;
        workingSize = size;
    }

    // Start performance tracker for merge sort
    auto* tracker = new PerformanceTracker{};
    tracker -> start();

    // Perform the sorting process
    Sorter::mergeSortInArray(workingArray, workingSize, searchType, true);

    // Stop the tracker
    tracker -> stop();

    // Copy sorted data back to the original array if sampling takes place
    if (shouldCopyBack) {

        // Clean the original array and return the working array
        delete[] array;
        array = workingArray;
        size = workingSize;
    }

    // Lastly, return the performance tracker
    return tracker;
}

PerformanceTracker* arrayQuickSort(Transaction* &array, int &size, const string &searchType, const bool &sample) {

    // Declare variables to store the information of the sampled array
    Transaction* workingArray;
    int workingSize;
    bool shouldCopyBack = false;

    // If sampling is needed, we sample for 100 records
    if (sample) {

        // Create a new array and copy the first 100 data into it
        workingArray = new Transaction[SAMPLING_SIZE];
        for (int i = 0; i < SAMPLING_SIZE; i++) workingArray[i] = array[i];

        // Set other values
        workingSize = SAMPLING_SIZE;
        shouldCopyBack = true;

    // If sampling is not required, maintain everything
    } else {
        workingArray = array;
        workingSize = size;
    }

    // Start performance tracker for quick sort
    auto* tracker = new PerformanceTracker{};
    tracker -> start();

    // Perform the sorting process
    Sorter::quickSortInArray(workingArray, 0, workingSize - 1, searchType, true);

    // Stop the tracker
    tracker -> stop();

    // Copy sorted data back to the original array if sampling takes place
    if (shouldCopyBack) {

        // Clean the original array and return the working array
        delete[] array;
        array = workingArray;
        size = workingSize;
    }

    // Lastly, return the performance tracker
    return tracker;
}

PerformanceTracker* listBubbleSort(DoublyLinkedList &list, const string &searchType, const bool &sample) {

    // Declare a variable to store the list to be sorted
    const DoublyLinkedList* sortingList = &list;
    DoublyLinkedList* tempList = nullptr;

    // If sampling is required, create a new list
    if (sample) {

        // The temporary list created to store nodes
        tempList = new DoublyLinkedList();

        // Initializing variables
        int i = 0;
        const Node* node = list.getHeadNode();

        // Only record nodes within the sample size
        while (node != nullptr && i < SAMPLING_SIZE) {

            // Create a copy of the transaction object and insert to the list
            Transaction transactionObject = node -> transactionObject;
            tempList -> insertAtEnd(&transactionObject);

            // Traverse to the next node
            node = node -> nextNode;
            i++;
        }

        // Replace the list
        sortingList = tempList;
    }

    // Create a performance tracker
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform bubble sort
    const DoublyLinkedList swappedList = Sorter::bubbleSortInList(*sortingList, searchType);

    // Stop the tracker
    tracker -> stop();

    // Clear and repopulate the items back into the list
    list.clear();
    const Node* currentNode = swappedList.getHeadNode();
    while (currentNode != nullptr) {
        list.insertAtEnd(&currentNode -> transactionObject);
        currentNode = currentNode -> nextNode;
    }

    // Clean up the temporary list
    if (tempList != nullptr) tempList -> clear();
    delete tempList;

    // Return the tracker
    return tracker;
}

PerformanceTracker* listInsertionSort(DoublyLinkedList &list, const string &searchType, const bool &sample) {

    // Declare a variable to store the list to be sorted
    const DoublyLinkedList* sortingList = &list;
    DoublyLinkedList* tempList = nullptr;

    // If sampling is required, create a new list
    if (sample) {

        // The temporary list created to store nodes
        tempList = new DoublyLinkedList();

        // Initializing variables
        int i = 0;
        const Node* node = list.getHeadNode();

        // Only record nodes within the sample size
        while (node != nullptr && i < SAMPLING_SIZE) {

            // Create a copy of the transaction object and insert to the list
            Transaction transactionObject = node -> transactionObject;
            tempList -> insertAtEnd(&transactionObject);

            // Traverse to the next node
            node = node -> nextNode;
            i++;
        }

        // Replace the list
        sortingList = tempList;
    }

    // Create a performance tracker
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform insertion sort
    const DoublyLinkedList swappedList = Sorter::insertionSortInList(*sortingList, searchType);

    // Stop the tracker
    tracker -> stop();

    // Clear and repopulate the items back into the list
    list.clear();
    const Node* currentNode = swappedList.getHeadNode();
    while (currentNode != nullptr) {
        list.insertAtEnd(&currentNode -> transactionObject);
        currentNode = currentNode -> nextNode;
    }

    // Delete the temporary list created
    if (tempList != nullptr) tempList -> clear();
    delete tempList;

    // Return the tracker
    return tracker;
}

PerformanceTracker* listMergeSort(DoublyLinkedList &list, const string &searchType, const bool &sample) {

    // Declare a variable to store the list to be sorted
    const DoublyLinkedList* sortingList = &list;
    DoublyLinkedList* tempList = nullptr;

    // If sampling is required, create a new list
    if (sample) {

        // The temporary list created to store nodes
        tempList = new DoublyLinkedList();

        // Initializing variables
        int i = 0;
        const Node* node = list.getHeadNode();

        // Only record nodes within the sample size
        while (node != nullptr && i < SAMPLING_SIZE) {

            // Create a copy of the transaction object and insert to the list
            Transaction transactionObject = node -> transactionObject;
            tempList -> insertAtEnd(&transactionObject);

            // Traverse to the next node
            node = node -> nextNode;
            i++;
        }

        // Replace the list
        sortingList = tempList;
    }

    // Create a performance tracker
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform merge sort
    const DoublyLinkedList swappedList = Sorter::mergeSortInList(*sortingList, searchType);

    // Stop the tracker
    tracker -> stop();

    // Clear and repopulate the items back into the list
    list.clear();
    const Node* currentNode = swappedList.getHeadNode();
    while (currentNode != nullptr) {
        list.insertAtEnd(&currentNode -> transactionObject);
        currentNode = currentNode -> nextNode;
    }

    // Delete the temporary list
    if (tempList != nullptr) tempList -> clear();
    delete tempList;

    // Return the tracker
    return tracker;
}

PerformanceTracker* listQuickSort(DoublyLinkedList &list, const string &searchType, const bool &sample) {

    // Declare a variable to store the list to be sorted
    const DoublyLinkedList* sortingList = &list;
    DoublyLinkedList* tempList = nullptr;

    // If sampling is required, create a new list
    if (sample) {

        // The temporary list created to store nodes
        tempList = new DoublyLinkedList();

        // Initializing variables
        int i = 0;
        const Node* node = list.getHeadNode();

        // Only record nodes within the sample size
        while (node != nullptr && i < SAMPLING_SIZE) {

            // Create a copy of the transaction object and insert to the list
            Transaction transactionObject = node -> transactionObject;
            tempList -> insertAtEnd(&transactionObject);

            // Traverse to the next node
            node = node -> nextNode;
            i++;
        }

        // Replace the list
        sortingList = tempList;
    }

    // Create a performance tracker
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform quick sort
    const DoublyLinkedList swappedList = Sorter::quickSortInList(*sortingList, searchType);

    // Stop the tracker
    tracker -> stop();

    // Clear and repopulate the items back into the list
    list.clear();
    const Node* currentNode = swappedList.getHeadNode();
    while (currentNode != nullptr) {
        list.insertAtEnd(&currentNode -> transactionObject);
        currentNode = currentNode -> nextNode;
    }

    // Delete the temporary list
    if (tempList != nullptr) tempList -> clear();
    delete tempList;

    // Return the tracker
    return tracker;
}

PerformanceTracker* arrayLinearSearch(Transaction* array, const int size, Transaction** &result, const string &searchType, int &matchCount) {

    // Create a performance tracker for tracking linear searching in arrays
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform linear search
    result = Searcher::linearSearchUsingArray(array, size, searchType, matchCount);

    // Stop and return the tracker
    tracker -> stop();
    return tracker;
}

PerformanceTracker* arrayBinarySearch(Transaction* array, const int size, Transaction** &result, const string &searchType, int &matchCount) {

    // Create a performance tracker to track binary search in arrays
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform binary search
    result = Searcher::binarySearchUsingArray(array, size, searchType, matchCount);

    // Stop and return the tracker
    tracker -> stop();
    return tracker;
}

PerformanceTracker* listLinearSearch(const DoublyLinkedList &list, Transaction** &outputList, string &searchType, int &outputSize) {

    // Create a performance tracker for tracking linear searching in linked lists
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform linear search
    outputList = Searcher::linearSearchUsingList(list, searchType, outputSize);

    // Stop and return the tracker
    tracker -> stop();
    return tracker;
}

PerformanceTracker* listBinarySearch(const DoublyLinkedList &list, Transaction** &outputList, string &searchType, int &outputSize) {

    // Performance tracker to track performance of binary search in linked lists
    auto* tracker = new PerformanceTracker();
    tracker -> start();

    // Perform binary search
    outputList = Searcher::binarySearchUsingList(list, searchType, outputSize);

    // Stop and return the tracker
    tracker -> stop();
    return tracker;
}