#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

void printStockList(Node *start);

List *initList();

void addToList(List *list, Node *node);

void assignValueToStock(char *data, Stock *stock);

Node *createNode(Stock *stock, Node *node);

#endif
