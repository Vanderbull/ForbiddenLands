#ifndef ACTOR_H
#define ACTOR_H

#include <string>
using namespace std;

#include <SDL2/SDL.h>
//#include "gameengine.h"
//#include "gamestate.h"
#include "randomizer.h"

struct ACTOR
{
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
    //int hunger = 0;
    //int thirst = 0;
    int faceImageID = 0;
    int worldMap = 0;

    struct CoordinatePair
    {
        int x;
        int y;
        int z;
    };
    CoordinatePair PlayerCoordinate = {15,1,0};
    CoordinatePair PlayerLastCoordinate = {15,1,0};

    ACTOR()
    {
        int counter = 0;

        professionElements.clear();

        for (std::string textElement : professionTextElements)
        {
            SDL_Rect rect;
            rect.x = 1200 - 150;
            rect.y = 225+(counter*50) - 15;
            rect.w = 300;
            rect.h = 30;
            professionElements.push_back(rect);
            counter++;
        };
        calculateStats();
    };

    void calculateStats()
    {
        this->uid = GenerateNumber(0, 10000);
        int count = 0;
        for (int aNumber : current_stats)
        {
            current_stats[count] = GenerateNumber(3, 18);
            count++;
        }
    };
};

#endif
