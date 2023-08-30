#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../SourceCode/Parser.h"

TEST_CASE("testing the ParseFile function") 
{
	std::string r1 = "@R1";
	auto test = Parser::ParseLine(r1);
	CHECK(test.signature == "R1");
	//CHECK(Parser::ParseLine("@R1").type == cmd_type::Address);
}