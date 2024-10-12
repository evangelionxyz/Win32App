#include "audio_engine.hpp"

#include "core/console_manager.hpp"
#include "core/window.hpp"

#include <windows.h>

AudioEngine::AudioEngine()
{
    m_Device = alcOpenDevice(nullptr);
    if (!m_Device)
    {
        std::string err_msg = ConsoleManager::get_instance().push_error("[Audio Engine] failed to create device");
        Window::show_message_box(err_msg, "Error", MB_OK | MB_ICONERROR);

        exit(EXIT_FAILURE);
    }

    m_Context = alcCreateContext(m_Device, nullptr);
    alcMakeContextCurrent(m_Context);
}

AudioEngine::~AudioEngine()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_Context);
    alcCloseDevice(m_Device);
}

void AudioEngine::add_sound(Sound *sound)
{
    m_Sounds.push_back(sound);
}

void AudioEngine::update()
{

}
