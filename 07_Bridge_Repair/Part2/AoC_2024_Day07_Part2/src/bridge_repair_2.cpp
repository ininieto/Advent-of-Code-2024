/*
	Advent of Code 2024 - 06.12.2024

	Link to the problem: https://adventofcode.com/2024/day/6

	Author of the solution: Inigo Nieto Cuadrado

*/

#include "bridge_repair_2.h"

#include <iostream>
#include <cmath>
#include <bitset>

#include "common.h"

// Function that concatenates two numbers
uint64_t concatenate(uint64_t num1, uint64_t num2) {

	std::string strNum1 = std::to_string(num1);
	std::string strNum2 = std::to_string(num2);

	std::string conc = strNum1 + strNum2;

	return stoull(conc);
}

// Function to convert a number to base 3
std::string toBase3(uint64_t num) {

	std::string ternNum;

	while (num > 0) {
		int mod = num % 3;
		ternNum = std::to_string(num % 3) + ternNum;
		num /= 3;
	}

	// Complete with 0s
	int numZeros = NUM_BITS - ternNum.size();
	std::string zeros;
	for (int i = 0; i < numZeros; i++)
		zeros.push_back('0');

	return zeros + ternNum;
}

// Function that will test all the possible operations
uint64_t countOperations(uint64_t result, const std::vector<uint64_t>& numbers) {

	// If the vector has N numbers, there are 3 ^ (N - 1) possible operations

	// I want to emulate a base 3 count to find all the combinations of +, || and *
	// 0: +, 1: ||, 2: *

	const int numElements = numbers.size();
	const uint64_t numCombinations = pow(3, numElements - 1);

	for (uint64_t i = 0; i < numCombinations; i++) {

		uint64_t testResult = numbers[0];

		// Get the ternary representation of i
		std::string ternNum = toBase3(i);

		// Isolate the last (N - 1) bits
		std::string operations = ternNum.substr(ternNum.size() - (numElements - 1));

		// Perform the operations
		for (int j = 0; j < operations.size(); j++) {
			if (operations[j] == '0')
				testResult += numbers[j + 1];
			else if (operations[j] == '1')
				testResult = concatenate(testResult, numbers[j + 1]);
			else
				testResult *= numbers[j + 1];
		}

		if (result == testResult)
			return testResult;
	}

	return 0;
}

int main() {


	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	uint64_t solution = 0;

	// Parse the input
	std::vector<std::string> lines = Common::split(input, "\n");

	for (const auto& line : lines) {
		uint64_t result = stoull(line.substr(0, line.find(':')));

		std::vector<uint64_t> numbers;
		std::string strNum;

		for (size_t pos = line.find(':') + 1; pos < line.length(); pos++) {
			if (line[pos] == ' ' && !strNum.empty()) {
				numbers.push_back(stoull(strNum));
				strNum.clear();
			}
			else if (line[pos] != ' ')
				strNum.push_back(line[pos]);
		}

		// Add the last number
		numbers.push_back(stoull(strNum));

		// Now that we have the result and the nums, perform the algorithm
		solution += countOperations(result, numbers);
	}

	std::cout << solution << '\n';
	return 0;

}