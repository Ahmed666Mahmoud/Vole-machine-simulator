#include "ProgramLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
using namespace std;

bool ProgramLoader::loadFile(string filePath, int startAddress, Memory& memory)
{
    // startAddress validation
    if (startAddress % 2 != 0 || startAddress < 0 || startAddress > 0xFE)
    {
        cout << "Start Address must be an even number between 0 and FE \n";
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
    int instructionsLoaded = 0;

    while (getline(file, line))
    {
        // Strip comments: ';' or '#' or '//'
        size_t commentPos = line.find(';');
        size_t hashPos = line.find('#');
        size_t slashPos = line.find("//");
        if (hashPos < commentPos) commentPos = hashPos;
        if (slashPos < commentPos) commentPos = slashPos;
        if (commentPos != string::npos) {
            line = line.substr(0, commentPos);
        }

        // Collect all hex characters from the line (filtering out whitespace and '0x')
        string hexChars = "";
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == '0' && i + 1 < line.length() && (line[i+1] == 'x' || line[i+1] == 'X')) {
                i++; // skip '0x'
                continue;
            }
            if (isxdigit(static_cast<unsigned char>(line[i]))) {
                hexChars += line[i];
            }
        }

        // Process hex characters in groups of 4 (1 instruction = 2 bytes = 4 hex digits)
        for (size_t i = 0; i + 3 < hexChars.length(); i += 4) {
            if (currentAddress >= 256) {
                cout << "Memory limit exceeded\n";
                file.close();
                return false;
            }

            string firstHalf = hexChars.substr(i, 2);
            string secondHalf = hexChars.substr(i + 2, 2);

            int firstByte = stoi(firstHalf, nullptr, 16);
            int secondByte = stoi(secondHalf, nullptr, 16);

            memory.setCell(currentAddress, firstByte);
            memory.setCell(currentAddress + 1, secondByte);

            currentAddress += 2;
            instructionsLoaded++;
        }
    }

    file.close();
    return (instructionsLoaded > 0);
}
