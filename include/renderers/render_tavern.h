#ifndef RENDER_TAVERN_H
#define RENDER_TAVERN_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

#include "healing_character.h"

std::string tavernTales()
{
    std::ifstream dataFile ("./data/tavern_tales");

    std::string line;
    std::string tales;

    int counter = 1;

    while(std::getline(dataFile, line))
    {
        if (line.length() == 0 || line[0] == '#')
        {
            // Ignore line
            counter++;
        }
        else
        {
            // cache the line
            std::istringstream tokenizer(line);

            std::getline(tokenizer, phlanTourCoordinateN[0], ','); // then get the tokens from it
            std::getline(tokenizer, phlanTourCoordinateN[1]); // last token: get the remainder of the line.

            if(tokenizer)
            {
                if(phlanTourCoordinateN[0] == std::to_string(counter))
                {
                    return phlanTourCoordinateN[1];
                }
                else
                {
                    //return "";
                }
                // success!
            }
            else
            {
               return "There were fewer than one commas in the line";
            }
        }
    }
}

void renderTavern()
{
    renderBackground("./images/shops/tavern.jpg");

    RenderText("TAVERN", White, current.w - 400, 20,48);
    RenderText(tavernTales(), White, 60, 120,32);

    RenderText("EAT", White, current.w/2, 220,32);
    RenderText("DRINK", White, current.w/2, 320,32);

    SDL_Rect TextFrame = FrameText("EAT",current.w/2, 220,32);

    if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            playerCharacter[playerCharacterSelected].coins_gold -= 100;
            mainLog.push_back("Payed 100 gold for a meal");
            healingCharacter();
        }
    }

    TextFrame = FrameText("DRINK",current.w/2, 320,32);

    if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
             playerCharacter[playerCharacterSelected].coins_gold -= 100;
             mainLog.push_back("Payed 100 gold for a drink");
             healingCharacter();
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect Leave = {current.w - 200,current.h - 50,190, 40};

    SDL_RenderFillRect(renderer, &Leave);
    RenderText("LEAVE", Black, current.w - 180, current.h - 70,48);

    if( SDL_PointInRect(&mousePosition, &Leave) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            PlayerCoordinate.x = LastPlayerCoordinate.x;
            PlayerCoordinate.y = LastPlayerCoordinate.y;
            tavern = 0;
            shop = 0;
        }
    }
    renderPCstatus();
}
#endif // RENDER_TAVERN_H
