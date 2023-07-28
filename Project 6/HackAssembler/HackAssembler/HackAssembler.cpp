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


int main(int argc, char* argv[])
{
	typedef struct bits3
	{
		unsigned int v1 : 3;  // 1st 3 bits (in 1st byte) are b1
		unsigned int : 5;  // padding
	};

	const std::unordered_map<std::string, std::string> predefined = {
	{"R0",	   "0000000000000000"},
	{"R1",	   "0000000000000001"},
	{"R2",	   "0000000000000010"},
	{"R3",	   "0000000000000011"},
	{"R4",	   "0000000000000100"},
	{"R5",	   "0000000000000101"},
	{"R6",	   "0000000000000110"},
	{"R7",	   "0000000000000111"},
	{"R8",	   "0000000000001000"},
	{"R9",	   "0000000000001001"},
	{"R10",	   "0000000000001010"},
	{"R11",	   "0000000000001011"},
	{"R12",	   "0000000000001100"},
	{"R13",	   "0000000000001101"},
	{"R14",	   "0000000000001110"},
	{"R15",	   "0000000000001111"},
	{"SP",	   "0000000000000000"},
	{"LCL",	   "0000000000000001"},
	{"ARG",	   "0000000000000010"},
	{"THIS",   "0000000000000011"},
	{"THAT",   "0000000000000100"},
	{"SCREEN", "0100000000000000"},
	{"KDB",	   "0110000000000000"}
	};

	const std::unordered_map<std::string, std::string> comp = {
	{"0",	   "0101010"},
	{"1",	   "0111111"},
	{"-1",	   "0111010"},
	{"D",	   "0001100"},
	{"A",	   "0110000"},
	{"M",	   "1110000"},
	{"!D",	   "0001101"},
	{"!A",	   "0110001"},
	{"!M",	   "1110001"},
	{"-D",	   "0001111"},
	{"-A",	   "0110011"},
	{"-M",	   "1110011"},
	{"D+1",	   "0011111"},
	{"A+1",	   "0110111"},
	{"M+1",	   "1110111"},
	{"D-1",	   "0001110"},
	{"A-1",	   "0110010"},
	{"M-1",	   "1110010"},
	{"D+A",	   "0000010"},
	{"D+M",	   "1000010"},
	{"D-A",	   "0010011"},
	{"D-M",	   "1010011"},
	{"A-D",	   "0000111"},
	{"M-D",	   "1000111"},
	{"D&A",	   "0000000"},
	{"D&M",	   "1000000"},
	{"D|A",	   "0010101"},
	{"D|M",	   "A010101"}
	};

	//const std::unordered_map<std::string, bits3> dest = {
	//{"null",   "000"},
	//{"M",	   "001"},
	//{"D",	   "010"},
	//{"DM",	   "011"},
	//{"A",	   "100"},
	//{"AM",	   "101"},
	//{"AD",	   "110"},
	//{"ADM",	   "111"}
	//};

	//const std::unordered_map<std::string, bits3> jump = {
	//{"null",   "000"},
	//{"JGT",	   "001"},
	//{"JEQ",	   "010"},
	//{"JGE",	   "011"},
	//{"JLT",	   "100"},
	//{"JNE",	   "101"},
	//{"JLE",	   "110"},
	//{"JMP",	   "111"}
	//};




	std::string s = std::bitset< 64 >(12345).to_string(); // string conversion

	std::cout << std::bitset< 64 >(54321) << ' '; // direct output

	std::bitset< 64 > input;
	std::cin >> input;
	unsigned long ul = input.to_ulong();


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
		.nargs(1)
		.required();

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
				//commands.push(whiteSpcae);
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
