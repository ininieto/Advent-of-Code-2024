/*
Advent of Code 2024 - 16.12.2024

Link to the problem : https://adventofcode.com/2024/day/16

Author of the solution : Inigo Nieto Cuadrado

*/

#include "reindeer_maze_2.h"

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>

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

    // Lowest distance (i, j, dir) -> dist
    std::unordered_map<std::string, int> lowestDist;

    // Map that relates a state with its previous optimal state / states
    std::unordered_map<std::string, std::unordered_set<std::string>> backtrack;

    // Set with the states that are ending of an optimal path
    std::unordered_set<std::string> endStates;

    // Optimal distance to the end Tile
    int bestDist = INT_MAX;

    Tile currentTile;

    while (!pq.empty()) {

        currentTile = pq.top();
        pq.pop();

        // Generate a unique state identifier
        std::string stateId = std::to_string(currentTile.pos.i) + "," + std::to_string(currentTile.pos.j) + "," + std::to_string(currentTile.dir);

        // Check if this position was already tracked
        if (lowestDist.find(stateId) == lowestDist.end())   // If untracked state, initialize to INT_MAX
            lowestDist[stateId] = INT_MAX;

        int dist = lowestDist[stateId];

        // Skip if greater distance
        if (currentTile.dist > dist) 
            continue;

        // Set the theoretical lowest distance
        lowestDist[stateId] = currentTile.dist;

        // Check if we've reached the end
        if (currentTile.pos == endPos) {

            if (currentTile.dist > bestDist) // Already tracked all the optimal paths
               break; 
            endStates.insert(stateId);
            bestDist = currentTile.dist;            // Update the best distance
        }

        // We know we are already in an optimal state, so we will add it to the backtrack map
        backtrack[stateId].insert(currentTile.prevState);
            
        // Try moving forward
        Coords nextPos = { currentTile.pos.i + directions[currentTile.dir].i, currentTile.pos.j + directions[currentTile.dir].j };
        Tile nextTile;
        if (grid[nextPos.i][nextPos.j] != '#') {
            nextTile = Tile(nextPos, currentTile.dir, currentTile.dist + 1);
            nextTile.prevState = stateId;
            pq.push(nextTile);
        }

        // Try rotating clockwise 
        nextTile = Tile(currentTile.pos, (currentTile.dir + 1) % 4, currentTile.dist + 1000);
        nextTile.prevState = stateId;
        pq.push(nextTile);
         
        // Try rotating counterclockwise
        nextTile = Tile(currentTile.pos, (currentTile.dir + 3) % 4, currentTile.dist + 1000);
        nextTile.prevState = stateId;
        pq.push(nextTile);
    }

    // Now we have the end states and the backtrack. We need to traverse it to find all the positions
    std::unordered_set<std::string> solutionPositions;
    
    // Queue to perform a BFS in the states
    std::queue<std::string> queue;
    
    // Initialize the queue with the end states
    for (const auto& state : endStates)
        queue.push(state);

    while (!queue.empty()) {

        std::string state = queue.front();
        queue.pop();

        if (state.empty())   continue;

        // Extract the position from the state (we don't care about the direction)
        size_t firstComma = state.find(',');
        size_t secondComma = state.find(',', firstComma + 1);

        std::string pos = state.substr(0, secondComma);

        // If that position was not tracked, add it
        if(!solutionPositions.count(pos))
            solutionPositions.insert(pos);

        // Add the next positions to the queue
        const auto nextStates = backtrack[state];

        for (const auto& nextState : nextStates)
            queue.push(nextState);

    }

    // Debug: print the grid
    for (const auto& pos : solutionPositions) {

        int i = std::stoi(pos.substr(0, pos.find(',')));
        int j = std::stoi(pos.substr(pos.find(',') + 1));
        grid[i][j] = 'O';
    }

    for (const auto& row : grid) {
        for (const auto& c : row) 
            std::cout << c;
        std::cout << '\n';
    }

    std::cout << "Solution: " << solutionPositions.size() << '\n';
    return 0;
}
