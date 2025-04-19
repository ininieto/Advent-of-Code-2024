#pragma once

#include <vector>
#include <string>

// Comparator for the pq. Longest string first
struct CompareByLength {
	bool operator() (const std::string& a, const std::string& b) const {
		return a.length() < b.length();
	}
};

// Function declarations
void parseInput(const std::string& input, std::vector<std::string>& tiles, std::vector<std::string>& designs);
