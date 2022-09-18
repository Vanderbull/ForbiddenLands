#ifndef CURE_CRITICAL_WOUNDS_H
#define CURE_CRITICAL_WOUNDS_H

void cureCriticalWounds()
{
    std::cout << "Cure critical wounds..." << std::endl;
    if( playerCharacter[playerCharacterSelected].hitpoints_current < (playerCharacter[playerCharacterSelected].hitpoints_max - 27) )
    {
        playerCharacter[playerCharacterSelected].hitpoints_current += GenerateNumber(0,27);
    }
};

#endif
