#pragma once

#include <string>
#include <vector>

struct Coords {
	int i, j;

	// Default constructor
	Coords() : i(-1), j(-1) {};

	// Constructor
	Coords(int i, int j) : i(i), j(j) {};

	// Equality operator for comparison
	bool operator==(const Coords& other) const {
		return i == other.i && j == other.j;
	}

	// Inequality operator
	bool operator!=(const Coords& other) const {
		return i != other.i || j != other.j;
	}
};

struct Tile {

	Coords pos;
	int dir;
	uint64_t dist;

	// Default constructor
	Tile() : pos(Coords(-1, -1)), dir(-1), dist(INT_MAX) {}

	// Param constructor
	Tile(Coords pos, int dir, uint64_t dist) : pos(pos), dir(dir), dist(dist) {}

	// Comparator to create the priority queue
	bool operator<(const Tile& other) const {
		return dist > other.dist;	// Smallest dist has the priority
	}
};


namespace Common {

	std::string readInputText(const std::string &inputText);
	std::vector<std::string> split(std::string text, const std::string &delim);
	void getGridDimensions(const std::string& input, size_t& nrows, size_t& ncols);
	void fillGrid(std::vector<std::vector<char>>& grid, const std::string& input);
	bool outOfBounds(const Coords& pos, const size_t nrows, const size_t ncols);
	std::vector<Coords> getSurroundings(Coords& pos, const size_t nrows, const size_t ncols);
	void printGrid(const std::vector<std::vector<char>>& grid);
}
