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
#include <algorithm>

using namespace std;

#include "globals.h"
#include "actor.h"
#include "ingametime.h"
#include "portals.h"
#include "randomizer.h"
#include "weather/weather.h"
#include "../version.h"
#include "classes/skillobject.h"
#include "classes/itemobject.h"
#include "classes/textureholder.h"
#include "classes/soundholder.h"
#include "classes/worldmap.h"
#include "classes/questobject.h"

extern int testing;

class TextureHolder;
class SoundHolder;
class WorldMap;
class QuestList;

class CGameState;

class CGameEngine
{
public:

    QuestList Quests;

    // Sound settings
    int music_volume = 0;
    int sfx_volume = 0;

    InGameTime gameTime;
    ACTOR SActor;
    ACTOR SNpc;
    QuestList questList;

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

	void DisplayQuests();
	int Generate(const int from, const int to);
	int RenderText(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize);
	int RenderTitle(std::string renderText, SDL_Color colorValue, int iX, int iY);
	int RenderBreadText(std::string renderText, SDL_Color colorValue, int iX, int iY);
	int RenderText2(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize);
	int RenderText3(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize);
	int RenderTextWrapped(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize, int wrapped);
	SDL_Texture* LoadTexture( const std::string &str, int alpha );

	void CreateItem(int index, std::string Name,int Efficiency,int MinDamage,int MaxDamage,
    int DmgType,int NumHands,int Bodypart,int UsedBy,int Skill,
    int BaseWorth,int Price,int Protection,int Enchantments,int Effect,
    int EffectCharges,int MinEffect,int MaxEffect,int Features);

    Item SpawnRandomItem();

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
	void renderQuests();
	void renderQuestsList();

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

    SDL_Color Green = {0, 255, 0, 255};
    SDL_Color BlueGreen = {255, 255, 255, 255};
    SDL_Color Blue = {0, 0, 255, 255};
    SDL_Color Red = {255, 0, 0, 255};
    SDL_Color White = {255, 255, 255, 255};
    SDL_Color Black = {0, 0, 0, 255};

    SDL_Texture* North;
    SDL_Texture* East;
    SDL_Texture* South;
    SDL_Texture* West;

    // Make these a blob
    SDL_Texture* mapTexture[16][16][4];
    SDL_Texture* encampTexture[4];
    SDL_Texture* battleState;
    SDL_Texture* gameoverState;
    SDL_Texture* slot;

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

    std::vector<std::string> v_ItemNames = {
                                            "Bronze ring","Iron ring",
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

    //std::vector<Item> v_Item;
    //access to the elements will be a bit harder (v[width * y +x] or v[height * x + y])
    std::array<Item,9*10> v_Item;
    std::array<Item,9*10> v_InventoryItem;
    std::vector<SkillObject> v_Skill;
    std::vector<SkillObject> v_LearnedSkill;
    SkillObject Skill;
	void AddItem();
	void AddSkill();



	// Look at enums with flags later
	enum BodyParts {HEAD,NECK,SHOULDER,CHEST,LEFT_ARM,RIGHT_ARM,HANDS,LEGS,FEET};

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
                RenderText(line.c_str(), Black, current.w / 2,countery*24,48);
                content.push_back(row);
                countery++;
            }
        }
        else
        {
            exit(99);
        }
    }

    Mix_Chunk* _sample[20];


	int number_of_enemies = 1;

	int random_events[16][16][28];

	int fog_of_war_raiding[16][16][28];
	int fog_of_war_worldmap[10][35];

    template<class Engine, class Integer, size_t SIZE>
    void fill_array(Engine& eng, std::array<Integer, SIZE>& a, Integer lower = 0, Integer upper = 1000)
    {
        std::uniform_int_distribution<Integer> uid1(lower, upper);

        std::generate(a.begin(), a.end(), [&]
        {
            return uid1(eng);
        });
    }

    template<typename Type, std::size_t M, std::size_t N, std::size_t O>
    constexpr void fill_3D_array(Type(&arr3D)[M][N][O], const Type val = Type{}) noexcept
    {
       std::fill_n(&arr3D[0][0][0], M * N * O, val);
       // or using std::fill
       // std::fill(&arr3D[0][0][0], &arr3D[0][0][0] + (M * N * O), val);
    }

    template<typename Type, std::size_t M, std::size_t N, std::size_t O>
    constexpr void print_3D_array(Type(&arr3D)[M][N][O]) noexcept
    {
       for (auto& arr2D : arr3D)
       {
          std::cout << "Array2D:.....\n";
          for (auto& arr : arr2D)
          {
             std::cout << "Array:.....\n";
             for (const Type ele : arr)
             {
                std::cout << ele << " ";
             }
             std::cout << "\n";
          }
       }
    }

    //Loot state variables
    int hides = 10;
    int slaves = 10;
    int gold = 0;
    int silver = 0;

    enum {WEST,EAST,SOUTH,NORTH};

    Mix_Music* song = NULL;

    struct Army
    {
        int old;
        int middleage;
        int young;
    };

    Army Raiding_Party;
    std::string Village_Name = "";

private:
	// the stack of states
	std::vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;

};



#endif
