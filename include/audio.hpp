#ifndef AUDIO_HPP
#define AUDIO_HPP

#ifdef __APPLE__
  #include <SDL_mixer.h>
#else
  #include <SDL2/SDL_mixer.h>
#endif

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
