/******************************************************************************

** Student Name: Boxuan Lu

** Student Number: s3654900

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

List *initList();

void addToList(List *list, Node *node);

void assignValueToStock(char *data, Stock *stock);

Node *createNode(Stock *stock, Node *node);

void sortList(VmSystem *system);

void sortListByID(VmSystem *system);

void reassignID(VmSystem *system);

#endif
