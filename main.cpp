#include <systemc.h>
#include "cpu.h"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    IndustryStyleCPU cpu("cpu");
    cpu.clk(clk);

    std::vector<Instr> prog = {
        Instr(OP_ADD, 3, 1, 2),
        Instr(OP_SW,  0, 0, 3, 4),
        Instr(OP_LW,  4, 0, 0, 4),
        Instr(OP_WFI, 0, 0, 0, 0)
    };

    cpu.load_program(prog);
    cpu.poke_reg(1, 10);
    cpu.poke_reg(2, 20);

    sc_start();

    cpu.dump_state();

    return 0;
}
