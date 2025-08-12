#include "Decode.h"

DecodeStage::DecodeStage() {}

ID_EX DecodeStage::decode(const IF_ID& if_id, const EX_MEM& ex_mem, const MEM_WB& mem_wb, const RegFile& rf) {
    ID_EX next_id_ex;
    next_id_ex.pc = if_id.pc;
    next_id_ex.instr = if_id.instr;

    auto read_with_forward = [&](int reg) -> int32_t {
        if (reg == 0) return 0;
        // EX->ID forward
        if (ex_mem.instr.op == OP_ADD && ex_mem.instr.rd == reg) return ex_mem.alu_out;
        // MEM/WB forward for ALU results
        if (mem_wb.instr.op == OP_ADD && mem_wb.instr.rd == reg) return mem_wb.alu_out;
        // MEM/WB forward for loads
        if (mem_wb.instr.op == OP_LW && mem_wb.instr.rd == reg) return mem_wb.mem_data;
        return rf.read(reg);
    };

    if (if_id.instr.op != OP_NOP) {
        next_id_ex.vrs1 = read_with_forward(if_id.instr.rs1);
        next_id_ex.vrs2 = read_with_forward(if_id.instr.rs2);
    }

    return next_id_ex;
}
