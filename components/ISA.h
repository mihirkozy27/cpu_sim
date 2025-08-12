#ifndef ISA_H
#define ISA_H

#include <systemc.h>
#include <cstdint>
#include <iostream>

enum Opcode : int { OP_NOP = 0, OP_ADD, OP_LW, OP_SW, OP_WFI};

struct Instr {
    Opcode op;
    int rd, rs1, rs2, imm;
    Instr() : op(OP_NOP), rd(0), rs1(0), rs2(0), imm(0) {}
    Instr(Opcode o, int d, int s1, int s2, int im=0) : op(o), rd(d), rs1(s1), rs2(s2), imm(im) {}

    bool operator==(const Instr& other) const {
        return op == other.op && rd == other.rd && rs1 == other.rs1 && rs2 == other.rs2 && imm == other.imm;
    }
    bool operator!=(const Instr& other) const { return !(*this == other); }
};

struct IF_ID {
    uint32_t pc = 0;
    Instr instr;

    bool operator==(const IF_ID& other) const {
        return pc == other.pc && instr == other.instr;
    }
    bool operator!=(const IF_ID& other) const { return !(*this == other); }
};

struct ID_EX {
    uint32_t pc = 0;
    Instr instr;
    int32_t vrs1 = 0;
    int32_t vrs2 = 0;

    bool operator==(const ID_EX& other) const {
        return pc == other.pc && instr == other.instr && vrs1 == other.vrs1 && vrs2 == other.vrs2;
    }
    bool operator!=(const ID_EX& other) const { return !(*this == other); }
};

struct EX_MEM {
    uint32_t pc = 0;
    Instr instr;
    int32_t alu_out = 0;
    int32_t vrs2 = 0;

    bool operator==(const EX_MEM& other) const {
        return pc == other.pc && instr == other.instr && alu_out == other.alu_out && vrs2 == other.vrs2;
    }
    bool operator!=(const EX_MEM& other) const { return !(*this == other); }
};

struct MEM_WB {
    uint32_t pc = 0;
    Instr instr;
    int32_t mem_data = 0;
    int32_t alu_out = 0;

    bool operator==(const MEM_WB& other) const {
        return pc == other.pc && instr == other.instr && mem_data == other.mem_data && alu_out == other.alu_out;
    }
    bool operator!=(const MEM_WB& other) const { return !(*this == other); }
};

// For tracing, we provide sc_trace overloads:

inline void sc_trace(sc_trace_file* tf, const Opcode& op, const std::string& name) {
    sc_trace(tf, static_cast<int>(op), name);
}

inline void sc_trace(sc_trace_file* tf, const Instr& instr, const std::string& name) {
    sc_trace(tf, instr.op, name + ".op");
    sc_trace(tf, instr.rd, name + ".rd");
    sc_trace(tf, instr.rs1, name + ".rs1");
    sc_trace(tf, instr.rs2, name + ".rs2");
    sc_trace(tf, instr.imm, name + ".imm");
}

inline void sc_trace(sc_trace_file* tf, const IF_ID& r, const std::string& name) {
    sc_trace(tf, r.pc, name + ".pc");
    sc_trace(tf, r.instr, name + ".instr");
}

inline void sc_trace(sc_trace_file* tf, const ID_EX& r, const std::string& name) {
    sc_trace(tf, r.pc, name + ".pc");
    sc_trace(tf, r.instr, name + ".instr");
    sc_trace(tf, r.vrs1, name + ".vrs1");
    sc_trace(tf, r.vrs2, name + ".vrs2");
}

inline void sc_trace(sc_trace_file* tf, const EX_MEM& r, const std::string& name) {
    sc_trace(tf, r.pc, name + ".pc");
    sc_trace(tf, r.instr, name + ".instr");
    sc_trace(tf, r.alu_out, name + ".alu_out");
    sc_trace(tf, r.vrs2, name + ".vrs2");
}

inline void sc_trace(sc_trace_file* tf, const MEM_WB& r, const std::string& name) {
    sc_trace(tf, r.pc, name + ".pc");
    sc_trace(tf, r.instr, name + ".instr");
    sc_trace(tf, r.mem_data, name + ".mem_data");
    sc_trace(tf, r.alu_out, name + ".alu_out");
}

inline const char* op_name(Opcode o) {
    switch (o) {
        case OP_ADD: return "ADD";
        case OP_LW: return "LW";
        case OP_SW: return "SW";
        case OP_WFI: return "WFI";
        default: return "NOP";
    }
}

#endif
