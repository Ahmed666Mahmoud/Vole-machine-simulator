#pragma once

#include "CPU.h"
#include "RegisterBank.h"
#include "Screen.h"
#include "Memory.h"
#include "ProgramLoader.h"
#include "ALU.h"
#include <iostream>
#include <string>

class Machine {
private:
    RegisterBank registers;
    Screen screen;
    Memory memory;
    ALU alu;
    CPU cpu;

public:
    Machine();
    void displayState();
    bool loadProgram(std::string filePath, int address);

    void step();
    void run();

    void setMemoryCell(int address, int value);
    void setRegisterValue(int index, std::string value);

    int getMemoryCell(int address) const;
    std::string getRegisterValue(int index) const;
    std::string getScreenBuffer() const;
    int getPC() const;
    std::string getIR() const;
    bool isHalted() const;
    void reset(int startAddress = 0);
    void clearScreen();
    void clearMemory();
    void clearRegisters();
    void fullReset(int startAddress = 0);
};
