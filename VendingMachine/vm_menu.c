#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/
void initMenu(MenuItem *menu) {
    /* initialize menu function */
    menu[0].function = displayItems;
    menu[1].function = purchaseItem;
    menu[2].function = saveAndExit;
    menu[3].function = addItem;
    menu[4].function = removeItem;
    menu[5].function = displayCoins;
    menu[6].function = resetStock;
    menu[7].function = resetCoins;
    menu[8].function = abortProgram;


    strcpy(menu[0].text, "Display Items");
    strcpy(menu[1].text, "Purchase Items");
    strcpy(menu[2].text, "Save and Exit");
    strcpy(menu[3].text, "Add Item");
    strcpy(menu[4].text, "Remove Item");
    strcpy(menu[5].text, "Display Coins");
    strcpy(menu[6].text, "Reset Stocks");
    strcpy(menu[7].text, "Reset Coins");
    strcpy(menu[8].text, "Abort Program");
}

void printMenu(MenuItem *menu) {
    int i;
    int count = 0;

    for (i = 0; i < 9; i++) {
        if (count == 0 && i == 0) {
            puts("Main Menu:");
            count++;
            i--;
        } else if (count == 1 && i == 3) {
            puts("Administrator-Only Menu:");
            count++;
            i--;
        } else {
            printf("\t%d. %s\n", i + 1, menu[i].text);
        }
    }
}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem *menu) {
    char optionInput[1 + EXTRA_SPACES];
    int option = 0;

    while (TRUE) {
        printMenu(menu);
        printf("Select your option(1-9): ");
        fgets(optionInput, sizeof(optionInput), stdin);

        /* check buffer overflow */
        if (optionInput[strlen(optionInput) - 1] != '\n') {
            printf("Invalid, try again\n");
            readRestOfLine();
        } else {
            /* convert user input to int */
            option = (int) strtol(optionInput, NULL, 10);

            if (option == 1) {
                return menu[option - 1].function;
            } else if (option == 2) {
                return menu[option - 1].function;
            } else if (option == 3) {
                return menu[option - 1].function;
            } else if (option == 4) {
                return menu[option - 1].function;
            } else if (option == 5) {
                return menu[option - 1].function;
            } else if (option == 6) {
                return menu[option - 1].function;
            } else if (option == 7) {
                return menu[option - 1].function;
            } else if (option == 8) {
                return menu[option - 1].function;
            } else if (option == 9) {
                return menu[option - 1].function;
            } else {
                printf("Invalid, try again\n");
            }
        }

    }
    return NULL;
}