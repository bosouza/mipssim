#ifndef WRITE_H_INCLUDED
#define WRITE_H_INCLUDED

#include <common.h>

struct write_input
{
};

class write
{
public:
    write(/* args */);
    ~write();
    void run(write_input);
};

#endif