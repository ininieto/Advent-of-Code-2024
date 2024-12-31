#pragma once

#include <vector>

#include "common.h"

void fillGrid(std::vector<std::vector<char>>& grid, const std::string& input);
void move(Coords& pos, Coords dir, std::vector<std::vector<char>>& grid);