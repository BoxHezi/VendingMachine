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

   /* load stock file */
   FILE *stockFile;
   stockFile = fopen(fileName, "r");

   if (stockFile == NULL) {
      printf("No stock file found!\n");
      return FALSE;
   }

   system->stockFileName = fileName;

   /* while the file has next line */
   while (fgets(data, sizeof(data), stockFile) != NULL) {
      Node *node = malloc(sizeof(Node));
      Stock *stock = malloc(sizeof(Stock));
      assignValueToStock(data, stock);

      createNode(stock, node);
      addToList(system->itemList, node);
      sortList(system);
   }

   fclose(stockFile);
   return TRUE;
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem *system, const char *fileName) {


   FILE *coinsFile;
   coinsFile = fopen(fileName, "r");

   if (coinsFile == NULL) {
      printf("No coins file found");
      return FALSE;
   }

   system->coinFileName = fileName;

   fclose(coinsFile);
   return TRUE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem *system) {
   return FALSE;
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
   unsigned dollarSize = 0;
   unsigned centSize = 0;
   unsigned onHandSize = 0;

   /* tempAmount is used to calculate length of int
    * (dollarSize, centSize and onHandSize)
    */
   unsigned tempAmount = 0;

   unsigned tempSize = 0;

   unsigned printSize = 0;
   unsigned totalPrintSize = 0;
   int i, j;

   Node *current;

   /*sortList(system);*/

   current = system->itemList->head;

   /*
    * calculate size need for each section dynamically
    */

   /* calculate max id size */
   for (j = 0; j < system->itemList->size; j++) {
      tempSize = (unsigned) strlen(current->data->id);
      if (idSize < tempSize) {
         idSize = tempSize;
      }
      current = current->next;
   }

   current = system->itemList->head;
   for (j = 0; j < system->itemList->size; j++) {
      tempSize = (unsigned) strlen(current->data->name);
      if (nameSize < tempSize) {
         nameSize = tempSize;
      }
      current = current->next;
   }

   current = system->itemList->head;
   for (j = 0; j < system->itemList->size; j++) {
      tempSize = 0;
      tempAmount = current->data->price.dollars;
      while ((double) tempAmount / 10 > 0) {
         if ((double) tempAmount / 10 < 1) {
            tempSize++;
            break;
         }
         tempAmount /= 10;
         tempSize++;
      }
      if (dollarSize < tempSize) {
         dollarSize = tempSize;
      }
      current = current->next;
   }
   priceSize = dollarSize;

   current = system->itemList->head;
   for (j = 0; j < system->itemList->size; j++) {
      tempSize = 0;
      tempAmount = current->data->price.cents;
      while ((double) tempAmount / 10 > 0) {
         if ((double) tempAmount / 10 < 1) {
            tempSize++;
            break;
         }
         tempAmount /= 10;
         tempSize++;
      }
      if (centSize < tempSize) {
         centSize = tempSize;
      }
      current = current->next;
   }
   /* +2 for the dot and $ sign */
   priceSize += centSize + 2;

   current = system->itemList->head;
   for (j = 0; j < system->itemList->size; j++) {
      tempSize = 0;
      tempAmount = current->data->onHand;
      while ((double) tempAmount / 10 > 0) {
         if ((double) tempAmount / 10 < 1) {
            tempSize++;
            break;
         }
         tempAmount /= 10;
         tempSize++;
      }
      if (onHandSize < tempSize) {
         onHandSize = tempSize;
      }
      current = current->next;
   }

   printf("ID");
   printSize = (unsigned) strlen("ID");
   if (idSize < printSize) {
      idSize = printSize;
   }
   while (printSize < idSize) {
      printf(" ");
      printSize++;
   }
   printf(" | ");

   printf("Name");
   printSize = (unsigned) strlen("Name");
   if (nameSize < printSize) {
      nameSize = printSize;
   }
   while (printSize < nameSize) {
      printf(" ");
      printSize++;
   }
   printf(" | ");

   printf("Available");
   printSize = (unsigned) strlen("Available");
   if (onHandSize < printSize) {
      onHandSize = printSize;
   }
   while (printSize < onHandSize) {
      printf(" ");
      printSize++;
   }
   printf(" | ");

   printf("Price");
   printSize = (unsigned) strlen("Price");
   if (priceSize < printSize) {
      priceSize = printSize;
   }
   while (printSize < priceSize) {
      printf(" ");
      printSize++;
   }



   /* +9 for 4 vertical bars in the menu and spaces after and before | */
   totalPrintSize = idSize + nameSize + priceSize + onHandSize + 9;
   printf("\n");
   for (i = 0; i < totalPrintSize; i++) {
      printf("-");
   }
   printf("\n");


   current = system->itemList->head;
   while (current != NULL) {

      printf("%s", current->data->id);
      printSize = (unsigned) strlen(current->data->id);
      /* print vertical alignment */
      while (printSize < idSize) {
         printf(" ");
         printSize++;
      }
      printf(" | ");

      printf("%s", current->data->name);
      printSize = (unsigned) strlen(current->data->name);
      while (printSize < nameSize) {
         printf(" ");
         printSize++;
      }
      printf(" | ");

      printf("%d", current->data->onHand);
      printSize = 0;
      tempAmount = current->data->onHand;
      while ((double) tempAmount / 10 > 0) {
         if ((double) tempAmount / 10 < 1) {
            printSize++;
            break;
         }
         tempAmount /= 10;
         printSize++;
      }

      /* while available become 0
       * make sure the size is 1 instead of 0 */
      if (tempAmount == 0) {
         printSize = 1;
      }

      while (printSize < onHandSize) {
         printf(" ");
         printSize++;
      }
      printf(" | ");

      printf("$%d.%02d", current->data->price.dollars, current->data->price.cents);
      printSize = 0;
      tempAmount = current->data->price.dollars;
      while ((double) tempAmount / 10 > 0) {
         if ((double) tempAmount / 10 < 1) {
            printSize++;
            break;
         }
         tempAmount /= 10;
         printSize++;
      }
      priceSize = printSize;
      tempAmount = current->data->price.cents;
      while ((double) tempAmount / 10 > 0) {
         if ((double) tempAmount / 10 < 1) {
            printSize++;
            break;
         }
         tempAmount /= 10;
         printSize++;
      }
      centSize = printSize;
      printSize = priceSize + centSize + 2;
      while (printSize < priceSize) {
         printf(" ");
         printSize++;
      }
      printf("\n");


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
         printf("Returning to Main Menu...\n");
         return;
      }

      if (itemIDInput[strlen(itemIDInput) - 1] != '\n') {
         printf("Invalid input, try again\n");
         readRestOfLine();
      } else {
         itemIDInput[strlen(itemIDInput) - 1] = '\0';
         while (currentItem != NULL) {
            if (strcmp(itemIDInput, currentItem->data->id) == 0) {
               printf("Item Found\n");

               if (currentItem->data->onHand == 0) {
                  printf("Sorry no more %s\n", currentItem->data->name);
               }

               printf("You have selected \"%s\t%s\". This wil be cost you $%d.%02d.\n", currentItem->data->name,
                      currentItem->data->desc, currentItem->data->price.dollars, currentItem->data->price.cents);
               printf("Please hand over the money - type in the value of each note/coin in cents.\n");

               printf("If you don't want purchase, please hit enter to cancel\n");
               itemPurchase = makePayment(system, currentItem);

               if (itemPurchase) {
                  currentItem->data->onHand--;
               }

               itemFound = TRUE;
               break;
            }

            currentItem = currentItem->next;
         }
         if (!itemFound) {
            printf("Item Not Found\n");
         } else {
            break;
         }
      }
   }
}

Boolean makePayment(VmSystem *system, Node *node) {
   char priceInput[MAX_PRICE_LENGTH + EXTRA_SPACES];
   unsigned price = 0;
   unsigned dollars = 0;
   unsigned cents = 0;
   Boolean priceValid = FALSE;
   Boolean enoughAmount = FALSE;

   while (!priceValid) {
      printf("You need to give us $%d.%02d: ", node->data->price.dollars, node->data->price.cents);
      fgets(priceInput, sizeof(priceInput), stdin);

      if (strcmp("\n\0", priceInput) == 0) {
         printf("Returning to menu...\n");
         return FALSE;
      }

      if (priceInput[strlen(priceInput) - 1] != '\n') {
         printf("Invalid, try again\n");
         readRestOfLine();
         continue;
      } else {
         priceInput[strlen(priceInput) - 1] = '\0';
         price = (unsigned) strtol(priceInput, NULL, 10);

         dollars = price / 100;
         cents = price % 100;

         if (!checkIncomeValidation(system, priceInput)) {
            printf("Error: $%d.%02d is not a valid denomination of money\n", dollars, cents);
            continue;
         } else {
            priceValid = TRUE;
         }
      }

      enoughAmount = checkAmount(system, node, dollars, cents);
      if (!enoughAmount) {
         printf("Returning to Main Menu...\n");
         return enoughAmount;
      }
   }

   return enoughAmount;

}

/* function to check correct denomination of coins input */
Boolean checkIncomeValidation(VmSystem *system, char *priceInString) {
   Boolean validIncome = FALSE;
   unsigned price = 0;
   int i;

   price = (unsigned) strtol(priceInString, NULL, 10);
   switch (price) {
      case 5:
         price = FIVE_CENTS;
         break;
      case 10:
         price = TEN_CENTS;
         break;
      case 20:
         price = TWENTY_CENTS;
         break;
      case 50:
         price = FIFTY_CENTS;
         break;
      case 100:
         price = ONE_DOLLAR;
         break;
      case 200:
         price = TWO_DOLLARS;
         break;
      case 500:
         price = FIVE_DOLLARS;
         break;
      case 1000:
         price = TEN_DOLLARS;
         break;
      default:
         validIncome = FALSE;
         break;
   }

   for (i = 0; i < NUM_DENOMS; i++) {
      if (price == system->cashRegister[i].denom) {
         validIncome = TRUE;
         break;
      }
   }

   return validIncome;
}

Boolean checkAmount(VmSystem *system, Node *itemToPurchase, unsigned dollars, unsigned cents) {
   Boolean reachAmount = FALSE;
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

         if (centAmountDue == 0 && dollarAmountDue == 0) {
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

         printf("You still need to give us $%d.%02d: ", dollarAmountDue, centAmountDue);
         fgets(priceInput, sizeof(priceInput), stdin);

         if (strcmp(priceInput, "\n\0") == 0) {
            return FALSE;
         }

         if (priceInput[strlen(priceInput) - 1] != '\n') {
            printf("Invalid, try again\n");
            readRestOfLine();
         } else {
            priceInput[strlen(priceInput) - 1] = '\0';
            price = (unsigned) strtol(priceInput, NULL, 10);
            dollars = price / 100;
            cents = price % 100;

            if (!checkIncomeValidation(system, priceInput)) {
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

   change = price - (dollarAmountDue * 100 + centAmountDue);
   dollarChange = change / 100;
   centChange = change % 100;

   printf("Thank you, here is your %s, and your change of $%d.%02d.\n",
          itemToPurchase->data->name,
          dollarChange, centChange);
   printf("Please come back soon.\n");

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

   exit(EXIT_SUCCESS);
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem *system) {
   generateID(system);
}

void generateID(VmSystem *system) {
   Node *idCheck = system->itemList->head;

   char *largestID = NULL;
   char val;
   int tempVal;
   int nonValLen = 1;

   int largestIDVal;
   char nextID[ID_LEN];
   int nextIDVal = 0;
   char nextIDValInString;

   int i = 0;

   while (idCheck->next != NULL) {
      if (idCheck->data->id > idCheck->next->data->id) {
         largestID = idCheck->data->id;
      }
      idCheck = idCheck->next;
   }

   for (i = 1; i < strlen(largestID); i++) {
      printf("%c\n", largestID[i]);
      val = largestID[i];
      tempVal = (int) strtol(&val, NULL, 10);
      printf("Val: %c\n", val);
      if (tempVal != 0) {
         break;
      }
      nonValLen++;
   }

   printf("%d\n", nonValLen);

   largestID += nonValLen;
   largestIDVal = (int) strtol(largestID, NULL, 10);
   printf("%d\n", largestIDVal);

   nextIDVal = largestIDVal + 1;
   printf("%d\n", nextIDVal);

   if (nextIDVal == 10) {
      nonValLen--;
   } else if (nextIDVal == 100) {
      nonValLen -= 2;
   } else if (nextIDVal == 1000) {
      nonValLen -= 3;
   }

   strcpy(&nextID[0], "I");
   for (i = 1; i < nonValLen; i++) {
      strcpy(&nextID[i], "0");
   }

   /* while (idCheck->next != NULL) {
      if (idCheck->data->id > idCheck->next->data->id) {
         nextID = idCheck->data->id;
      }
      idCheck = idCheck->next;
   } */
}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem *system) {}

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem *system) {}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem *system) {}

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
