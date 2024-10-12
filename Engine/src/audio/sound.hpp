#pragma once

#include <filesystem>
#include "audio_engine.hpp"

class Sound
{
public:
    Sound(const std::filesystem::path &filepath);
    ~Sound();

    void play();
    void pause();
    void stop();
    void set_volume(float volume);
    void set_pan(float pan);

    [[nodiscard]] float get_volume() const;
    [[nodiscard]] float get_seek() const;

    bool load_wav_file(const std::filesystem::path &filepath);
    bool is_loaded() const;
    bool is_playing() const;

private:
    bool m_Loaded = false;

    ALuint m_Buffer = 0;
    ALuint m_Source = 0;
};