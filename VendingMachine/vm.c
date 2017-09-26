#include "vm.h"

#define MENU_LENGTH 9

int main(int argc, char **argv) {
    VmSystem vendingSystem;
    MenuItem menu[MENU_LENGTH];
    MenuFunction choice;

    systemInit(&vendingSystem);
    if (argc != 3) {
        printf("Missing Files!\n");
        return EXIT_FAILURE;
    }
    if (!loadData(&vendingSystem, argv[1], argv[2])) {
        printf("File load failed!\n");
        exit(0);
    }
    if(!loadStock(&vendingSystem, argv[1])) {
        return EXIT_FAILURE;
    }
    loadCoins(&vendingSystem, argv[2]);

    initMenu(menu);
    while (TRUE) {
        printMenu(menu);
        choice = getMenuChoice(menu);

        if (choice == saveAndExit) {
            break;
        } else if (choice == NULL) {
            continue;
        }
        else {
            (*choice)(&vendingSystem);
        }
    }

    printf("Goodbye. \n\n");

    return EXIT_SUCCESS;
}
