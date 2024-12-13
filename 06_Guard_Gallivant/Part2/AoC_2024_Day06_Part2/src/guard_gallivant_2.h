#pragma once

#include <string>
#include <vector>

struct Coords {
	int i, j;

	// Constructor
	Coords() : i(-1), j(-1) {}
	Coords(int i, int j) : i(i), j(j) {}
};

struct Tile {

	char c;
	std::vector<Coords> directions;	// There might be several directions
};

void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input);
Coords turnRight(const Coords& currentDir);
bool outOfBounds(const Coords& pos, int nrows, int ncols);
bool checkLoop(std::vector<std::vector<Tile>> grid, Coords pos, Coords obstaclePos, int nrows, int ncols);
