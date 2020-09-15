// This file is responsible for loading a program to be executed and exposing the instructions.
// TODO: abstract intruction_memory interface to allow multiple implementations. Having a mock version
// would be useful for tests
#ifndef INSTRUCTION_MEMORY_H_INCLUDED
#define INSTRUCTION_MEMORY_H_INCLUDED

#include <string>
#include <vector>
#include <common.h>

using namespace std;

class instruction_memory
{
public:
    instruction_memory(string program_path);
    ~instruction_memory();
    instruction getInstruction(unsigned int address);

private:
    vector<instruction> instructions;
};

#endif