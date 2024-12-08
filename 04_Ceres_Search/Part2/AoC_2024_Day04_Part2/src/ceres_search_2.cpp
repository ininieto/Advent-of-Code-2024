/*
	Advent of Code 2024 - 04.12.2024

	Link to the problem: https://adventofcode.com/2024/day/4

	Author of the solution: Inigo Nieto Cuadrado

*/

#include "ceres_search_2.h"

#include <iostream>

#include "common.h"

// This function will find the letter 'A' and determine if there is an X-pattern surrounding it
int countOccurences(const std::vector<std::vector<char>>& grid) {

	int solution = 0;

	for (int i = 1; i < grid.size() - 1; i++) {
		for (int j = 1; j < grid[i].size() - 1; j++) {

			if (grid[i][j] == 'A') {
				if ((grid[i - 1][j - 1] == 'M' && grid[i + 1][j + 1] == 'S' || grid[i - 1][j - 1] == 'S' && grid[i + 1][j + 1] == 'M') &&
					(grid[i - 1][j + 1] == 'M' && grid[i + 1][j - 1] == 'S' || grid[i - 1][j + 1] == 'S' && grid[i + 1][j - 1] == 'M'))
					solution++;
			}
		}
	}

	return solution;
}

int main() {

	// Read the example and the input data
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Define a grid
	int nrows = 0, ncols = 0;
	Common::getGridDimensions(input, nrows, ncols);

	std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols));
	Common::fillGrid(grid, input);

	int solution = countOccurences(grid);

	std::cout << solution << '\n';
	return 0;
}