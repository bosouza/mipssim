#ifndef FETCH_H_INCLUDED
#define FETCH_H_INCLUDED

#include <common.h>
#include <instruction_memory.h>
#include <sstream>
#include <string>

#define PREDICTION_TABLE_SIZE 32

struct fetch_input
{
    bool branch;
    unsigned int branchAddress;
    bool branched;
    // execBEQ indicates that there's a BEQ in the execute stage. Used for updating the branch table
    bool execBEQ;
    // BEQAddress is the address of the BEQ instruction currently on the execute stage
    unsigned int BEQAddress;
};

struct fetch_output
{
    instruction i = {.opc = NOP};
    unsigned int PC = 0;
    bool branched = false;
    bool invalidatePrediction = false;
    bool insertBubble = false;
};

std::string fetch_output_str(fetch_output fo);

enum predictionState
{
    DONT_BRANCH,
    MISSED_DONT_BRANCH,
    BRANCH,
    MISSED_BRANCH
};

class fetch
{
public:
    fetch(instruction_memory *mem, bool enablePrediction);
    ~fetch();
    fetch_output run(fetch_input);
    bool shouldBranch(unsigned int address);
    void updateBranch(unsigned int address, bool hit);

private:
    instruction_memory *mem;
    unsigned int PC;
    bool predictionEnabled;
    predictionState branchTable[PREDICTION_TABLE_SIZE];
};

#endif