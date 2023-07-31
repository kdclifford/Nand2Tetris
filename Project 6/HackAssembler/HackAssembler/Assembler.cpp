#include "Assembler.h"

#include "HelperFuncs.h"

#include <bitset>


Assembler::Assembler()
	: varibleAddress_(16)
{
}

std::vector<uint16_t> Assembler::ParseFile(std::vector<std::string> file, std::vector<std::pair<std::string, uint32_t>>& lables)
{
	std::cout << "Second File Parse" << std::endl;
	std::vector<uint16_t> binaryCode;
	for (auto line : file)
	{
		//A-instructions
		if (line[0] == '@')
		{
			const std::string key = line.substr(1);
			const bool isAddressNumeric = Helpers::isNumeric(key);

			if (isAddressNumeric)
			{
				uint16_t numericKey = stoi(key);
				if (k_MaxAddress >= numericKey)
				{
					std::cout << "Found in predefined: " << std::endl;
					binaryCode.push_back(numericKey);
					continue;
				}
			}
			auto preDefinedAddress = KMaps::predefined.find(key);

			if (preDefinedAddress != KMaps::predefined.end())
			{
				std::cout << "Found in predefined: " << std::endl;
				binaryCode.push_back(preDefinedAddress->second);
				continue;
			}

			auto it = std::find_if(lables.begin(), lables.end(),
				[&key](const auto& lable) { return lable.first == key; });

			if (it != lables.end())
			{
				binaryCode.push_back(it->second);
				continue;
			}

			if (varibleAddress_ <= k_MaxAddress)
			{
				binaryCode.push_back(varibleAddress_++);
			}

		}
		//C-instructions
		else
		{
			uint16_t compAddress = 0, destAddress = 0, jumpAddress = 0;

			const std::string::size_type semiColon = line.find(';');
			const std::string::size_type equal = line.find('=');
			if (line.npos != equal) 
			{
				for (auto letter : line.substr(0, equal))
				{
					destAddress = destAddress | KMaps::dest.find(std::string(1, letter))->second;
				}
				compAddress = KMaps::comp.find(line.substr(equal + 1))->second;
			}
			else if (line.npos != semiColon)
			{
				compAddress = KMaps::comp.find(line.substr(0, semiColon))->second;
				jumpAddress = KMaps::jump.find(line.substr(semiColon + 1))->second;
			}

			binaryCode.push_back(compAddress| destAddress | jumpAddress);
		}
	}
	return binaryCode;
}