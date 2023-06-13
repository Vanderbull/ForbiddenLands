/// @file skillobject.h
#ifndef SKILLOBJECT_H
#define SKILLOBJECT_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>

class SkillObject {
public:

    std::string Name = "";
    std::string Group = "";
    int Learned = 0;
    int MaximumExpertise = 0;
    int InitialRequirementsAttribute = 0;
    int InitialRequirementsValue = 0;
    int GroupID = 0;
    std::string Description = "";
    SDL_Rect Position = {0,0,0,0};

    SkillObject(void);
    SkillObject( std::string N_, std::string Group_, int Learned_, int MaxExp_ );
    SkillObject( SDL_Rect Pos );
};

#endif
