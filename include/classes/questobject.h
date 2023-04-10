#ifndef QUESTOBJECT_H
#define QUESTOBJECT_H

#include <iostream>
#include <string>

class Quest
{
public:
    std::string task;
    std::string description;
    bool completed;
    Quest *next;

    Quest(std::string task,std::string description)
    {
        this->task = task;
        this->description = description;
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

    void addQuest(std::string task,std::string description);
//    {
//        Quest *newQuest = new Quest(task);
//        if (this->head == nullptr)
//        {
//          this->head = newQuest;
//        }
//        else
//        {
//          Quest *curr = this->head;
//          while (curr->next != nullptr)
//          {
//            curr = curr->next;
//          }
//          curr->next = newQuest;
//        }
//        this->size++;
//    }

    void completeQuest(std::string task);
//    {
//        Quest *curr = this->head;
//        while (curr != nullptr)
//        {
//          if (curr->task == task)
//          {
//            curr->completed = true;
//            break;
//          }
//          curr = curr->next;
//        }
//    }

    void displayQuests();
//    {
//        Quest *curr = this->head;
//        std::cout << "Quests:" << std::endl;
//        while (curr != nullptr)
//        {
//          std::cout << curr->task << ": " << (curr->completed ? "Completed" : "Incomplete") << std::endl;
//          curr = curr->next;
//        }
//    }
};

#endif
