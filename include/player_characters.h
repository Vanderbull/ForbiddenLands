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

struct ICollidableObject
{
    virtual ~ICollidableObject( ) { }
    virtual signed int QueryDamage( ) const = 0;
};

struct CollidableObject : ICollidableObject
{
    private:
        signed int Damage_;

    public:
        signed int QueryDamage( ) const
        { return( this->Damage_ ); }
};

struct IActor
{
    virtual ~IActor( ) { }
    virtual void Kill( ) = 0;
    virtual void Resurrect( ) = 0;
};

class Player : IActor
{
    private:
        signed int Health_;

    public:
        void Kill( ){};
        void Resurrect( ){};
        void OnObjectCollision( ICollidableObject *Object_ )
        {
            this->Health_ -= Object_->QueryDamage( );
            if( this->Health_ < 0 )
                this->Kill( );
        }
};

     Player myPlayer;

typedef struct playerCharacter
{
    std::vector<items> carriedItems;
    std::vector<spells> carriedSpells;
    int current_stats[6]; // 5 = CON
    std::string name = "default";
    int race = 0; // None
    int characterClass = 0; // None
    int coins_gold = 0;
    int ac_base = 10;
    int experience = 0;
    int encumbrance = 0;
    int ac_current = 0;
    int hitpoints_current = 0;
    int hitpoints_max = 0;
    int rowcounter = 0;
    SDL_Point mousePosition;
    int damage_vs_small = 0;
    int damage_vs_large = 0;
    int face = 0;
    int hunger = 0;
    int thirst = 0;
    SDL_Texture* faceImage;
    int healingPotions = 1;
    int initiative = 0;
    int daily_stamina = 100;
    int action_stamina = 100;

    void sleeping(int hours)
    {
        daily_stamina += hours;
        action_stamina += hours*10;
    };

    void generateInitiative()
    {
        initiative = Generate(1,6);
    };

    void increaseHunger()
    {
        if( hunger < 100 )
        hunger++;
    }

    void decreaseHunger()
    {
        if( hunger > 0 )
        hunger--;
    }

    void increaseThirst()
    {
        if( thirst < 100 )
        thirst++;
    }

    void decreaseThirst()
    {
        if( thirst > 0 )
        thirst--;
    }

    void calculateStats()
    {
        int count = 0;
        for (int aNumber : current_stats)
        {
            current_stats[count] = Generate(3, 18);//rand() % 15 + 3;
            count++;
        }
    };

    int startCounter = 0;
    int stopCounter = 6;
    int moveIndex = 0;

    void renderItemData(items renderItem)
    {
        SDL_Rect infoBox = {0,0,0,0};

        infoBox.h = 640;
        infoBox.w = 480;
        infoBox.x = 2560 - infoBox.w;
        infoBox.y = 0;

        SDL_SetRenderDrawColor(renderer,128,128,128,255);
        SDL_RenderFillRect(renderer, &infoBox);
        RenderTextWrapped(renderItem.name_1 + " " + renderItem.name_2 + " " + renderItem.name_3 + "\n" +
                          "Amount: " + std::to_string(renderItem.amount) + "\n" +
                          "Bonus: " + std::to_string(renderItem.bonus) + "\n" +
                          "Cursed: " + std::to_string(renderItem.cursed) + "\n" +
                          "D v L: " + std::to_string(renderItem.damage_vs_large) + "\n" +
                          "D v S: " + std::to_string(renderItem.damage_vs_small) + "\n" +
                          "Equipped: " + std::to_string(renderItem.equipped) + "\n" +
                          "Armour class: " + std::to_string(renderItem.armour_class) + "\n" +
                          "Icon: " + renderItem.icon.c_str() + "\n"
                          ,White,infoBox.x + infoBox.w / 2, infoBox.y + infoBox.h / 4, 24,infoBox.w / 2);
    };

    void renderCharacterViewItems()
    {
        rowcounter = 0;
        damage_vs_small = 0;
        moveIndex = 0;

        if( stopCounter < startCounter+5)
        {
            stopCounter = startCounter+5;
            if( stopCounter > carriedItems.size() -1 )
                stopCounter = carriedItems.size() -1;
        }

        SDL_Rect increase = {2510,500,50,50};
        SDL_SetRenderDrawColor(renderer,255,128,128,255);
        SDL_RenderFillRect(renderer, &increase);
        SDL_Point mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if( SDL_PointInRect(&mousePosition, &increase) )
        {
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( stopCounter < carriedItems.size()-1 )
                {
                    startCounter++;
                    stopCounter++;
                }
            }
        }

        RenderText(std::to_string(stopCounter) ,White, increase.x,increase.y, 48);

        SDL_Rect decrease = {2510,100,50,50};
        SDL_SetRenderDrawColor(renderer,255,128,128,255);
        SDL_RenderFillRect(renderer, &decrease);
          //SDL_Point mousePosition;
           // SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        if( SDL_PointInRect(&mousePosition, &decrease) )
        {
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( startCounter > 0)
                {
                    startCounter--;
                    stopCounter--;
                }
            }
        }
        RenderText(std::to_string(startCounter) ,White, decrease.x,decrease.y, 48);

        if( stopCounter >= carriedItems.size())
            stopCounter = carriedItems.size();

        // Render character inventory

        for (auto & renderItem: carriedItems)
        {
            if( rowcounter >= startCounter && rowcounter <= stopCounter )
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
                infoBox.y = 200 + (infoBox.h*moveIndex);

                SDL_SetRenderDrawColor(renderer,128,128,128,255);
                SDL_RenderFillRect(renderer, &infoBox);
                RenderText("INFO",White,infoBox.x, infoBox.y - textHeight /2, 24);

                if( SDL_PointInRect(&mousePosition, &infoBox) )
                {
                    SDL_PumpEvents();
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        renderItemData(renderItem);
                        SDL_Delay(50);
                    }
                }

                SDL_Rect itemBox = {0,0,0,0};

                itemBox.h = 160 ;
                itemBox.w = 160;
                itemBox.x = 1300;
                itemBox.y = 200 + (itemBox.h*moveIndex);

                if( renderItem.icon != "" )
                if( renderItem.equipped )
                {
                    gTexture = NULL;
                    //gTexture = LoadTexture("./icons/uiAtlas/ui_game_symbol_spatula.png",255);
                    gTexture = LoadTexture(renderItem.icon,255);
                    SDL_SetTextureColorMod(gTexture, 0, 255, 0); //set yellow letters
                    SDL_RenderCopy(renderer, gTexture, NULL, &itemBox);
                    SDL_DestroyTexture(gTexture);
                    gTexture = NULL;

                    RenderText(renderItem.getName(),White,itemBox.x + itemBox.w, itemBox.y, 24);

                    damage_vs_small += renderItem.damage_vs_small;
                }
                else
                {
                    gTexture = NULL;
                    gTexture = LoadTexture(renderItem.icon,255);
                    SDL_SetTextureColorMod(gTexture, 255, 255, 255); //set yellow letters
                    SDL_RenderCopy(renderer, gTexture, NULL, &itemBox);
                    SDL_DestroyTexture(gTexture);
                    gTexture = NULL;

                    RenderText(renderItem.getName(),White,itemBox.x + itemBox.w, itemBox.y, 24);
                    //RenderText(std::to_string(renderItem.amount),White,itemBox.x, itemBox.y, 24);
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
                        renderItem.equipped = !renderItem.equipped;
                        SDL_Delay(100);
                    }
                }

                SDL_Rect dropBox = {0,0,0,0};

                dropBox.h = 160;
                dropBox.w = 160;
                dropBox.x = 2000;
                dropBox.y = 200 + (dropBox.h*moveIndex);

                SDL_SetRenderDrawColor(renderer,128,128,128,255);
                SDL_RenderFillRect(renderer, &dropBox);
                RenderText("DROP",White,dropBox.x, dropBox.y - textHeight /2, 24);

                if( SDL_PointInRect(&mousePosition, &dropBox) )
                {
                    SDL_PumpEvents();
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        carriedItems.erase(carriedItems.begin() + rowcounter);
                        if( startCounter > 0 )
                        {
                            startCounter--;
                            stopCounter--;
                        }
                        droppedLoot();
                        SDL_Delay(50);
                    }
                }
                moveIndex++;
            }
            rowcounter++;
        }
    };

    playerCharacter()
    {
        std::cout << "loading playerCharacter..." << std::endl;
        race = Generate(0,7);
        calculateStats();
        calculateHitPoints();
        initItems();
        update();
        name = setName();
        face = Generate(0,20);
        faceImage = NULL;
    };

    void loadCharacterFace()
    {
        if( faceImage == NULL )
        {
            std::cout << "trying to load ./icons/faces/" << std::to_string(face) << ".png" << std::endl;
            faceImage = LoadTexture("./icons/faces/" + std::to_string(face) + ".png",255);
            if( faceImage == NULL )
            {
                std::cout << "failed to load ./icons/faces/" << std::to_string(face) << ".png" << std::endl;
                exit(99);
            }
            else
            {
                std::cout << "loaded ./icons/faces/" << std::to_string(face) << ".png" << std::endl;
            }
        }
    };

    void renderFace()
    {
        SDL_Rect FaceFrame = {64,64, 256, 256};
        SDL_RenderCopy(renderer, faceImage, NULL, &FaceFrame);
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

        //hit_dices = level_cleric;

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
        encumbranceTotal += coins_gold;
        return encumbranceTotal;
    }

    int getArmourClass()
    {
        ac_current = ac_base;
        for(const auto& value: carriedItems)
        {
            if( value.equipped == 1)
                ac_current += value.armour_class;
        }
        return ac_current;
    }

    // remove no class selected
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
        return "ILLUSIONIST";
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
        carriedItems.push_back(items());
        carriedItems.push_back(items());

        playerCharacterInventory[0].push_back(carriedItems.at(0).getName());
        playerCharacterInventory[1].push_back(carriedItems.at(1).getName());
        playerCharacterInventory[2].push_back(carriedItems.at(0).getName());
        playerCharacterInventory[3].push_back(carriedItems.at(1).getName());
        playerCharacterInventory[4].push_back(carriedItems.at(0).getName());
        playerCharacterInventory[5].push_back(carriedItems.at(1).getName());
    }
} playerCharacters;

#endif // PLAYER_CHARACTERS
