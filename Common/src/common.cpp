#include "common.h"

#include <fstream>
#include <iostream>

namespace Common {

    // Read input data from txt file
    std::string readInputText(const std::string &inputText) {

        std::fstream inputfile;
        std::string inputData;

        inputfile.open(inputText, std::ios::in);
        if (inputfile.is_open()) {
            std::string tp;

            while (getline(inputfile, tp)) {
                inputData += tp;
                inputData += '\n';
            }
        }
        return inputData;
    }

    // Function to split a std::string by a specific delimitator
    std::vector<std::string> split(std::string text, const std::string &delim) {

        std::vector<std::string> splittedText;
        size_t pos = 0;
        std::string token;

        while ((pos = text.find(delim)) != std::string::npos) {
            token = text.substr(0, pos);
            splittedText.push_back(token);
            text.erase(0, pos + delim.length());
        }

        if (text.length() > 0)
            splittedText.push_back(text);

        return splittedText;
    }

    // Function to get automatically the number of rows and columns
    void getGridDimensions(const std::string& input, size_t& nrows, size_t& ncols) {

        for (int i = 0; i < input.length(); i++) {
            if (input[i] == '\n' && ncols == 0)
                ncols = i;
            if (input[i] == '\n' && ncols > 0)
                nrows++;
        }
        //nrows ++;   // We must apply this correction
    }

    // Function to fill in the grid
    void fillGrid(std::vector<std::vector<char>>& grid, const std::string& input) {

        int nrows = grid.size(), ncols = grid[0].size();

        int strCounter = 0;

        for (int i = 0; i < nrows; i++) {
            for (int j = 0; j < ncols; j++) {

                if (input[strCounter] == '\n')
                    strCounter++;

                grid[i][j] = input[strCounter];
                strCounter++;
            }
        }
    }

    // Function to check if a position (i, j) is out of bounds
    bool outOfBounds(const Coords& pos, const size_t nrows, const size_t ncols) {
        return pos.i < 0 || pos.i >= nrows || pos.j < 0 || pos.j >= ncols;
    }

    std::vector<Coords> getSurroundings(Coords& pos, const size_t nrows, const size_t ncols) {

        std::vector<Coords> surroundings;

        Coords up = Coords(pos.i - 1, pos.j);
        Coords down = Coords(pos.i + 1, pos.j);
        Coords left = Coords(pos.i, pos.j - 1);
        Coords right = Coords(pos.i, pos.j + 1);

        if (!outOfBounds(up, nrows, ncols))
            surroundings.push_back(up);
        if (!outOfBounds(down, nrows, ncols))
            surroundings.push_back(down);
        if (!outOfBounds(left, nrows, ncols))
            surroundings.push_back(left);
        if (!outOfBounds(right, nrows, ncols))
            surroundings.push_back(right);

        return surroundings;
    }

    // Function to print a grid
    void printGrid(const std::vector<std::vector<char>>& grid){

        for (const auto& row : grid) {
            for (const auto& c : row) 
                std::cout << c;
            std::cout << '\n';
        }
        std::cout << "\n\n";
    }
}