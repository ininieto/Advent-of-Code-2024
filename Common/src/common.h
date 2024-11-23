#pragma once

#include <string>
#include <vector>

namespace Common {

	std::string readInputText(std::string inputText);
	std::vector<std::string> split(std::string text, std::string delim);
}
