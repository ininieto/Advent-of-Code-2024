#pragma once

#include <string>
#include <vector>

namespace Common {

	std::string readInputText(const std::string &inputText);
	std::vector<std::string> split(std::string text, const std::string &delim);
	void getGridDimensions(const std::string& input, int& nrows, int& ncols);
	void fillGrid(std::vector<std::vector<char>>& grid, const std::string& input);
}
