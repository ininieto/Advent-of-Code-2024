#pragma once

#include <vector>
#include <string>
#include <queue>

#include "common.h"

struct Tile {

	Coords pos;
	char c;
	uint64_t dist;
	Tile* prevTile;
	bool visited;

	// Default constructor
	Tile() : pos(Coords(-1, -1)), c('.'), dist(INT_MAX), prevTile(nullptr), visited(false) {}

	// Param constructor
	Tile(Coords pos, char c) : pos(pos), c(c), dist(INT_MAX), prevTile(nullptr), visited(false) {}
};
/*
// Comparator to create the priority queue
struct CompareDist {
	bool operator()(const Tile* a, const Tile* b) {
		return a->dist > b->dist;	// Smallest dist has the priority
	}
};
*/

void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input);
void printGrid(const std::vector<std::vector<Tile>>& grid);
// bool isQueued(std::priority_queue<Tile*, std::vector<Tile*>, CompareDist>& pq, const Tile* tile);
bool isInQueue(const std::vector<Tile*>& vecNextTiles, const Tile* tile);
void addTileToQueue(std::vector<Tile*>& vecNextTiles, Tile* tile);
void updateTile(std::vector<Tile*>& vecNextTiles, Tile* tile);