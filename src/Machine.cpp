#include "Machine.h"

#include <iostream>
using namespace std;

    Machine::Machine():cpu(memory,registers,alu,screen){}
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
        while(!cpu.halted()){
            step();
        }
    }
