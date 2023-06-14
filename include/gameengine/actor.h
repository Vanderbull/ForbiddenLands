/// @file actor.h
#ifndef ACTOR_H
#define ACTOR_H

#include <string>

#include <SDL2/SDL.h>
#include "randomizer.h"

class ACTOR
{
public:
    /**
     * @brief This is a member variable.
     *
     * It stores some important information.
     */
    uint32_t uid;

    /**
     * @brief Stores the name of the players character.
     */
    std::string name = "Enter name...";
    /**
     * @brief Enumeration of the different cardinal points.
     */
    enum {NORTH,EAST,SOUTH,WEST};
    /**
     * @brief What cardinal point the character is looking.
     */
    int compassNeedle = WEST;

    struct Professions
    {
        enum {VIKING,MARAUDER,SHIELDMAIDEN};
        std::vector<std::string> Names = { "VIKING", "MARAUDER","SHIELDMAIDEN"};
        std::vector<SDL_Rect> Button_Elements;
        int Choosen = 0;
    } Profession;

    /**
     * @brief Stats of the player character.
     */
    int current_stats[7];
    /**
     * @brief Number of coins carried by the player.
     */
    int coins_gold = 0;
    /**
     * @brief How much experience the player have.
     */
    int experience = 0;
    /**
     * @brief Player character hitpoints currently.
     */
    int hitpoints_current = 10;
    /**
     * @brief Player character max hitpoints.
     */
    int hitpoints_max = 10;
    /**
     * @brief how hungry is the player character.
     */
    int hunger = 0;
    /**
     * @brief How thirsty is the player character.
     */
    int thirst = 0;

    struct CoordinatePair
    {
        int x;
        int y;
        int z;
    };

    CoordinatePair PlayerCoordinate = {15,1,0};
    CoordinatePair PlayerLastCoordinate = {15,1,0};
    CoordinatePair WorldmapCoordinate = {5,14,0};
    CoordinatePair WorldmapLastCoordinate = {5,14,0};

    ACTOR(void);
    void calculateStats();
};

#endif
