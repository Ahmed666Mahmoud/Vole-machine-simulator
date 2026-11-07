#pragma once
#include <iostream>
using namespace std;
#include <string >
class RegisterBank
{
private :
	string registers[16];
public:
	RegisterBank();
	string getRegister(int regNum);
	void setRegister(int regNum, string value);
	void display();
	

};

