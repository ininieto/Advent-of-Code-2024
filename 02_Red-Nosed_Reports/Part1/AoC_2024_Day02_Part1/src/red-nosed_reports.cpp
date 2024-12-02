/*
    Advent of Code 2024 - 02.12.2024

    Link to the problem: https://adventofcode.com/2024/day/2

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include "red-nosed_reports.h"

#include <iostream>

#include "common.h"

// Function that converts the numbers from std::string to a vector of int
std::vector<int> toIntVector(const std::string &report) {

    std::vector<int> intReport;
    std::string temp;

    for (const char& c : report) {
        if (c != ' ')
            temp.push_back(c);
        else {
            intReport.push_back(stoi(temp));
            temp.clear();
        }
    }

    // Push_back the last element
    intReport.push_back(stoi(temp));

    return intReport;
}

/*
    A report will be considered safe if:
    - The levels are either all increasing or all decreasing.
    - Any two adjacent levels differ by at least one and at most three.
*/
bool checkSafe(const std::vector<int> &report) {

    int direction = 0;  // Variable that will determine increasing (1) or decreasing (-1)

    // Iterate over the levels
    for (int i = 1; i < report.size(); i++) {

        // Calculate the distance for a pair of adjacent levels
        int dist = report[i] - report[i - 1];

        // Guess if we are increasing or decreasing
        if (direction == 0 && dist != 0) 
            direction = dist / abs(dist);   // Direction will be 1 if increasing or -1 if decreasing

        // If no distance or high distance, directly return unsafe
        if (dist == 0 || abs(dist) > 3)
            return false;

        // If we detect a change in tendency, return unsafe
        if (dist > 0 && direction == -1 || dist < 0 && direction == 1)
            return false;
    }

    return true;

}

int main() {

    // Read the example and the input
    std::string example = Common::readInputText("../../resources/example.txt");
    std::string input = Common::readInputText("../../resources/input.txt");

    // Split the reports in a vector
    std::vector<std::string> reports = Common::split(input, "\n");

    // Check safety
    long int numSafeReports = 0;
    for (const std::string report : reports) 
        numSafeReports += checkSafe(toIntVector(report));   // Convert the report to a vector of ints
    
    // Print the solution
    std::cout << numSafeReports << '\n';

    return 0;
}