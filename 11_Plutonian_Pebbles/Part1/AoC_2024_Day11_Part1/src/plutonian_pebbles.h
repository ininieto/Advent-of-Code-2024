#pragma once

#include <vector>
#include <string>

void fillVec(std::vector<uint64_t>& vec, const std::string& input);
std::pair<uint64_t, uint64_t> splitNum(uint64_t num);
int getNumDigits(uint64_t num);
void blink(std::vector<uint64_t>& vec);