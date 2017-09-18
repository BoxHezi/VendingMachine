#include "vm.h"

#define MENU_LENGTH 9

int main(int argc, char **argv) {
    VmSystem vendingSystem;
    MenuItem menu[MENU_LENGTH];

    systemInit(&system);
    if (argc != 3) {
        printf("Missing Files!\n");
        return EXIT_FAILURE;
    }
    if (!loadData(&vendingSystem, argv[1], NULL)) {
        printf("File load failed!\n");
        return EXIT_FAILURE;
    }

    initMenu(menu);

    printf("Goodbye. \n\n");

    return EXIT_SUCCESS;
}
