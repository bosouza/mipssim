#include <fetch.h>
#include <iostream>

fetch::fetch(instruction_memory *mem, bool enablePrediction)
{
    this->mem = mem;
    this->PC = 0;
    this->predictionEnabled = enablePrediction;
}
fetch::~fetch()
{
}
fetch_output fetch::run(fetch_input in)
{
    if (in.branch)
    {
        this->PC = in.branchAddress;
    }
    auto next_instruction = this->mem->getInstruction(this->PC);
    auto currentPC = this->PC;
    if (next_instruction.opc == B)
        this->PC += next_instruction.opx.offset * 4;
    else
        this->PC += 4;
    return fetch_output{.i = next_instruction, .PC = currentPC};
}

std::string fetch_output_str(fetch_output fo)
{
    std::ostringstream out;
    out << "{ i.opc:" << fo.i.opc << " PC:" << fo.PC << " rs:" << fo.i.opx.rs << " rt:" << fo.i.opx.rt
        << " imm:" << fo.i.opx.imm << " offset:" << fo.i.opx.offset << " }";
    return out.str();
}