#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <array>
#include <cstdint>

class Memory {
  public:
    Memory();

    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);

  private:
    static constexpr uint16_t MEMORY_SIZE = 0x1000;
    std::array<uint8_t, MEMORY_SIZE> m_memory;
};

#endif