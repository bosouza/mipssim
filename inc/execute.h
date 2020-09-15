#ifndef EXECUTE_H_INCLUDED
#define EXECUTE_H_INCLUDED

#include <common.h>

struct execute_output
{
};

struct execute_input
{
};

class execute
{
public:
    execute(/* args */);
    ~execute();
    execute_output run(execute_input);
};

#endif