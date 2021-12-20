#ifndef HEALING_CHARACTER_H
#define HEALING_CHARACTER_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

// Rewrite this part of the code
void healingCharacter()
{
    if( playerCharacterSelected < 0 )
    {
        RenderText("You must select a character from the character list first...", White, current.w / 4, 20,48);
        mainLog.push_back("You must select a character from the character list first...");
    }
    else if( playerCharacter[playerCharacterSelected].hitpoints_current >= playerCharacter[playerCharacterSelected].hitpoints_max )
    {
        if( playerCharacter[playerCharacterSelected].hitpoints_current > playerCharacter[playerCharacterSelected].hitpoints_max )
        {
            mainLog.push_back(std::to_string(playerCharacter[playerCharacterSelected].hitpoints_current) + " > " + std::to_string(playerCharacter[playerCharacterSelected].hitpoints_max));
            playerCharacter[playerCharacterSelected].hitpoints_current = playerCharacter[playerCharacterSelected].hitpoints_max;
        }

        RenderText("There is nothing I can do for you...", White, current.w / 4, 20,48);
        mainLog.push_back("There is nothing I can do for you...");
    }
    else if( playerCharacter[playerCharacterSelected].hitpoints_current < (playerCharacter[playerCharacterSelected].hitpoints_max - 8) )
    {
        cureLightWounds();
    }
    else if( playerCharacter[playerCharacterSelected].hitpoints_current < (playerCharacter[playerCharacterSelected].hitpoints_max - 17) )
    {
        cureSeriousWounds();
    }
    else if( playerCharacter[playerCharacterSelected].hitpoints_current < (playerCharacter[playerCharacterSelected].hitpoints_max - 27) )
    {
        cureCriticalWounds();
    }
};

#endif // HEALING_CHARACTER_H
