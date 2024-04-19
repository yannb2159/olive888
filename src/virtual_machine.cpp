#include "virtual_machine.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

void VirtualMachine::init_vm_audio() { m_audio.init_audio(); }

void VirtualMachine::load_rom_from_file(const std::string &rom_path) {
    std::ifstream rom_file(rom_path, std::ios::binary);

    if (!rom_file.is_open())
        throw std::runtime_error("[Error] Unable to open the ROM file !");

    rom_file.seekg(0, std::ios::end);
    std::size_t rom_buf_size = rom_file.tellg();
    rom_file.seekg(0, std::ios::beg);

    std::vector<uint8_t> rom_buf;

    rom_buf.reserve(rom_buf_size);
    rom_file.read(reinterpret_cast<char *>(rom_buf.data()), rom_buf_size);
    rom_file.close();

    if (rom_buf_size >= MAX_ROM_SIZE)
        throw std::runtime_error(
            "[Error] This ROM is too big to fit into memory !");

    // load fontset into memory before we transfer the temp rom buffer to the
    // memory.
    for (std::size_t fontset_index = 0; fontset_index < FONTSET_SIZE;
         fontset_index++) {
        m_memory.write(fontset_index, FONTSET[fontset_index]);
    }

    for (std::size_t buf_index = 0; buf_index < rom_buf_size; buf_index++) {
        m_memory.write(buf_index + PROCESSOR_INTERNAL_PROGRAM_COUNTER_START,
                       rom_buf[buf_index]);
    }

    std::cout << "[Info] ROM loaded successfully into the memory !\n";
}

void VirtualMachine::set_key(uint8_t n, bool is_down) {
    m_virtual_processor.set_key(n, is_down);
}

void VirtualMachine::execute_processor_instruction() {
    uint16_t opcode = m_virtual_processor.fetch_next_opcode(m_memory);
    m_virtual_processor.execute_instruction(opcode, m_memory, m_render_table);
}

void VirtualMachine::update_processor_timers() {
    m_virtual_processor.update_timers(m_audio);
}

bool VirtualMachine::screen_need_repaint() {
    return m_virtual_processor.get_draw_flag();
}

void VirtualMachine::disable_repaint() {
    m_virtual_processor.reset_draw_flag();
}

bool VirtualMachine::is_pixel_switched_on(uint8_t x, uint8_t y) {
    return m_render_table.is_pixel_switched_on(x, y);
}