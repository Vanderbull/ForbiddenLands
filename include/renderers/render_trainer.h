#ifndef RENDER_TRAINER_H
#define RENDER_TRAINER_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

void renderTrainer()
{
    showEntries = getShopInventorySize() - scrollOffsetShop;
    showEntriesInShop = getShopInventorySize() - scrollOffsetShop;

    if( showEntries > 15)
        showEntries = 15;
    if( showEntriesInShop > 15)
        showEntriesInShop = 15;

    SDL_Rect StatsBox = {1000,100,400,425};

    renderBackground("./images/shops/shop3.jpg");
    renderShopCoins();

    RenderText("TRAINER", White, current.w - 400, 20,48);

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
            trainingHall = 0;
        }
    }
    renderPCstatus();
};

#endif // RENDER_SMITH_H
