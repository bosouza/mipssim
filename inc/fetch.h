#ifndef FETCH_H_INCLUDED
#define FETCH_H_INCLUDED

#include <common.h>
#include <instruction_memory.h>

struct fetch_output
{
    instruction i;
};

class fetch
{
public:
    fetch(instruction_memory *mem);
    ~fetch();
    fetch_output run();

private:
    instruction_memory *mem;
    unsigned int PC;
};

#endif