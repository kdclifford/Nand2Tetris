#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "KMaps.h"

const uint16_t k_MaxAddress = 0b0111'1111'1111'1111;

class Assembler
{
public:
	Assembler();
	std::vector<uint16_t> ParseFile(std::vector<std::string> file, std::vector<std::pair<std::string, uint32_t>>& lables);

private:
	uint16_t varibleAddress_;
};

