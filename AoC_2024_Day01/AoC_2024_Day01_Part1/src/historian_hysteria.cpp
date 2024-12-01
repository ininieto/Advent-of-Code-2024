/*
    Advent of Code 2024 - 01.12.2024

    Link to the problem: https://adventofcode.com/2024/day/1

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include "historian_hysteria.h"

#include <iostream> 
#include <algorithm>    // Needed for sort()

#include "common.h"

// Function to store the input data in vectors
void fillVectors(std::string input, std::vector<int>& vec1, std::vector<int>& vec2) {

    std::string line;
    size_t pos = 0;

    // Split the input string by scape lines
    while ((pos = input.find('\n')) != std::string::npos) {
        line = input.substr(0, pos);

        // Find the first number
        vec1.push_back(stoi(line.substr(0, line.find(' '))));

        // Find the second number
        for (size_t i = line.length(); i >= 0; i--) {
            if(line[i] == ' '){
                vec2.push_back(stoi(line.substr(i, line.length() - i)));
                break;
            }
        }

        // Delete the read line of the input string
        input.erase(0, pos + 1);
    }
}

int main(){

    // Store the example and input in a string
    std::string example = Common::readInputText("resources/example.txt");
    std::string input = Common::readInputText("resources/input.txt");

    // Store the first column in a vector and the second one in another
    std::vector<int> vec1, vec2;
    fillVectors(input, vec1, vec2);

    // Sort the vectors
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());

    // Find the total distance
    long int dist = 0;
    for (int i = 0; i < vec1.size(); i++) {
        dist += abs(vec1[i] - vec2[i]);
    }

    // Print the solution
    std::cout << dist << '\n';

    return 0;
}