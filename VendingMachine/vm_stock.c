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


/* print stock list */
void printStockList(Node *start) {

    if (start == NULL) {
        start = start->next;
    }

    while (start != NULL) {

        printf("%s|%s|%s|%d.%d|%d", start->data->id, start->data->name, start->data->desc,
               start->data->price.dollars, start->data->price.cents, start->data->onHand);

        start = start->next;
    }
    printf("\n");
}