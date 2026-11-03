#include <iostream>
#include "Memory.h"
#include "ProgramLoader.h"

int main() {
    Memory mem;


    bool success = ProgramLoader::loadFile("program1.txt", 0x00, mem);

    if (success) {
        std::cout << "Program loaded successfully!\n";
        mem.display(); // Prints out the memory grid to verify values are placed correctly
    } else {
        std::cout << "Failed to load program.\n";
    }

    return 0;
}
