#include <stdio.h>
#include <SDL2/SDL.h>
#include "skillobject.h"

SkillObject::SkillObject(void)
{

};
SkillObject::SkillObject( std::string N_, std::string Group_, int Learned_, int MaxExp_ )
{
    Name = N_;
};

SkillObject::SkillObject( SDL_Rect Pos)
{
//    SDL_Rect rect;
//    rect.x = 500;
//    rect.y = 170+(counter*50);
//    rect.w = 300;
//    rect.h = 30;
    Position = {Pos.x,Pos.y,Pos.w,Pos.h};
};
