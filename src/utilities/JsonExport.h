//
// Created by Lim Beng Rhui on 11/06/2025.
//

// Make sure the header file is only included once in the program
#pragma once

#include "../entities/DoublyLinkedList.h"
#include "../entities/Transaction.h"
#include <string>
#include <nlohmann/json_fwd.hpp>

/**
 * A utility struct that contains the method to convert and export arrays and linked lists into JSON files.
 */
struct JsonExport {

    // Methods to convert data into JSON
    static void convertToJson(Transaction** array, int arraySize, const string &filename = "export.json");
    static void convertToJson(Transaction* array, int arraySize, const string &filename = "export.json");
    static void convertToJson(const DoublyLinkedList* list, const string &filename = "export.json");

    // Utility methods to be used within the JsonExport class
    static string cleanString(const string &input);
};

