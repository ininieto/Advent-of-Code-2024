/*
Advent of Code 2024 - 10.12.2024

Link to the problem : https://adventofcode.com/2024/day/10

Author of the solution : Inigo Nieto Cuadrado

*/

#include "hoof_it_2.h"

#include <iostream>

// Function to fill in the Tile grid
void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input) {

	int nrows = grid.size(), ncols = grid[0].size();

	int strCounter = 0;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {

			if (input[strCounter] == '\n')
				strCounter++;

			grid[i][j] = Tile(input[strCounter] - '0', Coords(i, j));
			strCounter++;
		}
	}
}


// Function that returns all the surrounding positions, if they are in bounds
std::vector<Coords> getSurroundings(Coords& pos, const size_t nrows, const size_t ncols) {

	std::vector<Coords> surroundings;

	Coords up = Coords(pos.i - 1, pos.j);
	Coords down = Coords(pos.i + 1, pos.j);
	Coords left = Coords(pos.i, pos.j - 1);
	Coords right = Coords(pos.i, pos.j + 1);

	if (!Common::outOfBounds(up, nrows, ncols))
		surroundings.push_back(up);
	if (!Common::outOfBounds(down, nrows, ncols))
		surroundings.push_back(down);
	if (!Common::outOfBounds(left, nrows, ncols))
		surroundings.push_back(left);
	if (!Common::outOfBounds(right, nrows, ncols))
		surroundings.push_back(right);

	return surroundings;
}

// Function that counts the score of a trailhead
int getTrailheadScore(std::vector<std::vector<Tile>> grid, Coords pos) {

	// Obtain the number of rows and cols
	const size_t nrows = grid.size(), ncols = grid[0].size();

	int rating = 0;

	// Vector with the next tiles to be scanned
	std::vector<Tile*> nextTiles;

	// Define a pointer to the current Tile
	Tile* currentTile = &grid[pos.i][pos.j];

	nextTiles.push_back(currentTile);

	while (!nextTiles.empty()) {

		// Update the value of the current Tile
		currentTile = nextTiles[0];

		// Check if current height is already 9
		if (currentTile->height == 9) {
			currentTile->visited = true;
			rating++;
		}

		// Erase the current Tile from the queue
		nextTiles.erase(nextTiles.begin());

		// Get the surroundings
		std::vector<Coords> surroundings = getSurroundings(currentTile->pos, nrows, ncols);

		// Check if we can jump onto them
		for (const auto& s : surroundings) {
			if (grid[s.i][s.j].height == currentTile->height + 1) {
				Tile* nextTile = &grid[s.i][s.j];
				nextTile->prevTiles.push_back(currentTile);
				nextTiles.push_back(&grid[s.i][s.j]);
			}
		}
	}

	return rating;
}


int main() {

	// Read the input data
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Define a grid
	size_t nrows = 0, ncols = 0;
	Common::getGridDimensions(input, nrows, ncols);
	std::vector<std::vector<Tile>> grid(nrows, std::vector<Tile>(ncols));

	// Fill the grid
	fillGrid(grid, input);

	// Find all the trailheads
	uint64_t solution = 0;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (grid[i][j].height == 0)
				solution += getTrailheadScore(grid, Coords(i, j));
		}
	}

	std::cout << solution;

	return 0;

}

