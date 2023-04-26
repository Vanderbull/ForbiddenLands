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
    void completeQuest(std::string task);
    void displayQuests();
};

#endif
