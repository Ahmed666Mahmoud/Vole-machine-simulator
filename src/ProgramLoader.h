#pragma once
#include "Memory.h"
#include <iostream>
using namespace std;

class ProgramLoader
{
public:
    static bool loadFile(string filePath, int startAddress, Memory& memory);
};
