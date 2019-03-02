#pragma once
#include <iostream>
#include <iomanip>
#include <cassert>
#include <bitset>

class ALU
{
public:
	int And(int bitOne, int bitTwo);
	int Or(int bitOne, int bitTwo);
	int Xor(int bitOne, int bitTwo);
	std::bitset<32> FullAdder(std::bitset<32> a, std::bitset<32> b);
};

