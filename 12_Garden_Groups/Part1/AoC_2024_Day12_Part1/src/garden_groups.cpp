/*
Advent of Code 2024 - 12.12.2024

Link to the problem : https://adventofcode.com/2024/day/12

Author of the solution : Inigo Nieto Cuadrado

*/

#include "garden_groups.h"

#include <iostream>
#include <unordered_map>

/*
	Problem: I need to distinguish areas of plants, not all the plants of the same type.

	I guess I will need to create a struct Tile and make it have a boolean "visited" or something similar, so to 
	gather all the areas. Plus, I won't use the letters to group them in the hashmap, I will need to use numerical IDs

*/

// Function to fill in the grid
void fillGrid(std::vector<std::vector<Tile>>& grid, const std::string& input) {

	size_t nrows = grid.size(), ncols = grid[0].size();

	int strCounter = 0;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {

			if (input[strCounter] == '\n')
				strCounter++;

			grid[i][j] = Tile(input[strCounter], Coords(i, j));
			strCounter++;
		}
	}
}

// Function to find all the Coords that belong to each region
void findRegions(std::vector<std::vector<Tile>>& grid, std::vector<std::vector<Tile*>>& regions){

	const size_t nrows = grid.size(), ncols = grid[0].size();

	int currentID = -1;
	std::vector<Tile*> currentRegion;

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {

			// Define a pointer to the current Tile
			Tile* currentTile = &grid[i][j];

			// If the plant is already tracked, simply skip it
			if (currentTile->id > -1)
				continue;

			// Initialize a region
			currentID++;
			currentTile->id = currentID;
			currentRegion.push_back(currentTile);

			// Vector with the next tiles to be scanned
			std::vector<Tile*> nextTiles;

			nextTiles.push_back(currentTile);

			while (!nextTiles.empty()) {

				// Update the current Tile
				currentTile = nextTiles[0];

				// Erase the current Tile from the vector
				nextTiles.erase(nextTiles.begin());

				// Get the surrounding Tiles
				std::vector<Coords> surroundings = Common::getSurroundings(currentTile->pos, nrows, ncols);

				// Check if they have the same plant as the current one
				for (const auto& s : surroundings) {
					Tile* surroundingTile = &grid[s.i][s.j];
					
					if (surroundingTile->plant == currentTile->plant && surroundingTile->id == -1) {
						surroundingTile->id = currentTile->id;
						nextTiles.push_back(surroundingTile);
						currentRegion.push_back(surroundingTile);
					}
				}
			}

			// After all the Plants belonging to a Region were found, reset the currentRegion
			regions.push_back(currentRegion);
			currentRegion.clear();
		}
	}
}

int main() {

	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Save the input in a grid
	size_t nrows = 0, ncols = 0;
	Common::getGridDimensions(input, nrows, ncols);
	std::vector<std::vector<Tile>> grid(nrows, std::vector<Tile>(ncols));
	fillGrid(grid, input);

	// Get different areas of grass and label their id
	std::vector<std::vector<Tile*>> regions;	// Will contain the Coords  of the different regions
	findRegions(grid, regions);

	// Declare a map for the Area and another for Perimeter
	std::unordered_map<int, uint64_t> area;
	std::unordered_map<int, uint64_t> perim;

	// Iterate all over the regions
	for (const auto& region : regions) {

		// Get the area of the region
		area[region[0]->id] = region.size();

		// Get the perimeter of the region
		for (const auto& plant : region) {

			Coords pos = plant->pos;

			std::vector<Coords> surroundings = { Coords(pos.i - 1, pos.j) ,		// Up
												 Coords(pos.i + 1, pos.j) ,		// Down	
												 Coords(pos.i, pos.j - 1) ,		// Left
												 Coords(pos.i, pos.j + 1) };	// Right

			for (auto& s : surroundings) {
				if (Common::outOfBounds(s, nrows, ncols) || grid[s.i][s.j].id != plant->id)
					perim[region[0]->id]++;
			}
		}
	}

	// Get the total cost
	uint64_t totalCost = 0;

	for (const auto& plant : area) {
		int plantID = plant.first;
		totalCost += (area[plantID] * perim[plantID]);
	}

	std::cout << totalCost;

	return 0;
}

