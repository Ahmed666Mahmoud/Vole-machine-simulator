#pragma once
#include "Machine.h"

class MainMenu
{
private:
    Machine& machine;
public:
    MainMenu(Machine& m);

    void displayMenu();

    void handleChoice(int choice);

    void run();
};
