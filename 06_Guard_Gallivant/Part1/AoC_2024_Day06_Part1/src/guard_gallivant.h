#pragma once

struct Coords {
	int i, j;

	// Constructor
	Coords() : i(-1), j(-1) {}
	Coords(int i, int j) : i(i), j(j) {}
};

Coords turnRight(const Coords& currentDir);
bool outOfBounds(const Coords& pos, int nrows, int ncols);