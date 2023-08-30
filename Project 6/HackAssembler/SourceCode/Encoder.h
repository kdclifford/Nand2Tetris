#pragma once

#include "HelperFuncs.h"
#include "Commands.h"


namespace Encoder
{

	std::vector<uint16_t> TranslateASM(std::vector<Instruction>& instructions, std::unordered_map<std::string, uint16_t>& symbolTable)
	{
		uint16_t varibleAddress = 16;
		std::vector<uint16_t> binaryContainer;
		for (const auto instruction : instructions)
		{
			switch (instruction.type)
			{
			case cmd_type::LAddress:
			{
				auto binary = symbolTable.find(instruction.signature);
				if (binary != symbolTable.end())
				{
					binaryContainer.push_back(binary->second);
				}
				else
				{
					binaryContainer.push_back(varibleAddress++);
				}
				break;
			}
			case cmd_type::Address:
			{
				auto binary = symbolTable.find(instruction.signature);
				if (binary != symbolTable.end())
				{
					binaryContainer.push_back(binary->second);
				}
				else
				{
					binaryContainer.push_back(stoi(instruction.signature));
				}
				break;
			}
			case cmd_type::C0:
			{
				auto comp = Commands::comp.find(instruction.signature)->second;
				auto dest = Commands::dest.find(instruction.signature2)->second;
				auto jump = Commands::jump.find(instruction.signature3)->second;

				uint16_t binary = (comp | dest | jump);


				binaryContainer.push_back(binary);

				break;
			}
			case cmd_type::C1:
			{
				uint16_t dest = 0;
				
				for (auto letter : instruction.signature)
				{
					dest |= Commands::dest.find(std::string(1, letter))->second;
				}


				auto comp = Commands::comp.find(instruction.signature2)->second;
				uint16_t jump = 0;

				uint16_t binary = (comp | dest | jump);


				binaryContainer.push_back(binary);

				break;
			}
			case cmd_type::C2:
			{
				auto comp = Commands::comp.find(instruction.signature)->second;
				auto jump = Commands::jump.find(instruction.signature2)->second;
				uint16_t dest = 0;

				uint16_t binary = (comp | dest | jump);


				binaryContainer.push_back(binary);

				break;
			}

			}
		}

		return binaryContainer;
	}
}
