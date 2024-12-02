#pragma once

#include <string>
#include <vector>

namespace Common {

	std::string readInputText(const std::string &inputText);
	std::vector<std::string> split(std::string text, const std::string &delim);
}
