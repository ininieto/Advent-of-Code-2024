#pragma once

#include <iostream>
#include <vector>

std::vector<int> programToVector(const std::string& program);
uint64_t combo(int op, uint64_t regA, uint64_t regB, uint64_t regC);
bool checkValidOutput(const std::vector<int>& ref, const std::vector<int>& out);
