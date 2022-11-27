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
#include <vector>
#include <sys/utsname.h>
#include <array>
#include <map>
#include <dirent.h>
using namespace std;

#include "globals.h"
#include "actor.h"
//#include "ingametime.h"
#include "portals.h"
#include "randomizer.h"
#include "weather/weather.h"
#include "../version.h"

extern int testing;

class SkillObject {
public:

    std::string Name = "";
    std::string Group = "";
    int Learned = 0;
    int MaximumExpertise = 0;
    int InitialRequirementsAttribute = 0;
    int InitialRequirementsValue = 0;
    int GroupID = 0;
    //std::vector<std::string> UtilizedBy;
    std::string Description = "";

    SkillObject(void);
    SkillObject(std::string N_);
};

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

    int currentDay = 0;
    int currentTime = 0;
    int currentTimeOfDay = day;

    int currentTimeElapse(bool tick = false )
    {
        if( tick )
        {
            currentTime++;
            if( currentTime > 24 )
            {
                currentTime = 0;
                currentDay++;
            }
            if( currentTime > 6 && currentTime < 18 )
            {
                currentTimeOfDay = day;
            }
            else
            {
                currentTimeOfDay = night;
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
    //std::string mapTextureFile[16][16][4];

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
	std::vector<std::string> v_BaseMonsters = {"Cube, Ooze","Doppelganger","Goblin","Goblin, Warrior", "Goblin Chief", "Snail","Snail Fire","Snake Constrictor"};

    std::array<int, 300> armsAndArmoursValue;
    std::vector<SGenericItem> generalShopItems;
    std::vector<SGenericItem> jewelleryShopItems;
    std::vector<SGenericItem> silverShopItems;
    std::vector<SGenericItem> armsAndArmoursShopItems;

    //map<string, SDL_Texture*> myTextures;
    weather_engine cweather_engine;

    portal mapPortal[16][16];
    portal savePortal[16][16];

    void initPortal(std::string _dataFilePath)
    {
        std::cout << _dataFilePath.c_str() << std::endl;
        int x,y = 0;
        bool west,east,south,north = false;
        std::string west_map,east_map,south_map,north_map = _dataFilePath;
        int warp_x,warp_y;
        std::string description;

        bool directions[4] = {false,false,false,false};
        std::string directions_map[4] = {_dataFilePath.c_str(),_dataFilePath.c_str(),_dataFilePath.c_str(),_dataFilePath.c_str()};
        SDL_Point warp;

        std::ifstream dataFile (_dataFilePath);

        if(!dataFile)
        {
            cerr << "Error: init_portals(): file could not be opened" << _dataFilePath << endl;
            exit(EXIT_FAILURE);
        }

        do
        {
            dataFile >> x >> y >> west >> east >> south >> north >> west_map >> east_map >> south_map >> north_map >> warp_x >> warp_y >> description;
            mapPortal[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        while(!dataFile.eof());

        dataFile.close();
    };

    void loadPortal()
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading portals\n");

        initPortal("./assets(data/textures/maps/phlan/phlan_portals");
        for( int y = 0; y < 16; y++)
            for( int x = 0; x < 16; x++)
                savePortal[x][y].setupStruct(mapPortal[x][y]);
    };

    bool getActivePortal(int x, int y, std::string rotation)
    {
        if( mapPortal[x][y].getMap(rotation) != "")
        {
            //mapActive = mapPortal[x][y].getMap(rotation);
            loadPortal();
        }

        if( mapPortal[x][y].getMap(rotation) != "phlan" )
        {
            if( mapPortal[x][y].getX() != -1 )
                SActor.PlayerCoordinate.x = mapPortal[x][y].getX();
        }
        return mapPortal[x][y].active_portal(rotation);
    };

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

private:
	// the stack of states
	vector<CGameState*> states;

	//Actor SActor;

	bool m_running;
	bool m_fullscreen;
};



#endif
