#include "cpu.h"
#include <iomanip>

IndustryStyleCPU::IndustryStyleCPU(sc_module_name name)
    : sc_module(name),
      dmem(4096),
      pc(0),
      cycle(0),
      writeback_first(true),
      memory_stage(dmem),
      writeback_stage(rf, writeback_first) {
    SC_METHOD(step);
    sensitive << clk.pos();
    dont_initialize();
}

void IndustryStyleCPU::load_program(const std::vector<Instr>& program) {
    imem = program;
    pc = 0;
}

void IndustryStyleCPU::poke_reg(int idx, int32_t val) {
    rf.write_immediate(idx, val);
}

void IndustryStyleCPU::dump_state() const {
    std::cout << "Cycle: " << cycle << " PC: " << pc << "\n";
    rf.dump(8);
    dmem.dump(8);
}

void IndustryStyleCPU::step() {
    ++cycle;

    // Writeback stage
    writeback_stage.writeback(mem_wb_reg);

    // Memory stage
    mem_wb_reg = memory_stage.memory(ex_mem_reg);

    // Execute stage
    ex_mem_reg = execute_stage.execute(id_ex_reg);

    // Decode stage
    id_ex_reg = decode_stage.decode(if_id_reg, ex_mem_reg, mem_wb_reg, rf);

    // Fetch stage
    if_id_reg = fetch_stage.fetch(pc, imem);
    pc += 4;

    writeback_stage.commit();

    debug_print();
}

void IndustryStyleCPU::debug_print() const {
    std::cout << "cyc=" << std::setw(3) << cycle
              << " pc=" << std::setw(3) << if_id_reg.pc
              << " IF:" << op_name(if_id_reg.instr.op)
              << " | ID:" << op_name(id_ex_reg.instr.op)
              << " | EX:" << op_name(ex_mem_reg.instr.op)
              << " | MEM:" << op_name(mem_wb_reg.instr.op)
              << "\n";
}
