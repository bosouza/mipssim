#include <common.h>
#include <vector>
#include <iostream>

instruction newInstruction(std::string s)
{
    auto opcode_delimiter = s.find(" ");
    auto opcode = s.substr(0, opcode_delimiter);
    std::string operandsStr;
    if (!opcode.compare("add"))
    {
        // return instruction{.opc = ADD, .opx = processOperands(operandsStr, REGISTER, REGISTER, REGISTER)};
        return instruction{.opc = ADD};
    }
    else if (!opcode.compare("addi"))
    {
        // return instruction{.opc = ADDI, .opx = processOperands(operandsStr, REGISTER, REGISTER, IMMEDIATE)};
        return instruction{.opc = ADDI};
    }
    else if (!opcode.compare("sub"))
    {
        return instruction{.opc = SUB};
    }
    else if (!opcode.compare("subi"))
    {
        return instruction{.opc = SUBI};
    }
    else if (!opcode.compare("beq"))
    {
        return instruction{.opc = BEQ};
    }
    else if (!opcode.compare("b"))
    {
        return instruction{.opc = B};
    }
    else if (!opcode.compare("nop"))
    {
        return instruction{.opc = NOP};
    }
    else
    {
        std::cout << "invalid opcode found when parsing an instruction: " << opcode << std::endl;
        throw;
    }
}

// instruction newInstruction(string s)
// {
//     vector<string> segments;

//     string delim = ",";
//     auto start = 0U;
//     auto end = s.find(delim);
//     while (end != std::string::npos)
//     {
//         segments.push_back(s.substr(start, end - start));
//         start = end + delim.length();
//         end = s.find(delim, start);
//     }

//     if (segments.size() == 0)
//     {
//         cout << "empty instruction" << endl;
//     }
// }