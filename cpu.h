#ifndef CPU_H
#define CPU_H

#include <systemc.h>
#include <vector>
#include "components/ISA.h"
#include "components/RegFile.h"
#include "components/DataMemory.h"

#include "pipestages/Fetch.h"
#include "pipestages/Decode.h"
#include "pipestages/Execute.h"
#include "pipestages/Memory.h"
#include "pipestages/Writeback.h"

SC_MODULE(IndustryStyleCPU) {
    sc_in<bool> clk;

    IndustryStyleCPU(sc_module_name name);

    void load_program(const std::vector<Instr>& program);
    void poke_reg(int idx, int32_t val);
    void dump_state() const;

private:
    RegFile rf;
    DataMemory dmem;

    std::vector<Instr> imem;

    IF_ID if_id_reg;
    ID_EX id_ex_reg;
    EX_MEM ex_mem_reg;
    MEM_WB mem_wb_reg;

    uint32_t pc;
    unsigned long long cycle;
    bool writeback_first;

    FetchStage fetch_stage;
    DecodeStage decode_stage;
    ExecuteStage execute_stage;
    MemoryStage memory_stage;
    WritebackStage writeback_stage;

    void step();

    void debug_print() const;
};

#endif
