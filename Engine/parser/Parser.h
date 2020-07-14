#pragma once

#include "Common.h"

class Parser {
public:
	static std::map<std::string, std::string> parsePropertiesFile(std::string filename);
};