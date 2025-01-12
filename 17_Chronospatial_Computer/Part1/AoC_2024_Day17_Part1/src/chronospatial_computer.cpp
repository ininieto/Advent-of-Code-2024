/*
Advent of Code 2024 - 17.12.2024

Link to the problem : https://adventofcode.com/2024/day/17

Author of the solution : Inigo Nieto Cuadrado

*/

#include "chronospatial_computer.h"

#include <unordered_map>

#include "common.h"

// Function to return the combo of an operand
uint64_t combo(int op, uint64_t regA, uint64_t regB, uint64_t regC){

    if (op == 4)
        return regA;
    if (op == 5)
        return regB;
    if (op == 6)
        return regC;

    // If op is 0, 1, 2, 3
    return op;
}



int main() {

    // Read the input
    std::string example = Common::readInputText("../../resources/example.txt");
    std::string input = Common::readInputText("../../resources/input.txt");

    // Work with example
    // input = example;

    // Define the variables for the registers
    uint64_t regA, regB, regC;

    std::string program;

    // Parse the input
    std::vector<std::string> lines = Common::split(input, "\n");

    for (const auto& line : lines) {

        if (line.empty())
            continue;
        
        size_t colonPos = line.find(':');
        std::string text = line.substr(0, colonPos);

        if (text == "Register A") 
            regA = std::stoull(line.substr(colonPos + 2));
        else if (text == "Register B") 
            regB = std::stoull(line.substr(colonPos + 2));
        else if (text == "Register C") 
            regC = std::stoull(line.substr(colonPos + 2));
        else 
            program = line.substr(colonPos + 2);
    }

    // Eliminate the commas from the program string 
    size_t endPos = program.length();
    for (size_t pos = 0; pos < endPos; pos++) {
        if (program[pos] == ',') {
            program.erase(program.begin() + pos);
            endPos--;
        }
    }

    // Read the instructions
    int instructionPointer = 0;
    std::vector<int> output;

    while (instructionPointer < endPos) {

        int instruction = program[instructionPointer] - '0';
        int op = program[instructionPointer + 1] - '0';

        // adv
        if (instruction == 0)
            regA /= (pow(2, combo(op, regA, regB, regC)));
        // bxl
        else if (instruction == 1)
            regB = regB ^ op;
        // bst
        else if (instruction == 2)
            regB = combo(op, regA, regB, regC) % 8;
        // jnz
        else if (instruction == 3)
            instructionPointer = (regA != 0) ? op - 2 : instructionPointer; // Minus 2 because we add 2 later
        // bxc
        else if (instruction == 4)
            regB = regB ^ regC;
        // out
        else if (instruction == 5)
            output.push_back(combo(op, regA, regB, regC) % 8);
        // bdv
        else if (instruction == 6)
            regB = regA / pow(2, combo(op, regA, regB, regC));
        // cdv
        else if(instruction == 7)
            regC = regA / pow(2, combo(op, regA, regB, regC));

        instructionPointer += 2;

    }

    // Print the output
    for (const auto& e : output)
        std::cout << e << ',';

    return 0;
}

