#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <sys/utsname.h>
#include <array>
#include <map>
#include <dirent.h>
using namespace std;

#include "globals.h"
#include "actor.h"
#include "ingametime.h"
#include "portals.h"
#include "randomizer.h"
#include "weather/weather.h"
#include "../version.h"
#include "classes/skillobject.h"

extern int testing;

//class SkillObject {
//public:
//
//    std::string Name = "";
//    std::string Group = "";
//    int Learned = 0;
//    int MaximumExpertise = 0;
//    int InitialRequirementsAttribute = 0;
//    int InitialRequirementsValue = 0;
//    int GroupID = 0;
//    std::string Description = "";
//    SDL_Rect Position = {0,0,0,0};
//
//    SkillObject(void);
//    SkillObject( std::string N_, std::string Group_, int Learned_, int MaxExp_ );
//    SkillObject( SDL_Rect Pos);
//};

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

class TextureHolder
{
private:
    // A pointer of the same type as the class itself
    // the one and only instance
    //static TextureHolder* m_s_Instance;
public:
    // A map container from the STL,
    // that holds related pairs of String and Texture
    map<string, SDL_Texture*> m_Textures;

    // Texture textureBackground = TextureHolder::GetTexture(
    // "graphics/background_sheet.png");

    TextureHolder(){};
    //static Texture& GetTexture(string const& filename);
};

class SoundHolder
{
public:
    map<string, Mix_Chunk*> m_Sounds;

    SoundHolder(){};
};

class TextureHolder;
class SoundHolder;

class CGameState;

class CGameEngine
{
public:

    InGameTime gameTime;
    ACTOR SActor;
    ACTOR SNpc;

	void Init(const char* title, int width=640, int height=480,
		      int bpp=0, bool fullscreen=false);
	void Cleanup();
	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();
	void HandleEvents();
	void Update();
	void Draw();
	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	int Generate(const int from, const int to);
	int RenderText(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize);
	int RenderTitle(std::string renderText, SDL_Color colorValue, int iX, int iY);
	int RenderBreadText(std::string renderText, SDL_Color colorValue, int iX, int iY);
	int RenderText2(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize);
	int RenderText3(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize);
	int RenderTextWrapped(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize, int wrapped);
	SDL_Texture* LoadTexture( const std::string &str, int alpha );

	void loadMapTextures();
	void initShop();

	int ReferenceResolutionWidth = 2560;
	int ReferenceResolutionHeight = 1440;

	float ScaleResolution(int ResolutionWidth )
	{
        return ResolutionWidth / ReferenceResolutionWidth;
	};

    enum timeOfDay
    {
        day,
        night
    };

//    int currentDay = 0;
//    int currentTime = 0;
    int currentTimeOfDay = day;

    // Live ticking time or by movement
    int currentTimeElapse(bool tick = false )
    {
        if( tick )
        {
            gameTime.tm_sec++;

            if( gameTime.tm_sec == 60 )
            {
                gameTime.tm_sec = 0;
                gameTime.tm_min++;
            }
            if( gameTime.tm_min == 59 )
            {
                gameTime.tm_min = 0;
                gameTime.tm_hour++;
            }
            if( gameTime.tm_hour == 23 )
            {
                gameTime.tm_hour = 0;
                gameTime.tm_mday++;
               if( gameTime.tm_hour > 6 && gameTime.tm_hour < 18 )
                {
                    currentTimeOfDay = day;
                }
                else
                {
                    currentTimeOfDay = night;
                }
            }
            if( gameTime.tm_mon == 11 )
            {
                gameTime.tm_mon = 0;
                gameTime.tm_year++;
            }

        }
        return currentTimeOfDay;
    };

	void renderDaytime();

	TextureHolder TextureManager;
	SoundHolder SoundManager;

	SDL_Texture* BackgroundTexture;
	SDL_Event event;
	SDL_Rect gRect;
    SDL_Surface* gSurface;
	SDL_Texture* gTexture;
    SDL_Window * window;
    SDL_DisplayMode monitor[6];
    SDL_DisplayMode current;

    struct utsname uts;
    SDL_Renderer * renderer;

    SDL_Color Yellow = {255, 255, 255, 255};
    SDL_Color YellowGreen = {255, 255, 255, 255};
    SDL_Color Green = {0, 255, 0, 255};
    SDL_Color BlueGreen = {255, 255, 255, 255};
    SDL_Color Blue = {0, 0, 255, 255};
    SDL_Color BlueViolet = {255, 255, 255, 255};
    SDL_Color Violet = {255, 255, 255, 255};
    SDL_Color RedViolet = {255, 255, 255, 255};
    SDL_Color Red = {255, 0, 0, 255};
    SDL_Color RedOrange = {255, 255, 255, 255};
    SDL_Color Orange = {255, 255, 255, 255};
    SDL_Color YellowOrange = {255, 255, 255, 255};
    SDL_Color White = {255, 255, 255, 255};
    SDL_Color Black = {0, 0, 0, 255};

    SDL_Texture* North;
    SDL_Texture* East;
    SDL_Texture* South;
    SDL_Texture* West;

    // Make these a blob
    SDL_Texture* mapTexture[16][16][4];

    //Make these a blob
    TTF_Font* gameTitleFont;
    TTF_Font* gameBreadTextFont;

    int StartAbilityPoints = 20;

    uint32_t experience_required_for_level(double level)
    {
        double exp = 0;
        for(double x = 1; x<level; x++)
        {
            exp += std::floor(x + (300 + (level * 100)) * std::pow(2, (x / 10)));
        }
        exp = (std::round(std::floor(exp) / 10) * 10);
        return (uint32_t)exp;
    };

    std::vector<std::string> LearnedSkill;

    std::vector<SDL_Rect> SkillRect;

    uint32_t experience_required_for_skill_level(double level)
    {
        double exp = 0;
        for(double x=1;x<level;x++)
        {
            exp += std::floor(x + (150 + (level * 5)) * std::pow(2, (x / 10)));
        }
        exp = (std::round(std::floor(exp) / 10) * 10);
        return (uint32_t)exp;
    }

    int AllowedSkills = 3;

    // effect = the value indicated by the enchantment i.e. Power +2
    SkillObject test{};

    std::vector<std::string> v_ItemNames = {"Bardiche","Battle Axe","Bow",
                                            "Broad Axe","Club","Crossbow",
                                            "Dagger","Falchion","Flail",
                                            "Greatsword","Halberd","Hammer",
                                            "HandAxe","Long sword","Mace",
                                            "Morning star","Quarterstaff","Scimitar",
                                            "Scythe","Short sword","Spear",
                                            "War axe","Chainmail","Leather armor",
                                            "Plate mail","Ring mail","Robe",
                                            "Scale mail","Buckler","Shield",
                                            "Kite shield","Gauntlets","Helmet",
                                            "Mage hat","Bone amulet","Celtic amulet",
                                            "Stone amulet","Crystal amulet","Idol amulet",
                                            "Pentagram amulet","Cloak","Boots",
                                            "Staff","Bronze ring","Iron ring",
                                            "Silver ring","Golden ring","Jewel ring",
                                            "Pearl ring", "Emerald ring", "Opal ring",
                                            "Rune of Power","Rune of Personality","Rune of Intelligence",
                                            "Rune of Toughness","Rune of Technique","Rune of Quickness",
                                            "Rune of Perception","Rune of Fitness","Rune of Lore",
                                            "Rune of Persuasion","Rune of Taming","Rune of Quickhand",
                                            "Rune of Stealth","Rune of Awareness","Rune of Fire Element",
                                            "Rune of Air Element","Rune of Water Element","Rune of Earth Element",
                                            "Rune of Energy Element","Rune of Mental Element","Rune of Soul Element",
                                            "Potion of Healing","Potion of Cure Poison","Potion of Cure Flaming",
                                            "Potion of Cure Paralysis","Potion of Cure Fear","Potion of cure Insanity",
                                            "Potion of cure Exhaustion", "Potion of cure Curse", "Potion of Poison",
                                            "Torch",
                                            };

    std::vector<std::string> v_ItemNamesShop;

    std::vector<Item> v_Item;
    std::vector<SkillObject> v_Skill;
    SkillObject Skill;
	void AddItem();
	void AddSkill();

	int ChoosenProfession;
	int ChoosenRace;

	// Look at enums with flags later
	enum BodyParts {HEAD,NECK,SHOULDER,CHEST,ARM,HAND,FINGER,FEET};

	class BaseMonster
	{
	    std::string Name;
	    int Type;
	    int LV;
	    int HP;
	    int Pro;
	    int Tou;
	    int Qui;
	    int Actions;
	    int Resistance;
	    int Vunerability;
	};

    weather_engine cweather_engine;

    void read_directory(const std::string& name, std::vector<string>& v)
    {
        DIR* dirp = opendir(name.c_str());
        if(dirp == NULL)
        {
            std::cout << "Error in read_directory function, missing folder" << std::endl;
            exit(errno);
        }

        struct dirent * dp;
        while ((dp = readdir(dirp)) != NULL) {
            v.push_back(dp->d_name);
        }
        closedir(dirp);
    }

    std::vector<std::string> imagesFiles;

    SDL_Rect CurrentLocation{0,0,128,128};

    bool newGame = true;

    weather_engine WeatherEngine;

    SDL_Rect worldMapTiles[17][41];

    void generateWorldMapTiles()
    {
        for(int x = 0; x < 17; x++)
            for(int y = 0; y < 41; y++)
            {
                SDL_Rect imageSize = {x*16 + 50, y*16 + 50,8,8};
                worldMapTiles[x][y] = imageSize;
            }
    }

    void renderWorldMapTiles()
    {
        std::vector<vector<string>> content;
        std::vector<string> row;
        std::string line, word;
        int counterx,countery = 0;

        fstream file ("./assets/data/textures/sweden_data", ios::in);
        if(file.is_open())
        {
            while(getline(file, line))
            {
                row.clear();
                stringstream str(line);
                RenderText(line.c_str(), White, current.w / 2,countery*24,48);
                //RenderText(line.c_str(), White, 0,countery*24,48);
//                while(getline(str, word, ' '))
//                {
//                }
                content.push_back(row);
                countery++;
            }
        }
        else
        {
        exit(99);
        }
//        for(int x = 0; x < 17; x++)
//            for(int y = 0; y < 41; y++)
//            {
//                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
//                SDL_RenderFillRect(renderer, &worldMapTiles[x][y]);
//            }
    }

    Mix_Chunk* _sample[20];

private:
	// the stack of states
	vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;
};



#endif
