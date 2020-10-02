#ifndef EXECUTE_H_INCLUDED
#define EXECUTE_H_INCLUDED

#include <common.h>
#include <sstream>
#include <string>

struct execute_input
{
    // op determines what operation should be performed by the ALU
    opcode op;
    // immediate should actually be a 16-bit signed integer, but that was causing too much trouble
    int immediate;
    int offset;
    // rsValue is the value read from the instruction's $s
    int rsValue;
    // rtValue is the value read from the instruction's $t
    int rtValue;
    unsigned int PC;
};

struct execute_output
{
    // result is the output from the ALU module
    int result = 0;
};

std::string execute_output_str(execute_output eo);

class execute
{
public:
    execute(/* args */);
    ~execute();
    execute_output run(execute_input);
};

#endif