/*
	Advent of Code 2024 - 08.12.2024

	Link to the problem: https://adventofcode.com/2024/day/8

	Author of the solution: Inigo Nieto Cuadrado

*/

#include "resonant_collinearity.h"

#include <iostream>
#include <unordered_map>

#include "common.h"

// Function to fill in the grid
void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input) {

	size_t nrows = grid.size(), ncols = grid[0].size();

	int strCounter = 0;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {

			if (input[strCounter] == '\n')
				strCounter++;

			grid[i][j] = Tile(input[strCounter]);
			strCounter++;
		}
	}
}

// Funtion to determine if we are out of bounds
static bool outOfBounds(const Coords& pos, size_t nrows, size_t ncols) {
	return pos.i < 0 || pos.i >= nrows || pos.j < 0 || pos.j >= ncols;
}


int main() {

	// Read the input
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

	// Define a hashmap that links Frequencies and positions
	std::unordered_map<char, std::vector<Coords>> freqPositions;

	// Scan all the positions of the Antennas
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (grid[i][j].c != '.')
				freqPositions[grid[i][j].c].push_back(Coords(i, j));
		}
	}

	// Find all the pairs of frequencies 
	for (const auto& freq : freqPositions) {
		
		// freq.first indicates the frequency, and freq.second, a vector with all its coordinates
		std::vector<Coords> posVector = freq.second;

		// Iterate over the positions
		for (int i = 0; i < posVector.size(); i++) {

			Coords currentPosition = posVector[i];

			// Find all its pairs
			for (int j = 0; j < posVector.size(); j++) {
				if (j == i)
					continue;

				Coords pairPosition = posVector[j];

				// Find the vector that connects them
				Coords vector(pairPosition.i - currentPosition.i, pairPosition.j - currentPosition.j);

				// Find the position of the antinodes
				Coords antinode1(currentPosition.i - vector.i, currentPosition.j - vector.j);
				Coords antinode2(pairPosition.i + vector.i, pairPosition.j + vector.j);

				// Try to set the Antinodes in the grid
				if (!outOfBounds(antinode1, nrows, ncols))
					grid[antinode1.i][antinode1.j].isAntinode = true;
				if (!outOfBounds(antinode2, nrows, ncols))
					grid[antinode2.i][antinode2.j].isAntinode = true;
			}
		}
	}

	long int solution = 0;

	// Print the grid and find the number of antinodes
	for (const auto& row : grid) {
		for (const auto& e : row) {
			if (e.isAntinode) {
				solution++;
				std::cout << '#';
			}
			else
				std::cout << '.';
		}
		std::cout << '\n';
	}

	std::cout << solution << '\n';

	return 0;
}