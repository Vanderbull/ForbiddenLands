#include "actor.h"

ACTOR::ACTOR(void)
{
    int counter = 0;

    professionElements.clear();

    for (std::string textElement : professionTextElements)
    {
        SDL_Rect rect;
        rect.x = 1200 - 150;
        rect.y = 225+(counter*50) - 15;
        rect.w = 300;
        rect.h = 30;
        professionElements.push_back(rect);
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
