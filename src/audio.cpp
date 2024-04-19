#include "audio.hpp"
#include <iostream>
#include <stdexcept>

Audio::~Audio() {
    std::cout << "[Info] Freeing SDL mixer resources !\n";
    if (m_beep_sound)
        free(m_beep_sound);
    Mix_CloseAudio();
}

void Audio::init_audio() {
    if (Mix_OpenAudio(44100, AUDIO_S16LSB, MIX_DEFAULT_CHANNELS, 2048) < 0)
        throw std::runtime_error("[Error] Unable to initialize SDL_mixer !");

    m_beep_sound = Mix_LoadWAV("beep.wav");
    if (m_beep_sound == nullptr)
        throw std::runtime_error("[Error] Unable to load beep.wav");

    Mix_VolumeChunk(m_beep_sound, MIX_MAX_VOLUME / 2);
}

void Audio::play_beep_sound() {
    int check = Mix_PlayChannel(-1, m_beep_sound, 0);
    if (check == -1)
        std::cerr << "[Warning] Unable to play beep.wav !\n";
}