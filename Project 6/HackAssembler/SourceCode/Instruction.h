#pragma once

#include <vector>
#include <string>

enum class cmd_type
{
    Lable, 
    LAddress, 
    Address,
    C0,
    C1,
    C2,
};


struct Instruction 
{
    cmd_type type;

    std::string signature;
    std::string signature2;
    std::string signature3;
};