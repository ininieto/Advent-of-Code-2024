/*
	Advent of Code 2024 - 04.12.2024

	Link to the problem: https://adventofcode.com/2024/day/4

	Author of the solution: Inigo Nieto Cuadrado

*/

#include "ceres_search.h"

#include <iostream>

#include "common.h"

// Function to extract the rows 
void getRows(std::vector<std::vector<char>>& grid, std::vector<std::string>& rows) {

	for (const auto& row : grid) 
		rows.emplace_back(row.begin(), row.end());
}

// Function to extract the columns
void getCols(std::vector<std::vector<char>>& grid, std::vector<std::string>& cols) {

	for (int i = 0; i < grid.size(); i++) {
		std::string col;
		for (int j = 0; j < grid[i].size(); j++)
			col += grid[j][i];
		cols.push_back(col);
	}

}

// Function to extract all diagonals as strings
void getDiags(const std::vector<std::vector<char>>& grid, std::vector<std::string>& diags) {

	int n = grid.size();

	// Top-left to bottom-right diagonals
	for (int start = 0; start <= 2 * (n - 1); ++start) {
		std::string diagonal;
		for (int i = 0; i < n; ++i) {
			int j = start - i;
			if (j >= 0 && j < n) 
				diagonal += grid[i][j];
		}
		if (!diagonal.empty()) 
			diags.push_back(diagonal);
	}

	// Top-right to bottom-left diagonals
	for (int start = -(n - 1); start <= (n - 1); ++start) {
		std::string diagonal;
		for (int i = 0; i < n; ++i) {
			int j = i - start;
			if (j >= 0 && j < n) 
				diagonal += grid[i][j];
		}
		if (!diagonal.empty()) 
			diags.push_back(diagonal);
	}
}


// This function will receive an input line and find coincidences of a pattern on it
int countOccurences(const std::string& line) {

	int count = 0;

	for (size_t pos = 0; pos < line.length(); pos++) {
		if ((line[pos] == 'X' && line.substr(pos, 4) == "XMAS") || (line[pos] == 'S' && line.substr(pos, 4) == "SAMX")) 
			count++;
	}

	return count;
}

int main() {

	// Read the example and the input data
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// Define a grid
	int nrows = 0, ncols = 0;
	Common::getGridDimensions(input, nrows, ncols);

	std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols));
	Common::fillGrid(grid, input);

	// Define a rows, cols and diagonals vector
	std::vector<std::string> rows, cols, diags;

	// Fill these vectors
	getRows(grid, rows);
	getCols(grid, cols);
	getDiags(grid, diags);

	long int solution = 0;

	// Find occurrences in the rows
	for (const auto& row : rows) 
		solution += countOccurences(row);

	// Find occurrences in the cols
	for (const auto& col : cols) {
		solution += countOccurences(col);
	}

	// Find occurrences in the diags
	for (const auto& diag : diags) {
		solution += countOccurences(diag);
	}

	std::cout << solution << '\n';
	return 0;
}