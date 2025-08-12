#include "Writeback.h"

WritebackStage::WritebackStage(RegFile& rf_, bool writeback_first_) : rf(rf_), writeback_first(writeback_first_) {}

void WritebackStage::writeback(const MEM_WB& mem_wb) {
    if (mem_wb.instr.op == OP_ADD) {
        rf.schedule_write(mem_wb.instr.rd, mem_wb.alu_out);
    } else if (mem_wb.instr.op == OP_LW) {
        rf.schedule_write(mem_wb.instr.rd, mem_wb.mem_data);
    }

    if (mem_wb.instr.op == OP_WFI) {
        std::cout << "WFI retired. Stopping simulation." << std::endl;
        sc_stop();
    }

    if (writeback_first) {
        rf.commit();
    }
}

void WritebackStage::commit() {
    if (!writeback_first) {
        rf.commit();
    }
}
