#ifndef ITEMOBJECT_H
#define ITEMOBJECT_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>

#include "randomizer.h"

class Item {
public:

    std::string Name;
    int Efficiency;
    int MinDamage;
    int MaxDamage;
    int DmgType;
    int NumHands;
    int Bodypart;
    int UsedBy;
    int Skill;
    int BaseWorth;
    int Price;
    int Protection;
    int Enchantments;
    int Effect;
    int EffectCharges;
    int MinEffect;
    int MaxEffect;
    int Features;

    Item(void);
    Item(std::string,char,int);
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
