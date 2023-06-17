/// @file shipobject.h
#ifndef SHIPOBJECT_H
#define SHIPOBJECT_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>

#include "randomizer.h"

class ShipObject {
public:

    int Position_X = 5;
    int Position_Y = 14;

    ShipObject(void);
};

#endif
