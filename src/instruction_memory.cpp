#include <instruction_memory.h>

#include <iostream>
#include <fstream>

instruction_memory::instruction_memory(string program_path)
{
    ifstream instructionFile(program_path);
    if (!instructionFile.is_open())
    {
        cout << "cannot open file" << endl;
        throw;
    }

    string line;
    while (getline(instructionFile, line))
    {
        this->instructions.push_back(newInstruction(line));
    }
    instructionFile.close();
}

instruction_memory::instruction_memory(vector<instruction> i)
{
    // std::cout << "instruction[0].imm: " << i[0].opx.imm << std::endl;
    this->instructions = i;
}

instruction_memory::~instruction_memory()
{
}

instruction instruction_memory::getInstruction(unsigned int address)
{
    if (address % 4 != 0)
    {
        cout << "unaligned memory access" << endl;
        throw;
    }
    if (address / 4 >= this->instructions.size())
        return instruction{.opc = OOB};
    // {
    //     cout << "tried to read instruction outside limits, address: " << address << endl;
    //     throw;
    // }
    return this->instructions[address / 4];
}