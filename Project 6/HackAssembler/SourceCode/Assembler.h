#pragma once
#include <unordered_map>
#include <format>

class  Assembler
{
public:
	Assembler();

	std::unordered_map<std::string, uint16_t> symbolMap_;

	std::unordered_map<std::string, uint16_t> CreateSymbolTable();

	void AddLables(std::unordered_map<std::string, uint16_t>& lables);
};