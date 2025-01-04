/*
Advent of Code 2024 - 16.12.2024

Link to the problem : https://adventofcode.com/2024/day/16

Author of the solution : Inigo Nieto Cuadrado

*/

/* 105512 is too high */

#include "reindeer_maze.h"

#include <iostream>

// Function to fill in the grid
void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input) {

	size_t nrows = grid.size(), ncols = grid[0].size();

	int strCounter = 0;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {

			if (input[strCounter] == '\n')
				strCounter++;

			grid[i][j] = Tile(Coords(i, j), input[strCounter]);
			strCounter++;
		}
	}
}

// Debug function to print the grid
void printGrid(const std::vector<std::vector<Tile>>& grid) {

	for (const auto& row : grid) {
		for (const auto& c : row) {
			std::cout << c.c;
		}
		std::cout << '\n';
	}
}

// Function that returns true if a Tile* is already in the queue
bool isQueued(std::priority_queue<Tile*, std::vector<Tile*>, CompareDist>& pq, const Tile* tile) {

	auto copy = pq;	// Create a copy of the queue
	while (!copy.empty()) {
		if (copy.top() == tile)
			return true;
		copy.pop();
	}
	return false;
}


int main() {

	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string example2 = Common::readInputText("../../resources/example2.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example2;

	// Define a grid
	size_t nrows = 0, ncols = 0;
	Common::getGridDimensions(input, nrows, ncols);

	std::vector<std::vector<Tile>> grid(nrows, std::vector<Tile>(ncols));
	fillGrid(grid, input);

	// Find the starting and ending position
	Coords startPos, endPos;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (grid[i][j].c == 'S')
				startPos = Coords(i, j);
			else if (grid[i][j].c == 'E')
				endPos = Coords(i, j);

			if (startPos.i > -1 && endPos.i > -1)
				break;
		}
	}

	// As there are Walls surrounding the Maze, we don't need to check for out of bounds


	// Define a Dijkstra to scan all the possible paths to the end
	std::priority_queue<Tile*, std::vector<Tile*>, CompareDist> nextTiles;
	grid[startPos.i][startPos.j].dist = 0;
	nextTiles.push(&grid[startPos.i][startPos.j]);	// Add the starting position to the queue

	Coords currentDir(0, 1);	// Starting direction is East

	
	while (!nextTiles.empty()) {

		Tile* currentTile = nextTiles.top();	// Get the first element of the queue
		nextTiles.pop();						// Erase it from the queue

		if (currentTile->c == 'E') {
			break;
		}

		// Update the current direction
		if (currentTile->prevTile != nullptr)
			currentDir = Coords(currentTile->pos.i - currentTile->prevTile->pos.i, currentTile->pos.j - currentTile->prevTile->pos.j);

		// Debug
		// std::cout << "\nCurrent position: (" << currentTile->pos.i << ", " << currentTile->pos.j << "). Distance: " << currentTile->dist << "\n";
		// currentTile->c = 'X';
		// printGrid(grid);

		currentTile->visited = true;	// Set the current Tile as visited

		std::vector<Coords> surroundings = Common::getSurroundings(currentTile->pos, nrows, ncols);

		for (const auto& s : surroundings) {
			Tile* surroundingTile = &grid[s.i][s.j];

			// For each surrounding, check if they are eligible to jump onto
			//if (surroundingTile->c != '#' && !surroundingTile->visited && !isQueued(nextTiles, surroundingTile)) {
			if (surroundingTile->c != '#' && !surroundingTile->visited) {

				Coords dir(surroundingTile->pos.i - currentTile->pos.i, surroundingTile->pos.j - currentTile->pos.j);
				int scoreIncrease = (dir == currentDir) ? 1 : 1001;			// Straight step increases 1, turning 90º increases 1 + 1000

				if (currentTile->dist + scoreIncrease < surroundingTile->dist) {
					surroundingTile->dist = currentTile->dist + scoreIncrease;
					surroundingTile->prevTile = currentTile;
					nextTiles.push(surroundingTile);
				}

			}
		}
	}


	// Print the path to the end
	Tile* tile = &grid[endPos.i][endPos.j];

	std::cout << tile->dist << "\n\n";

	while (tile->prevTile != nullptr) {
		tile->c = 'X';
		tile = tile->prevTile;
	}

	printGrid(grid);

	return 0;
}


