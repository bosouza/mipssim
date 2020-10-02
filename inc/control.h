#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <common.h>

bool shouldLoadFromMemory(opcode);
bool shouldWriteToRegister(opcode);
unsigned int determineTargetRegister(opcode, unsigned int rd, unsigned int rt);
bool isConditionalBranchInstruction(opcode);
bool shouldBranch(bool branch, bool zero);

#endif