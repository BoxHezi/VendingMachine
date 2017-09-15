#include "vm.h"
#define MENU_LENGTH 9

int main(int argc, char ** argv)
{
    MenuItem menu[MENU_LENGTH];
    initMenu(menu);


    printf("Goodbye. \n\n");

    return EXIT_SUCCESS;
}
