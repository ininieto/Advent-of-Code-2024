/*
    Advent of Code 2024 - 01.12.2024

    Link to the problem: https://adventofcode.com/2024/day/1

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include "historian_hysteria_2.h"

#include <iostream> 

#include "common.h"


// Function to store the input data in vectors
void fillVectors(std::string input, std::vector<int> &vec, std::unordered_map<int, int> &repetitions) {

    std::string line;
    size_t pos = 0;

    // Split the input string by scape lines
    while ((pos = input.find('\n')) != std::string::npos) {
        line = input.substr(0, pos);

        // Find the first number
        vec.push_back(stoi(line.substr(0, line.find(' '))));

        // Count the times a number appear in the second column
        for (size_t i = line.length(); i >= 0; i--) {
            if (line[i] == ' ') {
                repetitions[stoi(line.substr(i, line.length() - i))]++; // Indexing a position that does not exist will create it, so no problem
                break;
            }
        }

        // Delete the read line of the input string
        input.erase(0, pos + 1);
    }
}

int main() {

    // Store the example and input in a string
    std::string example = Common::readInputText("../resources/example.txt");
    std::string input = Common::readInputText("../resources/input.txt");

    // Declare a vector for the first column and a hashmap for the second one
    std::vector<int> vec;
    std::unordered_map<int, int> repetitions;   // It will count how many times a number appears in the second column

    // Fill the vector and the hashmap
    fillVectors(input, vec, repetitions);

    // Compute the similarity
    long int similarity = 0;
    for (const int &e : vec) {
        similarity += e * repetitions[e];   // If the index didn't exist, it will automatically initialize to 0
    }

    // Print the solution
    std::cout << similarity << '\n';
    
    return 0;
}