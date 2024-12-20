#pragma once

#include <vector>
#include <string>

#include "common.h"

struct Tile {
	char plant;
	int id;
	Coords pos;

	// Default constructor
	Tile() : plant('.'), id(-1), pos(Coords(-1, -1)) {};

	// Param constructor
	Tile(char p, Coords pos) : plant(p), id(-1), pos(pos) {};
};

void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input);
void findRegions(std::vector<std::vector<Tile>>& grid, std::vector<std::vector<Tile*>>& regions);