//
// Created by cmchan04 on 6/8/2025.
//

#include "ChannelSeparator.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * This function rearranges and stores transactions records based on payment channel
 * @param source The main array / linked list that store all transactions
 * @param sourceSize Size of main Array
 * @param ach Array for ACH payment channel
 * @param card Array for card payment channel
 * @param upi Array for UPI payment channel
 * @param wireTransfer Array for wire_transfer payment channel
 */
void ChannelSeparator::splitToChannelArray(const Transaction* source, const int sourceSize,
                                           Transaction* &ach, int &achSize,
                                           Transaction* &card, int &cardSize,
                                           Transaction* &upi, int &upiSize,
                                           Transaction* &wireTransfer, int &wireSize) {

    // Counter for each array size
    int achCount = 0, cardCount = 0, upiCount = 0, wireCount = 0;

    // Loop through the length of the overall array to count the size for each channel
    for (int i = 0; i < sourceSize; ++i) {

        // Count for each channel
        if (const string &channel = source[i].paymentChannel; channel == "ACH") achCount++;
        else if (channel == "card") cardCount++;
        else if (channel == "UPI") upiCount++;
        else if (channel == "wire_transfer") wireCount++;
    }

    // Declare arrays for each transaction
    ach = new Transaction[achCount];
    card = new Transaction[cardCount];
    upi = new Transaction[upiCount];
    wireTransfer = new Transaction[wireCount];

    // Distribute data into different array
    for (int i = 0; i < sourceSize; ++i) {

        // Retrieve transaction
        const Transaction& transaction = source[i];

        // Add transaction to respective channels
        if (const string &channel = transaction.paymentChannel; channel == "ACH") {
            ach[achSize++] = transaction;

        } else if (channel == "card") {
            card[cardSize++] = transaction;

        } else if (channel == "UPI") {
            upi[upiSize++] = transaction;

        } else if (channel == "wire_transfer") {
            wireTransfer[wireSize++] = transaction;
        }
    }
}
