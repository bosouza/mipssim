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

int main(int argc, char *argv[])
{
    bool prediction = false;
    ostream log(nullptr);

    if (argc < 2)
    {
        cout << "the path to file wasn't specified at the program call. That will be finished" << endl;
        return 1;
    }

    for (int i = 2; i < argc; i++)
    {
        if (!string(argv[i]).compare("--prediction"))
            prediction = true;
        if (!string(argv[i]).compare("-v"))
            log.rdbuf(cout.rdbuf());
    }

    instruction_memory instruct_mem(argv[1]);

    fetch fetchStage(&instruct_mem, prediction);
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
    bool branch[5] = {0};
    int ALUResult[5];
    unsigned int targetReg[5];
    unsigned int PC[5];
    unsigned int rt[5];
    unsigned int rs[5];
    // this one is just for detecting that the program is finished
    opcode opc[5];

    // branchBubble indicates that the first pipeline stages should halt because of a conditional branch
    bool branchBubble = false;
    // discardInstruction indicates that the execute stage should ignore the instruction coming from decode
    bool discardInstruction = false;

    // in the first iteration only the first stage will do something
    int stagesToExecute = 1;
    int clockCounter = 0;
    while (1)
    {
        log << "clockCounter: " << clockCounter << endl;

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
            .writeRegWrite = false, // we consume this directly from the execute stage
            .writeTargetReg = 0,    // we consume this directly from the execute stage
            .writeData = 0,         // we consume this directly from the execute stage
        };
        in2 = {
            .i = out1.i,
            .regWrite = 0,     // we consume this directly from the write back stage
            .writeAddress = 0, // we consume this directly from the write back stage
            .PC = out1.PC,
            .writeData = 0}; // we consume this directly from the write back stage
        in1 = {
            .branch = false,    // we consume this directly from the execute stage
            .branchAddress = 0, // we consume this directly from the execute stage
            .branched = 0};     // we consume this directly from the execute stage

        // start at different points in the switch case statement based on how many stages should run (no breaks)
        switch (stagesToExecute)
        {
        case 5: // run all stages, from write-back to instruction fetch
            opc[4] = opc[3];
            regWrite[4] = regWrite[3];
            targetReg[4] = targetReg[3];
            out5 = writeStage.run(in5);
            log << "   write_output: " << write_output_str(out5) << endl;
        case 4: // run 4 first stages, from memory-access to instruction fetch
            opc[3] = opc[2];
            regWrite[3] = regWrite[2];
            memToReg[3] = memToReg[2];
            targetReg[3] = targetReg[2];
            ALUResult[3] = out3.result;
            out4 = memoryStage.run(in4);
        case 3: // run 3 first stages, from execute to instruction fetch
            if (discardInstruction)
            {
                opc[2] = NOP;
                branched[2] = false;
                regWrite[2] = false;
                memToReg[2] = false;
                targetReg[2] = 0;
                branch[2] = false;
            }
            else
            {
                opc[2] = opc[1];
                branched[2] = branched[1];
                regWrite[2] = out2.regWrite;
                memToReg[2] = out2.memToReg;
                targetReg[2] = out2.targetReg;
                branch[2] = out2.branch;
                PC[2] = PC[1];
            }

            // we consume data directly from the write-back stage, since there's no barrier there, and its output
            // will asynchronously propagate to the execute stage input
            inF.writeRegWrite = regWrite[4];
            inF.writeTargetReg = targetReg[4];
            inF.writeData = out5.writeData;

            // the forwarding unit executes in parallel to the execute stage
            outF = forwardingUnit.run(inF);
            log << "   forwarding_output: " << forwarding_output_str(outF) << endl;
            in3.rsValue = outF.rsValue;
            in3.rtValue = outF.rtValue;
            if (discardInstruction)
                in3 = execute_input{.op = NOP};
            out3 = executeStage.run(in3);
            // the branch signal means we had a BEQ, so now the fetch stage has to determine
            // if the branch should occur and start fetching instructions again
            if (out2.branch)
                branchBubble = false;
            log << "   execute_output: " << execute_output_str(out3) << endl;
        case 2: // run 2 first stages, from instruction-decode to instruction fetch
            opc[1] = out1.i.opc;
            PC[1] = out1.PC;
            rs[1] = out1.i.opx.rs;
            rt[1] = out1.i.opx.rt;
            branched[1] = out1.branched;
            // since the instruction decode stage only runs in the half end of the cycle, we can actually
            // consume the signals from the write-back stage, which runs only in the first half
            in2.regWrite = regWrite[4];
            in2.writeAddress = targetReg[4];
            in2.writeData = out5.writeData;
            out2 = decodeStage.run(in2);
            log << "   decode_output: " << decode_output_str(out2) << endl;
        case 1: // run only first stage (instruction fetch)
            // if we have to generate a bubble we just "read" a NOP, else we make an actual read
            if (branchBubble)
                out1 = fetch_output{.i = {.opc = NOP}};
            else
            {
                // since the instruction fetch stage starts on the end half of the cycle, and the branch-related
                // stuff from execute is calculated in the first half, we can actually consume it directly here
                in1.branch = shouldBranch(branch[2], out3.equal);
                in1.branchAddress = out3.branchAddress;
                in1.branched = branched[2];
                in1.execBEQ = opc[2];
                in1.BEQAddress = PC[2];
                out1 = fetchStage.run(in1);
            }
            discardInstruction = out1.invalidatePrediction;
            branchBubble = out1.insertBubble;
            log << "   fetch_output: " << fetch_output_str(out1) << endl;
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

    return 0;
}