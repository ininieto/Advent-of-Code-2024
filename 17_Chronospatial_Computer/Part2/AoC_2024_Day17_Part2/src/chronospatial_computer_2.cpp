/*
Advent of Code 2024 - 17.12.2024

Link to the problem : https://adventofcode.com/2024/day/17

Author of the solution : Inigo Nieto Cuadrado

*/

/* 10935550000 is too low */

#include "chronospatial_computer_2.h"

#include <unordered_map>

#include "common.h"

std::vector<int> programToVector(const std::string& program){

    std::vector<int> vecProgram(program.size());

    for (int i = 0; i < program.size(); i++)
        vecProgram[i] = program[i] - '0';

    return vecProgram;
}


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

// Function that will check if the output vector can become the reference
bool checkValidOutput(const std::vector<int>& ref, const std::vector<int>& out){

    size_t len = out.size();

    for (int i = 0; i < len; i++) {
        if (ref[i] != out[i])
            return false;
    }
    return true;
}

int main() {

    // Read the input
    std::string example = Common::readInputText("../../resources/example.txt");
    std::string example2 = Common::readInputText("../../resources/example_2.txt");
    std::string input = Common::readInputText("../../resources/input.txt");

    // Work with example
    // input = example2;

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

    // Define a vector with the elements of the program
    std::vector<int> vecProgram = programToVector(program);

    // Vector solution for the first part
    std::vector<int> ref = { 4,6,3,5,6,3,5,2,1,0 };  // Example
    // std::vector<int> ref = {5, 7, 3, 0};  // Example 2
    // std::vector<int> ref = { 1,5,0,1,7,4,1,0,3 };   // Real problem

    // Iteration variable for regA
    uint64_t i = 1546330000000;

    // Variable to end the loop
    bool endLoop = false;

    while (!endLoop) {

        // Debug
        if(i % 10000000 == 0)
            std::cout << i << '\n';

        if (i == 2024) {
            i++;
            continue;
        }

        if (i == 728)
            std::cout << " ";

        // Try with a new value for regA
        regA = i;

        // Read the instructions
        int instructionPointer = 0;
        std::vector<int> output;

        while (instructionPointer < endPos) {

            int instruction = program[instructionPointer] - '0';
            int op = program[instructionPointer + 1] - '0';

            bool newOut = false;

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
            else if (instruction == 5){
                output.push_back(combo(op, regA, regB, regC) % 8);
                newOut = true;
            }
            // bdv
            else if (instruction == 6)
                regB = regA / pow(2, combo(op, regA, regB, regC));
            // cdv
            else if (instruction == 7)
                regC = regA / pow(2, combo(op, regA, regB, regC));

            instructionPointer += 2;

            // If we added a new number to the vector, check if it is correct
            if (newOut && !checkValidOutput(vecProgram, output))
                break;
        }

        if (vecProgram == output) {
            endLoop = true;
            break;
        }

        // Increase i
        i++;
    }

    std::cout << i << '\n';

}

