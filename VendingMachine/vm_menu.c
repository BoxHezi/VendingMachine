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
    strcpy(menu[0].text, "\tDisplay Items");
    strcpy(menu[1].text, "\tPurchase Items");
    strcpy(menu[2].text, "\tSave and Exit");
    strcpy(menu[3].text, "\tAdd Item");
    strcpy(menu[4].text, "\tRemove Item");
    strcpy(menu[5].text, "\tDisplay Coins");
    strcpy(menu[6].text, "\tReset Stocks");
    strcpy(menu[7].text, "\tReset Coins");
    strcpy(menu[8].text, "\tAbort Program");

    getMenuChoice(menu);
    /*
    menu[0].text = "Display Items";
    menu[1].text = "Purchase Items";
    menu[2].text = "Save and Exit";
    menu[3].text = "Add Item";
    menu[4].text = "Remove Item";
    menu[5].text = "Display Coins";
    menu[6].text = "Reset Stock";
    menu[7].text = "Reset Coins";
    menu[8].text = "Abort Program";
    */

    /*
    printf("Main Menu:\n");
    printf("1.Display Items\n");
    printf("2.Purchase Items\n");
    printf("3.Save and Exit\n");
    printf("Administrator-Only Menu:\n");
    printf("4.Add Item\n");
    printf("5.Remove Item\n");
    printf("6.Display Coins\n");
    printf("7.Reset Stock\n");
    printf("8.Reset Coins\n");
    printf("9.Abort Program\n");
    printf("Select your option(1-9): ");
*/
}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem *menu) {
    char optionInput[1 + EXTRA_SPACES];
    int option = 0;
    Boolean validInput = FALSE;

    do {
        printMenu(menu);
        printf("Select your option(1-9): ");
        fgets(optionInput, sizeof(optionInput), stdin);

        /* check buffer overflow */
        if (optionInput[strlen(optionInput) - 1] != '\n') {
            printf("Invalid, try again\n");
            readRestOfLine();
        } else {
            /* convert user input to int */
            option = strtol(optionInput, NULL, 10);

            if (option == 1) {

            } else if (option == 2) {

            } else if (option == 3) {

            } else if (option == 4) {

            } else if (option == 5) {

            } else if (option == 6) {

            } else if (option == 7) {

            } else if (option == 8) {

            } else if (option == 9) {
                printf("Aborting...\n");
                validInput = TRUE;
            } else {
                printf("Invalid, try again\n");
            }
        }

    } while (!validInput);
    return NULL;
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
            printf("%d. %s\n", i + 1, menu[i].text);
        }
    }
}