#ifndef MENU_RESOURCE_H
#define MENU_RESOURCE_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

#include "main_menu.h"

bool Initialize(void)
{
    ///--- Last frame information to 0
    m_iPreviousCoordX=0;
    m_iPreviousCoordY=0;
    m_uPreviousMouseState=0;

    ///--- Get the current state of the mouse
    m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

    ///--- initialize the wheel to 0 to avoid problems
    m_iWheelX=0;
    m_iWheelY=0;
    return true;
}

void GetMousePosition(int& iCoordX, int& iCoordY)
{
    iCoordX=m_iCurrentCoordX;
    iCoordY=m_iCurrentCoordY;
}

void GetMouseDiff(int& iDiffX, int& iDiffY)
{
    iDiffX=m_iCurrentCoordX-m_iPreviousCoordX;
    iDiffY=m_iCurrentCoordY-m_iPreviousCoordY;
}

bool IsButtonTrigered(const Uint32 uButton)
{
    return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)!=0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)==0);
}
bool IsButtonPressed(const Uint32 uButton)
{
    return (SDL_BUTTON(uButton) & m_uCurrentMouseState)!=0;
}

int toggleIndex()
{
    static int selector = 0;

    selector ^= 1;                // toggle index
    return selector;
};

void adventureMenu()
{
    if( viewingCharacter )
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
        SDL_Rect background = {0, 0,current.w,current.h};
        SDL_RenderFillRect(renderer, &background);

        renderCharacterView();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
        SDL_Rect exitButton = {current.w - 210, current.h - 40, 200, 30};
        SDL_RenderFillRect(renderer, &exitButton);
        RenderText("EXIT", Black, current.w - 200, current.h - 37,fontSize);

        if( SDL_PointInRect(&mousePosition, &exitButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                viewingCharacter = 0;
            }
        }
    }
    else if( encamped )
    {
        if( toggleIndex() == 0 )
            encampTexture = LoadTexture("./images/encamp/encamp.png",255);
        else
            encampTexture = LoadTexture("./images/encamp/encamp2.png",255);

        SDL_RenderCopy(renderer, encampTexture, NULL, NULL);
        SDL_DestroyTexture(encampTexture);
        RenderText2("YOU SET UP CAMP...", White, current.w / 2, 200,32);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
        SDL_Rect exitButton = {current.w - 210, current.h - 40, 200, 30};
        SDL_RenderFillRect(renderer, &exitButton);
        if( SDL_PointInRect(&mousePosition, &exitButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                encamped = 0;
            }
        }

        readyButton = {current.w / 2 - 125, current.h  / 2 - 20,250,40};
        SDL_RenderFillRect(renderer, &readyButton);
        RenderText2("REST", Black, current.w / 2, current.h  / 2,fontSize);
        RenderText("BREAK CAMP", Black, current.w - 200, current.h - 37,fontSize);

        if( SDL_PointInRect(&mousePosition, &readyButton) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
            SDL_RenderDrawRect(renderer, &readyButton);
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                RenderText2("RESTING...", White, current.w / 2, current.h  / 2 + fontSize * 2,fontSize);

                for( int i = 0; i < (sizeof(playerCharacter)/sizeof(playerCharacter[0])); i++ )
                {
                    playerCharacter[i].hitpoints_current = playerCharacter[i].hitpoints_max;
                }
                encamped = 0;
            }
        }
    }
    else
    {
        renderPCstatus();
    }
}

int procentageLoaded = 0;

void LoadingScreen()
{
    //Initialize();
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto Width = DM.w;
    auto Height = DM.h;

    SDL_RenderClear(renderer);
    //SDL_RenderCopy(renderer, menuBackgroundTexture, NULL, NULL);

    //std::string procentageLoadedString = "loading, please wait... ";

    std::string procentageLoadedString = "loading, please wait... " + std::to_string(procentageLoaded) +  "%";
    RenderText(procentageLoadedString,Black,DM.w - 400,DM.h - 30,fontSize);

    loadingScreen = loadBestiary();

    procentageLoaded++;

    //loadingScreen = 0;
};

#endif // MENU_RESOURCE_H
