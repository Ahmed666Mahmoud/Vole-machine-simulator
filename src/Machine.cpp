#include "Machine.h"

#include <iostream>
using namespace std;

Machine::Machine():cpu(registers,memory,screen,alu){}
void Machine::displayState(){
memory.display();
registers.display();
screen.display();

}
bool Machine::loadProgram(string filePath,int address){
    ProgramLoader program;
    return  program.loadFile(filePath,address,memory);

}
void Machine::step(){
    cpu.step();
    displayState();
}
void Machine::run(){
    while(!cpu.isHalted()){
        step();
    }
}

void Machine::setMemoryCell(int address, int value){
    memory.setCell(address, value);
}

void Machine::setRegisterValue(int index, string value){
    registers.setRegister(index, value);
}
