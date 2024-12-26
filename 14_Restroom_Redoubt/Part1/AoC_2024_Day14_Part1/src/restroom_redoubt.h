#pragma once

#include <vector>

#include "common.h"


struct Robot {

	Coords pos;
	Coords v;

	// Default constructor
	Robot() : pos(Coords(-1, -1)), v(Coords(-1, -1)) {};

	// Param constructor
	Robot(int x, int y, int vx, int vy) : pos(Coords(y, x)), v(Coords(vy, vx)) {}
};

// Function declarations
void parseInput(const std::string& line, int& x, int& y, int& vx, int& vy);
void updateRobot(Robot& robot, const size_t nrows, const size_t ncols);