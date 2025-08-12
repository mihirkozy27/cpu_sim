#ifndef ALU_H
#define ALU_H

#include "ISA.h"

struct ALU {
    static int32_t compute(const Instr& ins, int32_t a, int32_t b) {
        switch (ins.op) {
            case OP_ADD: return a + b;
            case OP_LW:
            case OP_SW: return a + ins.imm;
            default: return 0;
        }
    }
};

#endif
