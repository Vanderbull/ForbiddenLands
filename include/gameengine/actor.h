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

    int current_stats[6];
    int coins_gold = 0;
    int experience = 0;
    int encumbrance = 0;
    int armour_class = 0;
    int hitpoints_current = 0;
    int hitpoints_max = 0;
    int damage = 0;
    int hunger = 0;
    int thirst = 0;
    SDL_Texture* faceImage;
    int healingPotions = 1;

    ACTOR()
    {
        calculateStats();
    };

//    void sleeping(int hours)
//    {
//        daily_stamina += hours;
//        action_stamina += hours*10;
//    };

//    void generateInitiative()
//    {
//        initiative = GenerateNumber(1,6);
//    };
//
//    void increaseHunger()
//    {
//        if( hunger < 100 )
//        hunger++;
//    };
//
//    void decreaseHunger()
//    {
//        if( hunger > 0 )
//        hunger--;
//    };
//
//    void increaseThirst()
//    {
//        if( thirst < 100 )
//        thirst++;
//    };

//    void decreaseThirst()
//    {
//        if( thirst > 0 )
//        thirst--;
//    };

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
