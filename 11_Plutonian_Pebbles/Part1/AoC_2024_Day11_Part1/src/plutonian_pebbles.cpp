/*
Advent of Code 2024 - 11.12.2024

Link to the problem : https://adventofcode.com/2024/day/11

Author of the solution : Inigo Nieto Cuadrado

*/

#include "plutonian_pebbles.h"

#include <iostream>
#include <unordered_map>

#include "common.h"

void fillVec(std::vector<uint64_t>& vec, const std::string& input) {

	std::string temp;

	for (const char c : input) {
		if (c == ' ' || c == '\n') {
			vec.push_back(stoull(temp));
			temp.clear();
		}
		else
			temp += c;
	}
}

// Function that returns a pair with the two halves of the number
std::pair<uint64_t, uint64_t> splitNum(uint64_t num) {

	std::string strNum = std::to_string(num);

	std::string strNum1 = strNum.substr(0, strNum.size()/2);
	std::string strNum2 = strNum.substr(strNum.size()/2);

	return std::pair<uint64_t, uint64_t>(std::stoull(strNum1), std::stoull(strNum2));
}

// Function that returns the number of digits of a number
int getNumDigits(uint64_t num) {

	// Convert the number into a string
	std::string strNum = std::to_string(num);

	return strNum.size();

	return 0;
}

// This function will apply the rules that are described
void blink(std::vector<uint64_t>& vec) {

	for (int i = 0; i < vec.size(); i++) {

		// If the number is a 0, convert it to 1
		if (vec[i] == 0)
			vec[i] = 1;

		// If the number has an even number of digits, split it
		else if (getNumDigits(vec[i]) % 2 == 0) {
			std::pair<uint64_t, uint64_t> pair = splitNum(vec[i]);

			vec[i] = pair.second;
			vec.insert(vec.begin() + i, pair.first);

			i++;	// Skip the new generated number
		}

		// If none of those rules apply, simply multiply by 2024
		else {
			vec[i] *= 2024;
		}
	}
}

int main() {

	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Save the data in a vector
	std::vector<uint64_t> vec;
	fillVec(vec, input);

	// Define a hashmap for memoization
	std::unordered_map<uint64_t, uint64_t> memo;

	// Perform the algorithm 25 times
	for (int i = 0; i < 25; i++) {
		blink(vec);
	}

	std::cout << vec.size();

	return 0;
}


