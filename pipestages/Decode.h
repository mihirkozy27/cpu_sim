#ifndef DECODE_H
#define DECODE_H

#include "../components/ISA.h"
#include "../components/RegFile.h"

class DecodeStage {
public:
    DecodeStage();
    ID_EX decode(const IF_ID& if_id, const EX_MEM& ex_mem, const MEM_WB& mem_wb, const RegFile& rf);
};

#endif
