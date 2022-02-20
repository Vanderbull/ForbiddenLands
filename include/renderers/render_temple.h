#ifndef RENDER_TEMPLE_H
#define RENDER_TEMPLE_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

#include "healing_character.h"

void renderTemple()
{
    renderShopCoins();

    currentViewTexture = LoadTexture("./images/shops/temple.jpg",255);
    SDL_RenderCopy(renderer, currentViewTexture, NULL, NULL);
    SDL_DestroyTexture(currentViewTexture);

    RenderText("TEMPLE", White, current.w - 400, 20,48);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect healButton = {current.w / 3, current.h / 4,190, 50};
    SDL_RenderFillRect(renderer, &healButton);
    RenderText("HEAL", Black, current.w / 3, current.h / 4,48);

    if( SDL_PointInRect(&mousePosition, &healButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
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
            templeShop = 0;
        }
    }
    renderPCstatus();
};

#endif // RENDER_TEMPLE_H
