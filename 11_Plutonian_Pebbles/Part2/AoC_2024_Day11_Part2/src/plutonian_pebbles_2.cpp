/*
Advent of Code 2024 - 11.12.2024

Link to the problem : https://adventofcode.com/2024/day/11

Author of the solution : Inigo Nieto Cuadrado

*/

#include "plutonian_pebbles_2.h"

#include <iostream>

#include "common.h"

void fillMap(std::unordered_map<uint64_t, uint64_t>& pebbles, const std::string& input) {

	std::string temp;

	for (const char c : input) {
		if (c == ' ' || c == '\n') {
			pebbles[stoull(temp)]++;
			temp.clear();
		}
		else
			temp += c;
	}
}

// Function that returns a pair with the two halves of the number
std::pair<uint64_t, uint64_t> splitNum(uint64_t num) {

	std::string strNum = std::to_string(num);

	std::string strNum1 = strNum.substr(0, strNum.size() / 2);
	std::string strNum2 = strNum.substr(strNum.size() / 2);

	return std::pair<uint64_t, uint64_t>(std::stoull(strNum1), std::stoull(strNum2));
}

// Function that returns the number of digits of a number
int getNumDigits(uint64_t num) {

	// Convert the number into a string
	std::string strNum = std::to_string(num);

	return strNum.size();
}


// This function will apply the rules that are described
void blink(std::unordered_map<uint64_t, uint64_t>& pebbles) {

	// Create a temporary map for this blink with the new pebbles
	std::unordered_map<uint64_t, uint64_t> newPebbles;

	for (auto& pebble : pebbles) {

		uint64_t pebbleNum = pebble.first;
		uint64_t pebbleCnt = pebble.second;

		if (pebbleNum == 0) {
			newPebbles[1] += pebbleCnt;
		}
		else if (getNumDigits(pebbleNum) % 2 == 0) {

			std::pair<uint64_t, uint64_t> pair = splitNum(pebble.first);

			// Add the new pebbles to the map
			newPebbles[pair.first] += pebbleCnt;
			newPebbles[pair.second] += pebbleCnt;
		}
		else {
			newPebbles[pebbleNum * 2024] += pebbleCnt;
		}
	}

	// Update the pebbles map
	pebbles = newPebbles;
}

int main() {

	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Save the data in a map
	std::unordered_map<uint64_t, uint64_t> pebbles;
	fillMap(pebbles, input);

	// Perform the algorithm 75 times
	for (int i = 0; i < 75; i++) {
		blink(pebbles);
	}

	// Count the number of pebbles
	uint64_t numPebbles = 0;

	for (const auto& pebble : pebbles) {
		numPebbles += pebble.second;
	}

	std::cout << numPebbles << '\n';

	return 0;
}


