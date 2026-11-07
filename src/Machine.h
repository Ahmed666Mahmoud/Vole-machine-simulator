#pragma once

#include "CPU.h"
#include "RegisterBank.h"
#include "Screen.h"
#include "Memory.h"
#include "ProgramLoader.h"
#include "ALU.h"
#include <iostream>
#include<string>
class Machine{
    private:
  
    RegisterBank registers;
    Screen screen;
    Memory memory;
    ALU alu;
      CPU cpu;
    public:
    Machine();
    void displayState();
    bool loadProgram(std::string filePath,int address);
        
 
    void step();
       
  
    void run();
       

};
