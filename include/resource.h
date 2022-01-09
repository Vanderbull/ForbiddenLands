#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>


#include "functions.h"
#include "texture_resource.h"
#include "common.h"
#include "npc.h"
#include "bestiary.h"
#include "map_resource.h"
#include "menu_resource.h"
#include "sound_resource.h"
#include "spells.h"

#include "render.h"
#include "boat.h"

npcEngine NPCs;

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

    //menuBackgroundTexture = LoadTexture("./images/menus/menuBackgroundTexture.png",255);
    //std::cout << "Loaded menu background graphics..." << std::endl;
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

rpg_data_engine crpg_data_engine;

void talkView()
{
};
void shopView()
{
};
void personalView()
{
};
void npcEngine()
{
};
void storyboardEngine()
{
};
void package()
{
};
void rpgDataEngine()
{
};

void determineSuprise()
{
};

SDL_Rect player = {5 * 48, 5 * 48, 48, 48};
SDL_Rect enemy = {5 * 48, 6 * 48, 48, 48};
int playerMovement = 12;
int enemyMovement = 12;

void fighting()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    SDL_RenderClear( renderer );
    for( int y = 0; y < 25; y++)
    {
        for( int x = 0; x < 50; x++)
        {
            SDL_Rect squared = {x * 48, y * 48, 48, 48};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
            SDL_RenderDrawRect(renderer, &squared);

            if( SDL_PointInRect(&mousePosition, &squared) & SDL_BUTTON(SDL_BUTTON_LEFT) )
            {
                SDL_PumpEvents();
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0,255);
                    SDL_RenderFillRect(renderer, &squared);

                    if( !Clicked )
                    {
                    }
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
                    SDL_RenderDrawRect(renderer, &squared);
                    Clicked = false;
                }
            }
        }
    }

                    SDL_SetRenderDrawColor(renderer, 255, 255, 0,255);
                    SDL_RenderFillRect(renderer, &player);
                    SDL_SetRenderDrawColor(renderer, 255, 0, 255,255);
                    SDL_RenderFillRect(renderer, &enemy);
            if( SDL_PointInRect(&mousePosition, &player) & SDL_BUTTON(SDL_BUTTON_LEFT) )
            {
                    RenderText("FIDGET", White, 1600, 920,12);
                    RenderText("Hitpoints: 10", White, 1600, 940,12);
                    RenderText("ac: 6", White, 1600, 960,12);
                    RenderText("Long sword +2", White, 1600, 980,12);
                    if(playerMovement > 0 )
                    {
                        player.x += 48;
                        playerMovement--;
                    }

            }
            if( SDL_PointInRect(&mousePosition, &enemy) & SDL_BUTTON(SDL_BUTTON_LEFT) )
            {
                    RenderText("FLOCKER MONSTRA", White, 1600, 920,12);
                    RenderText("Hitpoints: 100", White, 1600, 940,12);
                    RenderText("ac: 6", White, 1600, 960,12);
                    RenderText("", White, 1600, 980,12);
                    if(enemyMovement > 0 )
                    {
                        enemy.x += rand()%enemyMovement * 48;
                        enemyMovement--;
                    }
            }

            RenderText("VIEW", White, 1900, 940,12);
            RenderText("AIM", White, 1900, 960,12);
            RenderText("USE", White, 1900, 980,12);
            RenderText("CAST", White, 1900, 1000,12);
            RenderText("QUICK", White, 1900, 1020,12);
            RenderText("DONE", White, 1900, 1040,12);
}
