//Authored By Derek Parsons

#include "Driver.h"

Driver::Driver() {
	this->singleOne = std::bitset<32>(1);
}

//This function adds two numbers using a simulated ALU
int Driver::Add(int augend, int addend) //These are the technical names for the parts of an addition operation.
{
	//convert to binary
	std::bitset<32> a(augend);
	std::bitset<32> b(addend);

	//perform the addition
	std::bitset<32> answer = this->logicUnit->FullAdder(a, b);

	//convert back to int
	return (int)(answer.to_ulong());
}


//Subtracts the subtrahend from the minuend
int Driver::Subtract(int minuend, int subtrahend) //These are the technical names for the parts of a subtraction operation.
{
	//Make subtrahend into binary
	std::bitset<32> temp(subtrahend);
	//Make subtrahend negative using full adder.
	int negativeSubtrahend = (int)(this->logicUnit->FullAdder(temp.flip(), this->singleOne).to_ulong());
	//Use the Add function to finish
	return this->Add(minuend, negativeSubtrahend);
}


//Multplication
int Driver::Multiply(int multiplicand, int multiplier) //These are the technical names for the parts of a multiplcation operation.
{
	int a;
	int b;
	int product = 0;
	bool negative = false;

	//Accounting for negative numbers
	if (multiplicand < 0) {
		negative = !negative;
		multiplicand = this->Subtract(0, multiplicand);
	}
	if (multiplier < 0) {
		negative = !negative;
		multiplier = this->Subtract(0, multiplier);
	}

	//Make 'a' the smaller of the two. I think this will increase efficiency if the difference between the two numbers is large.
	if (multiplicand <= multiplier) {
		a = multiplicand;
		b = multiplier;
	}
	else {
		a = multiplier;
		b = multiplicand;
	}

	//Calculate using the ALU
	for (size_t i = 0; i < a; i++)
	{
		product = this->Add(product, b);
	}

	//Make the answer negative if needed
	if (negative) {
		product = this->Subtract(0, product);
	}

	return product;
}

//This performs integer division -- it does not provide a remainder. Dividend is divided by the divisor.
int Driver::Divide(int dividend, int divisor)
{
	int quotient = 0;
	bool negative = false;

	//Accounting for negative numbers
	if (dividend < 0) {
		negative = !negative;
		dividend = this->Subtract(0, dividend);
	}
	if (divisor < 0) {
		negative = !negative;
		divisor = this->Subtract(0, divisor);
	}

	//Calculate using ALU
	while (dividend >= divisor) {
		dividend = this->Subtract(dividend, divisor);
		quotient = this->Add(quotient, 1);
	}

	//Make the answer negative if needed
	if (negative) {
		quotient = this->Subtract(0, quotient);
	}

	return quotient;
}
