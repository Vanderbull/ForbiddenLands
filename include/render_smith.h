#ifndef RENDER_SMITH_H
#define RENDER_SMITH_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

std::vector<items> smithItems;

void generateSmithShopItems()
{
    smithItems.push_back(items());
    smithItems.push_back(items());
    smithItems.push_back(items());
    smithItems.push_back(items());
    smithItems.push_back(items());
    smithItems.push_back(items());
    smithItems.push_back(items());
    smithItems.push_back(items());
    smithItems.push_back(items());
    smithItems.push_back(items());
};

void renderSmithShop()
{
    renderBackground("./images/shops/shop3.jpg");
    //renderShopCoins();

    RenderText("SMITHY", White, current.w - 400, 20,48);

    // Render player character items

    for( int i = 0; i < playerCharacter[playerCharacterSelected].carriedItems.size(); i++ )
    {
        SDL_Rect itemButton = {current.w / 2,i*40 + 200,400,25};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &itemButton);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &itemButton);
        RenderText(playerCharacter[playerCharacterSelected].carriedItems.at(i).getName() +  " value: " + std::to_string(playerCharacter[playerCharacterSelected].carriedItems.at(i).value),Black,itemButton.x,itemButton.y,FontSize);
        if( SDL_PointInRect(&mousePosition, &itemButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( playerCharacter[playerCharacterSelected].carriedItems.size() > 0 )
                {
                    playerCharacter[playerCharacterSelected].coins_gold += playerCharacter[playerCharacterSelected].carriedItems.at(i).value;
                    smithItems.push_back(playerCharacter[playerCharacterSelected].carriedItems.at(i));
                    playerCharacter[playerCharacterSelected].carriedItems.erase(playerCharacter[playerCharacterSelected].carriedItems.begin() + i);
                }
                SDL_Delay(75);
            }
        }
    }

    for( int i = 0; i < smithItems.size(); i++ )
    {
        SDL_Rect itemBox = {0,0,0,0};

        itemBox.h = 40 ;
        itemBox.w = 40;
        itemBox.x = current.w / 6 - 60;
        itemBox.y = 200 + (i*40);

        gTexture = NULL;
        //gTexture = LoadTexture("./icons/uiAtlas/ui_game_symbol_spatula.png",255);
        gTexture = LoadTexture(smithItems.at(i).icon,255);
        SDL_SetTextureColorMod(gTexture, 0, 255, 0); //set yellow letters
        SDL_RenderCopy(renderer, gTexture, NULL, &itemBox);
        SDL_DestroyTexture(gTexture);
        gTexture = NULL;

        SDL_Rect itemButton = {current.w / 6,i*40 + 200,600,25};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &itemButton);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &itemButton);
        RenderText(smithItems.at(i).getName() +  " value: " + std::to_string(smithItems.at(i).value),Black,itemButton.x,itemButton.y,FontSize);
        if( SDL_PointInRect(&mousePosition, &itemButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( smithItems.size() > 0 )
                {
                    if( playerCharacter[playerCharacterSelected].coins_gold >= smithItems.at(i).value)
                    {
                        playerCharacter[playerCharacterSelected].coins_gold -= smithItems.at(i).value;
                        playerCharacter[playerCharacterSelected].carriedItems.push_back(smithItems.at(i));
                        smithItems.erase(smithItems.begin() + i);
                    }
                }
                SDL_Delay(75);
            }
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
            armsAndarmourShop = 0;
            shop = 0;
        }
    }
    renderPCstatus();
};

#endif // RENDER_SMITH_H
