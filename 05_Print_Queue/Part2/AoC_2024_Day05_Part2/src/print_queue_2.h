#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct Update {
	bool reordered;
	std::vector<int> vec;

	// Constructor
	Update(std::vector<int> v) : vec(v), reordered(false) {};
};

void parseOrderingRules(const std::string& line, std::unordered_map<int, std::vector<int>>& priority);
std::vector<int> parseUpdates(const std::string& line);