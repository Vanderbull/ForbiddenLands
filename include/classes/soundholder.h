/// @file soundholder.h
#ifndef SOUNDHOLDER_H
#define SOUNDHOLDER_H

#include <string>
#include <vector>
#include <map>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "randomizer.h"

class SoundHolder
{
public:
    map<string, Mix_Chunk*> m_Sounds;

    SoundHolder(){};
};

#endif
