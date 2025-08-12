#ifndef EXECUTE_H
#define EXECUTE_H

#include "../components/ISA.h"
#include "../components/Alu.h"

class ExecuteStage {
public:
    ExecuteStage();
    EX_MEM execute(const ID_EX& id_ex);
};

#endif
