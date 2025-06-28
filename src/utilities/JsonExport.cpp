//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include "JsonExport.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;
using namespace filesystem;

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
    if (array == nullptr || arraySize <= 0) throw invalid_argument("Array is null or empty.");

    // Start writing to file
    try {

        // Retrieve the output folder, and create the directory if needed
        const path outputDir = current_path().parent_path() / "src" / "resources" / "exported_json";
        create_directories(outputDir);

        // Generate the full directory and create a file inside it
        const path fullPath = outputDir / filename;
        ofstream file(fullPath, ios::out | ios::trunc);

        // Ensure the file is generated correctly
        if (!file.is_open()) throw runtime_error("Error: Cannot create or open file: " + fullPath.string());

        // Start writing JSON file (manually)
        file << "[\n";

        // Add transaction to JSON object
        for (int i = 0; i < arraySize; i++) {

            // Check if the element is null
            if (array[i] != nullptr) {

                // Dereference the transaction object
                const Transaction &transaction = *array[i];

                // Generate the JSON string for the transaction
                string jsonString = json(transaction).dump(4);

                // Proper indentation for each line
                file << "    ";

                // Loop through each line in the JSON string
                for (size_t j = 0; j < jsonString.length(); j++) {
                    file << jsonString[j];

                    // Indentation is added when a new line starts (except for the final line where the final '}' is added)
                    if (jsonString[j] == '\n' && j < jsonString.length() - 1) file << "    ";
                }

                // Check if it is the last object. If no, then add a comma and a new line
                if (i != arraySize - 1) file << ",\n";
            }
        }

        // Add an ending
        file << "\n]\n";

        // File written successfully and closed.
        file.close();
        cout << "File '" << filename << "' is exported to the \"exported_json\" folder successfully." << endl;

    // If any error occurs, show the error message
    } catch (const exception &e) {
        throw runtime_error("Error generating JSON file '" + filename + "'.");
    }
}

/**
 * This method generates a JSON file based on the data in the Transaction array.
 * @param array The pointer to a Transaction array
 * @param arraySize The size of the array
 * @param filename The name to be given to the output file
 */
void JsonExport::convertToJson(Transaction* array, const int arraySize, const string &filename) {

    // Check array size
    if (array == nullptr || arraySize <= 0) throw invalid_argument("Array pointer cannot be null or empty.");

    // Start writing to file
    try {

        // Retrieve the output folder, and create the directory if needed
        const path outputDir = current_path().parent_path() / "src" / "resources" / "exported_json";
        create_directories(outputDir);

        // Generate the full directory and create a file inside it
        const path fullPath = outputDir / filename;
        ofstream file(fullPath, ios::out | ios::trunc);

        // Ensure the file is generated correctly
        if (!file.is_open()) throw runtime_error("Error: Cannot create or open file: " + fullPath.string());

        // Start writing JSON file (manually)
        file << "[\n";

        // Add output to object
        for (int i = 0; i < arraySize; i++) {

            // Retrieve the transaction object
            const Transaction& transaction = array[i];

            // Generate the JSON string for the transaction
            string jsonString = json(transaction).dump(4);

            // Proper indentation for each line
            file << "    ";

            // Loop through each line in the JSON string
            for (size_t j = 0; j < jsonString.length(); j++) {
                file << jsonString[j];

                // Indentation is added when a new line starts (except for the final line where the final '}' is added)
                if (jsonString[j] == '\n' && j < jsonString.length() - 1) file << "    ";
            }

            // Check if it is the last object. If no, then add a comma and a new line
            if (i != arraySize - 1) file << ",\n";
        }

        // Add an ending
        file << "\n]\n";

        // File written successfully and closed.
        file.close();
        cout << "File '" << filename << "' is exported to the \"exported_json\" folder successfully." << endl;

    // If any error occurs, show the error message
    } catch (const exception &e) {
        throw runtime_error("Error generating JSON file '" + filename + "'.");
    }
}

/**
 * This method converts a doubly linked list into JSON format.
 * @param list The doubly linked list consisting of Transaction data
 * @param filename The name of the output file
 */
void JsonExport::convertToJson(const DoublyLinkedList* list, const string &filename) {

    // Check linked list size
    if (list == nullptr || list -> getSize() <= 0) throw invalid_argument("Linked list cannot be empty or null.");

    // Also, check for head node
    const Node* headNode = list -> getHeadNode();
    if (headNode == nullptr) throw invalid_argument("Linked list's head node is null despite non-zero size");

    // Start writing to file
    try {

        // Retrieve the output folder, and create the directory if needed
        const path outputDir = current_path().parent_path() / "src" / "resources" / "exported_json";
        create_directories(outputDir);

        // Generate the full directory and create a file inside it
        const path fullPath = outputDir / filename;
        ofstream file(fullPath, ios::out | ios::trunc);

        // Ensure the file is generated correctly
        if (!file.is_open()) throw runtime_error("Error: Cannot create or open file: " + fullPath.string());

        // Start writing JSON file (manually)
        file << "[\n";

        // Initialize variables and loop through each node
        const Node* currentNode = headNode;
        int count = 0;
        const int totalSize = list -> getSize();

        while (currentNode != nullptr) {

            // Retrieve transaction
            const Transaction &currentTransaction = *currentNode -> transactionObject;

            // Generate the JSON string for the transaction
            string jsonString = json(currentTransaction).dump(4);

            // Proper indentation for each line
            file << "    ";

            // Loop through each line in the JSON string
            for (size_t j = 0; j < jsonString.length(); j++) {
                file << jsonString[j];

                // Indentation is added when a new line starts (except for the final line where the final '}' is added)
                if (jsonString[j] == '\n' && j < jsonString.length() - 1) file << "    ";
            }

            // Check if it is the last object. If no, then add a comma and a new line
            if (++count < totalSize) file << ",\n";

            // Traverse to the next node
            currentNode = currentNode -> nextNode;
        }

        // Add an ending
        file << "\n]\n";

        // File written successfully and closed.
        file.close();
        cout << "File '" << filename << "' is exported to the \"exported_json\" folder successfully." << endl;

    // If any error occurs, show the error message
    } catch (const exception &e) {
        throw runtime_error("Error generating JSON file '" + filename + "'.");
    }
}
