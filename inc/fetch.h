#ifndef FETCH_H_INCLUDED
#define FETCH_H_INCLUDED

#include <common.h>
#include <instruction_memory.h>
#include <sstream>
#include <string>

struct fetch_input
{
    bool branch;
    unsigned int branchAddress;
    bool branched;
};

struct fetch_output
{
    instruction i = {.opc = NOP};
    unsigned int PC = 0;
    bool branched = false;
    bool invalidateBranch = false;
};

std::string fetch_output_str(fetch_output fo);

class fetch
{
public:
    fetch(instruction_memory *mem);
    ~fetch();
    fetch_output run(fetch_input);

private:
    instruction_memory *mem;
    unsigned int PC;
};

#endif