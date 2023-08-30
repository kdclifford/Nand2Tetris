#pragma once
#include <cassert>
#include <charconv>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string_view>
#include <system_error>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace Helpers
{
    static inline bool isNumeric(const std::string_view& input) {
        
        std::cout << "String: " << std::quoted(input) << ". ";
        int result{};
        auto [ptr, ec] = std::from_chars(input.data(), input.data() + input.size(), result);
        
        if (ec == std::errc())
        {
            std::cout << "Result: " << result << ", ptr -> " << std::quoted(ptr) << '\n';
            return true;
        }
        else if (ec == std::errc::invalid_argument)
        {
            std::cout << "That isn't a number.\n";
        }
        else if (ec == std::errc::result_out_of_range)
        {
            std::cout << "This number is larger than an int.\n";
        }
        return false;
    }

    // trim from start (in place)
    static inline std::string& ltrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            [](int c) {return !std::isspace(c); }));
        return s;
    }

    // trim from end (in place)
    static inline std::string& rtrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(),
            [](int c) { return !std::isspace(c); }).base(), s.end());
        return s;
    }

    // trim from both ends (in place)
    static inline void trim(std::string& s) {
        rtrim(s);
        ltrim(s);
    }

    // trim from start (copying)
    static inline std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
    }

    // trim from end (copying)
    static inline std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
    }

    static inline int FindElementValue(std::string key, std::vector<std::pair<std::string, uint16_t>> map)
    {
        auto it = std::find_if(map.begin(), map.end(), [&key](const auto& name) { return name.first == key; });
        return it != map.end() ? it->second : -1;
    }

}