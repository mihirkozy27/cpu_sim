#include "RegFile.h"

RegFile::RegFile() : pending_we(false), pending_waddr(0), pending_wdata(0) {
    for (int i = 0; i < 32; i++) regs[i] = 0;
}

int32_t RegFile::read(int idx) const {
    return (idx == 0) ? 0 : regs[idx];
}

void RegFile::schedule_write(int idx, int32_t value) {
    pending_we = true;
    pending_waddr = idx;
    pending_wdata = value;
}

void RegFile::commit() {
    if (pending_we && pending_waddr != 0)
        regs[pending_waddr] = pending_wdata;
    pending_we = false;
}

void RegFile::write_immediate(int idx, int32_t value) {
    if (idx != 0)
        regs[idx] = value;
}

void RegFile::dump(int n) const {
    for (int i = 0; i < n; i++)
        std::cout << "r" << i << "=" << regs[i] << " ";
    std::cout << "\n";
}
