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
        exit(EXIT_SUCCESS);
    } else {
        list->head = NULL;
        list->size = 0;
    }

    return list;
}

Node *createNode(Stock *data, Node *next) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error, can't create a new node!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    if (next == NULL) {
        newNode->next=NULL;
    }
    newNode->next = next;

    return newNode;
}

/* print stock list */
void printStockList(Node *start) {
    Node *currentItem = start;

    if (currentItem == NULL) {
        currentItem = currentItem->next;
    }

    while (currentItem != NULL) {

        printf("%s|%s|%s|%d.%d|%d", currentItem->data->id, currentItem->data->name, currentItem->data->desc,
               currentItem->data->price.dollars, currentItem->data->price.cents, currentItem->data->onHand);

        currentItem = currentItem->next;
    }
    printf("\n");
}