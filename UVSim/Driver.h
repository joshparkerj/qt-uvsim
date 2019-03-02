#pragma once

#include "ALU.h"
#include <bitset>

class Driver
{
public:
	Driver();
	std::bitset<32> singleOne;
	ALU* logicUnit = new ALU();
	int Add(int accumulator, int operand);
	int Subtract(int accumulator, int operand);
	int Multiply(int accumulator, int operand);
	int Divide(int accumulator, int operand);
};
