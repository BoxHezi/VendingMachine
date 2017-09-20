#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */


List *initList() {
    /* initialize list */
    List *list = malloc(sizeof(*list));
    if (list == NULL) {
        exit(EXIT_SUCCESS);
    } else {
        list->head = NULL;
        list->size = 0;
    }

    return list;
}


/* print stock list */
void printStockList(Node *start) {
    Node *currentItem = start;

    currentItem = currentItem->next;
    while (currentItem != NULL) {

        printf("%s|%s|%s|%d.%d|%d", currentItem->data->id, currentItem->data->name, currentItem->data->desc,
               currentItem->data->price.dollars, currentItem->data->price.cents, currentItem->data->onHand);

        currentItem = currentItem->next;
    }
    printf("\n");
}