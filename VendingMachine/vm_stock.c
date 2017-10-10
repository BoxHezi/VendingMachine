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
   List *list = malloc(sizeof(List));
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

/* add item to the end of the list */
void addToList(List *list, Node *node) {
   Node *tempNode = NULL;

   /* set node next to NULL avoid invalid pointer be added */
   node->next = NULL;

   /* check for the first time addition */
   if (list->head == NULL) {
      list->head = node;
   } else {
      tempNode = list->head;
      while (TRUE) {
         if (tempNode->next == NULL) {
            tempNode->next = node;
            break;
         }
         tempNode = tempNode->next;

      }
   }

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

   /* store value that convert string to int */
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
}

void sortList(VmSystem *system) {
   Node *currentItem;
   Stock *tempData;
   int i = 0;

   /* nested loop to make sure that item is sorted in correct order
    * if C,B,A is read, no nested loop will sort the list to B,A,C
    * by using nested loop, it will be sorted in A,B,C */
   for (i = 0; i < system->itemList->size; i++) {
      currentItem = system->itemList->head;
      while (currentItem->next != NULL) {
         if (strcmp(currentItem->data->name, currentItem->next->data->name) > 0) {
            tempData = currentItem->data;
            currentItem->data = currentItem->next->data;
            currentItem->next->data = tempData;
         }
         currentItem = currentItem->next;
      }
   }

}

void sortListByID(VmSystem *system) {
   Node *currentItem;
   Stock *tempData;
   int i = 0;

   for (i = 0; i < system->itemList->size; i++) {
      currentItem = system->itemList->head;
      while (currentItem->next != NULL) {
         if (strcmp(currentItem->data->id, currentItem->next->data->id) > 0) {
            tempData = currentItem->data;
            currentItem->data = currentItem->next->data;
            currentItem->next->data = tempData;
         }
         currentItem = currentItem->next;
      }
   }
}

/* when take out item form middle of the system
 * shift id after the item been removed by 1 */
void reassignID(VmSystem *system) {
   int idVal = 0;
   int nonValSize = 0;
   Node *currentItem = system->itemList->head;
   char newID[ID_LEN + NULL_SPACE];
   /* initialize the idValInString for max 4 digits longs
    * as the max id can be I9999 */
   char idValInString[4 + NULL_SPACE];

   sortListByID(system);

   while (currentItem != NULL) {
      idVal++;
      strcpy(newID, "I");

      /* nonValSize stand for number of zero after I
       * and before the first non-zero number */
      nonValSize = 3;

      if (idVal >= 10 && idVal < 100) {
         nonValSize = 2;
      } else if (idVal >= 100 && idVal < 1000) {
         nonValSize = 1;
      } else if (idVal > 1000) {
         nonValSize = 0;
      }

      while (nonValSize > 0) {
         strcat(newID, "0");
         nonValSize--;
      }

      sprintf(idValInString, "%d", idVal);
      strcat(newID, idValInString);

      strcpy(currentItem->data->id, newID);

      currentItem = currentItem->next;
   }
}