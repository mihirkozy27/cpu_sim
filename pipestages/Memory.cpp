#include "Memory.h"

MemoryStage::MemoryStage(DataMemory& dmem_) : dmem(dmem_) {}

MEM_WB MemoryStage::memory(const EX_MEM& ex_mem) {
    MEM_WB next_mem_wb;
    next_mem_wb.pc = ex_mem.pc;
    next_mem_wb.instr = ex_mem.instr;
    next_mem_wb.alu_out = ex_mem.alu_out;
    if (ex_mem.instr.op == OP_LW) {
        uint32_t word_index = static_cast<uint32_t>(ex_mem.alu_out) / 4;
        next_mem_wb.mem_data = dmem.read_word(word_index);
    } else if (ex_mem.instr.op == OP_SW) {
        uint32_t word_index = static_cast<uint32_t>(ex_mem.alu_out) / 4;
        dmem.write_word(word_index, ex_mem.vrs2);
    }
    return next_mem_wb;
}
