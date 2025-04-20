#pragma once

#include <vector>
#include <string>
#include <unordered_map>

// Comparator for the pq. Longest string first
struct CompareByLength {
    bool operator()(const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) const {
        return a.first.length() < b.first.length(); // longest first string = higher priority
    }
};

// Function declarations
void parseInput(const std::string& input, std::vector<std::string>& tiles, std::vector<std::string>& designs);
uint64_t countArrangements(const std::string& design, int pos, const std::vector<std::string>& tiles, std::unordered_map<int, uint64_t>& memo);
