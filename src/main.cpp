#include <stdio.h>
#include <iostream>
#include <instruction_memory.h>
#include <fetch.h>
#include <decode.h>
#include <execute.h>
#include <memory.h>
#include <write.h>

using namespace std;

int main()
{
    instruction_memory instruct_mem("./test1.txt");

    fetch fetchStage(&instruct_mem);
    decode decodeStage;
    execute executeStage;
    memory memoryStage;
    write writeStage;

    fetch_output out1;
    decode_output out2;
    execute_output out3;
    memory_output out4;

    // in the first iteration only the first stage will do something
    int stagesToExecute = 1;
    while (1)
    {
        // start at different points in the switch case statement based on how many stages should run (no breaks)
        switch (stagesToExecute)
        {
        case 5: // run all stages, from write-back to instruction fetch
        case 4: // run 4 first stages, from memory-access to instruction fetch
        case 3: // run 3 first stages, from execute to instruction fetch
        case 2: // run 2 first stages, from instruction-decode to instruction fetch
            out2 = decodeStage.run(decode_input{.i = out1.i});
        case 1: // run only first stage (instruction fetch)
            out1 = fetchStage.run();
            break;
        default:
            cout << "invalid state reached, stagesToExecute is " << stagesToExecute << endl;
            return 1;
        }
        if (stagesToExecute < 5)
            stagesToExecute++;
    }
}