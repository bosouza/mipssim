#include <memory.h>

memory::memory(unsigned int memorySize)
{
    this->mem = new int[memorySize];
}
memory::~memory()
{
    delete[] this->mem;
}
memory_output memory::run(memory_input in)
{
    // since we don't need to support load/store operations, this stage doesn't have to do anything
    return memory_output{};
}