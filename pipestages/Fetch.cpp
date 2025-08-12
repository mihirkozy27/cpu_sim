#include "Fetch.h"

FetchStage::FetchStage() {}

IF_ID FetchStage::fetch(uint32_t pc, const std::vector<Instr>& imem) {
    IF_ID next_if_id;
    next_if_id.pc = pc;
    uint32_t idx = pc / 4;
    if (idx < imem.size())
        next_if_id.instr = imem[idx];
    else
        next_if_id.instr = Instr();
    return next_if_id;
}
