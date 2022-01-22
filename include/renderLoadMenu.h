#ifndef RENDER_LOAD_MENU_H
#define RENDER_LOAD_MENU_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

void RenderLoadMenu()
{
    renderBackground("./images/menus/mainmenu.jpg");

    int HorizontalPosition = current.w - 400;

    SDL_Rect SaveGameA = {HorizontalPosition - (HorizontalPosition/7),220,600,30};
    SDL_Rect SaveGameB = {HorizontalPosition - (HorizontalPosition/7),260,600,30};
    SDL_Rect SaveGameC = {HorizontalPosition - (HorizontalPosition/7),300,600,30};
    SDL_Rect SaveGameD = {HorizontalPosition - (HorizontalPosition/7),340,600,30};
    SDL_Rect SaveGameE = {HorizontalPosition - (HorizontalPosition/7),380,600,30};
    SDL_Rect SaveGameF = {HorizontalPosition - (HorizontalPosition/7),420,600,30};
    SDL_Rect SaveGameG = {HorizontalPosition - (HorizontalPosition/7),460,600,30};
    SDL_Rect SaveGameH = {HorizontalPosition - (HorizontalPosition/7),500,600,30};
    SDL_Rect SaveGameI = {HorizontalPosition - (HorizontalPosition/7),540,600,30};
    SDL_Rect SaveGameJ = {HorizontalPosition - (HorizontalPosition/7),580,600,30};

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);

    SDL_RenderFillRect(renderer, &SaveGameA);
    SDL_RenderFillRect(renderer, &SaveGameB);
    SDL_RenderFillRect(renderer, &SaveGameC);
    SDL_RenderFillRect(renderer, &SaveGameD);
    SDL_RenderFillRect(renderer, &SaveGameE);
    SDL_RenderFillRect(renderer, &SaveGameF);
    SDL_RenderFillRect(renderer, &SaveGameG);
    SDL_RenderFillRect(renderer, &SaveGameH);
    SDL_RenderFillRect(renderer, &SaveGameI);
    SDL_RenderFillRect(renderer, &SaveGameJ);

    RenderText("SAVE GAMES",Black,140,180,24);

    RenderText2("A",White,HorizontalPosition,SaveGameA.y + 10,fontSize);
    RenderText2("B",White,HorizontalPosition,SaveGameB.y + 10,fontSize);
    RenderText2("C",White,HorizontalPosition,SaveGameC.y + 10,fontSize);
    RenderText2("D",White,HorizontalPosition,SaveGameD.y + 10,fontSize);
    RenderText2("E",White,HorizontalPosition,SaveGameE.y + 10,fontSize);
    RenderText2("F",White,HorizontalPosition,SaveGameF.y + 10,fontSize);
    RenderText2("G",White,HorizontalPosition,SaveGameG.y + 10,fontSize);
    RenderText2("H",White,HorizontalPosition,SaveGameH.y + 10,fontSize);
    RenderText2("I",White,HorizontalPosition,SaveGameI.y + 10,fontSize);
    RenderText2("J",White,HorizontalPosition,SaveGameJ.y + 10,fontSize);

    if( SDL_PointInRect(&mousePosition, &SaveGameA) ||
    SDL_PointInRect(&mousePosition, &SaveGameB) ||
    SDL_PointInRect(&mousePosition, &SaveGameC) ||
    SDL_PointInRect(&mousePosition, &SaveGameD) ||
    SDL_PointInRect(&mousePosition, &SaveGameE) ||
    SDL_PointInRect(&mousePosition, &SaveGameF) ||
    SDL_PointInRect(&mousePosition, &SaveGameG) ||
    SDL_PointInRect(&mousePosition, &SaveGameH) ||
    SDL_PointInRect(&mousePosition, &SaveGameI) ||
    SDL_PointInRect(&mousePosition, &SaveGameJ) )
    {
        // Nothing yet
    }
    else
    {
        disableSound = 0;
        Mix_FadeOutChannel(-1,1000);
    }

    if( MenuCounter > 0 )
    {
        SDL_RenderFillRect(renderer, NULL);
        RenderText("Loading game...", Red, 700,100,42);
        MenuCounter--;
    }
    else if( MenuCounterSwitch == 1)
    {
        activeView = DUNGEON;
        LoadMenu = 0;
        SaveMenu = 0;
        MenuCounterSwitch = 0;
    }
    else
    {
    }

    if( SDL_PointInRect(&mousePosition, &SaveGameA) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameA);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameA);
            loadingGameData("./data/savegames/savgama.dat");
            MenuCounter = 50;
            MenuCounterSwitch = 1;
        }
    }
    if( SDL_PointInRect(&mousePosition, &SaveGameB) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameB);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameB);
            std::ofstream SaveGame;
            loadingGameData("./data/savegames/savgamb.dat");
            MenuCounter = 50;
            MenuCounterSwitch = 1;
        }
    }
    if( SDL_PointInRect(&mousePosition, &SaveGameC) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameC);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameC);
            std::ofstream SaveGame;
            loadingGameData("./data/savegames/savgamc.dat");
            MenuCounter = 50;
            MenuCounterSwitch = 1;
        }
    }
    if( SDL_PointInRect(&mousePosition, &SaveGameD) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameD);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameD);
            std::ofstream SaveGame;
            loadingGameData("./data/savegames/savgamd.dat");
            MenuCounter = 50;
            MenuCounterSwitch = 1;
        }
    }
    if( SDL_PointInRect(&mousePosition, &SaveGameE) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameE);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameE);
            std::ofstream SaveGame;
            loadingGameData("./data/savegames/savgame.dat");
            MenuCounter = 50;
            MenuCounterSwitch = 1;
        }
    }
    if( SDL_PointInRect(&mousePosition, &SaveGameF) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameF);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameF);
            std::ofstream SaveGame;
            loadingGameData("./data/savegames/savgamf.dat");
            RenderText("Loading game...", Red, 700,100,42);
            activeView = DUNGEON;
            LoadMenu = 0;
            SaveMenu = 0;
        }
    }
    if( SDL_PointInRect(&mousePosition, &SaveGameG) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameG);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameG);
            std::ofstream SaveGame;
            loadingGameData("./data/savegames/savgamg.dat");
            RenderText("Loading game...", Red, 700,100,42);
            activeView = DUNGEON;
            LoadMenu = 0;
            SaveMenu = 0;
        }
    }
    if( SDL_PointInRect(&mousePosition, &SaveGameH) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameH);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameH);
            std::ofstream SaveGame;
            loadingGameData("./data/savegames/savgamh.dat");
            RenderText("Loading game...", Red, 700,100,42);
            activeView = DUNGEON;
            LoadMenu = 0;
            SaveMenu = 0;
        }
    }
    if( SDL_PointInRect(&mousePosition, &SaveGameI) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameI);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameI);
            std::ofstream SaveGame;
            loadingGameData("./data/savegames/savgami.dat");
            RenderText("Loading game...", Red, 700,100,42);
            activeView = DUNGEON;
            LoadMenu = 0;
            SaveMenu = 0;
        }
    }
    if( SDL_PointInRect(&mousePosition, &SaveGameJ) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameJ);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameJ);
            std::ofstream SaveGame;
            loadingGameData("./data/savegames/savgamj.dat");
            RenderText("Loading game...", Red, 700,100,42);
            activeView = DUNGEON;
            LoadMenu = 0;
            SaveMenu = 0;
        }
    }
    SDL_Rect ExitButton = {current.w - 220,current.h - 50,200,30};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
    SDL_RenderFillRect(renderer, &ExitButton);
    RenderText("EXIT", White, ExitButton.x,ExitButton.y,fontSize);

    if( SDL_PointInRect(&mousePosition, &ExitButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &ExitButton);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            LoadMenu = 0;
            SaveMenu = 0;
        }
    }
};
#endif // RENDER_LOAD_MENU_H
