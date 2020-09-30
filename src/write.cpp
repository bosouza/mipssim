#include <write.h>

write::write()
{
}
write::~write()
{
}
write_output write::run(write_input in)
{
    write_output out;
    if (in.memToReg)
    {
        out.writeData = in.memData;
    }
    else
    {
        out.writeData = in.regData;
    }
    return out;
}

std::string write_output_str(write_output wo)
{
    std::ostringstream out;
    out << "{ writeData:" << wo.writeData << " }";
    return out.str();
}