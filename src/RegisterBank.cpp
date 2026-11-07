#include "RegisterBank.h"

RegisterBank::RegisterBank() {
	for (int i = 0; i < 16; i++) {
		registers[i] = "00";
	}
}

string RegisterBank::getRegister(int regNum)
{
	return registers[regNum];
}

void RegisterBank::setRegister(int regNum, string value)
{
	registers[regNum] = value;
}

void RegisterBank::display()
{
	for (int i = 0; i < 16; i++) {
		cout << "R" << i << " = " << registers[i] << " \n";
	}
	
}






