#ifndef ACTOR_H
#define ACTOR_H

#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "randomizer.h"

struct ACTOR
{
    std::string name = "Actor name";

    int current_stats[6];
    int race = 0; // None
    int coins_gold = 0;
    int ac_base = 10;
    int experience = 0;
    int encumbrance = 0;
    int ac_current = 0;
    int hitpoints_current = 0;
    int hitpoints_max = 0;
    int rowcounter = 0;
    int damage = 0;
    SDL_Point mousePosition;
    int face = 0;
    int hunger = 0;
    int thirst = 0;
    SDL_Texture* faceImage;
    int healingPotions = 1;
    int initiative = 0;
    int daily_stamina = 100;
    int action_stamina = 100;

    void sleeping(int hours)
    {
        daily_stamina += hours;
        action_stamina += hours*10;
    };

    void generateInitiative()
    {
        initiative = GenerateNumber(1,6);
    };

    void increaseHunger()
    {
        if( hunger < 100 )
        hunger++;
    };

    void decreaseHunger()
    {
        if( hunger > 0 )
        hunger--;
    };

    void increaseThirst()
    {
        if( thirst < 100 )
        thirst++;
    };

    void decreaseThirst()
    {
        if( thirst > 0 )
        thirst--;
    };

    void calculateStats()
    {
        int count = 0;
        for (int aNumber : current_stats)
        {
            current_stats[count] = GenerateNumber(3, 18);
            count++;
        }
    };
};

#endif
