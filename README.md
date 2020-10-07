# MIPSsim

This simple simulator is a school project for a MIPS-like 5 stage pipelined processor. The only supported instructions are ADD , ADDI, SUB, SUBI, BEQ, B (SUBI and B aren't even real instructions). We print some statistics on the number of executed instructions and number of dirty instructions.

# Documentation
There's only this file and some diagrams we used in the `/docs` folder. We didn't implement any of those 100%, but got _inspired_ by it.

# Build
Just run `make build` on the project root

# Run
`./simulator` will run the built binary. There are 2 flags, `-v` for outputing debug messages (output of each stage on each clock cycle), and `--prediction` to enable the branch prediction algorithm.