/*
	Advent of Code 2024 - 06.12.2024

	Link to the problem: https://adventofcode.com/2024/day/6

	Author of the solution: Inigo Nieto Cuadrado

*/

/* I got an answer of 1783 but it is too low */
/* 1993 is too high */

#include "guard_gallivant_2.h"

#include <iostream>

#include "common.h"

// Function to fill in the grid
void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input) {

	int nrows = grid.size(), ncols = grid[0].size();

	int strCounter = 0;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {

			if (input[strCounter] == '\n')
				strCounter++;

			grid[i][j].c = input[strCounter];
			strCounter++;
		}
	}
}

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
bool outOfBounds(const Coords& pos, int nrows, int ncols) {

	return pos.i < 0 || pos.j < 0 || pos.i >= nrows || pos.j >= ncols;
}

// Function that will determine whether we have a loop or not
bool checkLoop(std::vector<std::vector<Tile>> grid, Coords pos, Coords obstaclePos, int nrows, int ncols) {

	// Set an obstacle in the current position
	grid[obstaclePos.i][obstaclePos.j].c = '#';

	// Starting direction is up
	Coords dir(-1, 0);

	while (true) {

		// Define a pointer to the current Tile
		Tile* currentTile = &grid[pos.i][pos.j];

		// Check if next position is visitable
		Coords nextPos(pos.i + dir.i, pos.j + dir.j);
		if (outOfBounds(nextPos, nrows, ncols))
			return false;
		else if (grid[nextPos.i][nextPos.j].c == '#')
			dir = turnRight(dir);	// Turn the direction 90º right

		// If the current Tile is already visited with the same direction --> Loop
		for (const auto& visitedDir : currentTile->directions) {
			if (visitedDir.i == dir.i && visitedDir.j == dir.j)
				return true;
		}

		// Update the tile's dir
		currentTile->directions.push_back(dir);

		// Move to the next position
		pos = Coords(pos.i + dir.i, pos.j+ dir.j);
	}

	// If we exit the loop, return false
	return false;
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
	std::vector<std::vector<Tile>> grid(ncols, std::vector<Tile>(nrows));

	// Fill the grid 
	fillGrid(grid, input);

	// Find the starting position
	Coords pos;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (grid[i][j].c == '^') {
				pos = Coords(i, j);
				break;
			}
		}
		if (pos.i > -1 && pos.j > -1)
			break;
	}

	Coords startPos = Coords(pos.i, pos.j);

	// Run the algorithm once and find the traced tiles

	std::vector<Coords> tracedCoords;

	Coords dir(-1, 0);	// Starting direction is up

	while (true) {

		// Set the current tile as traced
		bool coordAlreadyTraced = false;
		for (const auto& coord : tracedCoords) {
			if (coord.i == pos.i && coord.j == pos.j)
				coordAlreadyTraced = true;
		}

		// Make sure we don't add the same coord twice
		if(!coordAlreadyTraced)
			tracedCoords.push_back(Coords(pos.i, pos.j));

		// Check if next position is visitable
		Coords nextPos(pos.i + dir.i, pos.j + dir.j);
		if (outOfBounds(nextPos, nrows, ncols))
			break;
		else if (grid[nextPos.i][nextPos.j].c == '#')
			dir = turnRight(dir);	// Turn the direction 90º right

		// Move to the next position
		pos = Coords(pos.i + dir.i, pos.j + dir.j);
	}

	// Find all the spots that can form a loop
	long int solution = 0;

	// Reset the initial position
	pos = Coords(startPos.i, startPos.j);

	// Check loops for all traced positions
	for (const auto& obstaclePos : tracedCoords) 
		solution += checkLoop(grid, pos, obstaclePos, nrows, ncols);	// Check if we have a loop

	std::cout << solution << '\n';

	return 0;
}
