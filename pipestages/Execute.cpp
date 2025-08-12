#include "Execute.h"

ExecuteStage::ExecuteStage() {}

EX_MEM ExecuteStage::execute(const ID_EX& id_ex) {
    EX_MEM next_ex_mem;
    next_ex_mem.pc = id_ex.pc;
    next_ex_mem.instr = id_ex.instr;
    next_ex_mem.vrs2 = id_ex.vrs2;
    if (id_ex.instr.op != OP_NOP) {
        next_ex_mem.alu_out = ALU::compute(id_ex.instr, id_ex.vrs1, id_ex.vrs2);
    }
    return next_ex_mem;
}
