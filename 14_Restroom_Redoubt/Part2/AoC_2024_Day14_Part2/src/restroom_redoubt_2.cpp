/*
Advent of Code 2024 - 14.12.2024

Link to the problem : https://adventofcode.com/2024/day/14

Author of the solution : Inigo Nieto Cuadrado

*/

#include "restroom_redoubt_2.h"

#include <iostream>

// Function to store the input in variables
void parseInput(const std::string& line, int& x, int& y, int& vx, int& vy) {

	std::string num;

	for (size_t pos = 0; pos < line.size(); pos++) {

		if (line[pos] == 'p' || line[pos] == 'v' || line[pos] == '=')
			continue;
		else if (line[pos] == ',' && x == -1) {
			x = stoi(num);
			num.clear();
		}
		else if (line[pos] == ' ') {
			y = stoi(num);
			num.clear();
		}
		else if (line[pos] == ',' && x > -1) {
			vx = stoi(num);
			num.clear();
		}
		else
			num += line[pos];
	}
	vy = stoi(num);
}

// Function to update the position of the robot
void updateRobot(Robot& robot, const size_t nrows, const size_t ncols) {

	robot.pos.i += robot.v.i;
	robot.pos.j += robot.v.j;

	if (robot.pos.i < 0)
		robot.pos.i = (int)nrows + robot.pos.i;

	if (robot.pos.i >= nrows)
		robot.pos.i -= (int)nrows;

	if (robot.pos.j < 0)
		robot.pos.j = (int)ncols + robot.pos.j;

	if (robot.pos.j >= ncols)
		robot.pos.j -= (int)ncols;
}

// Debug function to print the grid
void printGrid(const std::vector<std::vector<char>>& grid){

	for (const auto& row : grid) {
		for (const auto& c : row) {
			std::cout << c;
		}
		std::cout << '\n';
	}

	std::cout << "\n\n";
}

// Function to get, somehow, the entropy of the grid. Will compress the grid in a string, and the length of that string will be our "entropy"
std::string compressGrid(const std::vector<std::vector<char>>& grid){

	std::string compressedGrid;

	// Compress the grid
	char currentChar = grid[0][0];
	compressedGrid += currentChar;

	for (const auto& row : grid) {
		for (const auto& c : row) {
			if (c != currentChar) {
				compressedGrid += c;
				currentChar = c;
			}
		}
	}
	return compressedGrid;
}

int main() {

	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	const size_t nrows = 103, ncols = 101;

	// Create a vector with Robots
	std::vector<Robot> robots;

	// Parse the input
	std::vector<std::string> lines = Common::split(input, "\n");

	for (const auto line : lines) {

		int x = -1, y = -1, vx = -1, vy = -1;
		parseInput(line, x, y, vx, vy);

		// Create a robot with this information
		robots.push_back(Robot(x, y, vx, vy));
	}

	int solution = 0;
	double minCompressedGridSize = pow(2, 31);

	for (int i = 1; i < nrows * ncols; i++) {

		// Create a grid
		std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols));

		// Initialize the grid with .
		for (int i = 0; i < nrows; i++) {
			for (int j = 0; j < ncols; j++) {
				grid[i][j] = '.';
			}
		}

		// Calculate the positions of the robots and print them in the grid
		for (auto& robot : robots) {
			updateRobot(robot, nrows, ncols);
			grid[robot.pos.i][robot.pos.j] = 'X';
		}

		// Compress the grid 
		std::string compressedGrid = compressGrid(grid);

		// Get the grid with the least entropy
		if (compressedGrid.size() < minCompressedGridSize) {
			minCompressedGridSize = (double)compressedGrid.size();
			solution = i;

			// Print the grid
			printGrid(grid);
		}
	}

	std::cout << solution;

	return 0;
}