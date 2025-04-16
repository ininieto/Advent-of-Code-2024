/*
Advent of Code 2024 - 18.12.2024

Link to the problem : https://adventofcode.com/2024/day/18

Author of the solution : Inigo Nieto Cuadrado

*/

#include "ram_run.h"

#include <iostream>
#include <sstream>
#include <queue>
#include <unordered_set>

#include "common.h"

int main() {

    // Read the input
    std::string example = Common::readInputText("../../resources/example.txt");
    std::string input = Common::readInputText("../../resources/input.txt");

    // Work with example
    const bool useExample = false;  // Set to false for real problem

    if (useExample)
        input = example;

    // Define a grid
    int nrows, ncols;
    if (useExample) {
        nrows = 7;
        ncols = 7;
    }
    else {
        nrows = 71;
        ncols = 71;
    }

    std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols));

    // Initialize the grid to empty position (.)
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            grid[i][j] = '.';
        }
    }

    // Read the input and set the first 12 bytes as corrupted positions as #
    std::istringstream lineStream(input);
    std::string line;
    int byteCount = 0;
    int maxBytes;

    if (useExample)
        maxBytes = 12;
    else
        maxBytes = 1024;

    while (std::getline(lineStream, line)) {
        std::istringstream pairStream(line);
        std::string aStr, bStr; // Strings to contain the two numbers of the pair
        
        if (std::getline(pairStream, aStr, ',') && std::getline(pairStream, bStr)) {
            byteCount++;

            if (byteCount > maxBytes)
                break;

            int a = std::stoi(aStr);
            int b = std::stoi(bStr);

            // Set the position in the grid as corrupted
            grid[b][a] = '#';
        }
    }

    // Perform a Dijkstra from (0, 0) to (nrows - 1, ncols - 1)
    Coords startPos{ 0, 0 }, endPos{ nrows - 1, ncols - 1 };

    // Define all the possible directions
    const std::vector<Coords> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // East, South, West, North

    // Define the priority queue
    std::priority_queue<Tile> pq;
    pq.push({ startPos, 0, 0}); // Start facing East with 0 cost

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

        // Check if next pos is in bounds and not #
        if (!Common::outOfBounds(nextPos, nrows, ncols) && grid[nextPos.i][nextPos.j] != '#')   
            pq.push({ nextPos, currentTile.dir, currentTile.dist + 1 });

        // Try rotating clockwise and counterclockwise
        pq.push({ currentTile.pos, (currentTile.dir + 1) % 4, currentTile.dist });
        pq.push({ currentTile.pos, (currentTile.dir + 3) % 4, currentTile.dist });

    }

    std::cout << "Lowest score: " << currentTile.dist << '\n';

	return 0;
}