#ifndef VIRTUAL_PROCESSOR_HPP
#define VIRTUAL_PROCESSOR_HPP

#include "audio.hpp"
#include "memory.hpp"
#include "render_table.hpp"
#include <array>
#include <cstdint>
#include <vector>

enum class KeyState { PRESSED, NOT_PRESSED };

class VirtualProcessor {
  public:
    VirtualProcessor();

    void set_key(uint8_t n, bool is_down);
    void update_timers(Audio &audio);
    bool get_draw_flag();
    void reset_draw_flag();
    uint16_t fetch_next_opcode(Memory &memory);
    void execute_instruction(uint16_t opcode, Memory &memory,
                             RenderTable &render_table);

  private:
    static constexpr uint8_t REGISTERS_COUNT = 16;
    static constexpr uint8_t KEYS_COUNT = 16;

    std::array<uint8_t, REGISTERS_COUNT> m_registers;
    std::array<KeyState, KEYS_COUNT> m_keys;
    std::vector<uint16_t> m_stack;

    uint16_t m_index_register;
    uint8_t m_delay_timer;
    uint8_t m_sound_timer;
    uint16_t m_program_counter;

    bool m_draw_flag;
};

#endif