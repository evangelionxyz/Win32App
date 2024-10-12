#include "sound.hpp"
#include "core/window.hpp"

#include "core/console_manager.hpp"

#include <iostream>

Sound::Sound(const std::filesystem::path &filepath)
{
    if (load_wav_file(filepath))
    {
        alGenSources(1, &m_Source);
        alSourcei(m_Source, AL_BUFFER, m_Buffer);

        m_Loaded = true;
    }
}

Sound::~Sound()
{
    alDeleteSources(1, &m_Source);
    alDeleteBuffers(1, &m_Buffer);
}

void Sound::play()
{
    alSourcePlay(m_Source);
}

void Sound::pause()
{
    alSourcePause(m_Source);
}

void Sound::stop()
{
    alSourceStop(m_Source);
}

void Sound::set_volume(float volume)
{
    alSourcef(m_Source, AL_GAIN, volume);
}

void Sound::set_pan(float pan)
{
    ALfloat pos[] = {pan, 0.0f, 0.0f};
    alSourcefv(m_Source, AL_POSITION, pos);
}

float Sound::get_volume() const
{
    float volume;
    alGetSourcef(m_Source, AL_GAIN, &volume);
    return volume;
}

float Sound::get_seek() const
{
    float offset;
    alGetSourcef(m_Source, AL_SEC_OFFSET, &offset);
    return offset;
}

bool Sound::load_wav_file(const std::filesystem::path &filepath)
{
    auto &console = ConsoleManager::get_instance();

    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open())
    {
        std::string err_msg = console.push_error("[Sound] failed to open WAV file: {} not found", filepath);
        Window::show_message_box(err_msg, "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    WavHeader header;
    file.read(reinterpret_cast<char *>(&header), sizeof(WavHeader));

    if (std::strncmp(header.riff, "RIFF", 4) != 0
        || std::strncmp(header.wave, "WAVE", 4) != 0
        || std::strncmp(header.fmt, "fmt ", 4) != 0)
    {
        std::string err_msg = console.push_error("[Sound] invalid WAV file: {}", filepath);
        Window::show_message_box(err_msg, "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    ALenum format;
    switch (header.numChannels)
    {
    case 1: format = (header.bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16; break;
    case 2: format = format = (header.bitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16; break;
    default:
    {
        std::string err_msg = console.push_error("Unsupported channel count: {}", header.numChannels);
        Window::show_message_box(err_msg, "Error", MB_OK | MB_ICONERROR);
        return false;
    }
    }

    char *data = new char[header.dataSize];
    file.read(data, header.dataSize);
    file.close();

    alGenBuffers(1, &m_Buffer);
    alBufferData(m_Buffer, format, data, header.dataSize, header.sampleRate);

    delete[] data;

    return true;
}

bool Sound::is_loaded() const
{
    return m_Loaded;
}

bool Sound::is_playing() const
{
    ALint state;
    alGetSourcei(m_Source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}