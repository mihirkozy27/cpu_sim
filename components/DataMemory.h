#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <vector>
#include <cstdint>
#include <iostream>

class DataMemory {
public:
    DataMemory(size_t words = 4096);

    int32_t read_word(uint32_t addr_word) const;

    void write_word(uint32_t addr_word, int32_t value);

    void dump(uint32_t words = 8) const;

private:
    std::vector<int32_t> mem;
};

#endif