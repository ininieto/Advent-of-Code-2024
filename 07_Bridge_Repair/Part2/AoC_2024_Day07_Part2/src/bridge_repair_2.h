#pragma once

#define NUM_BITS	64

#include <string>
#include <vector>

uint64_t concatenate(uint64_t num1, uint64_t num2);
std::string toBase3(uint64_t num);
uint64_t countOperations(uint64_t result, const std::vector<uint64_t>& numbers);