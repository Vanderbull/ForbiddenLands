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

void initBattle()
{
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

    SDL_Rect attack = {current.w / 3, current.h - 50,100,30};
    SDL_Rect magic = {current.w / 3 + 110, current.h - 50,100,30};
    SDL_Rect exit = {current.w / 3 + 220, current.h - 50,100,30};
    SDL_Rect healing = {current.w / 3 + 330, current.h - 50,100,30};
    SDL_Rect missile = {current.w / 3 + 440, current.h - 50,100,30};

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
        turnActive = true;
    }

    SDL_PumpEvents();
    if (event.type == SDL_MOUSEBUTTONUP)
        HOLD = false;

    if(turnActive)
    {
        SDL_Rect turnButton = {0,0,160, 160};
        SDL_RenderFillRect(renderer, &turnButton);

        if( !HOLD )
        if( SDL_PointInRect(&mousePosition, &turnButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(renderer, &turnButton);
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                turnActive = false;
            }
        }
    }
    else
    {
        turns++;
        turnActive = true;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect statsBackground = {0,current.h - 200,current.w, 200};
    SDL_RenderFillRect(renderer, &statsBackground);
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

    RenderText("ATTACK " + std::to_string(playerCharacter[playerCharacterSelected].damage_vs_small), White, actionButton[0].x, actionButton[0].y,20);
    RenderText("MAGIC", White, actionButton[1].x, actionButton[1].y,20);
    RenderText("EXIT", White, actionButton[2].x, actionButton[2].y,20);
    RenderText("HEALING", White, actionButton[3].x, actionButton[3].y,20);
    RenderText("MiSSILE", White, actionButton[4].x, actionButton[4].y,20);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &character[playerCharacterSelected]);
    SDL_RenderDrawRect(renderer, &NPCs.NPC[npc_active].SDL_Rectangle);

    if( !HOLD )
    if( SDL_PointInRect(&mousePosition, &actionButton[0]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &actionButton[0]);
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            HOLD = true;
            npc_health[npc_active] -= playerCharacter[playerCharacterSelected].damage_vs_small;
            playerCharacter[playerCharacterSelected].hitpoints_current -= playerCharacter[playerCharacterSelected].damage_vs_small;
            character_action[playerCharacterSelected] = 0;
            fadeSize = 25;
            SDL_Delay(45);
        }
    }
    if( SDL_PointInRect(&mousePosition, &actionButton[1]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &actionButton[1]);
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
        }
    }
    if( SDL_PointInRect(&mousePosition, &actionButton[2]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &actionButton[2]);
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
                activeView = dungeon;
                initBattleFlag = 0;
        }
    }

    // Healing potion quaff
    if( SDL_PointInRect(&mousePosition, &actionButton[3]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &actionButton[3]);
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if( healingPotion[playerCharacterSelected] > 0 )
            {
                healingPotion[playerCharacterSelected] -= 1;
                cureLightWounds();
                character_action[playerCharacterSelected] = 0;
                SDL_Delay(100);
            }
        }
    }
    if( SDL_PointInRect(&mousePosition, &actionButton[4]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &actionButton[4]);
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
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

    playerCharacterSelected = 0;
    for( int i = 0; i < 6; i++ )
    {
        if( playerCharacter[playerCharacterSelected].hitpoints_current <= 0 )
        {
            playerCharacterSelected++;
        }
        else if( character_action[playerCharacterSelected] <= 0 )
        {
            character_action[playerCharacterSelected] = 0;
            playerCharacterSelected++;
        }
    }

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
    }

    if( characterActionsReset == 0)
    {
        playerCharacterSelected = 0;

        for( int i = 0; i < 6; i++)
        {
            character_action[i] = 1;
        }
    }
    // end of character action check

    // Check resetting of the npc actions of none left

    for( int i = 0; i < 6; i++ )
    {
        if( npc_action[i] == 1 )
        {
            npcActionsReset == 0;
        }
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

    if( playerCharacter[playerCharacterSelected].damage_vs_small <= 0 )
        playerCharacter[playerCharacterSelected].damage_vs_small = 1;

    RenderText(std::to_string(turns), Black, 0, 0,40);

    npc_targeted = Generate(0,5);

    if( fadeSize > 0)
    {
        fadeSize--;
        RenderText(std::to_string(playerCharacter[playerCharacterSelected].damage_vs_small), Black, NPCs.NPC[npc_active].SDL_Rectangle.x, NPCs.NPC[npc_active].SDL_Rectangle.y - NPCs.NPC[npc_active].SDL_Rectangle.h,fadeSize*4);
        RenderText(std::to_string(npc_current_damage), Black, character[npc_targeted].x, character[npc_targeted].y,fadeSize*4);
    }

    int spacing = 100;

    for( int i = 0; i < 6; i++ )
    {
        if( npc_health[i] > 0 )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Texture* Texture = LoadTexture(enemyImages.at(enemyImageID[i]).c_str(),255);
            SDL_RenderCopyEx(renderer, Texture, NULL, &NPCs.NPC[i].SDL_Rectangle,0,0,SDL_FLIP_HORIZONTAL);
            SDL_DestroyTexture(Texture);
        }
    }

    for( int i=0; i< 6; i++ )
    {
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
        activeView = dungeon;
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
    }

    // Battle ended and game over
    if( playerCharacter[0].hitpoints_current <= 0 && playerCharacter[1].hitpoints_current <= 0 && playerCharacter[2].hitpoints_current <= 0 &&
        playerCharacter[3].hitpoints_current <= 0 && playerCharacter[4].hitpoints_current <= 0 && playerCharacter[5].hitpoints_current <= 0)
    {
        activeView = dungeon;
        initBattleFlag = 0;
        playerCharacterSelected = 0;
        for( int i=0; i< 6; i++ )
            character_action[i] = 1;
        quit = 1;
    }

    RenderText(playerCharacter[playerCharacterSelected].name, Blue, 100, current.h - 150,20);
    RenderText("HP: " + std::to_string(playerCharacter[playerCharacterSelected].getHitpoints()) + " / " + std::to_string(playerCharacter[playerCharacterSelected].hitpoints_max), Black, 100, current.h - 100,20);
    RenderText("Actions: " + std::to_string(character_action[playerCharacterSelected]), Black, 100, current.h - 50,20);

    RenderText(npc_name, Blue, current.w - 200, current.h - 150,20);
    RenderText("HP: " + std::to_string(npc_health[npc_active]), Black, current.w - 200, current.h - 100,20);
    RenderText("Actions: " + std::to_string(npc_action[npc_active]), Black, current.w - 200, current.h - 50,20);
    RenderText("HEALING POTIONS: " + std::to_string(healingPotion[playerCharacterSelected]), Black, current.w / 2, current.h - 200,20);
};

 #endif // BATTLE_VIEW
