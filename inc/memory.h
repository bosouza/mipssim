#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <common.h>

struct memory_output
{
};

struct memory_input
{
};

// currently not implemented, as we don't need it
class memory
{
public:
    memory(unsigned int memorySize);
    ~memory();
    memory_output run(memory_input);

private:
    // embed memory array inside the pipeline stage itself because it doesn't seem like
    // it's worth to factor it out atm
    int *mem;
};

#endif