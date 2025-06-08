//
// Created by cmchan04 on 6/8/2025.
//

#include "channelSeperator.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * This function rearranges and stores transactions records based on payment channel
 * @param source - The main array / linked list that store all transactions
 * @param sourceSize - Size of main Array
 * @param ach - Array for ACH payment channel
 * @param card - Array for card payment channel
 * @param upi - Array for UPI payment channel
 * @param wireTransfer - Array for wire_transfer payment channel
 *
 * @var *Count - count the size of array to be created
 */
void channelSeperator::splitByChannel(const Transaction *source, int sourceSize, Transaction *&ach, int &achSize,
                                      Transaction *&card, int &cardSize, Transaction *&upi, int &upiSize,
                                      Transaction *&wireTransfer, int &wireSize) {
    //Counter for Array Size
    int achCount = 0, cardCount = 0, upiCount = 0, wireCount = 0;

    for (int i = 0; i < sourceSize; ++i) {
        const string& channel = source[i].paymentChannel;
        if (channel == "ACH") ++achCount;
        else if (channel == "card") ++cardCount;
        else if (channel == "UPI") ++upiCount;
        else if (channel == "wire_transfer") ++wireCount;
    }

    //Declare Array Size
    ach = new Transaction[achCount];
    card = new Transaction[cardCount];
    upi = new Transaction[upiCount];
    wireTransfer = new Transaction[wireCount];

    // Distribute data into different array
    for (int i = 0; i < sourceSize; ++i) {
        const Transaction& t = source[i];
        const string& channel = t.paymentChannel;

        if (channel == "ACH") {
            ach[achSize++] = t;
        } else if (channel == "card") {
            card[cardSize++] = t;
        } else if (channel == "UPI") {
            upi[upiSize++] = t;
        } else if (channel == "wire_transfer") {
            wireTransfer[wireSize++] = t;
        }
    }

}
