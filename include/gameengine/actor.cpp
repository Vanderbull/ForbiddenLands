#include "actor.h"

ACTOR::ACTOR(void) : thirst(0), hunger(0), hitpoints_current(10), hitpoints_max(10)
{
    int counter = 0;

    for (const auto& name : Profession.Names)
    {
//        // Get the screen resolution must be set later when the video subsystem is initialized
//        SDL_DisplayMode dm;
//        if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
//            std::cerr << "SDL_GetDesktopDisplayMode failed: " << SDL_GetError() << std::endl;
//            exit(99);
//        }
//        else
//        {
//            std::cout << "Resolution: " << dm.w << " x " << dm.h << std::endl;
//            exit(99);
//        }

        SDL_Rect rect;
        rect.x = 1200 - 150;
        rect.y = 225+(counter*50) - 15;
        rect.w = 300;
        rect.h = 30;
//        // Center the rect on the screen
//        rect.x = (current.w - rect.w) / 2;
//        rect.y = (current.h - rect.h) / 2;

        Profession.Button_Elements.push_back(rect);
        counter++;
    };
    calculateStats();
};

void ACTOR::calculateStats()
{
    this->uid = GenerateNumber(0, 10000);
    int count = 0;
    for (int aNumber : current_stats)
    {
        current_stats[count] = GenerateNumber(3, 18);
        count++;
    }
};
