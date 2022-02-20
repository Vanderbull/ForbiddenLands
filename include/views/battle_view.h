#ifndef BATTLE_VIEW_H
#define BATTLE_VIEW_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>

#include <SDL2/SDL.h>
#include "common.h"

int initBattleFlag = 0;
int character_initiative[6] = {0,0,0,0,0,0};
int character_action[6] = {1,1,1,1,1,1};
int character_min, character_max;
int fadeSize = 0;
int damage = 0;
int playerSupriseSegments = 0;
int npcSupriseSegments = 0;

int supriseRollSegments()
{
    int playerRoll = Generate(1,6);
    int npcRoll = Generate(1,6);

    if( playerRoll == 1 )
        playerSupriseSegments = 1;
    else if( playerRoll == 2)
        playerSupriseSegments = 2;
    else if( playerRoll > 2 )
        playerSupriseSegments = 0;

    if( npcRoll == 1 )
        npcSupriseSegments = 1;
    else if( npcRoll == 2)
        npcSupriseSegments = 2;
    else if( npcRoll > 2 )
        npcSupriseSegments = 0;
};

void initBattle()
{
    supriseRollSegments();
    NPCs.init();

    for(int i = 0; i < 6; i++)
    {
        character_action[i] == 1;
    }
};

int turns = 0;
bool HOLD = false;

Mix_Chunk *gPunch = NULL;

bool turnActive = true;

void battleView()
{
    if( playerCharacter[0].getHitpoints() <= 0 )
    if( playerCharacter[1].getHitpoints() <= 0 )
    if( playerCharacter[2].getHitpoints() <= 0 )
    if( playerCharacter[3].getHitpoints() <= 0 )
    if( playerCharacter[4].getHitpoints() <= 0 )
    if( playerCharacter[5].getHitpoints() <= 0 )
        exit(99);

    SDL_Texture* Texture;
    SDL_Rect character[6];
    SDL_Rect character_fighting;
    SDL_Rect characterActionText[6];
    SDL_Rect actionButton[6];

    character_fighting = {700, 500,300,300};

    SDL_GetCurrentDisplayMode(0, &current);
    character[0] = {0, 0,100,144};
    character[1] = {0, 150,100,144};
    character[2] = {0, 300,100,144};
    character[3] = {0, 450,100,144};
    character[4] = {0, 600,100,144};
    character[5] = {0, 750,100,144};

    std::vector<std::string> playerImages;

    int characterActionsReset = 0;
    int npcActionsReset = 1;

    characterActionText[0] = {400, character[0].y + character[0].h - 50,125,25};
    characterActionText[1] = {400, character[1].y + character[1].h - 50,125,25};
    characterActionText[2] = {400, character[2].y + character[2].h - 50,125,25};
    characterActionText[3] = {400, character[3].y + character[3].h - 50,125,25};
    characterActionText[4] = {400, character[4].y + character[4].h - 50,125,25};
    characterActionText[5] = {400, character[5].y + character[5].h - 50,125,25};

    npcActionText[0] = {current.w - 300, character[0].y + character[0].h,225,25};
    npcActionText[1] = {current.w - 300, character[1].y + character[1].h,225,25};
    npcActionText[2] = {current.w - 300, character[2].y + character[2].h,225,25};
    npcActionText[3] = {current.w - 300, character[3].y + character[3].h,225,25};
    npcActionText[4] = {current.w - 300, character[4].y + character[4].h,225,25};
    npcActionText[5] = {current.w - 300, character[5].y + character[5].h,225,25};

    playerImages.clear();
    playerImages.push_back("./data/characters/134_4th_lvl_fighter-0.png");

    renderBackground("./images/battleBackground.png");

    if(initBattleFlag == 0)
    {
        getEnemyImageID();
        initBattle();
        initBattleFlag = 1;
        turns = 0;
        gPunch = Mix_LoadWAV( "data/sfx/Punch.wav" );
        npc_active = 0;
        turnActive = false;
        playerCharacter[0].generateInitiative();
        playerCharacter[1].generateInitiative();
        playerCharacter[2].generateInitiative();
        playerCharacter[3].generateInitiative();
        playerCharacter[4].generateInitiative();
        playerCharacter[5].generateInitiative();
        NPCs.NPC[0].generateInitiative();
        NPCs.NPC[1].generateInitiative();
        NPCs.NPC[2].generateInitiative();
        NPCs.NPC[3].generateInitiative();
        NPCs.NPC[4].generateInitiative();
        NPCs.NPC[5].generateInitiative();
    }

    SDL_PumpEvents();
    if (event.type == SDL_MOUSEBUTTONUP)
        HOLD = false;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    RenderFillRect(0,current.h - 200,current.w, 200);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    actionButton[0] = {300,current.h - 180,160, 160};
    actionButton[1] = {500,current.h - 180,160, 160};
    actionButton[2] = {700,current.h - 180,160, 160};
    actionButton[3] = {900,current.h - 180,160, 160};
    actionButton[4] = {1100,current.h - 180,160, 160};
    SDL_RenderFillRect(renderer, &actionButton[0]);
    SDL_RenderFillRect(renderer, &actionButton[1]);
    SDL_RenderFillRect(renderer, &actionButton[2]);
    SDL_RenderFillRect(renderer, &actionButton[3]);
    SDL_RenderFillRect(renderer, &actionButton[4]);

    RenderText("PLAYER SS: " + std::to_string(playerSupriseSegments), White, current.w / 2, 0,20);
    RenderText("NPC SS: " + std::to_string(npcSupriseSegments), White, current.w / 2, 30,20);
    RenderText("INITIATIVE[0]" + std::to_string(playerCharacter[0].initiative), White, current.w / 2, 60, 20);
    RenderText("INITIATIVE[1]" + std::to_string(playerCharacter[1].initiative), White, current.w / 2, 90, 20);
    RenderText("INITIATIVE[2]" + std::to_string(playerCharacter[2].initiative), White, current.w / 2, 120, 20);
    RenderText("INITIATIVE[3]" + std::to_string(playerCharacter[3].initiative), White, current.w / 2, 150, 20);
    RenderText("INITIATIVE[4]" + std::to_string(playerCharacter[4].initiative), White, current.w / 2, 180, 20);
    RenderText("INITIATIVE[5]" + std::to_string(playerCharacter[5].initiative), White, current.w / 2, 210, 20);

    RenderText("NPC INITIATIVE[0]" + std::to_string(NPCs.NPC[0]._initiative), White, current.w / 3, 60, 20);
    RenderText("NPC INITIATIVE[1]" + std::to_string(NPCs.NPC[1]._initiative), White, current.w / 3, 90, 20);
    RenderText("NPC INITIATIVE[2]" + std::to_string(NPCs.NPC[2]._initiative), White, current.w / 3, 120, 20);
    RenderText("NPC INITIATIVE[3]" + std::to_string(NPCs.NPC[3]._initiative), White, current.w / 3, 150, 20);
    RenderText("NPC INITIATIVE[4]" + std::to_string(NPCs.NPC[4]._initiative), White, current.w / 3, 180, 20);
    RenderText("NPC INITIATIVE[5]" + std::to_string(NPCs.NPC[5]._initiative), White, current.w / 3, 210, 20);

    RenderText("ATTACK " + std::to_string(playerCharacter[playerCharacterSelected].damage), White, actionButton[0].x, actionButton[0].y,20);
    RenderText("MAGIC", White, actionButton[1].x, actionButton[1].y,20);
    RenderText("FLEE", White, actionButton[2].x, actionButton[2].y,20);
    RenderText("HEALING", White, actionButton[3].x, actionButton[3].y,20);
    RenderText("SKIP", White, actionButton[4].x, actionButton[4].y,20);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &character[playerCharacterSelected]);
    SDL_RenderDrawRect(renderer, &NPCs.NPC[npc_active].SDL_Rectangle);

    if( !HOLD && character_action[playerCharacterSelected] == 1)
    if( SDL_PointInRect(&mousePosition, &actionButton[0]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &actionButton[0]);
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            HOLD = true;
            npc_health[npc_active] -= playerCharacter[playerCharacterSelected].damage;
            // damage player
            playerCharacter[playerCharacterSelected].hitpoints_current -= NPCs.NPC[npc_active]._damage;
            character_action[playerCharacterSelected] = 0;
            fadeSize = 25;
            SDL_Delay(45);
            character_action[playerCharacterSelected] = 0;
        }
    }
    if( !HOLD && character_action[playerCharacterSelected] == 1)
    if( SDL_PointInRect(&mousePosition, &actionButton[1]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &actionButton[1]);
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            HOLD = true;
            npc_health[npc_active] -= playerCharacter[playerCharacterSelected].damage;
            // damage player
            playerCharacter[playerCharacterSelected].hitpoints_current -= NPCs.NPC[npc_active]._damage;
            character_action[playerCharacterSelected] = 0;
            fadeSize = 25;
            SDL_Delay(45);
            character_action[playerCharacterSelected] = 0;
        }
    }
    if( SDL_PointInRect(&mousePosition, &actionButton[2]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &actionButton[2]);
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
                activeView = DUNGEON;
                initBattleFlag = 0;
        }
    }

    // Healing potion quaff
    if( playerCharacter[playerCharacterSelected].getHitpoints() < playerCharacter[playerCharacterSelected].hitpoints_max )
    {
        if( SDL_PointInRect(&mousePosition, &actionButton[3]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(renderer, &actionButton[3]);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( character_action[playerCharacterSelected] > 0)
                if( playerCharacter[playerCharacterSelected].healingPotions > 0 )
                {
                    playerCharacter[playerCharacterSelected].healingPotions -= 1;
                    cureLightWounds();
                    character_action[playerCharacterSelected] = 0;
                    SDL_Delay(100);
                }
            }
        }
    }
    else
    {
        if( SDL_PointInRect(&mousePosition, &actionButton[3]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                RenderText("NO NEED FOR HEALING", White, 50, current.h / 2,120);
            }
        }
    }

    if( SDL_PointInRect(&mousePosition, &actionButton[4]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &actionButton[4]);
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            character_action[playerCharacterSelected] = 0;
        }
    }

    Texture = LoadTexture(playerImages.at(0).c_str(),255);
    for( int i = 0; i < sizeof(character) / sizeof(SDL_Rect); i++ )
    {
        if( playerCharacter[i].hitpoints_current > 0 )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
            //character[i].x -= 32*i;
            SDL_RenderCopy(renderer, Texture, NULL, &character[i]);
        }
    }
    SDL_DestroyTexture(Texture);

    // Rendering the two fighting characters
    Texture = LoadTexture(playerImages.at(0).c_str(),255);
    SDL_RenderCopy(renderer, Texture, NULL, &character_fighting);
    SDL_DestroyTexture(Texture);

    Texture = LoadTexture(enemyImages.at(enemyImageID[npc_active]).c_str(),255);
    SDL_RenderCopyEx(renderer, Texture, NULL, &npc_fighting,0,0,SDL_FLIP_HORIZONTAL);
    SDL_DestroyTexture(Texture);

    // Check if the current active enemy is killed or not
    if( npc_health[npc_active] <= 0 )
    {
        mainLog.push_back(enemyImages.at(enemyImageID[npc_active]) + " killed for " + std::to_string(npc_experience[npc_active]) + " experience");
        playerCharacter[playerCharacterSelected].experience += npc_experience[npc_active];
        npc_active++;

        if(npc_active > 5)
        {
            npc_active = 0;
        }
    }
    // end of check

    for( int i = 0; i < 6; i++ )
    {
        if( SDL_PointInRect(&mousePosition, &character[i]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderDrawRect(renderer, &character[i]);
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( character_action[i] == 1 )
                {
                    playerCharacterSelected = i;
                }
            }
        }
    }

    // Check resetting of the character actions of none left

    for( int i = 0; i < 6; i++ )
    {
        if( character_action[i] == 1 )
        {
            characterActionsReset++;
        }
        if( npc_action[i] == 1 )
        {
            npcActionsReset == 0;
        }
    }

    if( characterActionsReset == 0)
    {
        turnActive = true;
        playerCharacterSelected = 0;
    }

    if( npcActionsReset == 0)
    {
        npc_active = 0;
        for( int i = 0; i < 6; i++ )
        {
            if( npc_health[i] > 0)
            {
                npc_action[i] = 1;
            }
            else
            {
                npc_action[i] = 0;
            }
        }
    }
    // end of npc actions check

    if( playerCharacter[playerCharacterSelected].damage <= 0 )
        playerCharacter[playerCharacterSelected].damage = 1;

    npc_targeted = Generate(0,5);

    for( int i = 0; i < 6; i++ )
    {
        if( npc_health[i] > 0 )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Texture* Texture = LoadTexture(enemyImages.at(enemyImageID[i]).c_str(),255);
            SDL_RenderCopyEx(renderer, Texture, NULL, &NPCs.NPC[i].SDL_Rectangle,0,0,SDL_FLIP_HORIZONTAL);
            SDL_DestroyTexture(Texture);
        }

        if( npc_health[i] >= 0 )
        if( SDL_PointInRect(&mousePosition, &NPCs.NPC[i].SDL_Rectangle) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderDrawRect(renderer, &NPCs.NPC[i].SDL_Rectangle);
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                npc_active = i;
            }
        }
    }

    // Battle ended when all enemies are dead
    if(npc_health[0] <= 0 && npc_health[1] <= 0 && npc_health[2] <= 0 && npc_health[3] <= 0 && npc_health[4] <= 0 && npc_health[5] <= 0)
    {
        activeView = DUNGEON;
        initBattleFlag = 0;
        playerCharacterSelected = 0;
        for( int i=0; i< 6; i++ )
            character_action[i] = 1;
        if( Generate(1,100) > 1)
        {
            mainLog.push_back("You found some treasure");
            playerCharacter[playerCharacterSelected].carriedItems.push_back(items());
            playerCharacter[playerCharacterSelected].coins_gold += Generate(0,1000);
        }
        for( int i=0; i< 6; i++ )
        playerCharacter[i].experience += Generate(0,1000);
        save_portals[PlayerCoordinate.x][PlayerCoordinate.y].encounter = 0;
    }

    // Battle ended and game over
    if( playerCharacter[0].hitpoints_current <= 0 && playerCharacter[1].hitpoints_current <= 0 && playerCharacter[2].hitpoints_current <= 0 &&
        playerCharacter[3].hitpoints_current <= 0 && playerCharacter[4].hitpoints_current <= 0 && playerCharacter[5].hitpoints_current <= 0)
    {
        activeView = DUNGEON;
        initBattleFlag = 0;
        playerCharacterSelected = 0;
        for( int i=0; i< 6; i++ )
            character_action[i] = 1;
        quit = 1;

        Texture = LoadTexture("./data/gameover/gameover.png",255);
        SDL_RenderCopyEx(renderer, Texture, NULL, NULL,0,0,SDL_FLIP_NONE);
        SDL_DestroyTexture(Texture);
        exit(99);
    }

    RenderText(playerCharacter[playerCharacterSelected].name, Blue, 100, current.h - 150,20);
    RenderText("HP: " + std::to_string(playerCharacter[playerCharacterSelected].getHitpoints()) + " / " + std::to_string(playerCharacter[playerCharacterSelected].hitpoints_max), Black, 100, current.h - 100,20);
    RenderText("Actions: " + std::to_string(character_action[playerCharacterSelected]), Black, 100, current.h - 50,20);

    RenderText(npc_name, Blue, current.w - 200, current.h - 150,20);
    RenderText("HP: " + std::to_string(npc_health[npc_active]) + " / " + std::to_string(NPCs.NPC[npc_active]._damage), Black, current.w - 200, current.h - 100,20);
    RenderText("Actions: " + std::to_string(npc_action[npc_active]), Black, current.w - 200, current.h - 50,20);
    RenderText("HEALING POTIONS: " + std::to_string(playerCharacter[playerCharacterSelected].healingPotions), Black, current.w / 2, current.h - 200,20);

    if(turnActive)
    {
        SDL_Rect turnButton = {current.w - 400,current.h - 170,160, 160};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &turnButton);
        RenderText("TURN " + std::to_string(turns), Black, current.w - 400, current.h - 170,20);

        if( SDL_PointInRect(&mousePosition, &turnButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(renderer, &turnButton);
            RenderText("TURN " + std::to_string(turns), White, current.w - 400, current.h - 170,20);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                turns++;
                for( int i = 0; i < 6; i++)
                {
                    character_action[i] = 1;
                }
                SDL_Delay(25);
                turnActive = false;
            }
        }
    }

    //skilltree();
    //skill_list();
};

 #endif // BATTLE_VIEW
