#include "vm_options.h"

#define MAX_DATA_LENGTH 512
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
    printf("Item ID|Item Name|Item Desc|Price|Number On Hand\n");
    printf("---------------------------------------------------\n");

    printStockList(system->itemList->head);

    /* <ID>|<NAME>|<DESCRIPTION>|<DOLLARS>.<CENTS>|<QUANTITY> */
}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem *system) {}

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
void addItem(VmSystem *system) {}

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