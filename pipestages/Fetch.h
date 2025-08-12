#ifndef FETCH_H
#define FETCH_H

#include "../components/ISA.h"
#include <vector>

class FetchStage {
public:
    FetchStage();
    IF_ID fetch(uint32_t pc, const std::vector<Instr>& imem);
};

#endif
