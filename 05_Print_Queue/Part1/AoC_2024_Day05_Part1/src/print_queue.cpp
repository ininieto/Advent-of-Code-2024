/*
	Advent of Code 2024 - 05.12.2024

	Link to the problem: https://adventofcode.com/2024/day/5

	Author of the solution: Inigo Nieto Cuadrado

*/

#include "print_queue.h"

#include <iostream>
#include <sstream>
#include <algorithm>

#include "common.h"

// Function to read the priority rules and store them in a hashmap
void parseOrderingRules(const std::string& line, std::unordered_map<int, std::vector<int>>& priority) {

	std::stringstream ss(line);
	int num1, num2;
	char delimiter;

	if (ss >> num1 >> delimiter >> num2 && delimiter == '|')
		priority[num1].push_back(num2);
}

// Function to read the updates
std::vector<int> parseUpdates(const std::string& line) {

	std::stringstream ss(line);
	std::vector<int> update;
	int num;
	char delimiter;

	while (ss >> num) {
		update.push_back(num);
		ss >> delimiter;
		if (delimiter != ',' && ss.peek() != EOF)
			return {};
	}
	return update;
}


int main() {

	// Read the example and the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Create a hashmap that will determine the priorities
	std::unordered_map<int, std::vector<int>> priority;

	// Create a vector to store the updates
	std::vector<std::vector<int>> updates;

	// Parse the input numbers
	std::istringstream inputStream(input);
	std::string line;
	bool readOrderingRules = true;

	while (std::getline(inputStream, line)) {

		if (line.empty()) {	// If we find the change of ordering rules and updates
			readOrderingRules = false;
			continue;
		}

		if (readOrderingRules)
			parseOrderingRules(line, priority);
		else
			updates.push_back(parseUpdates(line));
	}

	// Check if the updates are correctly ordered
	long int solution = 0;

	for (const auto& update : updates) {

		bool correctOrder = true;	// Firstly we will suppose correct order

		// Traverse all the numbers in the update
		for (int i = 0; i < update.size(); i++) {

			int currentNum = update[i];

			// Traverse the rest of the vector trying to find a misplace
			for (int j = i + 1; j < update.size(); j++) {

				int scannedNum = update[j];

				// Get the priority list of the scanned number
				auto it = priority.find(scannedNum);
				if (it != priority.end()) {
					std::vector<int> lowerPriority = it->second;	

					// Try to find the currentNum in the lower priority vector
					if (std::find(lowerPriority.begin(), lowerPriority.end(), currentNum) != lowerPriority.end()) {
						correctOrder = false;
						break;
					}
				}
			}
		}

		if (correctOrder) 
			solution += update[update.size() / 2];
	}

	std::cout << solution << '\n';

	return 0;
}


