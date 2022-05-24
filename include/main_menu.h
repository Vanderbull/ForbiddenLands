#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>
#include "../include/renderers/renderSaveMenu.h"
#include "../include/renderers/renderLoadMenu.h"
#include "../include/renderers/renderSettings.h"

bool MainMenuLoadBackground( std::string imageFile )
{
    MainMenuBackgroundTexture = NULL;
    MainMenuBackgroundTexture = LoadTexture(imageFile.c_str(),255);
    return true;
};

void initMainMenu()
{

};

void MainMenu()
{
    //SDL_RenderClear(renderer);
    //SDL_RenderCopy(renderer, MainMenuBackgroundTexture, NULL, NULL);

    RenderTitle(TITLE.c_str(),White,current.w / 2,200);

    int Repeat = 0;
    int buttonWidth = 600;
    int buttonHeight = 60;

    for(auto MenuChoice : MenuChoices)
    {
        SDL_Rect buttonPosition = { (current.w / 2) - (buttonWidth / 2), 500 + (Repeat*(buttonPosition.h+15)),buttonWidth,buttonHeight};

        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 192);
        SDL_RenderFillRect(renderer, &buttonPosition);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
        SDL_RenderDrawRect(renderer,&buttonPosition);

        RenderBreadText(MenuChoice.c_str(), White, buttonPosition.x + (buttonWidth / 2),buttonPosition.y + (buttonHeight / 2));

        if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

            SDL_PumpEvents();
            state = SDL_GetMouseState(NULL, NULL);
            if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
            {
                if( SettingsMenu != 1)
                {
                    if(MenuChoice == "PLAY")
                    {
                        activeView = DUNGEON;
                        LoadMenu = 0;
                        SaveMenu = 0;
                        CreateCharacter = 0;
                    }
                    if(MenuChoice == "SAVE")
                    {
                        SaveMenu = 1;
                        LoadMenu = 0;
                        SettingsMenu = 0;
                        CreateCharacter = 0;
                    }
                    if(MenuChoice == "LOAD")
                    {
                        SaveMenu = 0;
                        LoadMenu = 1;
                        SettingsMenu = 0;
                        CreateCharacter = 0;
                    }
                    if(MenuChoice == "CHARACTER MANAGER")
                    {
                        SaveMenu = 0;
                        LoadMenu = 0;
                        SettingsMenu = 0;
                        CreateCharacter = 1;
                    }
                    if(MenuChoice == "SETTINGS")
                    {
                        SettingsMenu = 1;
                        SaveMenu = 0;
                        LoadMenu = 0;
                        CreateCharacter = 0;
                    }
                    if(MenuChoice == "EXIT")
                    {
                        LoadMenu = 0;
                        SaveMenu = 0;
                        SettingsMenu = 0;
                        CreateCharacter = 0;

                        // Destroy resources
                        SDL_DestroyTexture(currentViewTexture);
                        SDL_DestroyTexture(gTexture);
                        atexit(SDL_Quit);
                        quit = 1;
                    }
                }
            }
        }
        ++Repeat;
    }

    if( SettingsMenu == 1 )
    {
        renderSettings();
    }
    else if( SaveMenu == 1 )
    {
        RenderSaveMenu();
    }
    else if( LoadMenu == 1)
    {
        RenderLoadMenu();
    }
    else if( CreateCharacter == 1)
    {
        renderCharacterCreation();
    }
};

#endif // MAIN_MENU_H
