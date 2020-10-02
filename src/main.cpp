#include <stdio.h>
#include <iostream>
#include <instruction_memory.h>
#include <fetch.h>
#include <decode.h>
#include <execute.h>
#include <memory.h>
#include <write.h>
#include <control.h>
#include <forwarding.h>

using namespace std;

int main()
{
    instruction_memory instruct_mem("./mytest.txt");

    fetch fetchStage(&instruct_mem);
    decode decodeStage;
    forwarding forwardingUnit;
    execute executeStage;
    // none of our supported instructions actually uses any memory, so we don't even need it
    memory memoryStage(0);
    write writeStage;

    fetch_output out1;
    decode_output out2;
    forwarding_output outF;
    execute_output out3;
    memory_output out4;
    write_output out5;

    fetch_input in1;
    decode_input in2;
    forwarding_input inF;
    execute_input in3;
    memory_input in4;
    write_input in5;

    // signals that just get passed from one stage to the next. None of them actually get passed
    // from the first to the last, but all arrays have the same size just so any specific index
    // uniquely identifies the specifc stage where the signal is passing thru
    bool regWrite[5] = {0};
    bool memToReg[5] = {0};
    bool branched[5] = {0};
    int ALUResult[5];
    unsigned int targetReg[5];
    unsigned int PC[5];
    unsigned int rt[5];
    unsigned int rs[5];
    // this one is just for detecting that the program is finished
    opcode opc[5];

    // branchBubble indicates that the first pipeline stages should halt because of a conditional branch
    bool branchBubble = false;

    // in the first iteration only the first stage will do something
    int stagesToExecute = 1;
    int clockCounter = 0;
    while (1)
    {
        cout << "clockCounter: " << clockCounter << endl;

        // determine the inputs based on the previous outputs
        in5 = {
            .memToReg = memToReg[3],
            .regData = ALUResult[3]};
        in4 = {};
        in3 = {
            .op = out2.op,
            .immediate = out2.immediate,
            .offset = out2.offset,
            .rsValue = 0,
            .rtValue = 0,
            .PC = PC[1]};
        inF = {
            .rs = rs[1],
            .rsValue = out2.rsValue,
            .rt = rt[1],
            .rtValue = out2.rtValue,
            .executeRegWrite = regWrite[2],
            .executeTargetReg = targetReg[2],
            .result = out3.result,
            .writeRegWrite = regWrite[4],
            .writeTargetReg = targetReg[4],
            .writeData = out5.writeData,
        };
        in2 = {
            .i = out1.i,
            .regWrite = regWrite[4],
            .writeAddress = targetReg[4],
            .PC = out1.PC,
            .writeData = out5.writeData};
        in1 = {
            .branch = shouldBranch(out2.branch, out2.equal),
            .branchAddress = out2.branchAddress,
            .branched = branched[2]};

        // start at different points in the switch case statement based on how many stages should run (no breaks)
        switch (stagesToExecute)
        {
        case 5: // run all stages, from write-back to instruction fetch
            opc[4] = opc[3];
            regWrite[4] = regWrite[3];
            targetReg[4] = targetReg[3];
            out5 = writeStage.run(in5);
            cout << "   write_output: " << write_output_str(out5) << endl;
        case 4: // run 4 first stages, from memory-access to instruction fetch
            opc[3] = opc[2];
            regWrite[3] = regWrite[2];
            memToReg[3] = memToReg[2];
            targetReg[3] = targetReg[2];
            ALUResult[3] = out3.result;
            out4 = memoryStage.run(in4);
        case 3: // run 3 first stages, from execute to instruction fetch
            opc[2] = opc[1];
            branched[2] = branched[1];
            regWrite[2] = out2.regWrite;
            memToReg[2] = out2.memToReg;
            targetReg[2] = out2.targetReg;
            // the forwarding unit executes in parallel to the execute stage
            outF = forwardingUnit.run(inF);
            cout << "   forwarding_output: " << forwarding_output_str(outF) << endl;
            in3.rsValue = outF.rsValue;
            in3.rtValue = outF.rtValue;
            out3 = executeStage.run(in3);
            // the branch signal means we had a BEQ, so now the fetch stage has to determine
            // if the branch should occur and start fetching instructions again
            if (out2.branch)
                branchBubble = false;
            cout << "   execute_output: " << execute_output_str(out3) << endl;
        case 2: // run 2 first stages, from instruction-decode to instruction fetch
            opc[1] = out1.i.opc;
            PC[1] = out1.PC;
            rs[1] = out1.i.opx.rs;
            rt[1] = out1.i.opx.rt;
            branched[1] = out1.branched;
            out2 = decodeStage.run(in2);
            cout << "   decode_output: " << decode_output_str(out2) << endl;
        case 1: // run only first stage (instruction fetch)
            // if we have to generate a bubble we just "read" a NOP, else we make an actual read
            if (branchBubble)
                out1 = fetch_output{.i = {.opc = NOP}};
            else
                out1 = fetchStage.run(in1);

            if (isConditionalBranchInstruction(out1.i.opc))
                branchBubble = true;
            cout << "   fetch_output: " << fetch_output_str(out1) << endl;
            break;
        default:
            cout << "invalid state reached, stagesToExecute is " << stagesToExecute << endl;
            return 1;
        }
        if (out1.i.opc == OOB && opc[1] == OOB && opc[2] == OOB && opc[3] == OOB && opc[4] == OOB)
        {
            cout << "program finished on clock " << clockCounter << endl;
            return 0;
        }
        clockCounter++;
        if (stagesToExecute < 5)
            stagesToExecute++;
    }
}