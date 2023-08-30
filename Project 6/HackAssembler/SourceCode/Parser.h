#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

#include <regex>
#include <format>

//#include "HelperFuncs.h"
#include "Instruction.h"

const std::regex comment{ "\/\/.+" };
const std::regex equalJump{ "^\s*([AMD]+)=(\d|[AMD][\-\+]\d|[AMD+-]+);([A-Z]{3})\s*$" };
const std::regex jump{ "^\s*([AMD0]);([A-Z]{3})\s*$" };
const std::regex equal{ "^\s*([AMD]*)=(\d|[AMD][\-\+]\d|[AMD+-]*)\s*$" };
const std::regex lable{ "\\((\\S+)\\)" };
const std::regex rAddress{ "^\s*@(R[0-9][0-5]|R[0-9])\s*$" };
const std::regex nAddress{ "^\s*@(\d*)\s*$" };
const std::regex lAddress{ "^\s*@(\\S*)\s*$" };

namespace Parser {

	Instruction ParseLine(std::string& line)
	{
		Instruction instruction;

		std::smatch m;

		//Helpers::trim(line);

		if (std::regex_search(line, m, lable))
		{
			instruction.type = cmd_type::Lable;
			instruction.signature = m[1];
		}
		else
		{
			if (std::regex_search(line, m, jump))
			{
				instruction.type = cmd_type::C2;
				instruction.signature = m[1];
				instruction.signature2 = m[2];
			}
			else if (std::regex_search(line, m, equalJump))
			{
				instruction.type = cmd_type::C0;
				instruction.signature = m[1];
				instruction.signature2 = m[2];
				instruction.signature3 = m[3];
			}
			else if (std::regex_search(line, m, equal))
			{
				instruction.type = cmd_type::C1;
				instruction.signature = m[1];
				instruction.signature2 = m[2];
			}
			else if (std::regex_search(line, m, rAddress) || std::regex_search(line, m, nAddress))
			{
				instruction.type = cmd_type::Address;
				instruction.signature = m[1];
			}
			else if (std::regex_search(line, m, lAddress))
			{
				instruction.type = cmd_type::LAddress;
				instruction.signature = m[1];
			}
			else if (std::regex_search(line, m, lAddress))
			{
				instruction.type = cmd_type::Lable;
				instruction.signature = m[1];
			}
		}
		return instruction;
	}


	std::pair<std::vector<Instruction>, std::unordered_map<std::string, uint16_t>> ParseFile(std::istream& file)
	{
		std::vector<Instruction> instructions;
		std::unordered_map<std::string, uint16_t> lables;
		uint16_t lineIndex = 0;

		std::string line;
		while (std::getline(file, line))
		{
			// Remove Comments
			line = std::regex_replace(line, comment, "");

			//Removes White Space and pushes the line to a container
			if (!line.empty())
			{
				//Helpers::trim(line); // Remove White spaces
				
				Instruction instruction = ParseLine(line);

				if(instruction.type == cmd_type::Lable)
				{ 
					lables.insert(std::pair<std::string, uint16_t>(instruction.signature, lineIndex));
				}
				else
				{
					instructions.push_back(ParseLine(line));
					lineIndex++;
				}
			}
		}
		return std::pair<std::vector<Instruction>, std::unordered_map<std::string, uint16_t>>(instructions, lables);
	}
}