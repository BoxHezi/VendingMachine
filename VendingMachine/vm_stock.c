#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

/* initialize list */
List *initList() {
    List *list = malloc(sizeof(*list));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    } else {
        list->head = NULL;
        list->size = 0;
    }

    return list;
}

/* create new node */
Node *createNode(Stock *stock, Node *node) {


    node->data = stock;
    node->next = NULL;

    return node;
}

void addToList(List *list, Node *node) {
    node->next = list->head;
    list->head = node;
    list->size++;
}

void assignValueToStock(char *data, Stock *stock) {
    /* get stock data from each line */
    char *id;
    char *name;
    char *desc;
    char *priceInString;
    char *dollarInString;
    char *centInString;
    char *onHandInString;

    unsigned dollars;
    unsigned cents;
    unsigned onHand;

    id = strtok(data, STOCK_DELIM);
    name = strtok(NULL, STOCK_DELIM);
    desc = strtok(NULL, STOCK_DELIM);
    priceInString = strtok(NULL, STOCK_DELIM);
    onHandInString = strtok(NULL, STOCK_DELIM);

    /* get dollars and cents from price as a string */
    dollarInString = strtok(priceInString, ".");
    centInString = strtok(NULL, ".");

    /* change and cast dollars, cents and onHand to unsigned */
    dollars = (unsigned) strtol(dollarInString, NULL, 10);
    cents = (unsigned) strtol(centInString, NULL, 10);
    onHand = (unsigned) strtol(onHandInString, NULL, 10);

    strcpy(stock->id, id);
    strcpy(stock->name, name);
    strcpy(stock->desc, desc);
    stock->price.dollars = dollars;
    stock->price.cents = cents;
    stock->onHand = onHand;
    printf("Stock added!\n");
}