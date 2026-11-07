#include "CPU.h"
#include "RegisterBank.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdint>
using namespace std;

CPU::CPU(RegisterBank& registers, Memory& memory, Screen& screen, ALU& alu)
	: PC(0), IR(""), Halted(false),
	registers(registers), memory(memory),
	screen(screen), alu(alu)
{
}
void CPU::reset(int startAddress)
{
	PC = startAddress;
	IR = "";
	Halted = false;
}

bool CPU::isHalted()
{
	return Halted ;
}

void CPU::step()
{
	
	if (Halted) {
		return;
	}

	
	if (PC < 0 || PC > 254) {
		Halted = true;
		return;
	}

	int firstByte = memory.getCell(PC);
	int secondByte = memory.getCell(PC + 1);

	stringstream ss;
	ss << hex << uppercase << setfill('0')
		<< setw(2) << firstByte
		<< setw(2) << secondByte;

	IR = ss.str();

	char opcode = IR[0];
	int regNum = stoi(string(1, IR[1]), nullptr, 16);
	string value = IR.substr(2, 2);

	PC += 2;

	if (opcode == '2')
	{
		registers.setRegister(regNum, value);
	}
	else if (opcode == '1') {
		int address = stoi(value, nullptr, 16);
		int memoryValue = memory.getCell(address);

		stringstream temp;
		temp << hex << uppercase << setfill('0')
			<< setw(2) << memoryValue;

		registers.setRegister(regNum, temp.str());
	}
	else if (opcode == '3') {
		int address = stoi(value, nullptr, 16);

		string regValue = registers.getRegister(regNum);
		int byteValue = stoi(regValue, nullptr, 16);

		if (address == 255) {
			screen.write(static_cast<uint8_t>(byteValue));
		}
		else {
			memory.setCell(address, byteValue);
		}
	}
	else if (opcode == '4') {
		int sourceReg = stoi(string(1, IR[2]), nullptr, 16);
		int destinationReg = stoi(string(1, IR[3]), nullptr, 16);

		string valueToMove = registers.getRegister(sourceReg);
		registers.setRegister(destinationReg, valueToMove);
	}
	else if (opcode == '5') {
		int regS = stoi(string(1, IR[2]), nullptr, 16);
		int regT = stoi(string(1, IR[3]), nullptr, 16);

		uint8_t valueS = stoi(registers.getRegister(regS), nullptr, 16);
		uint8_t valueT = stoi(registers.getRegister(regT), nullptr, 16);

		uint8_t result = alu.addTwoComplement(valueS, valueT);

		stringstream temp;
		temp << hex << uppercase << setfill('0')
			<< setw(2) << (int)result;

		registers.setRegister(regNum, temp.str());
	}
	else if (opcode == '6') {
		int regS = stoi(string(1, IR[2]), nullptr, 16);
		int regT = stoi(string(1, IR[3]), nullptr, 16);

		uint8_t valueS = stoi(registers.getRegister(regS), nullptr, 16);
		uint8_t valueT = stoi(registers.getRegister(regT), nullptr, 16);

		uint8_t result = alu.addFloatingPoint(valueS, valueT);

		stringstream temp;
		temp << hex << uppercase << setfill('0')
			<< setw(2) << (int)result;

		registers.setRegister(regNum, temp.str());
	}
	else if (opcode == '7') {
		int regS = stoi(string(1, IR[2]), nullptr, 16);
		int regT = stoi(string(1, IR[3]), nullptr, 16);

		uint8_t valueS = stoi(registers.getRegister(regS), nullptr, 16);
		uint8_t valueT = stoi(registers.getRegister(regT), nullptr, 16);

		uint8_t result = alu.bitewiseOR(valueS, valueT);

		stringstream temp;
		temp << hex << uppercase << setfill('0')
			<< setw(2) << (int)result;

		registers.setRegister(regNum, temp.str());
	}
	else if (opcode == '8') {
		int regS = stoi(string(1, IR[2]), nullptr, 16);
		int regT = stoi(string(1, IR[3]), nullptr, 16);

		uint8_t valueS = stoi(registers.getRegister(regS), nullptr, 16);
		uint8_t valueT = stoi(registers.getRegister(regT), nullptr, 16);

		uint8_t result = alu.bitewiseAND(valueS, valueT);

		stringstream temp;
		temp << hex << uppercase << setfill('0')
			<< setw(2) << (int)result;

		registers.setRegister(regNum, temp.str());
	}
	else if (opcode == '9') {
		int regS = stoi(string(1, IR[2]), nullptr, 16);
		int regT = stoi(string(1, IR[3]), nullptr, 16);

		uint8_t valueS = stoi(registers.getRegister(regS), nullptr, 16);
		uint8_t valueT = stoi(registers.getRegister(regT), nullptr, 16);

		uint8_t result = alu.bitewiseXOR(valueS, valueT);

		stringstream temp;
		temp << hex << uppercase << setfill('0')
			<< setw(2) << (int)result;

		registers.setRegister(regNum, temp.str());
	}
	else if (opcode == 'A') {
		int steps = stoi(string(1, IR[3]), nullptr, 16);

		uint8_t value = stoi(registers.getRegister(regNum), nullptr, 16);

		uint8_t result = alu.rotateRight(value, steps);

		stringstream temp;
		temp << hex << uppercase << setfill('0')
			<< setw(2) << (int)result;

		registers.setRegister(regNum, temp.str());
		}
	else if (opcode == 'B') {
		string regValue = registers.getRegister(regNum);
		string zeroValue = registers.getRegister(0);

		if (regValue == zeroValue) {
			PC = stoi(value, nullptr, 16);
		}
		}
	else if (opcode == 'C') {
		Halted = true;
}
}
