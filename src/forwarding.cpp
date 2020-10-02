#include <forwarding.h>
#include <iostream>
#include <sstream>

forwarding::forwarding()
{
}

forwarding::~forwarding()
{
}

forwarding_output forwarding::run(forwarding_input in)
{
    forwarding_output out;
    // forwading from the execute stage takes precedence from the write-back stage, as that's the
    // newest value for the register, and the one that should be observed by the current instruction

    // forward rs
    out.rsValue = in.rsValue;
    if (in.writeRegWrite && (in.rs == in.writeTargetReg))
        out.rsValue = in.writeData;
    if (in.executeRegWrite && (in.rs == in.executeTargetReg))
        out.rsValue = in.result;

    // forward rt
    out.rtValue = in.rtValue;
    if (in.writeRegWrite && (in.rt == in.writeTargetReg))
        out.rtValue = in.writeData;
    if (in.executeRegWrite && (in.rt == in.executeTargetReg))
        out.rtValue = in.result;

    return out;
}

std::string forwarding_output_str(forwarding_output fout)
{
    std::ostringstream out;
    out << "{ rsValue:" << fout.rsValue << " rtValue" << fout.rtValue << " }";
    return out.str();
}