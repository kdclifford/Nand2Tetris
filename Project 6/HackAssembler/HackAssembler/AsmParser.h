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
	AsmParser(std::string filePath);
	AsmParser() {};


	void OpenFile(std::string filePath);

private:
	std::ifstream file_;

	std::unordered_map<std::string, uint16_t*> addresses_;
	std::unordered_map<std::string, uint16_t*> lables_;

	std::vector<uint16_t*> parsedLines_;

	void ParseAsm_();
	void AddParsedLine_(uint16_t* value);
	void AddLable_(std::string key, uint16_t* value);
	void AddAddress_(std::string key, uint16_t* value);
	void ShowAddress_();
	void TranslateLableAddresses_();
	void TranslateAddressIDs_();
	void SaveToFile_(std::string filePath);
};

