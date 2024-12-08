#pragma once

#include <string>
#include <vector>

void getRows(std::vector<std::vector<char>>& grid, std::vector<std::string>& rows);
void getCols(std::vector<std::vector<char>>& grid, std::vector<std::string>& cols);
void getDiags(const std::vector<std::vector<char>>& grid, std::vector<std::string>& diags);
int countOccurences(const std::string& line);