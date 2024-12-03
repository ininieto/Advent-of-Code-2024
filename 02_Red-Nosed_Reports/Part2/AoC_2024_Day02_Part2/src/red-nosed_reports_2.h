#pragma once

#include <vector>
#include <string>

std::vector<int> toIntVector(const std::string& report);
bool checkSafe(const std::vector<int> &report);
bool problemDampener(std::vector<int> &report);