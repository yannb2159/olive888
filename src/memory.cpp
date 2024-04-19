#include "memory.hpp"
#include <iostream>

Memory::Memory() { m_memory.fill(0x0); }

void Memory::write(uint16_t addr, uint8_t data) {
    if (addr > MEMORY_SIZE - 1) {
        std::cerr << "[Warning] Memory WRITE command is out of range !\n";
        return;
    }

    m_memory[addr] = data;
}

uint8_t Memory::read(uint16_t addr) {
    if (addr > MEMORY_SIZE - 1) {
        std::cerr << "[Warning] Memory READ command is out of range !\n";
        return 0x0;
    }

    return m_memory[addr];
}