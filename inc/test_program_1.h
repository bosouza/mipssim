#include <common.h>
#include <vector>

vector<instruction> testProgram1 = {
    {
        .opc = ADDI,
        .opx = {
            .rs = 0,
            .rt = 1,
            .rd = 0,
            .imm = 1,
        },
    },
    {
        .opc = ADDI,
        .opx = {
            .rs = 0,
            .rt = 2,
            .rd = 0,
            .imm = 2,
        },
    },
    {
        .opc = ADDI,
        .opx = {
            .rs = 0,
            .rt = 3,
            .rd = 0,
            .imm = 2,
        },
    },
    {
        .opc = NOP,
    },
    {
        .opc = NOP,
    },
    {
        .opc = NOP,
    },
    {
        .opc = NOP,
    },
    {
        .opc = BEQ,
        .opx = {
            .rs = 0,
            .rt = 3,
            .rd = 0,
            .imm = 2,
            .offset = 9,
        },
    },
    {
        .opc = ADDI,
        .opx = {
            .rs = 0,
            .rt = 1,
            .rd = 0,
            .imm = 1,
        },
    },
    {
        .opc = ADDI,
        .opx = {
            .rs = 0,
            .rt = 2,
            .rd = 0,
            .imm = 1,
        },
    },
    {
        .opc = SUBI,
        .opx = {
            .rs = 3,
            .rt = 3,
            .rd = 0,
            .imm = 1,
        },
    },
    {
        .opc = NOP,
    },
    {
        .opc = NOP,
    },
    {
        .opc = NOP,
    },
    {
        .opc = NOP,
    },
    {
        .opc = B,
        .opx = {
            .rs = 0,
            .rt = 0,
            .rd = 0,
            .imm = 0,
            .offset = -8,
        },
    },
    {
        .opc = NOP,
    },
};