#include "virtual_machine.hpp"
#include <SDL2/SDL.h>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cerr << "[Error] No ROM provided !\n";
        std::cerr << "[Error] Usage : ./olive888 <rom.rom/rom.ch8>\n";
        return EXIT_FAILURE;
    }

    std::string rom_path = std::string(argv[1]);

    VirtualMachine chip8_vm;

    try {
        chip8_vm.init_vm_audio();
        chip8_vm.load_rom_from_file(rom_path);
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "[Error] Unable to initialize SDL !\n";
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow(
        "olive888 by Yann BOYER", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_SetWindowMaximumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetWindowResizable(window, SDL_FALSE);

    if (window == nullptr) {
        std::cerr << "[Error] Unable to initialize the window !\n";
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == nullptr) {
        std::cerr << "[Error] Unable to initialize the renderer !\n";
        return EXIT_FAILURE;
    }

    bool is_running = true;

    uint8_t div_cycles = 0;

    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                std::cout << "[Info] Exiting...\n";
                is_running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_1:
                    chip8_vm.set_key(0x1, true);
                    break;
                case SDLK_2:
                    chip8_vm.set_key(0x2, true);
                    break;
                case SDLK_3:
                    chip8_vm.set_key(0x3, true);
                    break;
                case SDLK_4:
                    chip8_vm.set_key(0xC, true);
                    break;
                case SDLK_q:
                    chip8_vm.set_key(0x4, true);
                    break;
                case SDLK_w:
                    chip8_vm.set_key(0x5, true);
                    break;
                case SDLK_e:
                    chip8_vm.set_key(0x6, true);
                    break;
                case SDLK_r:
                    chip8_vm.set_key(0xD, true);
                    break;
                case SDLK_a:
                    chip8_vm.set_key(0x7, true);
                    break;
                case SDLK_s:
                    chip8_vm.set_key(0x8, true);
                    break;
                case SDLK_d:
                    chip8_vm.set_key(0x9, true);
                    break;
                case SDLK_f:
                    chip8_vm.set_key(0xE, true);
                    break;
                case SDLK_z:
                    chip8_vm.set_key(0xA, true);
                    break;
                case SDLK_x:
                    chip8_vm.set_key(0x0, true);
                    break;
                case SDLK_c:
                    chip8_vm.set_key(0xB, true);
                    break;
                case SDLK_v:
                    chip8_vm.set_key(0xF, true);
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_1:
                    chip8_vm.set_key(0x1, false);
                    break;
                case SDLK_2:
                    chip8_vm.set_key(0x2, false);
                    break;
                case SDLK_3:
                    chip8_vm.set_key(0x3, false);
                    break;
                case SDLK_4:
                    chip8_vm.set_key(0xC, false);
                    break;
                case SDLK_q:
                    chip8_vm.set_key(0x4, false);
                    break;
                case SDLK_w:
                    chip8_vm.set_key(0x5, false);
                    break;
                case SDLK_e:
                    chip8_vm.set_key(0x6, false);
                    break;
                case SDLK_r:
                    chip8_vm.set_key(0xD, false);
                    break;
                case SDLK_a:
                    chip8_vm.set_key(0x7, false);
                    break;
                case SDLK_s:
                    chip8_vm.set_key(0x8, false);
                    break;
                case SDLK_d:
                    chip8_vm.set_key(0x9, false);
                    break;
                case SDLK_f:
                    chip8_vm.set_key(0xE, false);
                    break;
                case SDLK_z:
                    chip8_vm.set_key(0xA, false);
                    break;
                case SDLK_x:
                    chip8_vm.set_key(0x0, false);
                    break;
                case SDLK_c:
                    chip8_vm.set_key(0xB, false);
                    break;
                case SDLK_v:
                    chip8_vm.set_key(0xF, false);
                    break;
                default:
                    break;
                }
                break;
            }
        }

        try {
            chip8_vm.execute_processor_instruction();
            div_cycles++;
        } catch (std::exception &e) {
            std::cerr << e.what() << "\n";
            return EXIT_FAILURE;
        }

        if (chip8_vm.screen_need_repaint()) {
            for (uint8_t y = 0; y < CHIP8_SCREEN_HEIGHT; y++) {
                for (uint8_t x = 0; x < CHIP8_SCREEN_WIDTH; x++) {
                    SDL_Rect pixel = {x * SCALE_FACTOR, y * SCALE_FACTOR,
                                      SCALE_FACTOR, SCALE_FACTOR};
                    if (chip8_vm.is_pixel_switched_on(x, y))
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
                    else
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
                    SDL_RenderFillRect(renderer, &pixel);
                }
            }

            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);

            chip8_vm.disable_repaint();
        }

        if (div_cycles == TIMER_DIVISION_CLOCK) {
            chip8_vm.update_processor_timers();
            div_cycles = 0;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(CPU_CLOCK_DELAY));
    }

    SDL_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return EXIT_SUCCESS;
}
