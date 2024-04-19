#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <SDL2/SDL_mixer.h>

class Audio {
  public:
    Audio() = default;
    ~Audio();

    void init_audio();
    void play_beep_sound();

  private:
    Mix_Chunk *m_beep_sound;
};

#endif