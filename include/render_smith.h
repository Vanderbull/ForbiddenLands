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
//    showEntries = getShopInventorySize() - scrollOffsetShop;
//    showEntriesInShop = getShopInventorySize() - scrollOffsetShop;
//
//    if( showEntries > 15)
//        showEntries = 15;
//    if( showEntriesInShop > 15)
//        showEntriesInShop = 15;
//
//    SDL_Rect StatsBox = {1000,100,400,425};

    renderBackground("./images/shops/shop3.jpg");
    //renderShopScrollbars();
    renderShopCoins();

    RenderText("SMITHY", White, current.w - 400, 20,48);

    //pressUpArrow2Button(mousePosition,upArrow2);
    //pressDownArrow2Button(mousePosition,downArrow2);
    //pressUpArrowButton(mousePosition,upArrow);
    //pressDownArrowButton(mousePosition,downArrow);

    //changeShowEntries();

    //int counter2 = 0;

    // Render player character items

    for( int i = 0; i < playerCharacter[playerCharacterSelected].carriedItems.size(); i++ )
    {
        SDL_Rect itemButton = {current.w / 3,i*40 + 200,400,25};
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
                    playerCharacter[playerCharacterSelected].coins_copper += playerCharacter[playerCharacterSelected].carriedItems.at(i).value;
                    smithItems.push_back(playerCharacter[playerCharacterSelected].carriedItems.at(i));
                    playerCharacter[playerCharacterSelected].carriedItems.erase(playerCharacter[playerCharacterSelected].carriedItems.begin() + i);
                }
                SDL_Delay(75);
            }
        }
    }

    for( int i = 0; i < smithItems.size(); i++ )
    {
        SDL_Rect itemButton = {current.w / 6,i*40 + 200,400,25};
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
                    if( playerCharacter[playerCharacterSelected].coins_copper >= smithItems.at(i).value)
                    {
                        playerCharacter[playerCharacterSelected].coins_copper -= smithItems.at(i).value;
                        playerCharacter[playerCharacterSelected].carriedItems.push_back(smithItems.at(i));
                        smithItems.erase(smithItems.begin() + i);
                    }
                }
                SDL_Delay(75);
            }
        }
    }

    //if( playerCharacter[playerCharacterSelected].carriedItems.size() > 0 )
    //playerCharacter[playerCharacterSelected].carriedItems.erase(playerCharacter[playerCharacterSelected].carriedItems.begin());

//    if(playerCharacterInventory[playerCharacterSelected].size() > 0)
//    for( int i = offsetPlayerCharacterList; i < offsetPlayerCharacterList + showEntries; i++ )
//    {
//        int ButtonX = 1490;
//        int ButtonY = 200 + (counter2*30);
//
//        SDL_Rect itemBox = {ButtonX,ButtonY,400,25};
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//        SDL_RenderFillRect(renderer, &itemBox);
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderDrawRect(renderer, &itemBox);
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//
//        std::string playerItem = playerCharacterInventory[playerCharacterSelected].at(i).c_str();
//        //playerItem += std::to_string(playerCharacter[playerCharacterSelected].carriedItems.at(i).value);
//
//        RenderText(playerItem.c_str(),Black,ButtonX,ButtonY,FontSize);
//
//        if( SDL_PointInRect(&mousePosition, &itemBox) & SDL_BUTTON(SDL_BUTTON_LEFT) )
//        {
//            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//            SDL_RenderFillRect(renderer, &StatsBox);
//
//            // bought items
//            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
//            SDL_RenderFillRect(renderer, &itemBox);
//            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//            SDL_RenderDrawRect(renderer, &itemBox);
//            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//            RenderText(playerCharacterInventory[playerCharacterSelected].at(i).c_str(),Black,1050,100,FontSize);
//
//            removeIndex = counter2;
//
//            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
//            {
//                if(playerCharacterSelected >= 0)
//                {
//                    removeIndex = counter2;
//                    triggerRemove = 1;
//                    playerCharacter[playerCharacterSelected].carriedItems.at(i).value;
//                    pooled_coins_copper += armsAndArmoursValue.at(i);
//                    playerCharacter[playerCharacterSelected].coins_copper += armsAndArmoursValue.at(i);
//                }
//            }
//            SDL_Delay(75);
//        }
//        counter2++;
//    }
//
//    changeShowEntriesInShop();
//
//    int counter = 0;
//    for( int i = scrollOffsetShop; i < scrollOffsetShop + showEntriesInShop; i++ )
//    {
//        int RenderXPosition = 190;
//        int RenderYPosition = 200;
//
//        SDL_Rect itemBox = {RenderXPosition,RenderYPosition + (counter*30),400,25};
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//        SDL_RenderFillRect(renderer, &itemBox);
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderDrawRect(renderer, &itemBox);
//
//        RenderText(armsAndArmours.at(i).c_str() + std::to_string(armsAndArmoursValue.at(i)),Black,RenderXPosition + 10,RenderYPosition + (counter*30),FontSize);
//
//        if( SDL_PointInRect(&mousePosition, &itemBox) & SDL_BUTTON(SDL_BUTTON_LEFT) )
//        {
//            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//            SDL_RenderFillRect(renderer, &StatsBox);
//
//            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//            SDL_RenderDrawRect(renderer, &itemBox);
//
//            RenderText(armsAndArmours.at(i).c_str() + std::to_string(armsAndArmoursValue.at(i)),Black,1050,100,FontSize);
//
//            SDL_PumpEvents();
//            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
//            {
//                if( armsAndArmoursValue.at(i) < playerCharacter[playerCharacterSelected].coins_copper)
//                {
//                    playerCharacter[playerCharacterSelected].carriedItems.push_back(items());
//                    playerCharacterInventory[playerCharacterSelected].push_back(armsAndArmours.at(i).c_str());
//                    readyCharacterInventory[playerCharacterSelected].push_back("NO");
//                    playerCharacter[playerCharacterSelected].readyCharacterInventoryAC.push_back(0);
//                    playerCharacter[playerCharacterSelected].readyCharacterInventoryTHACO.push_back(0);
//                    pooled_coins_copper -= armsAndArmoursValue.at(i);
//                    playerCharacter[playerCharacterSelected].coins_copper -= armsAndArmoursValue.at(i);
//                    SDL_Delay(75);
//                }
//            }
//        }
//        counter++;
//    }
//
//    counter = 0;
//
//    if( triggerRemove )
//    {
//        playerCharacterInventory[playerCharacterSelected].erase(playerCharacterInventory[playerCharacterSelected].begin()+removeIndex);
//        readyCharacterInventory[playerCharacterSelected].erase(readyCharacterInventory[playerCharacterSelected].begin()+removeIndex);
//    }
//
//    triggerRemove = 0;

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
        }
    }
    renderPCstatus();
};

#endif // RENDER_SMITH_H
