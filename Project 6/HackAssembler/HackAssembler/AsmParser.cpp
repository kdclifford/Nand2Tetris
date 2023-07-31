#include "AsmParser.h"

#include "HelperFuncs.h"

std::vector<std::string> AsmParser::ParseFile(std::ifstream& file)
{
	std::string line;
	uint32_t lineIndex = 0;
	while (std::getline(file, line))
	{
		//Remove comments on same line as code
		int commentLine = line.find("//");
		if (commentLine > 0)
		{
			line = line.substr(0, commentLine);
			std::cout << "Same Line Comment Removed" << std::endl;
		}
		else if (commentLine == 0) {
			std::cout << "Comment Found" << std::endl;
			continue;
		}

		//Removes White Space and pushes the line to a container
		if (!line.empty())
		{
			Helpers::trim(line); // Remove White spaces

			if (line[0] == '(')
			{
				// Remove Brackets
				line.erase(0, 1);
				line.erase(line.size() - 1);
				lables_.push_back(std::pair<std::string, uint32_t>( line, lineIndex));
			}
			else
			{
				parsedFile_.push_back(line); // Push asmbley code to the container
				lineIndex++;
			}
		}
	}

	return parsedFile_;
}

std::vector<std::pair<std::string, uint32_t>> AsmParser::GetLables()
{
	return lables_;
}

//void AsmParser::SaveToFile(std::string filePath, std::vector<uint16_t>& newFile)
//{
//	std::ofstream hackFile(filePath+".hack");
//	std::cout << "Saving File: " << filePath + ".hack" << std::endl;
//
//	for (auto line : newFile)
//	{
//		hackFile << std::bitset<16>(line) << std::endl;
//	}
//
//	hackFile.close();
//}
