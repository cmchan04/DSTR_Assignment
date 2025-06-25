//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include "JsonExport.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

/**
 * A method to remove any invalid characters from a string (e.g. "\r")
 * @param input The raw string value
 * @return The cleaned string value with ASCII falls within 32 to 126 (e.g., alphabets, numbers, space, tilde)
 */
string JsonExport::cleanString(const string &input) {

    // Declared a string variable to store the cleaned string
    string cleaned;
    cleaned.reserve(input.size());

    // Loop through each character in the input
    for (const char c : input) {

        // Only append the ASCII characters that fulfill the criteria
        if (c >= 32 && c <= 126) cleaned += c;
    }

    // Return the cleaned string
    return cleaned;
}

/**
 * A method that defines the structure of the JSON format (similar to the \code toString()\endcode method in Java).
 * @param format The JSON struct that declares how a JSON output should be formatted.
 * @param transaction The transaction data to be written into JSON
 */
void to_json(json &format, const Transaction &transaction) {

    // Declare the format of the JSON file
    format = json{
        {"transaction_id",              JsonExport::cleanString(transaction.transactionId)},
        {"timestamp",                   JsonExport::cleanString(transaction.timestamp)},
        {"sender_account",              JsonExport::cleanString(transaction.senderAcc)},
        {"receiver_account",            JsonExport::cleanString(transaction.receiverAcc)},
        {"amount",                      transaction.amount},
        {"transaction_type",            JsonExport::cleanString(transaction.transactionType)},
        {"merchant_category",           JsonExport::cleanString(transaction.merchantCategory)},
        {"location",                    JsonExport::cleanString(transaction.location)},
        {"device_used",                 JsonExport::cleanString(transaction.deviceUsed)},
        {"is_fraud",                    transaction.isFraud},
        {"fraud_type",                  JsonExport::cleanString(transaction.fraudType)},
        {"time_since_last_transaction", transaction.timeSinceLastTransaction},
        {"spending_deviation_score",    transaction.spendingDeviationScore},
        {"velocity_score",              transaction.velocityScore},
        {"geo_anomaly_score",           transaction.geoAnomalyScore},
        {"payment_channel",             JsonExport::cleanString(transaction.paymentChannel)},
        {"ip_address",                  JsonExport::cleanString(transaction.ipAddress)},
        {"device_hash",                 JsonExport::cleanString(transaction.deviceHash)}
    };
}

/**
 * This method generates JSON data based on the data contained in the pointer to the pointer of a Transaction array.
 * @param array The pointer to the pointer of the transaction array
 * @param arraySize The size of the array
 * @param filename The file name for the output JSON file
 */
void JsonExport::convertToJson(Transaction** array, const int arraySize, const string &filename) {

    // Check array size
    if (array == nullptr || arraySize <= 0) {

        // Print error message if the array does not have data
        cerr << "Error: Array is null or empty" << endl;
        return;
    }

    // Declare a JSON object to store output
    json jsonCollection = json::array();

    // Add transaction to JSON object
    for (int i = 0; i < arraySize; i++) {

        // Ensure no null values are added
        if (array[i] != nullptr) jsonCollection.push_back(*array[i]);
    }

    // Generate the corresponding JSON file
    generateJsonFile(jsonCollection, filename);
}

/**
 * This method generates a JSON file based on the data in the Transaction array.
 * @param array The pointer to a Transaction array
 * @param arraySize The size of the array
 * @param filename The name to be given to the output file
 */
void JsonExport::convertToJson(Transaction* array, const int arraySize, const string &filename) {

    // Check array size
    if (array == nullptr || arraySize <= 0) {

        // Print error message if the array does not have data
        cerr << "Error: Array is null or empty" << endl;
        return;
    }

    // Declare a JSON object to store output
    json jsonCollection = json::array();

    // Add output to object
    for (int i = 0; i < arraySize; i++) {
        jsonCollection.push_back(array[i]);
    }

    // Generate the corresponding JSON file
    generateJsonFile(jsonCollection, filename);
}

/**
 * This method converts a doubly linked list into JSON format.
 * @param list The doubly linked list consisting of Transaction data
 * @param filename The name of the output file
 */
void JsonExport::convertToJson(const DoublyLinkedList* list, const string &filename) {

    // Check array size
    if (list == nullptr || list -> getSize() <= 0) {

        // Print error message when the list is empty
        cerr << "Error: Linked list is null or empty" << endl;
        return;
    }

    // Declare a JSON object to store output
    json jsonCollection = json::array();

    // Add output to the object
    for (const Node* currentNode = list -> getHeadNode(); currentNode != nullptr; currentNode = currentNode -> nextNode) {
        const Transaction &currentTransaction = currentNode -> transactionObject;
        jsonCollection.push_back(currentTransaction);
    }

    // Generate the corresponding JSON file
    generateJsonFile(jsonCollection, filename);
}

/**
 * This method creates a new JSON file while checking through different errors that might arise during file creation.
 * @param jsonObject The JSON object consisting of Transaction data
 * @param filename The name to be given to the new file
 */
void JsonExport::generateJsonFile(const json &jsonObject, const string &filename) {

    // Create the JSON file
    const string fullPath = filesystem::current_path().parent_path().string() + "/src/resources/exported_json/" + filename;
    ofstream file(fullPath);

    // Check if the file can be opened
    if (!file.is_open()) {
        cerr << "Error: Cannot create file " + filename << endl;
    }

    // Set the JSON with 4 spaces as index
    file << jsonObject.dump(4);

    // Check if the writing is successful
    if (file.fail()) {
        cerr << "Error: Cannot write file " << filename << endl;
        file.close();
        return;
    }

    // File written successfully and closed.
    file.close();
    cout << "File '" << filename << "' is exported to the \"exported_json\" folder successfully." << endl;
}
