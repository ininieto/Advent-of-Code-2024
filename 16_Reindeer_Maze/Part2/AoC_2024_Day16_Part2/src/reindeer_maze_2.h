#pragma once

#include <vector>

#include "common.h"

struct Tile {

    Coords pos;
    int dir;
    uint64_t dist;
    std::string prevState;


    // Default constructor
    Tile() : pos(Coords(-1, -1)), dir(-1), dist(INT_MAX) {}

    // Param constructor
    Tile(Coords pos, int dir, uint64_t dist) : pos(pos), dir(dir), dist(dist) {}

    // Comparator to create the priority queue
    bool operator<(const Tile& other) const {
        return dist > other.dist;	// Smallest dist has the priority
    }

    // Equality operator
    bool operator==(const Tile& other) const {
        return pos == other.pos && dir == other.dir && dist == other.dist;
    }
};

