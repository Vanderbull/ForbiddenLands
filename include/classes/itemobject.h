#ifndef ITEMOBJECT_H
#define ITEMOBJECT_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>

#include "randomizer.h"

struct ItemRecord
{
    std::string Name;
    std::string Icon = "./assets/data/textures/icons/uiAtlas/ui_game_symbol_other.png";
};

class Item {
public:

    std::string icon = "./assets/data/textures/icons/uiAtlas/ui_game_symbol_other.png";
    std::string Name = "EMPTY";
    int Efficiency = 0;
    int MinDamage= 0;
    int MaxDamage= 0;
    int DmgType= 0;
    int NumHands= 0;
    int Bodypart= 0;
    int UsedBy= 0;
    int Skill= 0;
    int BaseWorth= 0;
    int Price = 0;
    int Protection = 0;
    int Enchantments = 0;
    int Effect = 0;
    int EffectCharges = 0;
    int MinEffect = 0;
    int MaxEffect = 0;
    int Features = 0;
    int Equipped = 0;
    int Equipable = 0;
    SDL_Rect iconBox = {0,0,0,0};

    Item(void);
    Item(std::string);
};

struct SGenericItem
{
    // item types
    enum {ARMOUR,SHIELD,MISCELLANEOUS,POTION,RING,SCROLL,WEAPON};

    std::string icon = "./assets/data/textures/icons/uiAtlas/ui_game_symbol_other.png";
    std::string name;
    std::string description = "a very generic type of item";
    int unidentified = 0;
    std::string type = "";
    int cursed = 0;
    int amount = 0;
    int weight = 0;

    int equipped = 0;
    int damage = 0;

    bool edible = false;
    int calories = 0;

    bool equipable = false;
    int slot = 0;
    int armour_class = 0;

    bool sellable = false;
    int value = 0;

    SGenericItem()
    {
        value = GenerateNumber(0,256);
        amount = GenerateNumber(0,256);
    };

    std::string getName()
    {
        return name;
    };

    friend std::ostream& operator <<(std::ostream& os, SGenericItem const& a)
    {
        return os << a.name << ' '
                  << a.unidentified << ' '
                  << a.type << ' '
                  << a.armour_class << ' '
                  << a.cursed << ' '
                  << a.amount << ' '
                  << a.weight << ' '
                  << a.value << ' '
                  << a.equipped << ' ';
    }
};

#endif
