#ifndef DECODE_H_INCLUDED
#define DECODE_H_INCLUDED

#include <common.h>
#include <sstream>
#include <string>

struct decode_input
{
    instruction i;
    // regWrite, writeData and writeAddress control "if", "what" and "where" to write something
    bool regWrite;
    int writeData;
    unsigned int writeAddress;
};

struct decode_output
{
    int rsValue;
    int rtValue;
    opcode op;
    int immediate;
    int offset;
    bool regWrite;
    bool memToReg;
    unsigned int targetReg;
    bool branch;
};

std::string decode_output_str(decode_output dout);

class decode
{
public:
    decode();
    ~decode();
    decode_output run(decode_input);

private:
    unsigned int registers[REGISTER_QTY];
    void writeReg(unsigned int address, int data);
    int readReg(unsigned int address);
};

#endif