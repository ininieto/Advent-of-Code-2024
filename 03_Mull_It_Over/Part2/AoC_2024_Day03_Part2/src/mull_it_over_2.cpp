/*
	Advent of Code 2024 - 03.12.2024

	Link to the problem: https://adventofcode.com/2024/day/3

	Author of the solution: Inigo Nieto Cuadrado

*/

#include "mull_it_over_2.h"

#include <iostream>

#include "common.h"

int main() {

	// Read the example and the input data
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	long int result = 0;
	bool enabled = true;

	// Read character by character the string
	for (size_t i = 0; i < input.length(); i++) {

		// Try to read "do()" or "don't()"
		if (input[i] == 'd') {
			if (input.substr(i, 4) == "do()")
				enabled = true;
			else if (input.substr(i, 7) == "don't()")
				enabled = false;
		}

		// Try to read "mul("
		if (input[i] == 'm' && input.substr(i, 4) == "mul(" && enabled) {

			size_t pos = i + 4;	// Start reading after "mul("

			// Start reading the first number
			std::string strFirstNum, strSecondNum;
			int firstNum = -1, secondNum = -1;

			for (int j = pos; j < input.length(); j++) {
				if (isdigit(input[j]) && strFirstNum.length() < 3) {
					strFirstNum.push_back(input[j]);
					pos++;
				}
				else if (input[j] == ',' && !strFirstNum.empty()) { // If we find a comma and already found some numbers
					firstNum = stoi(strFirstNum);
					pos++;
					break;
				}
				else
					break;
			}

			// If a number was found, look for the second one
			if (firstNum > 0) {
				for (int j = pos; j < input.length(); j++) {   // We need to read after the comma

					if (isdigit(input[j]) && strSecondNum.length() < 3) {
						strSecondNum.push_back(input[j]);
						pos++;
					}
					else if (input[j] == ')' && !strSecondNum.empty()) { // If we find a closing bracket and already found some numbers
						secondNum = stoi(strSecondNum);
						pos++;
						break;
					}
					else
						break;
				}

				// If we found two numbers, we can now multiply them
				if (secondNum > 0)
					result += firstNum * secondNum;
			}
		}
	}

	// Print the result
	std::cout << result;

	return 0;
}