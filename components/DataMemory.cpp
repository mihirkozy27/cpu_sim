#include "DataMemory.h"

DataMemory::DataMemory(size_t words) : mem(words, 0) {}

int32_t DataMemory::read_word(uint32_t addr_word) const {
    if (addr_word < mem.size()) return mem[addr_word];
    return 0;
}

void DataMemory::write_word(uint32_t addr_word, int32_t value) {
    if (addr_word < mem.size()) mem[addr_word] = value;
}

void DataMemory::dump(uint32_t words) const {
    for (uint32_t i = 0; i < words && i < mem.size(); ++i)
        std::cout << "m[" << i << "]=" << mem[i] << " ";
    std::cout << "\n";
}
