#ifndef DECODE_H_INCLUDED
#define DECODE_H_INCLUDED

#include <common.h>

struct decode_output
{
    instruction i;
};

struct decode_input
{
    instruction i;
};

class decode
{
public:
    decode();
    ~decode();
    decode_output run(decode_input);
};

#endif