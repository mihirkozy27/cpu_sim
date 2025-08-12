#ifndef WRITEBACK_H
#define WRITEBACK_H

#include "../components/ISA.h"
#include "../components/RegFile.h"

class WritebackStage {
public:
    WritebackStage(RegFile& rf_, bool writeback_first_);
    void writeback(const MEM_WB& mem_wb);
    void commit();

private:
    RegFile& rf;
    bool writeback_first;
};

#endif
