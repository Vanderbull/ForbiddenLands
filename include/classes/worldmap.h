/// @file worldmap.h
#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>

#include "randomizer.h"

class WorldMap {
public:

    int map[20][25];

    WorldMap(void);
    WorldMap(std::string);


};

#endif
