#pragma once

#pragma once

#include "core/types.h"

#include <string>
#include <vector>

#include <fstream>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

struct WavHeader
{
    char riff[4];          // "RIFF"
    u32 chunkSize;         // Overall size of the file
    char wave[4];          // "WAVE"
    char fmt[4];           // "fmt "
    u32 subchunk1Size;     // Size of fmt chunk
    u16 audioFormat;       // Audio format (PCM = 1)
    u16 numChannels;       // Number of channels
    u32 sampleRate;        // Sampling rate
    u32 byteRate;          // byteRate = sampleRate * numChannels * bitsPerSample/8
    u16 blockAlign;        // blockAlign = numChannels * bitsPerSample/8
    u16 bitsPerSample;     // Bits per sample
    char data[4];          // "data"
    u32 dataSize;          // Size of the audio data
};

class Sound;
class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    void add_sound(Sound *sound);
    void update();
    
private:
    ALCdevice *m_Device;
    ALCcontext *m_Context;
    std::vector<Sound *> m_Sounds;
};

