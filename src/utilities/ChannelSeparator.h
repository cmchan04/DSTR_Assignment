//
// Created by cmchan04 on 6/8/2025.
//
#pragma once

#include "../entities/Transaction.h"
#include "../entities/DoublyLinkedList.h"

#pragma once

struct ChannelSeparator {

    //Declaration of functions
    static void splitToChannelArray(const Transaction* source, int sourceSize,
                                    Transaction* &ach, int &achSize,
                                    Transaction* &card, int &cardSize,
                                    Transaction* &upi, int &upiSize,
                                    Transaction* &wireTransfer, int &wireSize);

    static void splitToChannelList(const DoublyLinkedList* list,
                                   DoublyLinkedList* &achList,
                                   DoublyLinkedList* &cardList,
                                   DoublyLinkedList* &upiArray,
                                   DoublyLinkedList* &wireList);
};

