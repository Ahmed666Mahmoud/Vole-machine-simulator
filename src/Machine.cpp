#include "Machine.h"
#include <iostream>
using namespace std;

Machine::Machine() : cpu(registers, memory, screen, alu) {}

void Machine::displayState() {
    memory.display();
    registers.display();
    screen.display();
}

bool Machine::loadProgram(string filePath, int address) {
    ProgramLoader program;
    bool success = program.loadFile(filePath, address, memory);
    if (success) {
        cpu.reset(address);
    }
    return success;
}

void Machine::step() {
    cpu.step();
    displayState();
}

void Machine::run() {
    while (!cpu.isHalted()) {
        step();
    }
}

void Machine::setMemoryCell(int address, int value) {
    memory.setCell(address, value);
}

void Machine::setRegisterValue(int index, string value) {
    registers.setRegister(index, value);
}

int Machine::getMemoryCell(int address) const {
    return memory.getCell(address);
}

string Machine::getRegisterValue(int index) const {
    return registers.getRegister(index);
}

string Machine::getScreenBuffer() const {
    return screen.getBuffer();
}

int Machine::getPC() const {
    return cpu.getPC();
}

string Machine::getIR() const {
    return cpu.getIR();
}

bool Machine::isHalted() const {
    return cpu.isHalted();
}

void Machine::reset(int startAddress) {
    cpu.reset(startAddress);
    screen.clear();
}

void Machine::clearScreen() {
    screen.clear();
}

void Machine::clearMemory() {
    memory.clear();
}

void Machine::clearRegisters() {
    registers.clear();
}

void Machine::fullReset(int startAddress) {
    cpu.reset(startAddress);
    screen.clear();
    memory.clear();
    registers.clear();
}
