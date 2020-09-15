#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <string>

struct operands
{
    unsigned int rs = 0;
    unsigned int rt = 0;
    unsigned int rd = 0;
    unsigned int imm = 0;
    unsigned int offset = 0;
    unsigned int addr = 0;
};

enum operandType
{
    REGISTER,
    SHAMT,
    IMMEDIATE,
    OFFSET,
};

operands processOperands(std::string operandsStr, operandType...);

enum opcode
{
    ADD,
    ADDI,
    SUB,
    SUBI,
    BEQ,
    B,
    NOP,
};

struct instruction
{
    opcode opc;
    operands opx;
};

instruction newInstruction(std::string s);

#endif