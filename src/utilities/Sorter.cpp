//
// Created by Lim Beng Rhui on 11/06/2025.
//

#include "Sorter.h"

void Sorter::bubbleSortArray(Transaction *transactions, int size, const std::string &column, bool ascending) {

    // Convert the sort field to lower case
    string col = toLowerCase(column);

    // Start bubble sorting
    for (int i = 0; i < size; ++i) {

        // Counter
        if (i % 10000 == 0){
            cout << i << endl;
        }

        // Avoid unnecessary swapping for completed indexes
        for (int j = 0; j < size - i - 1; ++j) {

            // A flag that indicates should swap or not
            bool shouldSwap = false;

            // String Comparison
            if (col == "type")
                shouldSwap = ascending ? transactions[j].transactionType >transactions[j + 1].transactionType
                                       : transactions[j].transactionType < transactions[j + 1].transactionType;
            else if (col == "location")
                shouldSwap = ascending ? transactions[j].location > transactions[j + 1].location
                                       : transactions[j].location < transactions[j + 1].location;

            if (shouldSwap) {
                transactions->swap(transactions[j], transactions[j + 1]);
            }

        }
    }
}
