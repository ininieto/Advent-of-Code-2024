/*
Advent of Code 2024 - 14.12.2024

Link to the problem : https://adventofcode.com/2024/day/14

Author of the solution : Inigo Nieto Cuadrado

*/

#include "restroom_redoubt.h"

#include <iostream>

// Function to store the input in variables
void parseInput(const std::string& line, int& x, int& y, int& vx, int& vy) {

	std::string num;

	for (size_t pos = 0; pos < line.size(); pos++) {

		if (line[pos] == 'p' || line[pos] == 'v' || line[pos] == '=')
			continue;
		else if (line[pos] == ',' && x == -1) {
			x = stoi(num);
			num.clear();
		}
		else if (line[pos] == ' ') {
			y = stoi(num);
			num.clear();
		}
		else if (line[pos] == ',' && x > -1) {
			vx = stoi(num);
			num.clear();
		}
		else
			num += line[pos];
	}
	vy = stoi(num);
}

// Function to update the position of the robot
void updateRobot(Robot& robot, const size_t nrows, const size_t ncols){

	robot.pos.i += robot.v.i;
	robot.pos.j += robot.v.j;

	if (robot.pos.i < 0) 
		robot.pos.i = (int)nrows + robot.pos.i;
	
	if (robot.pos.i >= nrows)
		robot.pos.i -= (int)nrows;
	
	if (robot.pos.j < 0)
		robot.pos.j = (int)ncols + robot.pos.j;

	if (robot.pos.j >= ncols)
		robot.pos.j -= (int)ncols;
}


int main() {

	// Read the input
	std::string example = Common::readInputText("../../resources/example.txt");
	std::string input = Common::readInputText("../../resources/input.txt");

	// Work with example
	// input = example;

	// const size_t nrows = 7, ncols = 11;
	const size_t nrows = 103, ncols = 101;

	// Create a vector with Robots
	std::vector<Robot> robots;

	// Parse the input
	std::vector<std::string> lines = Common::split(input, "\n");

	for (const auto line : lines) {
	
		int x = -1, y = -1, vx = -1, vy = -1;
		parseInput(line, x, y, vx, vy);

		// Create a robot with this information
		robots.push_back(Robot(x, y, vx, vy));
	}

	for (int i = 0; i < 100; i++) {
		for (auto& robot : robots)
			updateRobot(robot, nrows, ncols);
	}

	// Count the robots per quadrant (q1 up-left, q2 up-right, q3 bottom-left, q4 bottom-right)
	uint64_t q1 = 0, q2 = 0, q3 = 0, q4 = 0;

	for (const auto& robot : robots) {

		if (robot.pos.i < nrows / 2 && robot.pos.j < ncols / 2)
			q1++;
		else if (robot.pos.i < nrows / 2 && robot.pos.j > ncols / 2)
			q2++;
		else if (robot.pos.i > nrows / 2 && robot.pos.j < ncols / 2)
			q3++;
		else if (robot.pos.i > nrows / 2 && robot.pos.j > ncols / 2)
			q4++;
	}

	uint64_t solution = 0;
	solution = q1 * q2 * q3 * q4;

	std::cout << solution << '\n';

	return 0;
}