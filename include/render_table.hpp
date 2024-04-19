#ifndef RENDER_TABLE_HPP
#define RENDER_TABLE_HPP

#include "consts.hpp"
#include <array>

enum class PixelState {
    SWITCHED_ON,
    SWITCHED_OFF,
};

class RenderTable {
  public:
    RenderTable();

    bool is_pixel_switched_on(uint8_t x, uint8_t y);
    void change_pixel_state_to(uint8_t x, uint8_t y, PixelState new_state);
    void clear();

  private:
    static constexpr uint16_t RENDER_TABLE_SIZE =
        CHIP8_SCREEN_WIDTH * CHIP8_SCREEN_HEIGHT;

    std::array<PixelState, RENDER_TABLE_SIZE> m_render_table;
};

#endif