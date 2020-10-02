#ifndef FORWARDING_H_INCLUDED
#define FORWARDING_H_INCLUDED

#include <common.h>

struct forwarding_input
{
    // rs from the decode stage
    unsigned int rs;
    // rsValue from the decode stage
    int rsValue;
    // rt from the decode stage
    unsigned int rt;
    // rtValue from the decode stage
    int rtValue;
    // regWrite from the execute stage
    bool executeRegWrite;
    // targetReg from the execute stage
    unsigned int executeTargetReg;
    // result from the execute stage
    int result;
    // regWrite from the write-back stage
    bool writeRegWrite;
    // targetReg from the write-back stage
    unsigned int writeTargetReg;
    // writeData from the write-back stage
    int writeData;
};

struct forwarding_output
{
    int rsValue;
    int rtValue;
};

std::string forwarding_output_str(forwarding_output dout);

class forwarding
{
public:
    forwarding();
    ~forwarding();
    forwarding_output run(forwarding_input);
};

#endif