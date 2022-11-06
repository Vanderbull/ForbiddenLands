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

    int current_stats[7];
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
        // Profession /////////////////////////////
        int counter = 0;

        professionElements.clear();

        for (std::string textElement : professionTextElements)
        {
            SDL_Rect rect;
            rect.x = 1200 - 150; // game->SActor.professionElements[counter].w / 2
            rect.y = 225+(counter*50) - 15; // game->SActor.professionElements[counter].h / 2
            rect.w = 300;
            rect.h = 30;
            professionElements.push_back(rect);
            counter++;
        };
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
