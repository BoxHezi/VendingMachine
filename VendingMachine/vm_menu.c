#include "vm_menu.h"

#define STOCK_DATA "stock.dat"
#define COIN_DATA "coins.dat"

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
    VmSystem vendingMachine;

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
                displayItems(&vendingMachine);
                return menu[option - 1].function;
            } else if (option == 2) {

            } else if (option == 3) {

            } else if (option == 4) {

            } else if (option == 5) {

            } else if (option == 6) {

            } else if (option == 7) {

            } else if (option == 8) {

            } else if (option == 9) {
                printf("Aborting...\n");

                exit(1);
            } else {
                printf("Invalid, try again\n");
            }
        }

    }
    return NULL;
}