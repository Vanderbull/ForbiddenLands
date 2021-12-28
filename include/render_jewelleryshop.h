#ifndef RENDER_JEWELLERYSHOP_H
#define RENDER_JEWELLERYSHOP_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

std::vector<items> jewelleryShopItems;

void generateJewelleryShopItems()
{
    jewelleryShopItems.push_back(items());
    jewelleryShopItems.push_back(items());
    jewelleryShopItems.push_back(items());
    jewelleryShopItems.push_back(items());
    jewelleryShopItems.push_back(items());
    jewelleryShopItems.push_back(items());
    jewelleryShopItems.push_back(items());
    jewelleryShopItems.push_back(items());
    jewelleryShopItems.push_back(items());
    jewelleryShopItems.push_back(items());
};

void renderJewelleryShop()
{
    renderBackground("./images/shops/shop3.jpg");
    //initShop();
    renderShopScrollbars();
    renderShopCoins();
    RenderText("JEWELLERY SHOP", White, current.w - 400, 20,48);

    int counter2 = 0;

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
        RenderText(playerCharacterInventory[playerCharacterSelected].at(i).c_str(),Black,ButtonX,ButtonY,FontSize);

        if( SDL_PointInRect(&mousePosition, &itemBox) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            removeIndex = counter2;

            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if(playerCharacterSelected >= 0)
                {
                    removeIndex = counter2;
                    triggerRemove = 1;
                    playerCharacter[playerCharacterSelected].coins_copper += 9;
                }
                SDL_Delay(75);
            }
        }
        counter2++;
    }

    int counter = 0;
    for( int i = scrollOffsetShop; i < scrollOffsetShop + showEntriesInShop; i++ )
    {
        int RenderXPosition = 190;
        int RenderYPosition = 200;

        SDL_Rect itemBox = {490,200 + (counter*30),400,25};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &itemBox);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &itemBox);

        if( SDL_PointInRect(&mousePosition, &itemBox) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if(playerCharacter[playerCharacterSelected].coins_copper > 0)
                {
                    playerCharacterInventory[playerCharacterSelected].push_back(jewelleryStoreItems.at(i).c_str());
                    readyCharacterInventory[playerCharacterSelected].push_back("NO");
                    playerCharacter[playerCharacterSelected].readyCharacterInventoryAC.push_back(0);
                    playerCharacter[playerCharacterSelected].readyCharacterInventoryTHACO.push_back(0);

                    playerCharacter[playerCharacterSelected].coins_copper -= 9;
                }
                SDL_Delay(75);
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
            jewelleryShop = 0;
        }
    }
    renderPCstatus();
};

#endif // RENDER_JEWELLERYSHOP_H
