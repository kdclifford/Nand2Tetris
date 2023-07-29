#include <argparse.hpp>
#include "AsmParser.h"

//Basic
const std::string k_add = "../../add/Add.asm";
const std::string k_max = "../../max/Max.asm";
const std::string k_pong = "../../pong/Pong.asm";
const std::string k_rect = "../../rect/Rect.asm";

//Less
const std::string k_maxL = "../../max/MaxL.asm";
const std::string k_pongL = "../../pong/PongL.asm";
const std::string k_rectL = "../../rect/RectL.asm";

int main(int argc, char* argv[])
{
	argparse::ArgumentParser program("HackAssembler");

	program.add_argument("-f", "--filePath")
		.help("File path to asm file")
		.nargs(1)
		.required();
		//.default_value(k_max);

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

	AsmParser asmParser(filePath);

	return 0;
}