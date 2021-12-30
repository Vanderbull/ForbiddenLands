#ifndef PLAYER_CHARACTERS_H
#define PLAYER_CHARACTERS_H

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

std::vector<std::string> readyCharacterInventory[6];
std::vector<std::string> playerCharacterInventory[6];

char NamePrefix[7][5] = {
    "", //who said we need to add a prefix?
    "bel", //lets say that means "the good"
    "nar", //"The not so good as Bel"
    "xan", //"The evil"
    "bell", //"the good"
    "natr", //"the neutral/natral"
    "ev", //Man am I original
};

char NameSuffix[16][5] = {
    "", "us", "ix", "ox", "ith",
    "ath", "um", "ator", "or", "axia",
    "imus", "ais", "itur", "orex", "o",
    "y"
};

const char NameStems[20][10] = {
    "adur", "aes", "anim", "apoll", "imac",
    "educ", "equis", "extr", "guius", "hann",
    "equi", "amora", "hum", "iace", "ille",
    "inept", "iuv", "obe", "ocul", "orbis"
};

//The return type is void because we use a pointer to the array holding
// the characters of the name.
void NameGen(char* PlayerName)
{
    PlayerName[0]=0; //initialize the string to "" (zero length string).
    //add the prefix...
    strcat(PlayerName, NamePrefix[(rand() % 7)]);
    //add the stem...
    strcat(PlayerName, NameStems[(rand() % 20)]);
    //add the suffix...
    strcat(PlayerName, NameSuffix[(rand() % 16)]);
    //Make the first letter capital...
    PlayerName[0]=toupper(PlayerName[0]);
    return;
};

// Move this structure to its own file when possible
struct items
{
    std::string name_1 = "";
    std::string name_2 = "";
    std::string name_3 = "";
    int unidentified = 0;
    int type = 0;
    int bonus = 0;
    int save = 0; // armour class
    int cursed = 0;
    int amount = 0;
    int weight = 0;
    int value = 0;
    int properties_1 = 0;
    int properties_2 = 0;
    int properties_3 = 0;
    int equipped = 0;
    int damage_vs_small = 0;
    int damage_vs_large = 0;

    items()
    {
        bool ArmourAndShield = false;
        bool MiscellaneousMagic = false;
        bool MiscellaneousWeapons = false;
        bool Potions = false;
        bool Rings = false;
        bool RodsStavesAndWands = false;
        bool Scrolls = false;
        bool Swords = false;

        value = Generate(0,256);
        amount = Generate(0,256);
        // MASTER MAGIC ITEM TABLES
        switch( Generate(0,7) )
        {
        case 0:
            {
                ArmourAndShield = true;
                // FORM
                switch( Generate(0,8) )
                {
                    case 0:
                    {
                        name_1 = "Banded";
                    } break;
                    case 1:
                    {
                        name_1 = "Chain Mail";
                    } break;
                    case 2:
                    {
                        name_1 = "Leather";
                    } break;
                    case 3:
                    {
                        name_1 = "Plate Mail";
                    } break;
                    case 4:
                    {
                        name_1 = "Ring Mail";
                    } break;
                    case 5:
                    {
                        name_1 = "Splinted";
                    } break;
                    case 6:
                    {
                        name_1 = "Scale Mail";
                    } break;
                    case 7:
                    {
                        name_1 = "Studded Leather";
                    } break;
                    case 8:
                    {
                        name_1 = "Shield";
                    } break;
                };
                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "+1";
                        bonus = 1;
                    } break;
                    case 1:
                    {
                        name_2 = "+2";
                        bonus = 2;
                    } break;
                    case 2:
                    {
                        name_2 = "+3";
                        bonus = 3;
                    } break;
                    case 3:
                    {
                        name_2 = "+4/+5";
                        bonus = 4;
                    } break;
                    case 4:
                    {
                        name_2 = "Cursed";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Special";
                    } break;
                };
            }break;
        case 1:
            {
                MiscellaneousMagic = true;
               switch( Generate(0,4) )
                {
                    case 0:
                    {
                        name_1 = "Common";
                    } break;
                    case 1:
                    {
                        name_1 = "Less Common";
                    } break;
                    case 2:
                    {
                        name_1 = "Uncommon";
                    } break;
                    case 3:
                    {
                        name_1 = "Rare";
                    } break;
                };
               switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "Incense of Meditation";
                    } break;
                    case 1:
                    {
                        name_2 = "Javelin of the Raptor";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 2:
                    {
                        name_2 = "Thunder Spear";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 3:
                    {
                        name_2 = "Boots of Elvenkind";
                    } break;
                    case 4:
                    {
                        name_2 = "Candle of Invocation";
                    } break;
                    case 5:
                    {
                        name_2 = "Dust of Appearance";
                    } break;
                };
            }break;
        case 2:
            {
            MiscellaneousWeapons = true;
               switch( Generate(0,3) )
                {
                    case 0:
                    {
                        name_1 = "Arrow";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 1:
                    {
                        name_1 = "Axe";
                        damage_vs_small = 6;
                        damage_vs_large = 4;
                    } break;
                    case 2:
                    {
                        name_1 = "Bolt";
                        damage_vs_small = 4;
                        damage_vs_large = 4;
                    } break;
                    case 3:
                    {
                        name_1 = "Bow";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                };
                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "+1";
                        bonus = 1;
                    } break;
                    case 1:
                    {
                        name_2 = "+2";
                        bonus = 2;
                    } break;
                    case 2:
                    {
                        name_2 = "+3";
                        bonus = 3;
                    } break;
                    case 3:
                    {
                        name_2 = "+4/+5";
                        bonus = 4;
                    } break;
                    case 4:
                    {
                        name_2 = "Cursed";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Special";
                    } break;
                };
            }break;
        case 3:
            {
            Potions = true;
               switch( Generate(0,3) )
                {
                    case 0:
                    {
                        name_1 = "Potion";
                    } break;
                    case 1:
                    {
                        name_1 = "Potion";
                    } break;
                    case 2:
                    {
                        name_1 = "Potion";
                    } break;
                    case 3:
                    {
                        name_1 = "Potion";
                    } break;
                };
                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "+1";
                        bonus = 1;
                    } break;
                    case 1:
                    {
                        name_2 = "+2";
                        bonus = 2;
                    } break;
                    case 2:
                    {
                        name_2 = "+3";
                        bonus = 3;
                    } break;
                    case 3:
                    {
                        name_2 = "+4/+5";
                        bonus = 4;
                    } break;
                    case 4:
                    {
                        name_2 = "Cursed";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Special";
                    } break;
                };
            }break;
        case 4:
            {
            Rings = true;
            //FORM
            name_1 = "Ring";

                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "Charisma";
                    } break;
                    case 1:
                    {
                        name_2 = "Feather Falling";
                    } break;
                    case 2:
                    {
                        name_2 = "Fire Resistance";
                    } break;
                    case 3:
                    {
                        name_2 = "Free Action";
                    } break;
                    case 4:
                    {
                        name_2 = "Genie Summoning";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Invisibility";
                    } break;
                };
            }break;
        case 5:
            {
            RodsStavesAndWands = true;
            name_1 = "";

                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "Rod of Absorption";
                    } break;
                    case 1:
                    {
                        name_2 = "Rod of Cancellation";
                    } break;
                    case 2:
                    {
                        name_2 = "Rod of Captivation";
                    } break;
                    case 3:
                    {
                        name_2 = "Rod of Lordly Might";
                    } break;
                    case 4:
                    {
                        name_2 = "Rod of Resurrection";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Rod of Rulership";
                    } break;
                };
            }break;
        case 6:
            {
            Scrolls = true;
            // TYPE
               switch( Generate(0,2) )
                {
                    case 0:
                    {
                        name_1 = "Spell";
                    } break;
                    case 1:
                    {
                        name_1 = "Protection";
                    } break;
                    case 2:
                    {
                        name_1 = "Cursed";
                    } break;
                };
                //SPELLS
                switch( Generate(0,3) )
                {
                    case 0:
                    {
                        name_2 = "Cleric";
                    } break;
                    case 1:
                    {
                        name_2 = "Druid";
                    } break;
                    case 2:
                    {
                        name_2 = "Illusionist";
                    } break;
                    case 3:
                    {
                        name_2 = "Magic User";
                    } break;
                };
            }break;
        case 7:
            {
                Swords = true;
                // FORM
               switch( Generate(0,3) )
                {
                    case 0:
                    {
                        name_1 = "Bastard Sword";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 1:
                    {
                        name_1 = "Broadsword";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 2:
                    {
                        name_1 = "Longsword";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 3:
                    {
                        name_1 = "Shortsword";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                };
                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "+1";
                        bonus = 1;
                    } break;
                    case 1:
                    {
                        name_2 = "+2";
                        bonus = 2;
                    } break;
                    case 2:
                    {
                        name_2 = "+3";
                        bonus = 3;
                    } break;
                    case 3:
                    {
                        name_2 = "+4/+5";
                        bonus = 4;
                    } break;
                    case 4:
                    {
                        name_2 = "Cursed";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Special";
                    } break;
                };
            }break;
        }
    };

    items( int aValue )
    {
        name_1 = "WATER GOT DAMN IT";
    };

    std::string getName()
    {
        return name_1 + " " + name_2 + " " + name_3;
    };

    friend std::ostream& operator <<(std::ostream& os, items const& a)
    {
        return os << a.name_1 << " " << a.name_2 << " " << a.name_3 << ' '
                  << a.unidentified << ' '
                  << a.type << ' '
                  << a.bonus << ' '
                  << a.save << ' '
                  << a.cursed << ' '
                  << a.amount << ' '
                  << a.weight << ' '
                  << a.value << ' '
                  << a.properties_1 << ' '
                  << a.properties_2 << ' '
                  << a.properties_3 << ' '
                  << a.equipped << ' ';
    }
};

items gameItems[100];

void initItems();

bool lootDropped = false;
bool droppedLoot()
{
    lootDropped = true;
    return lootDropped;
};

void resetLootDropped()
{
    lootDropped = false;
}

typedef struct playerCharacter
{
    std::vector<int> readyCharacterInventoryAC;
    std::vector<int> readyCharacterInventoryTHACO;
    std::vector<int> readyCharacterInventoryDamage;
    std::vector<int> readyCharacterInventoryCost;
    std::vector<std::string> readyCharacterInventoryName;
    std::vector<items> carriedItems;

    int current_stats[6]; // 5 = CON

    std::string name = "default";

    int race = 0; // None
    int characterClass = 0; // None

    // Make a array of these instead
    int coins_copper = 0;
    int coins_silver = 0;
    int coins_electrum = 0;
    int coins_gold = 0;
    int coins_platinum = 0;
    int gender = 0;
    int ac_base = 10;
    int thaco_base = 20;
    int experience = 0;
    int encumbrance = 0;
    int thaco_current = 0;
    int ac_current = 0;
    int hitpoints_current = 0;
    int hitpoints_max = 0;
    // Make the class levels into a array
    int level_cleric = 10;
    int level_fighter = 0;
    int level_magic_user = 0;
    int level_thief = 0;

    int uuid = 0;

    int rowcounter = 0;
    int fontSize = 24;
    int xMouse = 0, yMouse = 0;
    SDL_Point mousePosition;

    int damage_vs_small = 0;
    int damage_vs_large = 0;
    int face = Generate(0,20);

    void calculateStats()
    {
        int count = 0;
        for (int aNumber : current_stats)
        {
            current_stats[count] = Generate(3, 18);//rand() % 15 + 3;
            count++;
        }
    };

    // Improve this function
    void calculateCoins()
    {
        coins_copper = 0;
        coins_electrum = 0;
        coins_platinum = 0;
        coins_silver = 0;
        coins_gold = ( rand()% 15 + 3 ) * 10;
    };

    void printGameItems(std::vector<items> &readyInventory,int x, int y, int fontsize)
    {
        rowcounter = 0;
        for (auto & renderItem: readyInventory)
        {
            if( renderItem.equipped )
            {
                RenderText("EQUIPPED ",White,x,y + (20*rowcounter),fontSize);
                RenderText(renderItem.getName(),White,x + 175,y + (20*rowcounter),fontSize);
            }
            else
            {
                RenderText("NOT EQUIPPED ",White,x,y + (20*rowcounter),fontSize);
                RenderText(renderItem.getName(),White,x + 175,y + (20*rowcounter),fontSize);
            }
            rowcounter++;
        }
    }

    void renderCharacterViewItems()
    {
        rowcounter = 0;
        damage_vs_small = 0;

        RenderText("READY ITEM",White, 1500,100, 48);
        RenderText(getName() + "'S ITEMS",Blue, 1500,70, 24);

        // Render character inventory

        for (auto & renderItem: carriedItems)
        {
            SDL_Point mousePosition;
            SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

            int textWidth = 0;
            int textHeight = 0;
            TTF_Font* m_font = NULL;
            m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 24);
            if(!m_font)
            {
                printf("TTF_OpenFont: %s\n", TTF_GetError());
                // handle error
            }
            if( TTF_SizeText(m_font, "GET THIS HEIGHT VALUE", &textWidth, &textHeight) )
            {
            }

            TTF_CloseFont(m_font);
            m_font = NULL;

            SDL_Rect infoBox = {0,0,0,0};

            infoBox.h = 160;
            infoBox.w = 160;
            infoBox.x = 1800;
            infoBox.y = 200 + (infoBox.h*rowcounter);

            SDL_SetRenderDrawColor(renderer,128,128,128,255);
            SDL_RenderFillRect(renderer, &infoBox);
            RenderText("INFO",White,infoBox.x, infoBox.y - textHeight /2, 24);

            if( SDL_PointInRect(&mousePosition, &infoBox) )
            {
                SDL_PumpEvents();
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    SDL_Rect infoBox = {0,0,0,0};

                    infoBox.h = 640;
                    infoBox.w = 480;
                    infoBox.x = 2560 - infoBox.w;
                    infoBox.y = 0;


                    SDL_SetRenderDrawColor(renderer,128,128,128,255);
                    SDL_RenderFillRect(renderer, &infoBox);
                    RenderTextWrapped(renderItem.name_1 + " " + renderItem.name_2 + " " + renderItem.name_3 + " " + "INFO more information about this item and stuff that are really cool and stuff.",White,infoBox.x + infoBox.w / 2, infoBox.y + infoBox.h / 4, 24,infoBox.w / 2);

                    SDL_Delay(50);
                }
            }

            SDL_Rect dropBox = {0,0,0,0};

            dropBox.h = 160;
            dropBox.w = 160;
            dropBox.x = 2000;
            dropBox.y = 200 + (dropBox.h*rowcounter);

            SDL_SetRenderDrawColor(renderer,128,128,128,255);
            SDL_RenderFillRect(renderer, &dropBox);
            RenderText("DROP",White,dropBox.x, dropBox.y - textHeight /2, 24);

            if( SDL_PointInRect(&mousePosition, &dropBox) )
            {
                SDL_PumpEvents();
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    carriedItems.erase(carriedItems.begin() + rowcounter);
                    droppedLoot();
                    SDL_Delay(50);
                }
            }

            SDL_Rect itemBox = {0,0,0,0};

            itemBox.h = 160 ;
            itemBox.w = 160;
            itemBox.x = 1300;
            itemBox.y = 200 + (itemBox.h*rowcounter);

            if( renderItem.equipped )
            {
                gTexture = NULL;
                gTexture = LoadTexture("./icons/uiAtlas/ui_game_symbol_spatula.png",255);
                SDL_SetTextureColorMod(gTexture, 0, 255, 0); //set yellow letters
                SDL_RenderCopy(renderer, gTexture, NULL, &itemBox);
                SDL_DestroyTexture(gTexture);
                gTexture = NULL;

                damage_vs_small += renderItem.damage_vs_small;
            }
            else
            {
                gTexture = NULL;
                gTexture = LoadTexture("./icons/uiAtlas/ui_game_symbol_spatula.png",255);
                SDL_SetTextureColorMod(gTexture, 255, 255, 255); //set yellow letters
                SDL_RenderCopy(renderer, gTexture, NULL, &itemBox);
                SDL_DestroyTexture(gTexture);
                gTexture = NULL;

                RenderText(renderItem.getName(),White,itemBox.x + itemBox.w, itemBox.y, 24);
                RenderText(std::to_string(renderItem.amount),White,itemBox.x, itemBox.y, 24);
            }

            if( SDL_PointInRect(&mousePosition, &itemBox) )
            {
                SDL_PumpEvents();
                if (SDL_GetMouseState(NULL, NULL) == 0)
                {
                    SDL_Rect hooverBox = {mousePosition.x,mousePosition.y - textHeight /2,textWidth,textHeight};
                    SDL_SetRenderDrawColor(renderer,128,128,128,255);
                    SDL_RenderFillRect(renderer, &hooverBox);
                    RenderText(renderItem.getName(),White,mousePosition.x, mousePosition.y - textHeight /2, 24);
                }
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    //RenderText("PRESSED THE BUTTON",Red, mousePosition.x,mousePosition.y - textHeight /2, 24);
                    renderItem.equipped = !renderItem.equipped;
                    SDL_Delay(100);
                }
            }
            rowcounter++;
        }
    };

    playerCharacter()
    {
        race = rand()% 7;
        characterClass = rand()% 10;
        gender = rand()% 2;
        calculateCoins();
        calculateStats();
        calculateHitPoints();
        initItems();
        readyCharacterInventoryName.push_back(carriedItems.at(0).getName());
        update();
        name = setName();
        gender = rand()%2;
        uuid++;
    };

    void renderFace()
    {
        SDL_Rect FaceFrame = {64,64, 256, 256};

        SDL_DestroyTexture(gTexture);
        gTexture = NULL;
        gTexture = LoadTexture("./icons/faces/" + std::to_string(face) + ".png",255);
        SDL_RenderCopy(renderer, gTexture, NULL, &FaceFrame);
        SDL_DestroyTexture(gTexture);
        gTexture = NULL;
    };

    std::string setName()
    {
        char Player1Name[21];
        NameGen(Player1Name);
        name = Player1Name;
        return name;
    };

    std::string getName()
    {
        return name;
    };

    // Make all these functions into one that returns the requested class level
    int getClericLevel()
    {
        return level_cleric;
    };

    int getFighterLevel()
    {
        return level_fighter;
    };

    int getMagicUserLevel()
    {
        return level_magic_user;
    };

    int getThiefLevel()
    {
        return level_thief;
    };

    int getExperience()
    {
        return experience;
    }

    int calculateHitPoints()
    {
        int hit_dices = 0;
        int calculated_hitpoints = 0;
        int hitpoints_modifier = 0;

        if( current_stats[5] == 3 )
            hitpoints_modifier = -2;
        if( current_stats[5] == 4 )
            hitpoints_modifier = -1;
        if( current_stats[5] == 5 )
            hitpoints_modifier = -1;
        if( current_stats[5] == 6 )
            hitpoints_modifier = -1;
        if( current_stats[5] == 7 )
            hitpoints_modifier = 0;
        if( current_stats[5] == 8 )
            hitpoints_modifier = 0;
        if( current_stats[5] == 9 )
            hitpoints_modifier = 0;
        if( current_stats[5] == 10 )
            hitpoints_modifier = 0;
        if( current_stats[5] == 11 )
            hitpoints_modifier = 0;
        if( current_stats[5] == 12 )
            hitpoints_modifier = 0;
        if( current_stats[5] == 13 )
            hitpoints_modifier = 0;
        if( current_stats[5] == 14 )
            hitpoints_modifier = 0;
        if( current_stats[5] == 15 )
            hitpoints_modifier = 1;
        if( current_stats[5] == 16 )
            hitpoints_modifier = 2;
        if( current_stats[5] == 17 )
            hitpoints_modifier = 2;
        if( current_stats[5] == 18 )
            hitpoints_modifier = 2;
        if( current_stats[5] == 19 )
            hitpoints_modifier = 2;

        hit_dices = level_cleric;

        for( int i = 0; i <= hit_dices; i++ )
        {
            calculated_hitpoints += Generate(1,6);
            calculated_hitpoints += hitpoints_modifier;
        }

        hitpoints_current = calculated_hitpoints;
        hitpoints_max = calculated_hitpoints;
        return calculated_hitpoints;
    };
    int getHitpoints()
    {
        return hitpoints_current;
    }

    int getEncumbrance()
    {
        int encumbranceTotal = 0;
        encumbranceTotal += coins_copper;
        encumbranceTotal += coins_silver;
        encumbranceTotal += coins_electrum;
        encumbranceTotal += coins_gold;
        encumbranceTotal += coins_platinum;
        return encumbranceTotal;
    }

    int getArmourClass()
    {
        ac_current = ac_base;
        for(const auto& value: carriedItems)
        {
            if( value.equipped == 1)
                ac_current += value.bonus;
        }
        return ac_current;
    }

    int getToHitArmourClass()
    {
        // Attack roll ≥ THAC0 - AC
        switch( level_cleric )
        {
            case 1:
                thaco_base = 20;
                break;
            case 2:
                thaco_base = 20;
                break;
            case 3:
                thaco_base = 20;
                break;
            case 4:
                thaco_base = 18;
                break;
            case 5:
                thaco_base = 18;
                break;
            case 6:
                thaco_base = 18;
                break;
            case 7:
                thaco_base = 16;
                break;
            case 8:
                thaco_base = 16;
                break;
            case 9:
                thaco_base = 16;
                break;
            case 10:
                thaco_base = 14;
                break;
            case 11:
                thaco_base = 14;
                break;
            case 12:
                thaco_base = 14;
                break;
            case 13:
                thaco_base = 12;
                break;
            case 14:
                thaco_base = 12;
                break;
            case 15:
                thaco_base = 12;
                break;
            case 16:
                thaco_base = 10;
                break;
            case 17:
                thaco_base = 10;
                break;
            case 18:
                thaco_base = 10;
                break;
            case 19:
                thaco_base = 8;
                break;
            case 20:
                thaco_base = 8;
                break;
        }
        thaco_current = thaco_base;

        return thaco_current;
    }

    std::string getGender()
    {
        if( gender == 0)
            return "FEMALE";
        if( gender == 1)
            return "MALE";
    }

    std::string getClass()
    {
        if( characterClass == 0)
        return "NO CHARACTER CLASS SELECTED";
        if( characterClass == 1)
        return "ASSASSIN";
        if( characterClass == 2)
        return "CLERIC";
        if( characterClass == 3)
        return "DRUID";
        if( characterClass == 4)
        return "FIGHTER";
        if( characterClass == 5)
        return "Illusionist";
        if( characterClass == 6)
        return "PALADIN";
        if( characterClass == 7)
        return "RANGER";
        if( characterClass == 8)
        return "THIEF";
        if( characterClass == 9)
        return "MAGIC USER";
    };

    std::string getRace()
    {
        if( race == 0)
        return "DWARF";
        if( race == 1)
        return "ELF";
        if( race == 2)
        return "GNOME";
        if( race == 3)
        return "HALF ELF";
        if( race == 4)
        return "HALFLING";
        if( race == 5)
        return "HALF-ORC";
        if( race == 6)
        return "HUMAN";
    }

    void update()
    {
        getEncumbrance();
    }
    void initItems()
    {
        carriedItems.push_back(items());
        //carriedItems.at(0) = gameItems[0];
        carriedItems.push_back(items());
        //carriedItems.at(1) = gameItems[1];
        carriedItems.push_back(items());
        //carriedItems.at(1) = gameItems[2];

        playerCharacterInventory[0].push_back(carriedItems.at(0).getName());
        playerCharacterInventory[1].push_back(carriedItems.at(1).getName());
        playerCharacterInventory[2].push_back(carriedItems.at(0).getName());
        playerCharacterInventory[3].push_back(carriedItems.at(1).getName());
        playerCharacterInventory[4].push_back(carriedItems.at(0).getName());
        playerCharacterInventory[5].push_back(carriedItems.at(1).getName());
        readyCharacterInventory[0].push_back("NO");

        readyCharacterInventoryAC.push_back(0);
        readyCharacterInventoryAC.push_back(0);
        readyCharacterInventoryAC.push_back(0);
        readyCharacterInventoryAC.push_back(0);
        readyCharacterInventoryAC.push_back(0);
        readyCharacterInventoryAC.push_back(0);
        readyCharacterInventoryTHACO.push_back(0);
        readyCharacterInventoryTHACO.push_back(0);
        readyCharacterInventoryTHACO.push_back(0);
        readyCharacterInventoryTHACO.push_back(0);
        readyCharacterInventoryTHACO.push_back(0);
        readyCharacterInventoryTHACO.push_back(0);
        readyCharacterInventoryDamage.push_back(0);
        readyCharacterInventoryDamage.push_back(0);
        readyCharacterInventoryDamage.push_back(0);
        readyCharacterInventoryDamage.push_back(0);
        readyCharacterInventoryDamage.push_back(0);
        readyCharacterInventoryDamage.push_back(0);
        readyCharacterInventoryCost.push_back(0);
        readyCharacterInventoryCost.push_back(0);
        readyCharacterInventoryCost.push_back(0);
        readyCharacterInventoryCost.push_back(0);
        readyCharacterInventoryCost.push_back(0);
        readyCharacterInventoryCost.push_back(0);
    }
} playerCharacters;



#endif // PLAYER_CHARACTERS
