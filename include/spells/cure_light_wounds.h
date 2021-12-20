#ifndef CURE_LIGHT_WOUNDS_H
#define CURE_LIGHT_WOUNDS_H

void cureLightWounds()
{
    std::cout << "Cure light wounds..." << std::endl;
    if( playerCharacter[playerCharacterSelected].hitpoints_current < (playerCharacter[playerCharacterSelected].hitpoints_max - 8) )
    {
        playerCharacter[playerCharacterSelected].hitpoints_current += Generate(0,8);
    }
};

#endif
