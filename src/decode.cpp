#include <decode.h>
#include <control.h>
#include <iostream>

decode::decode()
{
}

decode::~decode()
{
}

decode_output decode::run(decode_input in)
{
    // first write, then read
    if (in.regWrite)
        this->writeReg(in.writeAddress, in.writeData);

    decode_output out;
    // read rs and rt no matter what, if it's garbage the other stages just won't use it
    out.rsValue = this->readReg(in.i.opx.rs);
    out.rtValue = this->readReg(in.i.opx.rt);
    out.op = in.i.opc;
    out.immediate = in.i.opx.imm;
    out.offset = in.i.opx.offset;
    out.memToReg = shouldLoadFromMemory(in.i.opc);
    out.regWrite = shouldWriteToRegister(in.i.opc);
    out.targetReg = determineTargetRegister(in.i.opc, in.i.opx.rd, in.i.opx.rt);
    out.branch = isConditionalBranchInstruction(in.i.opc);
    return out;
}

void decode::writeReg(unsigned int address, int data)
{
    if (!isValidRegister(address))
    {
        std::cout << "tried to write to an invalid register: " << address << std::endl;
        throw;
    }
    this->registers[address] = data;
}

// read registry identified by address. If an invalid address is provided, it just returns 0
int decode::readReg(unsigned int address)
{
    if (!isValidRegister(address))
        address = 0;

    if (address == 0)
        return 0;

    return this->registers[address];
}

std::string decode_output_str(decode_output dout)
{
    std::ostringstream out;
    out << "{ rsValue:" << dout.rsValue << " rtValue:" << dout.rtValue << " op:" << dout.op
        << " immediate:" << dout.immediate << " regWrite:" << dout.regWrite
        << " branch:" << dout.branch << " offset:" << dout.offset
        << " memToReg:" << dout.memToReg << " targetReg:" << dout.targetReg << " }";
    return out.str();
}