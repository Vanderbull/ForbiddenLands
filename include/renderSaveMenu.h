#ifndef RENDER_SAVE_MENU_H
#define RENDER_SAVE_MENU_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

void RenderSaveMenu()
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

    if( SDL_PointInRect(&mousePosition, &SaveGameA) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &SaveGameA);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &SaveGameA);
            savingGameData("./data/savegames/savgama.dat");
            RenderText("Saving game...", Red, 700,100,42);
            LoadMenu = 0;
            SaveMenu = 0;
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
            savingGameData("./data/savegames/savgamb.dat");
            RenderText("Saving game...", Red, 700,100,42);
            LoadMenu = 0;
            SaveMenu = 0;
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
            savingGameData("./data/savegames/savgamc.dat");
            RenderText("Saving game...", Red, 700,100,42);
            LoadMenu = 0;
            SaveMenu = 0;
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
            savingGameData("./data/savegames/savgamd.dat");
            RenderText("Saving game...", Red, 700,100,42);
            LoadMenu = 0;
            SaveMenu = 0;
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
            savingGameData("./data/savegames/savgame.dat");
            RenderText("Saving game...", Red, 700,100,42);
            LoadMenu = 0;
            SaveMenu = 0;
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
            savingGameData("./data/savegames/savgamf.dat");
            RenderText("Saving game...", Red, 700,100,42);
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
            savingGameData("./data/savegames/savgamg.dat");
            RenderText("Saving game...", Red, 700,100,42);
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
            savingGameData("./data/savegames/savgamh.dat");
            RenderText("Saving game...", Red, 700,100,42);
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
            savingGameData("./data/savegames/savgami.dat");
            RenderText("Saving game...", Red, 700,100,42);
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
            savingGameData("./data/savegames/savgamj.dat");
            RenderText("Saving game...", Red, 700,100,42);
            LoadMenu = 0;
            SaveMenu = 0;
        }
    }
    SDL_Rect ExitButton = {current.w - 220,current.h - 50,200,30};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
    SDL_RenderFillRect(renderer, &ExitButton);

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

#endif // RENDER_SAVE_MENU_H
