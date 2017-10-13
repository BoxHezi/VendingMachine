/******************************************************************************

** Student Name: Boxuan Lu

** Student Number: s3654900

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm_options.h"

#define MAX_DATA_LENGTH 512
#define MAX_PRICE_LENGTH 4
/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state. Look at the structure
 * defined in vm_system.h.
 **/
Boolean systemInit(VmSystem *system) {

   system->itemList = initList();
   initCoins(system->cashRegister);
   system->stockFileName = NULL;
   system->coinFileName = NULL;


   return TRUE;
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem *system) {
   Node *current = system->itemList->head;
   Node *previous = NULL;

   while (current != NULL) {
      previous = current;
      current = current->next;
      free(previous->data);
      free(previous);
   }


   free(system->itemList);
}

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
      VmSystem *system, const char *stockFileName, const char *coinsFileName) {
   system->stockFileName = stockFileName;
   system->coinFileName = coinsFileName;
   return TRUE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem *system, const char *fileName) {
   char data[MAX_DATA_LENGTH];
   Node *node;
   Stock *stock;

   /* load stock file */
   FILE *stockFile;
   stockFile = fopen(fileName, "r");

   if (stockFile == NULL) {
      printf(COLOR_RED "No stock file found!\n" COLOR_RESET);
      return FALSE;
   }

   system->stockFileName = fileName;

   /* while the file has next line */
   while (fgets(data, sizeof(data), stockFile) != NULL) {
      node = malloc(sizeof(Node));
      stock = malloc(sizeof(Stock));
      assignValueToStock(data, stock);

      createNode(stock, node);
      addToList(system->itemList, node);
   }
   sortList(system);

   fclose(stockFile);
   return TRUE;
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem *system, const char *fileName) {
   char data[MAX_DATA_LENGTH];

   FILE *coinsFile;
   coinsFile = fopen(fileName, "r");

   if (coinsFile == NULL) {
      printf(COLOR_RED "No coins file found" COLOR_RESET);
      return FALSE;
   }

   system->coinFileName = fileName;

   while (fgets(data, sizeof(data), coinsFile) != NULL) {
      storeCoin(system, data);
   }

   fclose(coinsFile);
   return TRUE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem *system) {
   FILE *fp;
   Node *node;

   sortListByID(system);

   printf(COLOR_YELLOW "Writing to file...\n" COLOR_RESET);
   fp = fopen(system->stockFileName, "w");

   node = system->itemList->head;

   while (node != NULL) {
      fprintf(fp, "%s|%s|%s|%u.%02u|%u\n", node->data->id, node->data->name,
              node->data->desc, node->data->price.dollars,
              node->data->price.cents, node->data->onHand);

      node = node->next;
   }

   fclose(fp);
   systemFree(system);
   return TRUE;
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem *system) {
   return FALSE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem *system) {
   unsigned idSize = 0;
   unsigned nameSize = 0;
   unsigned priceSize = 0;
   unsigned onHandSize = 0;

   /* tempAmount is used to calculate length of int
    * (dollarSize, centSize and onHandSize)
    */
   unsigned tempAmount = 0;

   unsigned tempSize = 0;

   unsigned printSize = 0;
   unsigned totalPrintSize = 0;
   int i;

   Node *current;

   current = system->itemList->head;

   /*
    * calculate size need for each section dynamically
    */

   /* calculate max id size */
   for (i = 0; i < system->itemList->size; i++) {
      tempSize = (unsigned) strlen(current->data->id);
      if (idSize < tempSize) {
         idSize = tempSize;
      }
      current = current->next;
   }

   current = system->itemList->head;
   for (i = 0; i < system->itemList->size; i++) {
      tempSize = (unsigned) strlen(current->data->name);
      if (nameSize < tempSize) {
         nameSize = tempSize;
      }
      current = current->next;
   }

   current = system->itemList->head;
   for (i = 0; i < system->itemList->size; i++) {
      tempAmount = current->data->price.dollars * 100
                   + current->data->price.cents;
      tempSize = getNumberLength((tempAmount));
      if (priceSize < tempSize) {
         priceSize = tempSize;
      }
      current = current->next;
   }
   /* +2 for the dot and dollar sign */
   priceSize += 2;

   current = system->itemList->head;
   for (i = 0; i < system->itemList->size; i++) {
      tempAmount = current->data->onHand;
      tempSize = getNumberLength((tempAmount));
      if (onHandSize < tempSize) {
         onHandSize = tempSize;
      }
      current = current->next;
   }

   printf("%-5s | %-*s | Available | Price\n", "ID", nameSize, "Name");

   /* update each size to make print out vertically alignment */
   printSize = (unsigned) strlen("ID");
   if (idSize < printSize) {
      idSize = printSize;
   }

   printSize = (unsigned) strlen("Name");
   if (nameSize < printSize) {
      nameSize = printSize;
   }

   printSize = (unsigned) strlen("Available");
   if (onHandSize < printSize) {
      onHandSize = printSize;
   }

   printSize = (unsigned) strlen("Price");
   if (priceSize < printSize) {
      priceSize = printSize;
   }

   /* +9 for 4 vertical bars in the menu and spaces after and before | */
   totalPrintSize = idSize + nameSize + priceSize + onHandSize + 9;
   for (i = 0; i < totalPrintSize; i++) {
      printf("-");
   }
   printf("\n");

   current = system->itemList->head;
   while (current != NULL) {

      printf("%-5s | %-*s | %-*d | $%d.%02d\n", current->data->id, nameSize,
             current->data->name, onHandSize, current->data->onHand,
             current->data->price.dollars, current->data->price.cents);

      current = current->next;

   }

   for (i = 0; i < totalPrintSize; i++) {
      printf("-");
   }
   printf("\n");

}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem *system) {
   Boolean itemPurchase;
   Boolean itemFound = FALSE;
   Boolean available = TRUE;
   char itemIDInput[ID_LEN + EXTRA_SPACES];
   Node *currentItem;

   printf("Purchase Item\n");
   printf("----------------\n");

   while (!itemFound) {
      /* reset the currentItem point to first item in the list */
      currentItem = system->itemList->head;

      printf("Please enter the ID of the item you want to purchase: ");
      fgets(itemIDInput, sizeof(itemIDInput), stdin);

      /* if user hit enter only, bring user back to main menu */
      if (strcmp(itemIDInput, "\n\0") == 0) {
         printf(COLOR_YELLOW "Returning to Main Menu...\n" COLOR_RESET);
         return;
      }

      if (itemIDInput[strlen(itemIDInput) - 1] != '\n') {
         printf(COLOR_RED "Invalid input, try again\n" COLOR_RESET);
         readRestOfLine();
      } else {
         itemIDInput[strlen(itemIDInput) - 1] = '\0';
         while (currentItem != NULL) {
            if (strcmp(itemIDInput, currentItem->data->id) == 0) {
               printf("Item Found\n");

               if (currentItem->data->onHand == 0) {
                  printf(COLOR_RED "Sorry no more %s\n"
                               COLOR_RESET, currentItem->data->name);
                  available = FALSE;
                  break;
               }

               printf("You have selected \"%s\t%s\". This wil be cost you $%d.%02d.\n",
                      currentItem->data->name, currentItem->data->desc,
                      currentItem->data->price.dollars, currentItem->data->price.cents);
               printf("Please hand over the money - "
                            "type in the value of each note/coin in cents.\n");

               printf("If you don't want purchase, please hit enter to cancel\n");
               itemPurchase = makePayment(currentItem);

               if (itemPurchase) {
                  currentItem->data->onHand--;
               }

               itemFound = TRUE;
               break;
            }

            currentItem = currentItem->next;
         }

         if (!available) {
            continue;
         } else if (!itemFound) {
            printf(COLOR_RED "Item Not Found!\n" COLOR_RESET);
         }
      }
   }
}

Boolean makePayment(Node *node) {
   char priceInput[MAX_PRICE_LENGTH + EXTRA_SPACES];
   unsigned price = 0;
   unsigned dollars = 0;
   unsigned cents = 0;
   Boolean priceValid = FALSE;
   Boolean enoughAmount = FALSE;

   while (!priceValid) {
      printf("You need to give us $%d.%02d: ",
             node->data->price.dollars, node->data->price.cents);
      fgets(priceInput, sizeof(priceInput), stdin);

      if (strcmp("\n\0", priceInput) == 0) {
         printf(COLOR_YELLOW "Returning to menu...\n" COLOR_RESET);
         return FALSE;
      }

      if (priceInput[strlen(priceInput) - 1] != '\n') {
         printf(COLOR_RED "Invalid, try again\n" COLOR_RESET);
         readRestOfLine();
         continue;
      } else {
         priceInput[strlen(priceInput) - 1] = '\0';
         price = (unsigned) strtol(priceInput, NULL, 10);

         dollars = price / 100;
         cents = price % 100;

         if (!checkIncomeValidation(priceInput)) {
            printf("Error: $%d.%02d is not a valid denomination of money\n", dollars, cents);
            continue;
         } else {
            priceValid = TRUE;
         }
      }

      enoughAmount = checkAmount(node, dollars, cents);
      if (!enoughAmount) {
         printf(COLOR_YELLOW "Returning to Main Menu...\n" COLOR_RESET);
         return enoughAmount;
      }
   }

   return enoughAmount;

}

/* function to check correct denomination of coins input */
Boolean checkIncomeValidation(char priceInString[]) {
   unsigned price = 0;

   price = (unsigned) strtol(priceInString, NULL, 10);
   /* hard coded valid denomination */
   if (price == 5 || price == 10 || price == 20 || price == 50 ||
       price == 100 || price == 200 || price == 500 || price == 1000) {
      return TRUE;
   } else {
      return FALSE;
   }
}

Boolean checkAmount(Node *itemToPurchase, unsigned dollars, unsigned cents) {
   Boolean reachAmount = FALSE;

   /* amount of money user input */
   unsigned price = dollars * 100 + cents;

   /* use int, for centAmountDue might become negative */
   int dollarAmountDue = itemToPurchase->data->price.dollars;
   int centAmountDue = itemToPurchase->data->price.cents;

   unsigned change = 0;
   unsigned dollarChange = 0;
   unsigned centChange = 0;

   char priceInput[MAX_PRICE_LENGTH + EXTRA_SPACES];

   /* check if user enter enough money to purchase item */
   while (!reachAmount) {
      if (dollars > dollarAmountDue) {
         reachAmount = TRUE;
      } else {
         dollarAmountDue = dollarAmountDue - dollars;
         centAmountDue = centAmountDue - cents;

         if (centAmountDue <= 0 && dollarAmountDue <= 0) {
            /* set price to 0 as centAmountDue is negative
             * change is calculated by using
             * user input minus amount of money due
             * i.e. price - (dollarAmountDue * 100 + centAmountDue)
             * set price to 0 as price minus a negative number will
             * become positive */
            price = 0;
            break;
         }

         /* when centAmountDue less than 0
          * re-calculate the dollarAmountDue and centAmountDue
          */
         if (centAmountDue < 0) {
            centAmountDue = centAmountDue + 100;
            dollarAmountDue--;
         }

         printf("You still need to give us $%d.%02d: ",
                dollarAmountDue, centAmountDue);
         fgets(priceInput, sizeof(priceInput), stdin);

         if (strcmp(priceInput, "\n\0") == 0) {
            return FALSE;
         }

         if (priceInput[strlen(priceInput) - 1] != '\n') {
            printf(COLOR_RED "Invalid, try again\n" COLOR_RESET);
            readRestOfLine();
         } else {
            priceInput[strlen(priceInput) - 1] = '\0';
            price = (unsigned) strtol(priceInput, NULL, 10);
            dollars = price / 100;
            cents = price % 100;

            if (!checkIncomeValidation(priceInput)) {
               printf("Error: $%d.%02d is not a valid denomination of money\n", dollars, cents);

               /* avoid decrease of dollarAmountDue if some invalid amount is input */
               dollarAmountDue = dollarAmountDue + dollars;
               centAmountDue = centAmountDue + cents;
               continue;
            }

            if (dollars > dollarAmountDue) {
               reachAmount = TRUE;
            }

         }
      }

   }

   /* calculate change amount */
   change = price - (dollarAmountDue * 100 + centAmountDue);
   dollarChange = change / 100;
   centChange = change % 100;

   printf(COLOR_GREEN "Thank you, here is your %s, and your change of $%d.%02d.\n",
          itemToPurchase->data->name, dollarChange, centChange);
   printf("Please come back soon.\n" COLOR_RESET);

   return reachAmount;
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem *system) {
   saveStock(system);
   saveCoins(system);
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem *system) {
   Stock *newItem = malloc(sizeof(Stock));
   Node *newNode = malloc(sizeof(Node));
   char nextName[NAME_LEN + EXTRA_SPACES];
   char nextDesc[DESC_LEN + EXTRA_SPACES];
   char *priceSeparator = ".";

   /* +1 for the dot */
   char nextPrice[MAX_PRICE_LENGTH + EXTRA_SPACES + 1];
   unsigned nextDollar = 0;
   unsigned nextCent = 0;

   char nextID[ID_LEN + NULL_SPACE];
   generateID(system, nextID);

   printf("The new item will have the the Item id of %s.\n", nextID);
   while (TRUE) {
      printf("Enter the item name: ");
      fgets(nextName, sizeof(nextName), stdin);
      if (strcmp("\n\0", nextName) == 0) {
         printf(COLOR_YELLOW "Returning to Main Menu...\n" COLOR_RESET);
         /* free memory allocated when user discard to add item */
         free(newItem);
         free(newNode);
         return;
      }

      if (nextName[strlen(nextName) - 1] != '\n') {
         printf(COLOR_RED "Invalid, try again\n" COLOR_RESET);
         readRestOfLine();
      } else {
         nextName[strlen(nextName) - 1] = '\0';
         break;
      }
   }

   while (TRUE) {
      printf("Enter the item description: ");
      fgets(nextDesc, sizeof(nextDesc), stdin);
      if (strcmp("\n\0", nextDesc) == 0) {
         printf(COLOR_YELLOW "Returning to Main Menu...\n" COLOR_RESET);
         free(newItem);
         free(newNode);
         return;
      }

      if (nextDesc[strlen(nextDesc) - 1] != '\n') {
         printf(COLOR_RED "Invalid, try again\n" COLOR_RESET);
         readRestOfLine();
      } else {
         nextDesc[strlen(nextDesc) - 1] = '\0';
         break;
      }
   }

   while (TRUE) {
      printf("Please enter price for this item: ");
      fgets(nextPrice, sizeof(nextPrice), stdin);
      if (strcmp("\n\0", nextPrice) == 0) {
         printf(COLOR_YELLOW "Returning to Main Menu...\n" COLOR_RESET);
         free(newItem);
         free(newNode);
         return;
      }

      if (nextPrice[strlen(nextPrice) - 1] != '\n') {
         printf(COLOR_RED "Invalid, try again\n" COLOR_RESET);
         readRestOfLine();
      } else {
         nextPrice[strlen(nextPrice) - 1] = '\0';
         if (nextPrice[strlen(nextPrice) - 3] != *priceSeparator) {
            printf("Error, please enter a dot to separate dollar and cent\n");
            continue;
         }

         nextDollar = (unsigned) strtol(strtok(nextPrice, priceSeparator), NULL, 10);
         nextCent = (unsigned) strtol(strtok(NULL, priceSeparator), NULL, 10);

         if (nextCent % 5 != 0) {
            printf("Invalid cents!\n");
         } else {
            break;
         }
      }
   }

   strcpy(newItem->id, nextID);
   strcpy(newItem->name, nextName);
   strcpy(newItem->desc, nextDesc);
   newItem->price.dollars = nextDollar;
   newItem->price.cents = nextCent;
   newItem->onHand = DEFAULT_STOCK_LEVEL;

   printf(COLOR_GREEN "This item \"%s - %s.\" has now been added to the menu\n"
         COLOR_RESET, newItem->name, newItem->desc);

   createNode(newItem, newNode);
   addToList(system->itemList, newNode);
   sortList(system);
}

/* function to generate ID for next item */
char *generateID(VmSystem *system, char nextID[]) {
   /* length of I and zeros */
   int nonValLen = 1;

   /* calculate the what should the ID for
    * the next item be
    */
   int largestIDVal = system->itemList->size;
   int nextIDVal = largestIDVal + 1;
   char nextIDValInString[4 + NULL_SPACE];

   int i = 0;

   /* update how many 0 are needed */
   if (nextIDVal >= 10 && nextIDVal < 100) {
      nonValLen = 3;
   } else if (nextIDVal >= 100 && nextIDVal < 1000) {
      nonValLen = 2;
   } else if (nextIDVal > 1000) {
      nonValLen = 1;
   } else {
      nonValLen = 4;
   }

   strcpy(&nextID[0], "I");
   nonValLen--;

   for (i = 0; i < nonValLen; i++) {
      strcat(nextID, "0");
   }

   /* convert int to string */
   sprintf(nextIDValInString, "%d", nextIDVal);

   /* appending to string */
   strcat(nextID, nextIDValInString);

   return nextID;
}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem *system) {
   Node *itemToDel = NULL;
   Node *currentItem = NULL;
   char idInput[ID_LEN + EXTRA_SPACES];
   Boolean itemFound = FALSE;

   while (!itemFound) {
      currentItem = system->itemList->head;
      printf("Enter the item id of the item to remove from the menu: ");
      fgets(idInput, sizeof(idInput), stdin);
      if (strcmp(idInput, "\n\0") == 0) {
         printf(COLOR_YELLOW "Returning to main menu...\n" COLOR_RESET);
         return;
      }

      if (idInput[strlen(idInput) - 1] != '\n') {
         printf(COLOR_RED "Invalid, try again!\n" COLOR_RESET);
         readRestOfLine();
      } else {
         idInput[strlen(idInput) - 1] = '\0';

         while (currentItem != NULL) {
            if (strcmp(currentItem->data->id, idInput) == 0) {
               itemToDel = currentItem;
               itemFound = TRUE;
               break;
            }

            currentItem = currentItem->next;
         }

         if (!itemFound) {
            printf(COLOR_RED "No such item found!\n" COLOR_RESET);
         }
      }
   }

   currentItem = system->itemList->head;
   while (currentItem != NULL) {

      /* if the first item in the list need to be removed */
      if (itemToDel == currentItem) {
         system->itemList->head = currentItem->next;
         break;
      }
      /* if the last item need to be removed */
      else if (currentItem->next == itemToDel) {
         if (itemToDel->next == NULL) {
            currentItem->next = NULL;
         } else {
            currentItem->next = itemToDel->next;
         }
         break;
      }
      currentItem = currentItem->next;
   }

   printf(COLOR_GREEN "\"%s - %s %s\" has now been removed from the system.\n"
         COLOR_RESET, itemToDel->data->id, itemToDel->data->name,
          itemToDel->data->desc);

   free(itemToDel->data);
   free(itemToDel);
   system->itemList->size--;
   reassignID(system);
   sortList(system);
}

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem *system) {
   int i = 0;
   int actualValue = 0;
   int printSize = 0;

   printf("Denomination | Count\n");

   for (i = 7; i >= 0; i--) {
      actualValue = denomToValue(system->cashRegister[i].denom);
      if (actualValue >= 100) {
         actualValue /= 100;
         printf("%d dollars", actualValue);
         printSize = getNumberLength((unsigned) actualValue) + 8;
         /* print out space */
         while (printSize < strlen("Denomination")) {
            printf(" ");
            printSize++;
         }
      } else {
         printf("%d cents", actualValue);
         printSize = getNumberLength((unsigned) actualValue) + 6;
         while (printSize < strlen("Denomination")) {
            printf(" ");
            printSize++;
         }
      }
      printf(" | ");
      printf("%d\n", system->cashRegister[i].count);
   }

}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem *system) {
   Node *currentItem = system->itemList->head;

   printf("Resetting stock count...\n");
   while (currentItem != NULL) {
      currentItem->data->onHand = DEFAULT_STOCK_LEVEL;

      currentItem = currentItem->next;
   }
}

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem *system) {}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem *system) {
   printf("Aborting...\n");
   systemFree(system);
   exit(0);
}
