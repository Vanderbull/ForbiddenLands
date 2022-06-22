#ifndef ACTOR_H
#define ACTOR_H

#include <string>
using namespace std;

struct ACTOR
{
    int current_stats[6]; // 5 = CON
    std::string name = "default";
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
};

#endif
