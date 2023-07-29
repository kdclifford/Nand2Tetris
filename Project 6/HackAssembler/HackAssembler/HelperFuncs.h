#pragma once
#include <sstream>


namespace Helpers
{

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
}