/*
	Advent of Code 2024 - 06.12.2024

	Link to the problem: https://adventofcode.com/2024/day/6

	Author of the solution: Inigo Nieto Cuadrado

*/

#include "guard_gallivant.h"

#include <iostream>

#include "common.h"

Coords turnRight(const Coords& currentDir) {

	if (currentDir.i == 0 && currentDir.j == -1)	// Left
		return Coords(-1, 0);	// Up
	else if (currentDir.i == 1 && currentDir.j == 0)	// Down
		return Coords(0, -1);	// Left
	else if (currentDir.i == 0 && currentDir.j == 1)	// Right
		return Coords(1, 0);	// Down
	else	// Up
		return Coords(0, 1);	// Right
}

// Function that will return true when out of bounds
bool outOfBounds(const Coords& pos, int nrows, int ncols){

	return pos.i < 0 || pos.j < 0 || pos.i >= nrows || pos.j >= ncols;
}


int main() {

	// Read the input 
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Define a grid
	int nrows = 0, ncols = 0;
	Common::getGridDimensions(input, nrows, ncols);
	std::vector<std::vector<char>> grid(ncols, std::vector<char>(nrows));
	
	// Fill the grid 
	Common::fillGrid(grid, input);

	// Find the starting position
	Coords pos;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] == '^') {
				pos = Coords(i, j);
				break;
			}
		}
		if (pos.i > -1 && pos.j > -1)
			break;
	}

	// Define a "visited" grid
	std::vector<std::vector<bool>> visited(ncols, std::vector<bool>(nrows));

	// Get the number of visited tiles
	Coords dir(-1, 0);	// Starting direction is up

	while (!outOfBounds(pos, nrows, ncols)) {

		// Set the current position as visited
		visited[pos.i][pos.j] = true;

		// Check if next position is visitable
		Coords nextPos(pos.i + dir.i, pos.j + dir.j);
		if (outOfBounds(nextPos, nrows, ncols))
			break;
		else if (grid[pos.i + dir.i][pos.j + dir.j] == '#') 
			dir = turnRight(dir);	// Turn the direction 90º right

		// Move to the next position
		pos.i += dir.i;
		pos.j += dir.j;
	}

	// Count the visited positions
	long int solution = 0;
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			solution += visited[i][j];
		}
	}

	std::cout << solution << '\n';

	return 0;
}