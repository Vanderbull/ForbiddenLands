#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>

#include "randomizer.h"

class WorldMap {
public:

    std::string icon = "./assets/data/textures/icons/uiAtlas/ui_game_symbol_other.png";
    std::string Name = "EMPTY";
    int Efficiency = 0;
    int MinDamage= 0;
    int MaxDamage= 0;
    int DmgType= 0;
    int NumHands= 0;
    int Bodypart= 0;
    int UsedBy= 0;
    int Skill= 0;
    int BaseWorth= 0;
    int Price = 0;
    int Protection = 0;
    int Enchantments = 0;
    int Effect = 0;
    int EffectCharges = 0;
    int MinEffect = 0;
    int MaxEffect = 0;
    int Features = 0;
    int Equipped = 0;
    int Equipable = 0;
    SDL_Rect iconBox = {0,0,0,0};

    WorldMap(void);
    WorldMap(std::string);
};

#endif
