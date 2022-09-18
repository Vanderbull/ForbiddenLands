#ifndef CURE_SERIOUS_WOUNDS_H
#define CURE_SERIOUS_WOUNDS_H

void cureSeriousWounds()
{
    std::cout << "Cure serious wounds..." << std::endl;
    if( playerCharacter[playerCharacterSelected].hitpoints_current < (playerCharacter[playerCharacterSelected].hitpoints_max - 17) )
    {
        playerCharacter[playerCharacterSelected].hitpoints_current += GenerateNumber(0,17);
    }
};

#endif
