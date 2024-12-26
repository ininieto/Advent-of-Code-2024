/*
Advent of Code 2024 - 13.12.2024

Link to the problem : https://adventofcode.com/2024/day/13

Author of the solution : Inigo Nieto Cuadrado

*/

#include "claw_contraption.h"

#include <iostream>
#include <sstream>

#include "common.h"

// Function to read a line of input and get the numeric variables
void parseInput(const std::string& line, int& x, int& y){

	std::string num;

	for (size_t pos = line.find(':') + 4; pos < line.size(); pos++) {
		if (isdigit(line[pos]))
			num += line[pos];
		else if (line[pos] == ',') {
			x = stoi(num);
			num.clear();
		}
	}
	y = stoi(num);
}

/*
	Function to solve a 2x2 equations system. We have a matrix (a, b; c, d) * (x; y) = (e; f)  
	The solutions to that system will be (solX; solY)
*/
bool solveEquation(const int a, const int b, const int c, const int d, const int e, const int f, double& solX, double& solY){

	// Calculate the determinant of the matrix
	const double det = a * d - b * c;

	// Make sure the determinant is not zero
	if (det == 0)
		return false;

	// Compute the solutions
	solX = (d * e - b * f) / det;
	solY = (a * f - c * e) / det;

	// Return true if we have integer solution and lower than 100
	return solX == std::floor(solX) && solY == std::floor(solY);
}

int main() {

	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Parse the input
	std::vector<std::string> lines = Common::split(input, "\n");

	int xA = -1, xB = -1, yA = -1, yB = -1;		// Declare the constants for (x, y) and (A, B)
	int prizeX = -1, prizeY = -1;

	// Variable to handle the solution
	uint64_t solution = 0;

	for (const auto line : lines) {

		// Skip the empty lines
		if (line.empty())
			continue;

		std::string label = line.substr(0, line.find(':'));

		// Extract the value of the variables
		if (label == "Button A") 
			parseInput(line, xA, yA);
		else if (label == "Button B") 
			parseInput(line, xB, yB);
		else 
			parseInput(line, prizeX, prizeY);

		// Now we have all the variables, we can perform the algorithm
		if (xA > -1 && yA > -1 && xB > -1 && yB > -1 && prizeX > -1 && prizeY > -1) {

			double solA, solB;

			if (solveEquation(xA, xB, yA, yB, prizeX, prizeY, solA, solB))
				solution += ((uint32_t)solA * 3) + (uint32_t)solB;

			// Reset the variables
			xA = -1;
			xB = -1;
			yA = -1;
			yB = -1;
			prizeX = -1;
			prizeY = -1;
		}
	}

	std::cout << solution << '\n';

	return 0;
}

