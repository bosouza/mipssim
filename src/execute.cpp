#include <execute.h>

execute::execute()
{
}

execute::~execute()
{
}

execute_output execute::run(execute_input in)
{
    execute_output out;
    // B was already processed on fetch, don't need to do anything
    // NOP does nothing, also doesn't require any operations
    switch (in.op)
    {
    case ADD:
        out.result = in.rsValue + in.rtValue;
        break;
    case ADDI:
        out.result = in.rsValue + in.immediate;
        break;
    case SUB:
        out.result = in.rsValue - in.rtValue;
        break;
    case SUBI:
        out.result = in.rsValue - in.immediate;
        break;
    case BEQ:
        out.equal = in.rsValue == in.rtValue;
        out.branchAddress = in.PC + in.offset * 4;
        break;
    }

    return out;
}

std::string execute_output_str(execute_output eo)
{
    std::ostringstream out;
    out << "{ result:" << eo.result << " equal:" << eo.equal << " branchAddress:" << eo.branchAddress << " }";
    return out.str();
}
