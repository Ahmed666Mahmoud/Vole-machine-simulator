#include "MainMenu.h"
#include <iostream>
using namespace std;

MainMenu::MainMenu(Machine& m) : machine(m) {}

void MainMenu::displayMenu()
{
    cout << "\t Vole Machine Simulator\t\n";
    cout << "\t ======================\t\n";
    cout << "1. Load program from file\n";
    cout << "2. Overwrite a memory cell or register\n";
    cout << "3. Run program all at once\n";
    cout << "4. Execute step by step\n";
    cout << "5. Display machine state\n";
    cout << "6. Exit\n";
    cout << "Enter your option (1 - 6): ";
}

void MainMenu::handleChoice(int choice)
{
    if (choice == 1)
    {
        string filepath;
        int startAddrss;
        cout << "Enter file path: ";
        cin >> filepath;
        cout << "Enter even start address in hexadecimal: ";
        cin >> hex >> startAddrss >> dec;

        if (machine.loadProgram(filepath, startAddrss))
        {
            cout << "Program loaded successfully\n";
        }
        else
        {
            cout << "Failed to load program\n";
        }
    }
    else if (choice == 2)
    {
        // waiting for machine class to be done so I can add setters in it to use
    }
    else if (choice == 3)
    {
        machine.run();
    }
    else if (choice == 4)
    {
        machine.step();
    }
    else if (choice == 5)
    {
        machine.displayState();
    }
    else if (choice == 6)
    {
        cout << "Exiting Simulator\n";
    }
    else
    {
        cout << "Invalid choice! Select a number between 1 and 6\n";
    }
}

void MainMenu::run()
{
    int choice = 0;
    do
    {
        displayMenu();

        if (!(cin >> choice))
        {
            cout << "Invalid input! Please enter a number\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        handleChoice(choice);

    } while (choice != 6);
}
