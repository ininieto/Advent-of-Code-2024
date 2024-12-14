#pragma once

#include <string>
#include <vector>

struct Tile {
	char c;
	bool isAntinode;

	// Constructor
	Tile() : c(' '), isAntinode(false) {};
	Tile(char c) : c(c), isAntinode(false) {};
};

void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input);
