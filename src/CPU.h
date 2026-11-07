#pragma once
#include <iostream>
#include "Memory.h"
#include "RegisterBank.h"
#include "Screen.h"
#include "ALU.h"


using namespace std;
class CPU
{
private:
	int PC;
	string IR;
	bool Halted;
	RegisterBank& registers;
	Memory& memory;
	Screen& screen;
	ALU& alu;
	
public :
	CPU(RegisterBank& registers,Memory &memory,Screen &screen,ALU&alu);
	void reset(int startAddress);
	bool isHalted();
	void step();
};

