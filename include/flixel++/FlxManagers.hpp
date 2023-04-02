#ifndef FLXMANAGERS_HPP
#define FLXMANAGERS_HPP
#include "flixel++/Common.hpp"
#include "flixel++/FlxSound.hpp"
namespace Flx
{
    class Random
    {
        private:
        std::mt19937 engine;
        public:
        Random();
        Random(int seed);
        ~Random();
        int number(int min, int max);
        float floating(float min, float max);
        bool boolean(float chance);
    };

    class SoundManager
    {
        private:
        #ifdef FLIXEL_OPENAL
        ALCdevice *device;
        ALCcontext *context;
        #endif
        public:
        Flx::Sound* music;
        SoundManager();
        ~SoundManager();
        SoundData generateBuffers(std::vector<char>& bufferData, size_t rate);
    };
}

#endif // FLXMANAGERS_HPP