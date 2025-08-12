#ifndef MEMORY_H
#define MEMORY_H

#include "../components/ISA.h"
#include "../components/DataMemory.h"

class MemoryStage {
public:
    MemoryStage(DataMemory& dmem_);
    MEM_WB memory(const EX_MEM& ex_mem);

private:
    DataMemory& dmem;
};

#endif
