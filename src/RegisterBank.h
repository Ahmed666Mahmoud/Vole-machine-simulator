#pragma once
#include <iostream>
#include <string>
using namespace std;

class RegisterBank
{
private:
	string registers[16];
public:
	RegisterBank();
	string getRegister(int regNum) const;
	void setRegister(int regNum, string value);
	void display();
	void clear();
};
