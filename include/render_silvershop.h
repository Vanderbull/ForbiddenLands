#ifndef RENDER_SILVERSHOP_H
#define RENDER_SILVERSHOP_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

std::vector<items> silverShopItems;

void generateSilverShopItems()
{
    silverShopItems.push_back(items());
    silverShopItems.push_back(items());
    silverShopItems.push_back(items());
    silverShopItems.push_back(items());
    silverShopItems.push_back(items());
    silverShopItems.push_back(items());
    silverShopItems.push_back(items());
    silverShopItems.push_back(items());
    silverShopItems.push_back(items());
    silverShopItems.push_back(items());
};

void renderSilverShop()
{
    SDL_Rect StatsBox = {1000,100,400,425};

    renderBackground("./images/shops/shop3.jpg");
    renderShopScrollbars();
    renderShopCoins();

    RenderText("SILVER SHOP", White, current.w - 400, 20,48);

    int counter2 = 0;

    // Render player character items
    if(playerCharacterInventory[playerCharacterSelected].size() > 0)
    for( int i = offsetPlayerCharacterList; i < offsetPlayerCharacterList + showEntries; i++ )
    {
        int ButtonX = 1490;
        int ButtonY = 200 + (counter2*30);

        SDL_Rect itemBox = {ButtonX,ButtonY,400,25};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &itemBox);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &itemBox);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        std::string playerItem = playerCharacterInventory[playerCharacterSelected].at(i).c_str();
        playerItem += std::to_string(armsAndArmoursValue.at(i));

        RenderText(playerItem.c_str(),Black,ButtonX,ButtonY,FontSize);

        if( SDL_PointInRect(&mousePosition, &itemBox) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &StatsBox);

            // bought items
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
            SDL_RenderFillRect(renderer, &itemBox);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &itemBox);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            RenderText(playerCharacterInventory[playerCharacterSelected].at(i).c_str(),Black,1050,100,FontSize);

            removeIndex = counter2;

            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if(playerCharacterSelected >= 0)
                {
                    removeIndex = counter2;
                    triggerRemove = 1;
                    //pooled_coins_copper += armsAndArmoursValue.at(i);
                    playerCharacter[playerCharacterSelected].coins_gold += armsAndArmoursValue.at(i);
                }
            }
            SDL_Delay(75);
        }
        counter2++;
    }

    counter = 0;
    for( int i = scrollOffsetShop; i < scrollOffsetShop + showEntriesInShop; i++ )
    {
        int RenderXPosition = 190;
        int RenderYPosition = 200;

        SDL_Rect itemBox = {RenderXPosition,RenderYPosition + (counter*30),400,25};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &itemBox);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &itemBox);

        if( SDL_PointInRect(&mousePosition, &itemBox) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &StatsBox);

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &itemBox);

            RenderText(silverStoreItems.at(i).c_str(),Black,1050,100,FontSize);

            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( armsAndArmoursValue.at(i) < playerCharacter[playerCharacterSelected].coins_gold)
                {
                    playerCharacterInventory[playerCharacterSelected].push_back(silverStoreItems.at(i).c_str());
                    readyCharacterInventory[playerCharacterSelected].push_back("NO");
                    //playerCharacter[playerCharacterSelected].readyCharacterInventoryAC.push_back(0);
                    //playerCharacter[playerCharacterSelected].readyCharacterInventoryTHACO.push_back(0);
                    playerCharacter[playerCharacterSelected].coins_gold -= armsAndArmoursValue.at(i);
                    SDL_Delay(75);
                }
            }
        }
        counter++;
    }

    counter = 0;

    if( triggerRemove )
    {
        playerCharacterInventory[playerCharacterSelected].erase(playerCharacterInventory[playerCharacterSelected].begin()+removeIndex);
        readyCharacterInventory[playerCharacterSelected].erase(readyCharacterInventory[playerCharacterSelected].begin()+removeIndex);
    }

    triggerRemove = 0;

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
            silverShop = 0;
        }
    }
    renderPCstatus();
};

#endif // RENDER_SILVERSHOP_H
