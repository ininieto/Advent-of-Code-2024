#pragma once

#include <vector>
#include <string>
#include <unordered_map>


void fillMap(std::unordered_map<uint64_t, uint64_t>& pebbles, const std::string& input);
std::pair<uint64_t, uint64_t> splitNum(uint64_t num);
int getNumDigits(uint64_t num);
void blink(std::unordered_map<uint64_t, uint64_t>& pebbles);