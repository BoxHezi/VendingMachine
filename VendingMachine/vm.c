#include "vm.h"

#define MENU_LENGTH 9

int main(int argc, char **argv) {
    VmSystem vendingSystem;
    MenuItem menu[MENU_LENGTH];

    systemInit(&vendingSystem);
    if (argc != 3) {
        printf("Missing Files!\n");
        return EXIT_FAILURE;
    }
    if (!loadData(&vendingSystem, argv[1], argv[2])) {
        printf("File load failed!\n");
        exit(1);
    }

    while (TRUE) {
        initMenu(menu);
        getMenuChoice(menu);
    }

    printf("Goodbye. \n\n");

    return EXIT_SUCCESS;
}
