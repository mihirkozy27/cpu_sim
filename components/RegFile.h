#ifndef REGFILE_H
#define REGFILE_H

#include <cstdint>
#include <iostream>

class RegFile {
public:
    RegFile();

    int32_t read(int idx) const;

    void schedule_write(int idx, int32_t value);

    void commit();

    void write_immediate(int idx, int32_t value);

    void dump(int n = 8) const;

private:
    int32_t regs[32];
    bool pending_we;
    int pending_waddr;
    int32_t pending_wdata;
};

#endif
