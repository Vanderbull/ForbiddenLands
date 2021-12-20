#ifndef BLESS_H
#define BLESS_H

void bless()
{
    std::cout << "blessing..." << std::endl;
    playerCharacter[playerCharacterSelected].thaco_current++;
};

#endif
