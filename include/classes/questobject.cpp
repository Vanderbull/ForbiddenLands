#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine/gameengine.h"
#include "questobject.h"

class GameEngine;

void QuestList::displayQuests()
{
    SDL_Color REDRIC = {255,255,255,255};
    Quest *curr = this->head;
    std::cout << "Quests:" << std::endl;
    while (curr != nullptr)
    {
      std::cout << curr->task << ": " << (curr->completed ? "Completed" : "Incomplete") << std::endl;
      curr = curr->next;
    }
    exit(0);
}
