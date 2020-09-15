#include <fetch.h>
#include <iostream>

fetch::fetch(instruction_memory *mem)
{
    this->mem = mem;
    this->PC = 0;
}
fetch::~fetch()
{
}
fetch_output fetch::run()
{
    auto next_instruction = this->mem->getInstruction(this->PC);
    this->PC += 4;

    return fetch_output{.i = next_instruction};
}