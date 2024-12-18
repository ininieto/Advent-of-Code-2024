#pragma once

#include <vector>

#include "common.h"

struct Tile {

	int height;
	Coords pos;
	std::vector<Tile*> prevTiles;
	bool visited;

	// Default constructor
	Tile() : height(-1), pos(Coords(-1, -1)), prevTiles(), visited(false) {};

	// Param constructor
	Tile(int height, Coords pos) : height(height), pos(pos), prevTiles(), visited(false) {};
};

void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input);
std::vector<Coords> getSurroundings(Coords& pos, const size_t nrows, const size_t ncols);
int getTrailheadScore(std::vector<std::vector<Tile>> grid, Coords pos);
