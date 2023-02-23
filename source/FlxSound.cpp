#include "flixel++/FlxSound.hpp"
#include "flixel++/FlxG.hpp"

Flx::Sound::Sound()
{
}

Flx::Sound::~Sound()
{
    #ifdef FLIXEL_OPENAL
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    vorbis_info_clear(info);
    #endif
}

void Flx::Sound::play()
{
    startTime = Flx::Globals::game->backend->getTicks();
    #ifdef FLIXEL_OPENAL
    alSourcePlay(source);
    #endif
}

void Flx::Sound::load(const char *path)
{
    #if defined(TREMOR) && !defined(__WIN32)
    ov_open(fopen(path, "r"), &vorbis, nullptr, 0);
    #else
    ov_fopen(path, &vorbis);
    #endif

    info = ov_info(&vorbis, -1);

    #ifdef FLIXEL_OPENAL
    alGenBuffers(1, &buffer);
    #endif

    int current_section;
    while (true)
    {
        std::vector<char> pcm(4096);
        long result = ov_read(&vorbis, pcm.data(), pcm.size(),
        #ifndef TREMOR
            0, 2, 1, 
        #endif
            &current_section
        );

        if (result == 0)
            break;

        if (result < 0)
        {
            return;
        }

        bufferData.insert(bufferData.end(), pcm.begin(), pcm.begin() + result);
    }
    #ifdef FLIXEL_OPENAL
    alBufferData(buffer, AL_FORMAT_STEREO16, bufferData.data(), bufferData.size(), info->rate);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    #endif
}

float Flx::Sound::getPosition()
{
    float val = 0;
    #ifdef FLIXEL_OPENAL
    alGetSourcef(buffer, AL_SEC_OFFSET, &val);
    #endif
    return val * 1000;
}
