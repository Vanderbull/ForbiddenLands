#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

#include "functions.h"
#include "texture_resource.h"
#include "items/item.h"
#include "spells/spell.h"
#include "common.h"
#include "weather/weather.h"
#include "npc.h"
#include "bestiary.h"
#include "map_resource.h"
#include "menu_resource.h"
#include "sound_resource.h"
#include "spells.h"
#include "quests/quest.h"
#include "skilltree/skilltree.h"

#include "../include/renderers/render.h"
//#include "name_generator.h"

npcEngine NPCs;

void naturalHealing()
{
    playerCharacter[0].hitpoints_current++;
    playerCharacter[1].hitpoints_current++;
    playerCharacter[2].hitpoints_current++;
    playerCharacter[3].hitpoints_current++;
    playerCharacter[4].hitpoints_current++;
    playerCharacter[5].hitpoints_current++;
};

std::string getexepath()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    return std::string( result, (count > 0) ? count : 0 );
};

void initGame()
{
    //loadBestiary();
    loadingScreen = 1;
    int GL_SwapInterval = SDL_GL_SetSwapInterval(1);

    if( GL_SwapInterval == 0)
    {
        std::cout << "SDL_GL_SetSwapInterval adaptive vsync SUCCESS..." << std::endl;
    }
    else if( GL_SwapInterval == -1 )
    {
        std::cout << "SDL_GL_SetSwapInterval adaptive vsync FAILED..." << std::endl;

        std::cout << " Trying with immediate vsync..." << std::endl;
        GL_SwapInterval = SDL_GL_SetSwapInterval(0);
         if( GL_SwapInterval == 0)
        {
            std::cout << "SDL_GL_SetSwapInterval immediate vsync SUCCESS..." << std::endl;
        }
        else if( GL_SwapInterval == -1 )
        {
            std::cout << "SDL_GL_SetSwapInterval immediate vsync FAILED..." << std::endl;
        }
    }

    std::cout << "Mix_VolumeMusic = " << Mix_VolumeMusic(0) << std::endl;

    std::cout << "Verified savegames..." << std::endl;

    MenuChoices.clear();
    MenuChoices.push_back("PLAY");
    MenuChoices.push_back("SAVE");
    MenuChoices.push_back("LOAD");
    MenuChoices.push_back("CHARACTER MANAGER");
    MenuChoices.push_back("SETTINGS");
    MenuChoices.push_back("EXIT");

    if( mainLog.empty() )
    {
        std::cout << "Empty mainLog" << std::endl;
    }

    North = LoadTexture("./images/compass/north.png",255);
    West = LoadTexture("./images/compass/west.png",255);
    South = LoadTexture("./images/compass/south.png",255);
    East = LoadTexture("./images/compass/east.png",255);
};

void getCompassDirection()
{
    std::cout << compassDirection.at(compassNeedle) << std::endl;
    Rotation = compassDirection.at(compassNeedle);
};

void rotateCounterClockWise()
{
    if( compassNeedle == 0 )
        compassNeedle = compassDirection.size()-1;
    else
        compassNeedle--;
};

void rotateClockWise()
{
    if( compassNeedle == compassDirection.size()-1 )
        compassNeedle = 0;
    else
        compassNeedle++;
};

int Button(SDL_Point mousePosition, SDL_Rect Area, SDL_Renderer* Renderer )
{
    if( SDL_PointInRect(&mousePosition, &Area) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 128);
        SDL_RenderDrawRect(Renderer, &Area);

        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 128);
            SDL_RenderFillRect(Renderer, &Area);
            return 1;
        }
        return 0;
    }
    return -1;
};

class Command
{
    public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class JumpCommand : public Command
{
    public:
    virtual void execute() { Jump(); };
    private:
    void Jump(){};
};

class inputhandler
{
    public:
    void handleinput();
    private:
    Command* buttonX_;
};

struct rpg_data_engine
{
    unsigned int experience_points = 0;
    unsigned int credits = 0;
    unsigned int inc_experience(unsigned int amount)
    {
        return amount;
    };
    unsigned int dec_experience(unsigned int amount)
    {
        return amount;
    }

    //is responsible for tracking and dictating experiences, checking flags, and counting inventories. One element that must be carefully
    //considered is the choice of data that should be saved in the saved games. Is it necessary to track every single item the player
    //drops in the wilderness? What about all the NPC stats? When can the player save? Very few CRPGs let you save in the middle of a
    //battle, and other CRPGs even limit saves to only certain spots (Final Fantasy VII saving posts).
};

struct storyboard_engine
{

};

struct npc_engine
{

};

rpg_data_engine crpg_data_engine;
storyboard_engine cstoryboard_engine;
npc_engine cnpc_engine;
