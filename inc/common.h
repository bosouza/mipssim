#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <string>

// How many registers there are
#define REGISTER_QTY 32

void rtrim(std::string &s, char c);

void ltrim(std::string &s, char c);

void trim(std::string &s, char c);

enum instructionFormat
{
    //R-format
    REGISTER,
    //I-format
    IMMEDIATE,
    //J-format
    JUMP,
};

struct operands
{
    //operation code
    unsigned int op = 0;
    //register source
    unsigned int rs = 0;
    /* register target: 
    In a R-format instruction it is the 2nd register operand
    In a I-format instruction it is the register destination/source
    */
    unsigned int rt = 0;
    //register destination
    unsigned int rd = 0;
    //immediate value
    int imm = 0;
    //offset value
    int offset = 0;
    //shift amount
    unsigned int shamnt = 0;
    //function code - identifies the specific R-format instruction
    unsigned int funct = 0;
    //address
    unsigned int addr = 0;
};

enum instructionLayoutPart
{
    _OP,
    _RS,
    _RT,
    _RD,
    _SHAMT,
    _FUNCT,
    _IMMEDIATE,
    _OFFSET,
    _ADDRESS,
};

enum opcode
{
    ADD,
    ADDI,
    SUB,
    SUBI,
    BEQ,
    B,
    NOP,
    OOB,
};

struct instruction
{
    opcode opc;
    operands opx;
    instructionFormat format;
};

instruction newInstruction(std::string s);

// isValidRegister checks that the provided address is whithin the expected range of
// register addresses
bool isValidRegister(unsigned int address);

#endif