#include "Assembler.h"

Assembler::Assembler()
{
	symbolMap_ = CreateSymbolTable();
}

std::unordered_map<std::string, uint16_t> Assembler::CreateSymbolTable()
{
	std::unordered_map<std::string, uint16_t> symbolMap;

	//Add First 15 values
	for (int i = 0; i < 16; i++)
	{
		symbolMap.insert(std::pair<std::string, uint16_t>(std::format("R{}", i), i));
	}

	const auto predefined = std::vector{ "SP", "LCL", "ARG", "THIS", "THAT" };

	for (int i = 0; i < predefined.size(); i++)
	{
		symbolMap.insert(std::pair<std::string, uint16_t>(predefined[i], i));
	}

	//Screen Address
	symbolMap.insert(std::pair<std::string, uint16_t>("SCREEN", 16384));

	//Key Board Address
	symbolMap.insert(std::pair<std::string, uint16_t>("KDB", 24576));

	return symbolMap;
}

void Assembler::AddLables(std::unordered_map<std::string, uint16_t>& lables)
{
	symbolMap_.insert(lables.begin(), lables.end());
}
