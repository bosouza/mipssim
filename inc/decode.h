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
    unsigned int writeAddress;
    unsigned int PC;
    int writeData;
};

struct decode_output
{
    int rsValue = 0;
    int rtValue = 0;
    opcode op = NOP;
    int immediate = 0;
    int offset = 0;
    bool regWrite = false;
    bool memToReg = false;
    unsigned int targetReg = 0;
    bool branch = false;
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