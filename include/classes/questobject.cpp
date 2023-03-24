#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine/gameengine.h"
#include "questobject.h"

class GameEngine;

void QuestList::addQuest(std::string task)
{
    Quest *newQuest = new Quest(task);
    if (this->head == nullptr)
    {
      this->head = newQuest;
    }
    else
    {
      Quest *curr = this->head;
      while (curr->next != nullptr)
      {
        curr = curr->next;
      }
      curr->next = newQuest;
    }
    this->size++;
}

void QuestList::completeQuest(std::string task)
{
    Quest *curr = this->head;
    while (curr != nullptr)
    {
      if (curr->task == task)
      {
        curr->completed = true;
        break;
      }
      curr = curr->next;
    }
}

void QuestList::displayQuests()
{
    Quest *curr = this->head;
    std::cout << "Quests:" << std::endl;
    while (curr != nullptr)
    {
      std::cout << curr->task << ": " << (curr->completed ? "Completed" : "Incomplete") << std::endl;
      curr = curr->next;
    }
    exit(0);
}
