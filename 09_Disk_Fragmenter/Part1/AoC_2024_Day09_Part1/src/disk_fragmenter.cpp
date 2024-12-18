/*
Advent of Code 2024 - 09.12.2024

Link to the problem : https://adventofcode.com/2024/day/9

Author of the solution : Inigo Nieto Cuadrado

*/

#include "disk_fragmenter.h"

#include <iostream>

#include "common.h"

int main() {

	// Read the input data
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Vector that will hold all the numbers and spaces
	std::vector<int> chain;

	bool isBlock = true;
	int currentID = 0;

	// Fill a vector with the ID or -1 (space)
	for (const char c : input) {
		if (isBlock) {
			
			int numFiles = c - '0';

			for (int i = 0; i < numFiles; i++) 
				chain.push_back(currentID);

			currentID++;
			isBlock = false;
		}
		else {
			int numSpaces = c - '0';

			for (int i = 0; i < numSpaces; i++) 
				chain.push_back(-1);
			
			isBlock = true;
		}
	}

	int lastNumPos = chain.size() - 1;
	int lastNum = -1;

	for (int i = 0; i < chain.size(); i++) {

		// Find the first blank space
		if (chain[i] != -1)
			continue;

		// Get the last number
		lastNum = chain[lastNumPos];

		while (lastNum == -1) {
			lastNumPos--;
			chain.erase(chain.end() - 1);
			lastNum = chain[lastNumPos];
		}
		
		// Move the last number to the first space
		chain[i] = lastNum;

		// Erase the last position
		chain.erase(chain.end() - 1);
		lastNumPos--;
	}

	// Obtain the checksum
	uint64_t checksum = 0;
	for (int i = 0; i < chain.size(); i++) 
		checksum += i * chain[i];

	std::cout << checksum << '\n';

	return 0;
}

	
