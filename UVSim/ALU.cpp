//Authored By Derek Parsons

#include "ALU.h"

int ALU::And(int bitOne, int bitTwo)
{
	assert(bitOne == 1 || bitOne == 0);
	assert(bitTwo == 1 || bitTwo == 0);
	return (bitOne & bitTwo); //binary AND operation
}

int ALU::Or(int bitOne, int bitTwo)
{
	assert(bitOne == 1 || bitOne == 0);
	assert(bitTwo == 1 || bitTwo == 0);
	return (bitOne | bitTwo); //binary OR operation
}

int ALU::Xor(int bitOne, int bitTwo)
{
	assert(bitOne == 1 || bitOne == 0);
	assert(bitTwo == 1 || bitTwo == 0);
	return (bitOne ^ bitTwo); //binary XOR operation
}

std::bitset<32> ALU::FullAdder(std::bitset<32> a, std::bitset<32> b)
{
	std::bitset<32> answer(0);
	int carry = 0;
	int temp1;
	int temp2;
	int temp3;

	//Implement the full adder algorithm
	for (size_t i = 0; i < 32; i++)
	{
		temp1 = this->Xor(a[i], b[i]);
		answer[i] = this->Xor(temp1, carry);
		temp2 = this->And(temp1, carry);
		temp3 = this->And(a[i], b[i]);
		carry = this->Or(temp2, temp3);
	}
	if (carry) {
		//This is an overflow error, but from what I can tell, we aren't supposed to throw errors or anthing here --Derek
	}

	return answer;
}
