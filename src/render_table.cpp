#include "render_table.hpp"
#include <iostream>

RenderTable::RenderTable() { m_render_table.fill(PixelState::SWITCHED_OFF); }

bool RenderTable::is_pixel_switched_on(uint8_t x, uint8_t y) {
    if (x > CHIP8_SCREEN_WIDTH || y > CHIP8_SCREEN_HEIGHT) {
        std::cerr << "[Warning] Invalid coordinates -> X : " << unsigned(x)
                  << " Y : " << unsigned(y) << "\n";
        return false;
    }

    return m_render_table[y * CHIP8_SCREEN_WIDTH + x] ==
           PixelState::SWITCHED_ON;
}

void RenderTable::change_pixel_state_to(uint8_t x, uint8_t y,
                                        PixelState new_state) {
    if (x > CHIP8_SCREEN_WIDTH || y > CHIP8_SCREEN_HEIGHT) {
        std::cerr << "[Warning] Invalid coordinates -> X : " << unsigned(x)
                  << " Y : " << unsigned(y) << "\n";
        return;
    }

    m_render_table[y * CHIP8_SCREEN_WIDTH + x] = new_state;
}

void RenderTable::clear() {
    for (uint8_t y = 0; y < CHIP8_SCREEN_HEIGHT; y++) {
        for (uint8_t x = 0; x < CHIP8_SCREEN_WIDTH; x++) {
            m_render_table[y * CHIP8_SCREEN_WIDTH + x] =
                PixelState::SWITCHED_OFF;
        }
    }
}