//
// Created by cmchan04 on 6/8/2025.
//

#include "ChannelSeparator.h"
#include <string>

#include "StringUtil.h"

using namespace std;

/**
 * This function rearranges and stores transaction records based on the payment channel
 * @param source The main array or linked list that stores all transactions
 * @param sourceSize Size of main Array
 * @param ach Array for the ACH payment channel                     @param achSize new size of the ACH array
 * @param card Array for the card payment channel                   @param cardSize new size of the card array
 * @param upi Array for the UPI payment channel                     @param upiSize new size of the UPI array
 * @param wireTransfer Array for the wire_transfer payment channel  @param wireSize new size of the wire transfer array
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

/**
 * This method categorizes each transaction into their respective channels.
 * @param list The original list consisting of all transaction data
 * @param achList The new list consisting ACH
 * @param cardList The new list consisting card
 * @param upiList The new list consisting UPI
 * @param wireList The new list consisting wire transfer
 */
void ChannelSeparator::splitToChannelList(const DoublyLinkedList* list,
                                          DoublyLinkedList* &achList,
                                          DoublyLinkedList* &cardList,
                                          DoublyLinkedList* &upiList,
                                          DoublyLinkedList* &wireList) {

    // Reset the lists
    if (achList != nullptr) achList -> clear();
    else achList = new DoublyLinkedList();

    if (cardList != nullptr) cardList -> clear();
    else cardList = new DoublyLinkedList();

    if (upiList != nullptr) upiList -> clear();
    else upiList = new DoublyLinkedList();

    if (wireList != nullptr) wireList -> clear();
    else wireList = new DoublyLinkedList();

    // Loop through each node
    const Node* currentNode = list -> getHeadNode();
    while (currentNode != nullptr) {

        // Retrieve the payment channel
        Transaction* currentObject = currentNode -> transactionObject;

        // Check the transaction type and add to the new list
        if (string currentPayment = toLowerCase(currentObject -> paymentChannel);
                currentPayment == "ach")                    achList -> insertAtEnd(currentObject);
        else if (currentPayment == "card")                  cardList -> insertAtEnd(currentObject);
        else if (currentPayment == "upi")                   upiList -> insertAtEnd(currentObject);
        else if (currentPayment == "wire_transfer")          wireList -> insertAtEnd(currentObject);

        // Move on to the next node
        currentNode = currentNode -> nextNode;
    }
}
