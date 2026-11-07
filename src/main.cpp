#include <iostream>
#include "Machine.h"
#include "MainMenu.h"

int main() {
    Machine myMachine;

    MainMenu menu(myMachine);

    menu.run();

    return 0;
}
