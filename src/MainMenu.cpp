#include "MainMenu.h"
#include <iostream>
using namespace std;

MainMenu::MainMenu(Machine& m) : machine(m) {}

void MainMenu::displayMenu()
{
    cout << "\n\t Vole Machine Simulator\t\n";
    cout << "\t========================\t\n";
    cout << "1. Load program from file\n";
    cout << "2. Memory / Register operations (Overwrite or Clear)\n";
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
        int scndChoice = 0;
        cout << "\n--- Memory / Register Operations ---\n";
        cout << "1. Overwrite Memory Cell\n";
        cout << "2. Overwrite Register\n";
        cout << "3. Clear All Memory (set all cells to 00)\n";
        cout << "4. Clear All Registers (set all registers to 00)\n";
        cout << "5. Full Reset (Clear CPU, Memory, Registers, Screen)\n";
        cout << "Enter your choice (1 - 5): ";

        if (!(cin >> scndChoice))
        {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }

        if (scndChoice == 1)
        {
            int address, value;
            cout << "Enter memory address in hexadecimal: ";
            cin >> hex >> address >> dec;
            cout << "Enter the new hexadecimal value for the cell: ";
            cin >> hex >> value >> dec;

            machine.setMemoryCell(address, value);
            cout << "Memory cell updated.\n";
        }
        else if (scndChoice == 2)
        {
            int registerIndex;
            string value;
            cout << "Enter the register index (0 - 15): ";
            cin >> registerIndex;
            cout << "Enter the new hexadecimal value (2 digits): ";
            cin >> value;

            machine.setRegisterValue(registerIndex, value);
            cout << "Register updated.\n";
        }
        else if (scndChoice == 3)
        {
            machine.clearMemory();
            cout << "All memory cells cleared to 00.\n";
        }
        else if (scndChoice == 4)
        {
            machine.clearRegisters();
            cout << "All registers cleared to 00.\n";
        }
        else if (scndChoice == 5)
        {
            machine.fullReset(0);
            cout << "Full reset complete.\n";
        }
        else
        {
            cout << "Invalid Option!\n";
        }
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
