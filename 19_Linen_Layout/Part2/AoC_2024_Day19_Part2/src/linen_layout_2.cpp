/*
Advent of Code 2024 - 19.12.2024

Link to the problem : https://adventofcode.com/2024/day/19

Author of the solution : Inigo Nieto Cuadrado

*/

#include "linen_layout_2.h"

#include <iostream>
#include <sstream>

#include "common.h"

// Function that parses the input and fills a vector with the tiles and other with the designs
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

// Recursive function that will profit memoization to count all the possible arrangements for a design
uint64_t countArrangements(const std::string& design, int pos, const std::vector<std::string>& tiles, std::unordered_map<int, uint64_t>& memo){

    // If we reached the end of the design, valid arrangement
    if (pos == design.size())
        return 1;

    // If cached
    if (memo.count(pos))
        return memo[pos];

    uint64_t result = 0;
    for (const auto& tile : tiles) {
        if (design.substr(pos, tile.size()) == tile) {
            result += countArrangements(design, pos + tile.size(), tiles, memo);
        }
    }

    // Cache result
    memo[pos] = result;

    return result;
}

int main() {

    // Read the input
    std::string example = Common::readInputText("../../resources/example.txt");
    std::string input = Common::readInputText("../../resources/input.txt");

    // Work with example
    const bool useExample = false;  // Set to false for real problem

    if (useExample)
        input = example;

    // Define the vectors 
    std::vector<std::string> tiles;     // Will contain the pieces to be combined
    std::vector<std::string> designs;   // Will contain the designs that we need to create

    // Parse the input
    parseInput(input, tiles, designs);

    // Define the counter for valid arrangements
    uint64_t possibleArrangements = 0;

    // Iterate all the designs
	for (const auto& design : designs) {

        // Define a map for memoization
        std::unordered_map<int, uint64_t> memo;

        possibleArrangements += countArrangements(design, 0, tiles, memo);
	}

    std::cout << possibleArrangements << '\n';

    return 0;
}