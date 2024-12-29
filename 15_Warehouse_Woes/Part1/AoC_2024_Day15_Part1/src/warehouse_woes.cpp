/*
Advent of Code 2024 - 15.12.2024

Link to the problem : https://adventofcode.com/2024/day/15

Author of the solution : Inigo Nieto Cuadrado

*/

#include "warehouse_woes.h"

#include <iostream>
#include <unordered_map>

// Function that will move the robot in the given direction
void move(Coords& pos, Coords dir, std::vector<std::vector<char>>& grid){

	Coords nextPos(pos.i + dir.i, pos.j + dir.j);

	// If next position is a wall, we don't move
	if (grid[nextPos.i][nextPos.j] == '#') {	
		return;
	}
	// If the next position is free, jump
	else if (grid[nextPos.i][nextPos.j] == '.') {
		grid[nextPos.i][nextPos.j] = '@';
		grid[pos.i][pos.j] = '.';
		pos = nextPos;
		return;
	}
	// If there is a box, try to push it
	else {

		// Get the number of consecutive balls ahead
		int numBalls = 0;

		while (grid[nextPos.i][nextPos.j] == 'O') {
			numBalls++;
			nextPos = Coords(nextPos.i + dir.i, nextPos.j + dir.j);

			// If there is a wall after some boxes, simply return
			if (grid[nextPos.i][nextPos.j] == '#')
				return;
		}

		// Move the elements from last to first
		for (int i = numBalls + 1; i > 0; i--) {

			Coords currentPos(nextPos.i - dir.i, nextPos.j - dir.j);

			// We cannot move a wall
			if (grid[currentPos.i][currentPos.j] == '#') {
				grid[nextPos.i][nextPos.j] = '.';
				continue;
			}

			grid[nextPos.i][nextPos.j] = grid[currentPos.i][currentPos.j];

			// Update the current position
			if (grid[nextPos.i][nextPos.j] == '@') {
				grid[pos.i][pos.j] = '.';	// Add a space in the position where the @ was
				pos = nextPos;
			}

			// Point the next position to the current position for the next iteration
			nextPos = currentPos;
		}
	}
}

int main() {

	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string smallExample = Common::readInputText("../../resources/smallExample.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Divide the input in grid and instructions
	std::string gridInput = input.substr(0, input.find("\n\n") + 1);
	std::string instructions = input.substr(input.find("\n\n") + 2);

	// Define a grid
	size_t nrows = 0, ncols = 0;
	Common::getGridDimensions(gridInput, nrows, ncols);

	std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols));
	Common::fillGrid(grid, gridInput);

	// Get the starting position
	Coords pos;
	for (size_t i = 0; i < nrows; i++) {
		for (size_t j = 0; j < ncols; j++) {
			if (grid[i][j] == '@') {
				pos = Coords(i, j);
				break;
			}
		}
	}

	// Start reading the instructions
	Coords up(-1, 0), down(1, 0), left(0, -1), right(0, 1);
	std::unordered_map<char, Coords> dir = { {'^', up}, {'v', down}, {'<', left}, {'>', right} };	// Associate the characters with the directions

	for (const char c : instructions) {

		// Skip the unwanted characters
		if (c == '\n')
			continue;

		move(pos, dir.at(c), grid);
	}

	Common::printGrid(grid);

	// Calculate the GPS Coordinates
	uint64_t solution = 0;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (grid[i][j] == 'O')
				solution += 100 * i + j;
		}
	}

	std::cout << solution;

	return 0;
}


