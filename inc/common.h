#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <string>

// How many registers there are
#define REGISTER_QTY 32

struct operands
{
    unsigned int rs = 0;
    unsigned int rt = 0;
    unsigned int rd = 0;
    int imm = 0;
    int offset = 0;
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
    OOB,
};

struct instruction
{
    opcode opc;
    operands opx;
};

instruction newInstruction(std::string s);

// isValidRegister checks that the provided address is whithin the expected range of
// register addresses
bool isValidRegister(unsigned int address);

#endif