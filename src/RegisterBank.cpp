#include "RegisterBank.h"

RegisterBank::RegisterBank() {
	clear();
}

string RegisterBank::getRegister(int regNum) const
{
	if (regNum < 0 || regNum >= 16) return "00";
	return registers[regNum];
}

void RegisterBank::setRegister(int regNum, string value)
{
	if (regNum >= 0 && regNum < 16) {
		registers[regNum] = value;
	}
}

void RegisterBank::display()
{
	for (int i = 0; i < 16; i++) {
		cout << "R" << i << " = " << registers[i] << " \n";
	}
}

void RegisterBank::clear()
{
	for (int i = 0; i < 16; i++) {
		registers[i] = "00";
	}
}
