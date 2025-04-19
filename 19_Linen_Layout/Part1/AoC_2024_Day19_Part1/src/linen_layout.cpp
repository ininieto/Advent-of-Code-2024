/*
Advent of Code 2024 - 19.12.2024

Link to the problem : https://adventofcode.com/2024/day/19

Author of the solution : Inigo Nieto Cuadrado

*/

#include "linen_layout.h"

#include <iostream>
#include <sstream>
#include <unordered_set>

#include "common.h"

void parseInput(const std::string& input, std::vector<std::string>& tiles, std::vector<std::string>& designs) {

    std::istringstream iss(input);
    std::string line;

    // Read the first line
    if (std::getline(iss, line)) {
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ',')) {
            // Remove leading/trailing whitespace
            item.erase(0, item.find_first_not_of(" \t\n\r"));
            item.erase(item.find_last_not_of(" \t\n\r") + 1);
            tiles.push_back(item);
        }
    }

    // Skip the empty line
    std::getline(iss, line);

    // Read the remaining lines
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            designs.push_back(line);
        }
    }
}

int main() {

    // Read the input
    std::string example = Common::readInputText("../../resources/example.txt");
    std::string input = Common::readInputText("../../resources/input.txt");

    // Work with example
    const bool useExample = true;  // Set to false for real problem

    if (useExample)
        input = example;

    // Define the vectors 
    std::vector<std::string> tiles;     // Will contain the pieces to be combined
    std::vector<std::string> designs;   // Will contain the designs that we need to create

    // Parse the input
    parseInput(input, tiles, designs);

    // Define the counter for valid designs
    int possibleDesigns = 0;

    // Iterate all the designs
    for (const auto& design : designs) {

        // Debug
        std::cout << "---------------------- Current design: " << design << "-------------------------------\n";

        // Define a vector with the candidates
        std::vector<std::string> candidates;

        // Define a set with the already tested patterns
        std::unordered_set<std::string> visitedCandidates;

        // Try with all the tiles for each design
        for (const auto& tile : tiles) {

            int tileSize = tile.size();

            std::string sub = design.substr(0, tileSize);

            if (tile == sub)
                candidates.push_back(tile);
        }

        // If there are no candidates, skip
        if (candidates.empty())
            continue;

        bool designFound = false;

        // Now we have the first candidates. We need to work just with these candidates
        while (!designFound) {

            // With all the candidates, try with all the tiles
            for (int i = 0; i < candidates.size(); i++) {

                std::string candidate = candidates[i];

                // If already visited candidate, skip
                if (visitedCandidates.count(candidate))  continue;
                visitedCandidates.insert(candidate);

                // Debug
                std::cout << "Current candidate : " << candidate << '\n';

                // bool newCandidateFound = false;

                for (const auto& tile : tiles) {

                    // Get the next substr of the number of chars of the tile
                    int tileSize = tile.size();
                    std::string sub = design.substr(candidate.size(), tileSize);

                    // If the substr is equal than the tile, add a new candidate
                    if (sub == tile) {
                        // newCandidateFound = true;
                        std::string newCandidate = candidate + tile;

                        if (newCandidate == design) {
                            designFound = true;
                            break;
                        }
                        candidates.push_back(newCandidate);
                    }
                }

                // If design found, break
                if (designFound) {
                    possibleDesigns++;
                    break;
                }

                // Delete the current candidate and decrease the index
                candidates.erase(candidates.begin() + i);
                i--;
            }

            // If we reach here, it means the design is not possible
            break;
        }
    }

    
    std::cout << possibleDesigns << '\n';
	

	return 0;
}