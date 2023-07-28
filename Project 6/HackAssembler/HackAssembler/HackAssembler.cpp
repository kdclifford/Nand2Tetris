// HackAssembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <format>
#include <argparse.hpp>
#include <unordered_map>
#include <bitset>
#include <stdexcept>

bool isNumeric(const std::string& input) {
	try {
		size_t pos;
		std::stod(input, &pos);
		return pos == input.length(); // Check if entire string was successfully converted
	}
	catch (std::invalid_argument&) {
		return false; // Conversion failed
	}
	catch (std::out_of_range&) {
		return false; // Number is out of range
	}
}

int main(int argc, char* argv[])
{
	typedef struct instruction
	{
		unsigned int start : 3;  // padding
		//unsigned int a : 1;  // a
		unsigned int c : 7;  // comp
		unsigned int d : 3;  // dest
		unsigned int j : 3;  // jump
	};

	const std::unordered_map<std::string, uint16_t> predefined = {
	{"R0",	    {0b0}},
	{"R1",	    {0b1}},
	{"R2",	    {0b10}},
	{"R3",	    {0b11}},
	{"R4",	    {0b100}},
	{"R5",	    {0b101}},
	{"R6",	    {0b110}},
	{"R7",	    {0b111}},
	{"R8",	    {0b1000}},
	{"R9",		{0b1001}},
	{"R10",		{0b1010}},
	{"R11",		{0b1011}},
	{"R12",		{0b1100}},
	{"R13",		{0b1101}},
	{"R14",		{0b1110}},
	{"R15",		{0b1111}},
	{"SP",	    {0b0}},
	{"LCL",		{0b1}},
	{"ARG",		{0b10}},
	{"THIS",    {0b11}},
	{"THAT",    {0b100}},
	{"SCREEN",  {0b100'0000'0000'0000}},
	{"KDB",		{0b110'0000'0000'0000}}
	};

	std::unordered_map<std::string, uint16_t> otherAddresses;


	const std::unordered_map<std::string, uint8_t> comp = {
	{"0",	   {0b10'1010}},
	{"1",	   {0b11'1111}},
	{"-1",	   {0b11'1010}},
	{"D",	   {0b1100}},
	{"A",	   {0b11'0000}},
	{"M",	   {0b111'0000}},
	{"!D",	   {0b1101}},
	{"!A",	   {0b11'0001}},
	{"!M",	   {0b111'0001}},
	{"-D",	   {0b1111}},
	{"-A",	   {0b11'0011}},
	{"-M",	   {0b111'0011}},
	{"D+1",	   {0b1'1111}},
	{"A+1",	   {0b11'0111}},
	{"M+1",	   {0b111'0111}},
	{"D-1",	   {0b1'110}},
	{"A-1",	   {0b11'0010}},
	{"M-1",	   {0b111'0010}},
	{"D+A",	   {0b10}},
	{"D+M",	   {0b100'0010}},
	{"D-A",	   {0b1'0011}},
	{"D-M",	   {0b101'0011}},
	{"A-D",	   {0b111}},
	{"M-D",	   {0b100'0111}},
	{"D&A",	   {0b0}},
	{"D&M",	   {0b100'0000}},
	{"D|A",	   {0b1'0101}},
	{"D|M",	   {0b101'0101}}
	};

	const std::unordered_map<std::string, uint8_t> dest = {
	{"null",   {0b0}},
	{"M",	   {0b1}},
	{"D",	   {0b10}},
	{"DM",	   {0b11}},
	{"A",	   {0b100}},
	{"AM",	   {0b101}},
	{"AD",	   {0b110}},
	{"ADM",	   {0b111}}
	};

	const std::unordered_map<std::string, uint8_t> jump = {
	{"null",   {0b0}},
	{"JGT",	   {0b1}},
	{"JEQ",	   {0b10}},
	{"JGE",	   {0b11}},
	{"JLT",	   {0b100}},
	{"JNE",	   {0b101}},
	{"JLE",	   {0b110}},
	{"JMP",	   {0b111}}
	};

	//Basic
	const std::string k_add = "../../add/Add.asm";
	const std::string k_max = "../../max/Max.asm";
	const std::string k_pong = "../../pong/Pong.asm";
	const std::string k_rect = "../../rect/Rect.asm";

	//Less
	const std::string k_maxL = "../../max/MaxL.asm";
	const std::string k_pongL = "../../pong/PongL.asm";
	const std::string k_rectL = "../../rect/RectL.asm";

	argparse::ArgumentParser program("program_name");


	program.add_argument("-f", "--filePath")
		.help("File path to asm file")
		.default_value(k_add)
		.nargs(1);
		//.required();

	//Try pass args
	try {
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		return 1;
	}

	//Get program arguments
	const auto filePath = program.get<std::string>("--filePath");

	//Open asm File
	std::ifstream myfile(filePath);

	if (myfile.is_open()) {   //checking whether the file is open
		std::string line;
		while (std::getline(myfile, line))
		{
			if (line.find("//") != std::string::npos) {
				std::cout << "found comment" << '\n';
				continue;
			}

			std::stringstream ss(line);
			std::string whiteSpcae;
			while (std::getline(ss, whiteSpcae, ' '))
			{

				if (whiteSpcae[0] == '@')
				{
					const std::string key = whiteSpcae.substr(1);

					const auto address = predefined.find(key);

					if (address != predefined.end())
					{
						std::cout << std::bitset<16>(address->second) << std::endl;
					}
					else
					{
						const auto address2 = otherAddresses.find(key);
						if (address2 == otherAddresses.end())
						{
							if (isNumeric(key))
							{
								std::cout << std::bitset<16>(std::stoi(key)) << std::endl;
							}
							else
							{
								const int value = (15 + otherAddresses.size());

								std::pair<std::string, uint16_t> newAdress(key, value);

								otherAddresses.insert(newAdress);

								std::cout << "new address added: " << std::bitset<16>(newAdress.second) << std::endl;
							}

						}
					}
				}
						else
						{
							const auto test = predefined.find(whiteSpcae);

							std::string comp2 = "";
							std::string dest2 = "";

							bool equal = false;
							// Returns first token
							for (const auto letter : whiteSpcae)
							{
								if (letter == '=')
								{
									equal = true;
								}
								else if (equal)
								{
									comp2 += letter;
								}
								else
								{
									dest2 += letter;
								}
							}


							instruction binary = { {0b111},	{comp.find(comp2)->second},	{dest.find(dest2)->second}, {0b000}};
							std::cout << std::bitset<3>(binary.start) << std::bitset<7>(binary.c) << std::bitset<3>(binary.d) << std::bitset<3>(binary.j) << std::endl;
						}

			}
		}
	}

	myfile.close();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
