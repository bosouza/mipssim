#include <fetch.h>
#include <control.h>
#include <iostream>

fetch::fetch(instruction_memory *mem, bool enablePrediction)
{
    this->mem = mem;
    this->PC = 0;
    this->predictionEnabled = enablePrediction;
    for (int i = 0; i < PREDICTION_TABLE_SIZE; i++)
        this->branchTable[i] = DONT_BRANCH;
}
fetch::~fetch()
{
}
fetch_output fetch::run(fetch_input in)
{
    fetch_output out;
    if (this->predictionEnabled)
    {
        if (in.execBEQ)
        {
            // if our branch prediction misssed 2 cycles ago, we'll have to just follow the correct branch
            if (in.branched != in.branch)
            {
                this->PC = in.branchAddress;
                out.invalidatePrediction = true;
                // update branch table with the missed predition
                this->updateBranch(in.BEQAddress, false);
            }
            else
            {
                // update branch table with the correct predition
                this->updateBranch(in.BEQAddress, true);
            }
        }
    }
    else
    {
        // if prediction is disabled we just continue reading, the caller is responsible for inserting a bubble
        if (in.branch)
            this->PC = in.branchAddress;
    }
    out.i = this->mem->getInstruction(this->PC);
    out.PC = this->PC;
    if (out.i.opc == B)
        this->PC += out.i.opx.offset * 4;
    else if (out.i.opc == BEQ)
    {
        if (this->predictionEnabled)
        {
            unsigned int targetAddress = this->PC + out.i.opx.offset * 4;
            if (this->shouldBranch(this->PC))
            {
                this->PC = targetAddress;
                out.branched = true;
            }
            else
            {
                this->PC += 4;
                out.branched = false;
            }
        }
        else
        {
            out.insertBubble = true;
            this->PC += 4;
        }
    }
    else
        this->PC += 4;
    return out;
}

bool fetch::shouldBranch(unsigned int address)
{
    return true;
    switch (this->branchTable[address % PREDICTION_TABLE_SIZE])
    {
    case DONT_BRANCH:
        return false;
    case MISSED_DONT_BRANCH:
        return false;
    case BRANCH:
        return true;
    case MISSED_BRANCH:
        return true;
    default:
        std::cout << "this case shouldn't happen" << std::endl;
        throw;
    }
}

void fetch::updateBranch(unsigned int address, bool hit)
{
    auto tableAddress = address % PREDICTION_TABLE_SIZE;
    auto currentState = this->branchTable[tableAddress];
    if (hit)
    {
        // if we missed our second last predition (MISSED_BRANCH or MISSED_DONT_BRANCH) but now the same
        // predition was a hit, make the same predition next time
        if (currentState == MISSED_BRANCH)
            this->branchTable[tableAddress] = BRANCH;
        if (currentState == MISSED_DONT_BRANCH)
            this->branchTable[tableAddress] = DONT_BRANCH;
    }
    else
    {
        // if we missed the last predition there are some updates to be done based on the second last
        // prediction result. In general, if we'd missed the second to last we now go to the opposite,
        // while having hit the second to last means we go to the opposite on the next miss
        switch (currentState)
        {
        case DONT_BRANCH:
            this->branchTable[tableAddress] = MISSED_DONT_BRANCH;
            break;
        case MISSED_DONT_BRANCH:
            this->branchTable[tableAddress] = BRANCH;
            break;
        case BRANCH:
            this->branchTable[tableAddress] = MISSED_BRANCH;
            break;
        case MISSED_BRANCH:
            this->branchTable[tableAddress] = DONT_BRANCH;
            break;
        default:
            std::cout << "this case shouldn't happen" << std::endl;
            throw;
        }
    }
}

std::string fetch_output_str(fetch_output fo)
{
    std::ostringstream out;
    out << "{ i.opc:" << fo.i.opc << " PC:" << fo.PC << " rs:" << fo.i.opx.rs << " rt:" << fo.i.opx.rt
        << " offset:" << fo.i.opx.offset << " invalidatePrediction:" << fo.invalidatePrediction
        << " imm:" << fo.i.opx.imm << " insertBubble:" << fo.insertBubble
        << " branched:" << fo.branched << " }";
    return out.str();
}
