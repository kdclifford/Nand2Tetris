#include "AsmParser.h"
#include "HelperFuncs.h"

#include <bitset>

AsmParser::AsmParser(std::string filePath)
{
	OpenFile(filePath);
	SaveToFile_(filePath);
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
						AddParsedLine_(new uint16_t( preDefinedAddress->second));
					}
					else
					{
						auto address = addresses_.find(key);
						if (address == addresses_.end())
						{
							if (Helpers::isNumeric(key))
							{
								std::cout << "Is numeric Addres" << std::endl;
								AddParsedLine_(new uint16_t(std::stoi(key)));
							}
							else
							{
								uint16_t* value = new uint16_t(0);//(15 + addresses_.size());

								AddAddress_(key, value);

								std::cout << "new address added:" << std::endl;
								AddParsedLine_(value);
							}
						}
						else
						{
							std::cout << "Found in addresses: " << std::endl;
							AddParsedLine_(address->second);
						}
					}
				}
				else if (whiteSpcae.find('(') != std::string::npos)
				{
					std::string removeBrackets = whiteSpcae.substr(0, whiteSpcae.size() - 1);
					removeBrackets = removeBrackets.substr(1);
					AddLable_(removeBrackets, new uint16_t(parsedLines_.size()));
				}
				else
				{
					std::string comp, dest,jump;

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

					auto destElement = KMaps::dest.find(dest);
					uint16_t concatDest = 0;
					if (dest != "null")
					{
						if (destElement == KMaps::dest.end())
						{
							for (auto letter : dest)
							{
								concatDest | KMaps::dest.find(std::string(1, letter))->second;
							}
						}
						else
						{
							concatDest = destElement->second;
						}
					}

					AddParsedLine_(new uint16_t(KMaps::comp.find(comp)->second | concatDest | KMaps::jump.find(jump)->second));
				}
			}
		}
	}
	std::cout << "Closing File" << std::endl;
	file_.close();

	//Second pass for labels
	TranslateLableAddresses_();
	ShowAddress_();
}

void AsmParser::AddParsedLine_(uint16_t* value)
{
	parsedLines_.push_back(std::move(value));
}

void AsmParser::AddLable_(std::string key, uint16_t* value)
{
	lables_.insert(std::pair<std::string, uint16_t*>(key, value));
}

void AsmParser::AddAddress_(std::string key, uint16_t* value)
{
	addresses_.insert(std::pair<std::string, uint16_t*>(key, value));
}

void AsmParser::ShowAddress_()
{
	for (const auto value : parsedLines_)
	{
		std::cout << std::bitset<16>((*value)) << std::endl;
	}
}

void AsmParser::TranslateLableAddresses_()
{
	for(auto& [lable, v] : lables_)
	{
		for (auto& [key, value] : addresses_)
		{
			if (key == lable)
			{
				(*value) = (*v);
				v = std::move(value);
				addresses_.erase(key);
				break;
			}
		}
	}
	TranslateAddressIDs_();
}

void AsmParser::TranslateAddressIDs_()
{
	uint16_t index = 16;
	for (auto& [key, value] : addresses_)
	{
		(*value) = index++;
	}
}

void AsmParser::SaveToFile_(std::string filePath)
{
	std::ofstream hackFile(filePath+".hack");

	for (auto line : parsedLines_)
	{
		hackFile << std::bitset<16>(*line) << std::endl;
	}

	hackFile.close();
}
