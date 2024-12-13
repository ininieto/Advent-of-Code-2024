/*
	Advent of Code 2024 - 06.12.2024

	Link to the problem: https://adventofcode.com/2024/day/6

	Author of the solution: Inigo Nieto Cuadrado

*/

#include "bridge_repair.h"

#include <iostream>
#include <cmath>
#include <bitset>

#include "common.h"

// Function that will test all the possible operations
uint64_t countOperations(uint64_t result, const std::vector<uint64_t>& numbers) {

	// If the vector has N numbers, there are 2 ^ (N - 1) possible operations

	// I want to emulate a binary count to find all the combinations of + and *
	// A 0 will represent the sum operation and a 1 the multiplication

	const int numElements = numbers.size();
	const int numCombinations = pow( 2, numElements - 1);

	for (int i = 0; i < numCombinations; i++) {

		uint64_t testResult = numbers[0];
		
		// Get the binary representation of i
		std::string binNum = std::bitset<NUM_BITS>(i).to_string();

		// Isolate the last (N - 1) bits
		std::string operations = binNum.substr(binNum.size() - (numElements - 1));

		// Perform the operations
		for (int j = 0; j < operations.size(); j++) {
			if (operations[j] == '0')
				testResult += numbers[j + 1];
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