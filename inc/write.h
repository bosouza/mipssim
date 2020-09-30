#ifndef WRITE_H_INCLUDED
#define WRITE_H_INCLUDED

#include <common.h>
#include <sstream>
#include <string>

struct write_input
{
    bool memToReg;
    int regData;
    int memData;
};

struct write_output
{
    int writeData;
};

std::string write_output_str(write_output wo);

class write
{
public:
    write(/* args */);
    ~write();
    write_output run(write_input);
};

#endif