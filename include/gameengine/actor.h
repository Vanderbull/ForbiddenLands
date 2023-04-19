#ifndef ACTOR_H
#define ACTOR_H

#include <string>

#include <SDL2/SDL.h>
#include "randomizer.h"

class ACTOR
{
public:
    uint32_t uid;
    std::string name = "Enter name...";

    std::vector<std::string> professionTextElements = { "VIKING", "MARAUDER","SHIELDMAIDEN"};
    std::vector<SDL_Rect> professionElements;

    int ChoosenProfession = 0;
    enum {
        VIKING,
        MARAUDER,
        SHIELDMAIDEN
    };

    int current_stats[7];
    int coins_gold = 0;
    int experience = 0;
    int encumbrance = 0;
    int armour_class = 0;
    int hitpoints_current = 10;
    int hitpoints_max = 10;
    int damage = 0;
    int faceImageID = 0;
    int worldMap = 0;
    int cityMap = 0;
    int hunger = 0;
    int thirst = 0;

    struct CoordinatePair
    {
        int x;
        int y;
        int z;
    };

    CoordinatePair PlayerCoordinate = {15,1,0};
    CoordinatePair PlayerLastCoordinate = {15,1,0};
    CoordinatePair WorldmapCoordinate = {35,14,0};
    CoordinatePair WorldmapLastCoordinate = {35,14,0};

    ACTOR(void);
    void calculateStats();

};

#endif
