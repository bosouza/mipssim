#include <control.h>

bool shouldLoadFromMemory(opcode)
{
    // we currently don't support any instruction that read from memory
    return false;
}

bool shouldWriteToRegister(opcode opc)
{
    switch (opc)
    {
    case ADD:
    case ADDI:
    case SUB:
    case SUBI:
        return true;
    default:
        return false;
    }
}

unsigned int determineTargetRegister(opcode opc, unsigned int rd, unsigned int rt)
{
    switch (opc)
    {
    case ADD:
    case SUB:
        return rd;
    case ADDI:
    case SUBI:
        return rt;
    }
    return 0;
}

bool isConditionalBranchInstruction(opcode opc)
{
    return opc == BEQ;
}

bool shouldBranch(bool branch, bool zero)
{
    return branch && zero;
}

bool shouldBranch(bool branch, int rsValue, int rtValue)
{
    return branch && (rsValue == rtValue);
}