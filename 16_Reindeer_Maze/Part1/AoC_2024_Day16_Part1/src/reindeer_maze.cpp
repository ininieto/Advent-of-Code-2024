/*
Advent of Code 2024 - 16.12.2024

Link to the problem : https://adventofcode.com/2024/day/16

Author of the solution : Inigo Nieto Cuadrado

*/

#include "reindeer_maze.h"

#include <iostream>
#include <queue>
#include <unordered_set>

#include "common.h"


int main() {

    // Read the input
    std::string example = Common::readInputText("../../resources/example.txt");
    std::string example2 = Common::readInputText("../../resources/example2.txt");
    std::string input = Common::readInputText("../../resources/input.txt");

    // Work with example
    // input = example2;

    // Define a grid
    size_t nrows = 0, ncols = 0;
    Common::getGridDimensions(input, nrows, ncols);

    std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols));
    Common::fillGrid(grid, input);

    // Define all the possible directions
    const std::vector<Coords> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // East, South, West, North

    // Find the starting and ending position
    Coords startPos, endPos;
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            if (grid[i][j] == 'S') {
                startPos = { i, j };
            }
            else if (grid[i][j] == 'E') {
                endPos = { i, j };
            }
        }
    }

    // Priority queue for Dijkstra
    std::priority_queue<Tile> pq;
    pq.push({ startPos, 0, 0 }); // Start facing East with 0 cost

    // Visited states (i, j, dir)
    std::unordered_set<std::string> visited;

    Tile currentTile;

    while (!pq.empty()) {

        currentTile = pq.top();
        pq.pop();

        // Generate a unique state identifier
        std::string stateId = std::to_string(currentTile.pos.i) + "," + std::to_string(currentTile.pos.j) + "," + std::to_string(currentTile.dir);

        // Skip if already visited
        if (visited.count(stateId)) continue;
        visited.insert(stateId);

        // Check if we've reached the end
        if (currentTile.pos == endPos)
            break;

        // Try moving forward
        Coords nextPos = { currentTile.pos.i + directions[currentTile.dir].i, currentTile.pos.j + directions[currentTile.dir].j };
        if (grid[nextPos.i][nextPos.j] != '#')
            pq.push({ nextPos, currentTile.dir, currentTile.dist + 1 });

        // Try rotating clockwise and counterclockwise
        pq.push({ {currentTile.pos.i, currentTile.pos.j}, (currentTile.dir + 1) % 4, currentTile.dist + 1000 });
        pq.push({ {currentTile.pos.i, currentTile.pos.j}, (currentTile.dir + 3) % 4, currentTile.dist + 1000 });
    }

    std::cout << "Lowest score: " << currentTile.dist << '\n';
    return 0;
}
