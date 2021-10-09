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
std::vector<int> Add_Binary_Numbers(std::vector<int> num1, std::vector<int> num2);

std::vector<int> HALF_SUBTRACTOR(int a, int b);
std::vector<int> FULL_SUBTRACTOR(int a, int b);

void GATE_DEFINITIONS();

int main()
{
	// GATE_DEFINITIONS();

	std::vector<int> res = HALF_SUBTRACTOR(1, 1);
	std::cout << res[0] << res[1] << std::endl;
	/*
	std::vector<int> NUM_1 = { 1, 0, 1, 1, 0, 0, 1 };
	std::vector<int> NUM_2 = { 0, 0, 0, 1, 1, 0, 1 };
	std::vector<int> FINAL_VAL = Add_Binary_Numbers(NUM_1, NUM_2);

	for (int i = 0; i < FINAL_VAL.size(); i++)
		std::cout << FINAL_VAL[i];

	std::cout << std::endl;
	*/

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
	std::vector<int> res;

	std::vector<int> init_val;
	init_val = HALF_ADDER(num_1[num_1.size() - 1], num_2[num_2.size() - 1]);
	int sum = init_val[1];
	int carry = init_val[0];
	init_val.clear();
	res.push_back(sum);

	for (int i = 5; i >= 0; i--)
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

std::vector<int> FULL_SUBTRACTOR(int a, int b)
{
	std::vector<int> res;
	return res;
}