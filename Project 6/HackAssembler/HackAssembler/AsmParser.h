#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "KMaps.h"


class AsmParser
{
public:
	AsmParser() {};

	std::vector<std::string> ParseFile(std::ifstream& file);

	std::vector<std::pair<std::string, uint32_t>> GetLables();

private:
	std::vector<std::string> parsedFile_;
	std::vector<std::pair<std::string, uint32_t>> lables_;
};

