#include "ProgramLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;

bool ProgramLoader::loadFile(string filePath, int startAddress, Memory& memory)
{
    // startAddress validation
    if (startAddress % 2 != 0 or startAddress < 0 or startAddress > 0xFF)
    {
        cout << "Start Address must be a number between 0 and FF \n";
        return false;
    }
    // opening the file
    ifstream file(filePath);
    if (!file.is_open())
    {
        cout << "Could not open file " << filePath << "\n";
        return false;
    }

    int currentAddress = startAddress;
    string line;

    while(getline(file, line))
    {
        long long firstChar = -1;
        firstChar = line.find_first_not_of(" \r\n\t");
        if (firstChar == -1 or line[firstChar] == ';')
        {
            continue;
        }

        string instruction = line.substr(firstChar, 4);
        if (instruction.size() != 4) continue;

        // check if the instruction if valid
        bool validhex = true;
        for (int i = 0; i < 4; i++)
        {
            if (!isxdigit(instruction[i])) validhex = false;
        }
        if (!validhex) continue;

        // split the instruction and put it in memory
        string firstHalf = instruction.substr(0,2), secondHalf = instruction.substr(2,2);
        int firstByte = stoi(firstHalf, nullptr, 16), secondByte = stoi(secondHalf, nullptr, 16);
        memory.setCell(currentAddress, firstByte);
        memory.setCell(currentAddress + 1, secondByte);

        currentAddress += 2;

        if (currentAddress >= 256)
        {
            cout << "Memory limit exceeded\n";
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}
