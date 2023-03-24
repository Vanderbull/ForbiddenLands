#ifndef QUESTOBJECT_H
#define QUESTOBJECT_H

#include <iostream>
#include <string>

class Quest
{
public:
  std::string task;
  bool completed;
  Quest *next;

  Quest(std::string task)
  {
    this->task = task;
    this->completed = false;
    this->next = nullptr;
  }
};

class QuestList
{
public:
  Quest *head;
  int size;

  QuestList()
  {
    this->head = nullptr;
    this->size = 0;
  }

  void addQuest(std::string task);
  void completeQuest(std::string task);
  void displayQuests();

};

#endif
