/*
Advent of Code 2024 - 15.12.2024

Link to the problem : https://adventofcode.com/2024/day/15

Author of the solution : Inigo Nieto Cuadrado

*/

#include "warehouse_woes_2.h"

#include <iostream>
#include <unordered_map>

// Function to fill in the grid
void fillGrid(std::vector<std::vector<char>>& grid, const std::string& input) {

	size_t nrows = grid.size(), ncols = grid[0].size();

	int strCounter = 0;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j += 2) {

			if (input[strCounter] == '\n')
				strCounter++;

			char c = input[strCounter];

			if (c == '#') {
				grid[i][j] = '#';
				grid[i][j + 1] = '#';
			}
			else if (c == 'O') {
				grid[i][j] = '[';
				grid[i][j + 1] = ']';
			}
			else if (c == '.') {
				grid[i][j] = '.';
				grid[i][j + 1] = '.';
			}
			else if (c == '@') {
				grid[i][j] = '@';
				grid[i][j + 1] = '.';
			}
			strCounter++;
		}
	}
}

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

		// If direction is left/right
		if (dir.i == 0) {

			// Get the number of consecutive boxes ahead (actually the positions that are related to boxes. [] are two positions = 2 boxes)
			int numBoxes = 0;

			while (grid[nextPos.i][nextPos.j] == '[' || grid[nextPos.i][nextPos.j] == ']') {
				numBoxes++;
				nextPos = Coords(nextPos.i + dir.i, nextPos.j + dir.j);

				// If there is a wall after some boxes, simply return
				if (grid[nextPos.i][nextPos.j] == '#')
					return;
			}

			// Move the elements from last to first
			for (int i = numBoxes; i >= 0; i--) {

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
		// If direction is up/down
		else {

			// Get the adjacent part of the box
			Coords nextAdjacent = (grid[nextPos.i][nextPos.j] == ']') ? Coords(nextPos.i, nextPos.j - 1) : Coords(nextPos.i, nextPos.j + 1);

			// We must now also check if the adjacent box has boxes ahead
			std::vector<Coords> nextBoxes = { nextPos, nextAdjacent };
			std::vector<Coords> tempNextBoxes = nextBoxes;				// Temporal vector to find all the boxes that we must move (BFS)

			// In this while loop we will capture all the boxes that must be moved
			while (!tempNextBoxes.empty()) {

				Coords currentBox = tempNextBoxes[0];			// Examine the first box in the vector
				tempNextBoxes.erase(tempNextBoxes.begin());		// Erase this box from the vector

				Coords currentNext(currentBox.i + dir.i, currentBox.j + dir.j);

				// Check if the current box has a box ahead
				if (grid[currentNext.i][currentNext.j] == '#') 		// If we find a Wall we don't move
					return;
				else if (grid[currentNext.i][currentNext.j] == '[' || grid[currentNext.i][currentNext.j] == ']') {	// If there are boxes ahead

					// If it is not already, add it to the vector
					if (std::find(nextBoxes.begin(), nextBoxes.end(), currentNext) == nextBoxes.end()) {

						nextBoxes.push_back(currentNext);
						tempNextBoxes.push_back(currentNext);

						// Add the adjacent

						Coords adjacent = (grid[currentNext.i][currentNext.j] == '[') ? Coords(currentNext.i, currentNext.j + 1) : Coords(currentNext.i, currentNext.j - 1);

						nextBoxes.push_back(adjacent);
						tempNextBoxes.push_back(adjacent);
					}
				}
			}

			// Move all the boxes
			for (int i = nextBoxes.size() - 1; i >= 0; i--) {

				const auto& box = nextBoxes[i];

				grid[box.i + dir.i][box.j + dir.j] = grid[box.i][box.j];
				grid[box.i][box.j] = '.';
			}

			// Move the current position
			grid[pos.i][pos.j] = '.';
			pos = nextPos;
			grid[nextPos.i][nextPos.j] = '@';
		}
	}
}

int main() {

	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string smallExample = Common::readInputText("../../resources/smallExample.txt");
	std::string smallExample2 = Common::readInputText("../../resources/smallExample2.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Divide the input in grid and instructions
	std::string gridInput = input.substr(0, input.find("\n\n") + 1);
	std::string instructions = input.substr(input.find("\n\n") + 2);

	// Define a grid
	size_t nrows = 0, ncols = 0;
	Common::getGridDimensions(gridInput, nrows, ncols);

	// Duplicate the number of columns
	ncols *= 2;

	std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols));
	fillGrid(grid, gridInput);

	// std::cout << "Initial state:\n";
	// Common::printGrid(grid);

	// Get the starting position
	Coords pos;
	for (size_t i = 0; i < nrows; i++) {
		for (size_t j = 0; j < ncols; j++) {
			if (grid[i][j] == '@') {
				pos = Coords((int)i, (int)j);
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

		// Debug
		// std::cout << "Move " << c << ":\n";
		// Common::printGrid(grid);
	}


	// Calculate the GPS Coordinates
	uint64_t solution = 0;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (grid[i][j] == '[')
				solution += 100 * i + j;
		}
	}

	std::cout << solution;

	return 0;
}


