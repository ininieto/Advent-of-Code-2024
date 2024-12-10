#pragma once

#include <string>
#include <vector>
#include <unordered_map>

void parseOrderingRules(const std::string& line, std::unordered_map<int, std::vector<int>>& priority);
std::vector<int> parseUpdates(const std::string& line);