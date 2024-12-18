/*
Advent of Code 2024 - 09.12.2024

Link to the problem : https://adventofcode.com/2024/day/9

Author of the solution : Inigo Nieto Cuadrado

*/

#include "disk_fragmenter_2.h"

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

	while(true) {

		/* ------------ Find the last block of files ------------ */
		int lastNum = chain[lastNumPos];

		// Exit condition
		if (lastNum == 0)
			break;

		// If there is blank space at the end of the chain, simply skip it
		while (lastNum == -1) {
			lastNumPos--;
			lastNum = chain[lastNumPos];
		}

		int numFilesBlock = 1;
		size_t pos = lastNumPos - 1;

		while (chain[pos] == lastNum) {
			numFilesBlock++;
			pos--;
		}

		/* ------------ Find the first available block of spaces ------------ */
		int numSpaces = 0;
		int spacePos = -1;

		int i;
		for (i = 0; i < lastNumPos; i++) {	// Must search at the left of the block file

			if (chain[i] == -1)	// If we find a space
				numSpaces++;
			else {
				if (numSpaces >= numFilesBlock) {	// Space only valid if it can fit the block 
					spacePos = i - numSpaces;
					break;
				}
				numSpaces = 0;
			}
		}

		// If there are no available spaces, don't move the file block
		if (i == lastNumPos) {
			lastNumPos -= numFilesBlock;
			continue;
		}

		// Here we have found a space that could fit the block
		for (int j = spacePos; j < spacePos + numFilesBlock; j++) {
			chain[j] = lastNum;
			chain[lastNumPos] = -1;	// Add a space in the moved position
			lastNumPos--;
		}
	}

	// Obtain the checksum
	uint64_t checksum = 0;
	for (int i = 0; i < chain.size(); i++)
		if(chain[i] != -1)
			checksum += i * chain[i];

	std::cout << checksum << '\n';

	return 0;
}


