#include "AsmParser.h"
#include "HelperFuncs.h"

#include <bitset>

AsmParser::AsmParser(std::string filePath)
{
	OpenFile(filePath);
}

void AsmParser::OpenFile(std::string filePath)
{
	file_.open(filePath);
	if (file_.is_open()) {
		std::cout << "File is open: " << filePath << std::endl;
		ParseAsm_();
	}
	else
	{
		throw std::invalid_argument("No File Found");
	}
}

void AsmParser::ParseAsm_()
{
	std::cout << "Parsing File" << std::endl;

	std::string line;
	while (std::getline(file_, line))
	{
		//Remove comments on same line as code
		int lineIndex = line.find("//");
		if (lineIndex > 0)
		{
			//removeLastN(line, line.size() - lineIndex);
			line = line.substr(0, lineIndex);
		}

		if (line.find("//") == 0) {
			std::cout << "Comment Found" << std::endl;
			continue;
		}

		std::stringstream ss(line);
		std::string whiteSpcae;
		ss >> std::ws;
		while (std::getline(ss, whiteSpcae, ' '))
		{
			if (!whiteSpcae.empty())
			{
				if (whiteSpcae.find('@') != std::string::npos)
				{
					const std::string key = whiteSpcae.substr(1);

					const auto preDefinedAddress = KMaps::predefined.find(key);

					if (preDefinedAddress != KMaps::predefined.end())
					{
						std::cout << "Found in predefined: " << std::endl;
						AddParsedLine_(preDefinedAddress->second);
					}
					else
					{
						const auto address = addresses_.find(key);
						if (address == addresses_.end())
						{
							if (Helpers::isNumeric(key))
							{
								std::cout << "Is numeric Addres" << std::endl;
								AddParsedLine_(std::stoi(key));
							}
							else
							{
								const int value = 0;//(15 + addresses_.size());

								AddAddress_(key, value);

								std::cout << "new address added:" << std::endl;
								AddParsedLine_(address->second);
							}
						}
					}
				}
				else if (whiteSpcae.find('(') != std::string::npos)
				{
					AddLable_(whiteSpcae, parsedLines_.size());
				}
				else
				{
					std::string comp = "";
					std::string dest = "";
					std::string jump = "";

					const std::string::size_type semiColon = whiteSpcae.find(';');
					const std::string::size_type equal = whiteSpcae.find('=');
					if (whiteSpcae.npos != equal) {
						dest = whiteSpcae.substr(0, equal);
						comp = whiteSpcae.substr(equal + 1);
						jump = "null";
					}
					else if (whiteSpcae.npos != semiColon)
					{						 
						comp = whiteSpcae.substr(0, semiColon);
						jump = whiteSpcae.substr(semiColon + 1);
						dest = "null";
					}

					const uint16_t concatInt = (KMaps::comp.find(comp)->second | KMaps::dest.find(dest)->second | KMaps::jump.find(jump)->second);

					AddParsedLine_(concatInt);
					//instruction binary = { {0b111},	{KMaps::comp.find(comp)->second},	{KMaps::dest.find(dest)->second}, {KMaps::jump.find(jump)->second} };
					//std::cout << std::bitset<16>(KMaps::comp.find(comp)->second | KMaps::dest.find(dest)->second | KMaps::jump.find(jump)->second) << std::endl;
				}
			}
		}
	}
	std::cout << "Closing File" << std::endl;
	file_.close();




	ShowAddress_();


}

void AsmParser::AddParsedLine_( uint16_t line)
{
	parsedLines_.push_back(line);
}

void AsmParser::AddLable_(std::string key, uint16_t value)
{
	lables_.insert(std::pair<std::string, uint16_t>(key, value));
}

void AsmParser::AddAddress_(std::string key, uint16_t value)
{
	addresses_.insert(std::pair<std::string, uint16_t>(key, value));
}

void AsmParser::ShowAddress_()
{
	for (auto line : parsedLines_)
	{
		std::cout << std::bitset<16>(line) << std::endl;
	}
}

void AsmParser::TranslateLableAddresses_()
{
	for (auto line : parsedLines_)
	{
		std::cout << std::bitset<16>(line) << std::endl;
	}
}
