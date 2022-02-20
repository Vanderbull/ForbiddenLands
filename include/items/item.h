#ifndef ITEM_H
#define ITEM_H

struct items
{
    // item types
    enum {ARMOUR,SHIELD,MISCELLANEOUS,POTION,RING,SCROLL,WEAPON};

    std::string icon = "./icons/uiAtlas/ui_game_symbol_other.png";
    std::string name;
    std::string description = "a very generic type of item";
    int unidentified = 0;
    int type = 0;
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

    items()
    {
        value = Generate(0,256);
        amount = Generate(0,256);
    };

    std::string getName()
    {
        return name;
    };

    friend std::ostream& operator <<(std::ostream& os, items const& a)
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

struct food : items
{
    food()
    {
        std::string icon = "./icons/items/food.png";
        name = "food";
        unidentified = 0;
        cursed = 0;
        weight = 0;
        value = 0;
    };
    food(std::string iName)
    {
        name = iName;
    }
};

struct armour : items
{
    armour()
    {
        std::string icon = "./icons/items/armour.png";
        name = "armour";
    };
    armour(std::string iName)
    {
        name = iName;
    }

};

struct weapon : items
{
    weapon()
    {
        std::string icon = "./icons/items/weapon.png";
        name = "weapon";
    };
    weapon(std::string iName)
    {
        name = iName;
    }
};

struct scroll : items
{
    scroll()
    {
        std::string icon = "./icons/items/scroll.png";
        name = "scroll";
    };
    scroll(std::string iName)
    {
        name = iName;
    }
};

struct book : items
{
    book()
    {
        std::string icon = "./icons/items/potion.png";
        name = "book";
    };
    book(std::string iName)
    {
        name = iName;
    }
};

struct potion : items
{
    potion()
    {
        std::string icon = "./icons/items/potion.png";
        name = "potion";
    };
    potion(std::string iName)
    {
        name = iName;
    }
};

std::vector<items> gameItems;

void loadItemIcons()
{
  string line;
  int counter = 0;
  ifstream myfile ("soundbible.org");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
        if (line.length() == 0 || line[0] == '#')
        {
        }
        else
        {
            cout << line << '\n';
            counter++;
        }
    }
    myfile.close();
  }
  else
    throw runtime_error("File Not Found!");


    gameItems.push_back(weapon("Dagger"));
    gameItems.push_back(weapon("Club"));
    gameItems.push_back(weapon("Spike club"));
    gameItems.push_back(weapon("Shortsword"));

};

struct trader
{
    std::vector<items> traderItems;

    trader()
    {
        for( int i = 0; i < 10; i++ )
        {
            switch( Generate(0,7) )
            {
            case 0:
                traderItems.push_back(food("Meat and turnips"));
                break;
            case 1:
                traderItems.push_back(armour());
                break;
            case 2:
                traderItems.push_back(weapon());
                break;
            case 3:
                traderItems.push_back(scroll());
                break;
            case 4:
                traderItems.push_back(book());
                break;
            case 5:
                traderItems.push_back(potion());
                break;
            case 6:
                traderItems.push_back(gameItems.at(0));
                break;
            }
        }
    };
};

trader traders[100];

#endif
