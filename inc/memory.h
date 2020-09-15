#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <common.h>

struct memory_output
{
};

struct memory_input
{
};

class memory
{
public:
    memory();
    ~memory();
    memory_output run(memory_input);
};

#endif