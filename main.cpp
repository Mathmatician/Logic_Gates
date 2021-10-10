/*---------------------------------------------------------------------------------------
	Author: Jerome Richards Jr.															
	Description: Functions designed to simulate logic gates.

	IMPORTANT: These logic gates only work if they have the same number of input bits.
			   Anything else could result in undefined behaviour.

---------------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int AND_GATE(int a, int b);
int OR_GATE(int a, int b);
int NAND_GATE(int a, int b);
int NOR_GATE(int a, int b);
int XOR_GATE(int a, int b);
int NOT_GATE(int val);

std::vector<int> HALF_ADDER(int a, int b);
std::vector<int> FULL_ADDER(int a, int b, int c);
std::vector<int> Add_Binary_Numbers(std::vector<int> num_1, std::vector<int> num_2);

std::vector<int> HALF_SUBTRACTOR(int a, int b);
std::vector<int> FULL_SUBTRACTOR(int a, int b, int B);
std::vector<int> Subtract_Binary_Numbers(std::vector<int> num_1, std::vector<int> num_2);

bool GREATER_THAN(std::vector<int> num_1, std::vector<int> num_2);
bool LESS_THAN(std::vector<int> num_1, std::vector<int> num_2);
bool EQUAL_TO(std::vector<int> num_1, std::vector<int> num_2);

std::vector<int> ZeroFiller(std::vector<int> num_1, std::vector<int> num_2);

void GATE_DEFINITIONS();

int main()
{
	std::vector<int> num_1 = { 1, 1, 0, 1, 1, 0, 0, 1 };
	std::vector<int> num_2 = { 0, 1, 0, 1, 1, 0, 0, 1 };
	std::vector<int> ADDED_VAL = Add_Binary_Numbers(num_1, num_2);
	std::vector<int> SUBTRACTED_VAL = Subtract_Binary_Numbers(num_1, num_2);
	
	for (int i = 0; i < SUBTRACTED_VAL.size(); i++)
		std::cout << SUBTRACTED_VAL[i];

	std::cout << std::endl;
	
	for (int i = 0; i < ADDED_VAL.size(); i++)
		std::cout << ADDED_VAL[i];

	std::cout << std::endl;
	
	return 0;
}

int NOT_GATE(int val)
{
	if (val == 1)
		return 0;
	if (val == 0)
		return 1;
}

int AND_GATE(int a, int b)
{
	return a & b;
}

int OR_GATE(int a, int b)
{
	return a | b;
}

int NAND_GATE(int a, int b)
{
	return NOT_GATE(a & b);
}

int NOR_GATE(int a, int b)
{
	return NOT_GATE(a | b);
}

int XOR_GATE(int a, int b)
{
	return a ^ b;
}

void GATE_DEFINITIONS()
{
	std::cout << "AND Gate values:" << std::endl;
	std::cout << AND_GATE(0, 0) << std::endl;
	std::cout << AND_GATE(0, 1) << std::endl;
	std::cout << AND_GATE(1, 0) << std::endl;
	std::cout << AND_GATE(1, 1) << std::endl;

	std::cout << std::endl;

	std::cout << "OR Gate values:" << std::endl;
	std::cout << OR_GATE(0, 0) << std::endl;
	std::cout << OR_GATE(0, 1) << std::endl;
	std::cout << OR_GATE(1, 0) << std::endl;
	std::cout << OR_GATE(1, 1) << std::endl;

	std::cout << std::endl;

	std::cout << "NAND Gate values:" << std::endl;
	std::cout << NAND_GATE(0, 0) << std::endl;
	std::cout << NAND_GATE(0, 1) << std::endl;
	std::cout << NAND_GATE(1, 0) << std::endl;
	std::cout << NAND_GATE(1, 1) << std::endl;

	std::cout << std::endl;

	std::cout << "NOR Gate values:" << std::endl;
	std::cout << NOR_GATE(0, 0) << std::endl;
	std::cout << NOR_GATE(0, 1) << std::endl;
	std::cout << NOR_GATE(1, 0) << std::endl;
	std::cout << NOR_GATE(1, 1) << std::endl;

	std::cout << std::endl;

	std::cout << "XOR Gate values:" << std::endl;
	std::cout << XOR_GATE(0, 0) << std::endl;
	std::cout << XOR_GATE(0, 1) << std::endl;
	std::cout << XOR_GATE(1, 0) << std::endl;
	std::cout << XOR_GATE(1, 1) << std::endl;
}

std::vector<int> HALF_ADDER(int a, int b)
{
	int sum = XOR_GATE(a, b);
	int carry = AND_GATE(a, b);

	std::vector<int> res;
	res.push_back(carry);
	res.push_back(sum);
	return res;
}

std::vector<int> FULL_ADDER(int a, int b, int c)
{
	// HALF-ADDER 1
	int sum1 = XOR_GATE(a, b);
	int carry1 = AND_GATE(a, b);

	// HALF-ADDER 1
	int sum2 = XOR_GATE(sum1, c); // final sum value
	int carry2 = AND_GATE(sum1, c);

	// OR GATE
	int carry_f = OR_GATE(carry1, carry2); // final carry

	std::vector<int> res;
	res.push_back(carry_f);
	res.push_back(sum2);
	return res;

}

std::vector<int> Add_Binary_Numbers(std::vector<int> num_1, std::vector<int> num_2)
{
	if (num_1.size() > num_2.size())
		return Add_Binary_Numbers(num_1, ZeroFiller(num_1, num_2));

	if (num_2.size() > num_1.size())
		return Add_Binary_Numbers(num_2, ZeroFiller(num_2, num_1));

	std::vector<int> res;

	std::vector<int> init_val;
	init_val = HALF_ADDER(num_1[num_1.size() - 1], num_2[num_2.size() - 1]);
	int sum = init_val[1];
	int carry = init_val[0];
	init_val.clear();
	res.push_back(sum);

	int start = num_1.size() - 2;
	for (int i = start; i >= 0; i--)
	{
		std::vector<int> val = FULL_ADDER(num_1[i], num_2[i], carry);
		sum = val[1];
		carry = val[0];
		val.clear();
		res.push_back(sum);
	}

	if (carry == 1)
		res.push_back(1);

	std::reverse(res.begin(), res.end());

	return res;
}

std::vector<int> HALF_SUBTRACTOR(int a, int b)
{
	int difference = XOR_GATE(a, b);
	int borrow = AND_GATE(NOT_GATE(a), b);

	std::vector<int> res;
	res.push_back(borrow);
	res.push_back(difference);
	return res;
}

std::vector<int> FULL_SUBTRACTOR(int a, int b, int B)
{
	// HALF-SUBTRACTOR 1
	int difference1 = XOR_GATE(a, b);
	int borrow1 = AND_GATE(NOT_GATE(a), b);

	// HALF-SUBTRACTOR 1
	int difference2 = XOR_GATE(difference1, B); // final difference
	int borrow2 = AND_GATE(NOT_GATE(difference1), B);

	// OR GATE
	int borrow_f = OR_GATE(borrow2, borrow1); // final borrow

	std::vector<int> res;
	res.push_back(borrow_f);
	res.push_back(difference2);
	return res;
}

std::vector<int> Subtract_Binary_Numbers(std::vector<int> num_1, std::vector<int> num_2)
{
	if (num_1.size() > num_2.size())
	{
		std::vector<int> mod_num = ZeroFiller(num_1, num_2);
		return Subtract_Binary_Numbers(num_1, mod_num);
	}

	if (num_2.size() > num_1.size())
	{
		std::vector<int> mod_num = ZeroFiller(num_2, num_1);
		return Subtract_Binary_Numbers(num_2, mod_num);
	}

	std::vector<int> res;

	std::vector<int> init_val;
	init_val = HALF_SUBTRACTOR(num_1[num_1.size() - 1], num_2[num_2.size() - 1]);
	int difference = init_val[1];
	int borrow = init_val[0];
	init_val.clear();
	res.push_back(difference);

	int start = num_1.size() - 2;
	for (int i = start; i >= 0; i--)
	{
		std::vector<int> val = FULL_SUBTRACTOR(num_1[i], num_2[i], borrow);
		difference = val[1];
		borrow = val[0];
		val.clear();
		res.push_back(difference);
	}

	if (borrow == 1)
		res.push_back(1);

	std::reverse(res.begin(), res.end());

	return res;
}

bool GREATER_THAN(std::vector<int> num_1, std::vector<int> num_2)
{
	int start_for_num_1 = 0;
	if (num_1.size() > num_2.size())
	{
		while(start_for_num_1 < num_1.size() - num_2.size())
		{
			if (num_1[start_for_num_1] == 1)
				return true;

			start_for_num_1++;
		}
	}
	else if (num_1.size() < num_2.size())
	{
		return !GREATER_THAN(num_2, num_1);
	}

	for (int i = 0; i < num_2.size(); i++)
	{
		if (num_1[start_for_num_1 + i] > num_2[i])
			return true;
		else if (num_2[i] > num_1[start_for_num_1 + i])
			return false;
	}


	return false;
}

bool LESS_THAN(std::vector<int> num_1, std::vector<int> num_2)
{
	return !(GREATER_THAN(num_1, num_2) || EQUAL_TO(num_1, num_2));
}

bool EQUAL_TO(std::vector<int> num_1, std::vector<int> num_2)
{
	int start_for_num_1 = 0;
	if (num_1.size() > num_2.size())
	{
		while (start_for_num_1 < num_1.size() - num_2.size())
		{
			if (num_1[start_for_num_1] == 1)
				return false;

			start_for_num_1++;
		}
	}
	else if (num_1.size() < num_2.size())
	{
		return EQUAL_TO(num_2, num_1);
	}

	for (int i = 0; i < num_2.size(); i++)
	{
		if (num_1[start_for_num_1 + i] != num_2[i])
			return false;
	}

	return true;
}

std::vector<int> ZeroFiller(std::vector<int> num_1, std::vector<int> num_2)
{
	std::vector<int> res;
	int adjustor = 0;
	if (num_1.size() > num_2.size())
	{
		for (int i = 0; i < num_1.size(); i++)
		{
			if (num_1.size() - i > num_2.size()) 
			{
				res.push_back(0);
				adjustor++;
			}
			else
				res.push_back(num_2[i - adjustor]);
		}
	}
	else if (num_2.size() < num_1.size())
	{
		return ZeroFiller(num_2, num_1);
	}
	else if (num_2.size() == num_1.size())
	{
		return num_2;
	}

	return res;
}