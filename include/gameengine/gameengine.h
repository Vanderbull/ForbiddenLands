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
#include "portals.h"
#include "randomizer.h"
#include "weather/weather.h"
#include "../version.h"

extern int testing;

class SkillObject {
public:

    std::string Name;
    int MaximumExpertise;
    int InitialRequirementsAttribute;
    int InitialRequirementsValue;
    int Group;
    std::vector<std::string> UtilizedBy;
    std::string Description;

    SkillObject(void);
    SkillObject(std::string,char,int);
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

    std::string icon = "./icons/uiAtlas/ui_game_symbol_other.png";
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

	int RenderText(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize);
	int RenderTitle(std::string renderText, SDL_Color colorValue, int iX, int iY);
	int RenderBreadText(std::string renderText, SDL_Color colorValue, int iX, int iY);
	int RenderText2(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize);
	int RenderText3(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize);
	int RenderTextWrapped(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize, int wrapped);
	SDL_Texture* LoadTexture( const std::string &str, int alpha );

	void loadMapTextures();
	void initShop();

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
	SDL_Surface* screen;
    SDL_Surface* gSurface;

	SDL_Texture* gTexture;

    SDL_Window * window;
    SDL_DisplayMode monitor[6];
    SDL_DisplayMode current;

    struct utsname uts;
    SDL_Renderer * renderer;
	SDL_Renderer * renderer2;

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
    // Color Wheel end

    SDL_Color White = {255, 255, 255, 255};
    SDL_Color Black = {0, 0, 0, 255};

    SDL_Texture* North;
    SDL_Texture* East;
    SDL_Texture* South;
    SDL_Texture* West;
    SDL_Texture* menuBackgroundTexture;
    SDL_Texture* currentViewTexture;
    SDL_Texture* encampTexture;
    //SDL_Texture* gTexture;

    // Make these a blob
    SDL_Texture* mapTexture[16][16][4];
    std::string mapTextureFile[16][16][4];

    SDL_Texture* MainMenuBackgroundTexture;

    //Make these a blob
    TTF_Font* gameTitleFont;
    TTF_Font* gameBreadTextFont;

    struct CoordinatePair
    {
        int x;
        int y;
        int z;
    };
    CoordinatePair PlayerCoordinate = {15,1,0};

    // Abilities
    int Power = 15;
    int Intelligence = 15;
    int Personality = 15;
    int Toughness = 15;
    int Technique = 15;
    int Quickness = 15;
    int Perception = 15;

    int Ability[7] = {15,15,13,15,15,15,15};

    int StartAbilityPoints = 20;

    enum {POW, INT, PERS, TOU, TECH, QUI, PERC};

    int PowerMod = floor( Power - 20 / 2 );
    int IntelligenceMod = floor( Intelligence - 20 / 2 );
    int PersonalityMod = floor( Personality - 20 / 2 );
    int ToughnessMod = floor( Toughness - 20 / 2 );
    int TechniqueMod = floor( Technique - 20 / 2 );
    int QuicknessMod = floor( Quickness - 20 / 2 );
    int PerceptionMod = floor( Perception - 20 / 2 );

    int AbilityMod[7] = {PowerMod,IntelligenceMod,PersonalityMod,ToughnessMod,TechniqueMod,QuicknessMod,PerceptionMod};

    int PowerBonus = 0;
    int IntelligenceBonus = 4;
    int PersonalityBonus = 0;
    int ToughnessBonus = 4;
    int TechniqueBonus = 0;
    int QuicknessBonus = 0;
    int PerceptionBonus = 0;

    int KnightBaseHP = 40 + (5 * ToughnessMod);
    int ClericBaseHP = 28 + (3 * ToughnessMod);
    int WizardBaseHP = 28 + (3 * ToughnessMod);

    int KnightHPLevel = 6;
    int ClericHPLevel = 3;
    int WizardHPLevel = 3;

    int TotalSpells = IntelligenceMod;

    int InitiateSpellAllocation = 10 + IntelligenceMod;
    int ApprenticeSpellAllocation = floor(7*0.7);
    int AdeptSpellAllocation = floor(4*0.7);
    int MasterSpellAllocation = floor(2*0.7);
    int GrandMasterSpellAllocation = floor(1*0.7);

    int KnightStrongAbilityPower = 7;
    int KnightStrongAbilityThoughness = 7;
    int KnightWeakAbilityIntelligence = 7;

    int ClericStrongAbilityIntelligence = 7;
    int ClericStrongAbilityPersonality = 7;
    int ClericWeakAbilityPower = 7;

    int WizardStrongAbilityIntelligence = 7;
    int WizardStrongAbilityPerception = 7;
    int WizardWeakAbilityPower = 7;

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

    std::vector<std::string> SkillGroups = { "Weapon", "Armour","Magic","Misc"};

   std::vector<std::string> Skill = { "Fitness", "Lore","Persuasion","Taming","Quickhand","Stealth","Awareness","Short blade",
                                    "Long blade","Bow","Bludgeon","Short axe","Long axe","Poleblade","Pole","Shield","Leather armour",
                                    "Chained armour","Scaled armour","Plated armour","Rune magic"};
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

    std::vector<std::string> v_ItemNames = {"Bardiche", "Bardiche +1", "Bardiche +2", "Bardiche +3", // Weapon
                                            "Battle Axe", "Battle Axe +2", "Battle Axe +3",
                                            "Bow", "Bow +1", "Bow +2", "Bow +3",
                                            "Broad Axe", "Broad Axe +1","Broad Axe +2","Broad Axe +3",
                                            "Club","Club +1","Club +2","Club +3",
                                            "Crossbow", "Cross bow +1","Cross bow +2","Cross bow +3",
                                            "Dagger","Dagger +1","Dagger +2","Dagger +3",
                                            "Falchion","Falchion +1","Falchion +2","Falchion +3",
                                            "Flail","Flail +1","Flail +2","Flail +3",
                                            "Greatsword","Greatsword +1","Greatsword +2","Greatsword +3",
                                            "Halberd","Halberd +1","Halberd +2","Halberd +3",
                                            "Hammer","Hammer +1","Hammer +2","Hammer +3",
                                            "HandAxe","HandAxe +1","HandAxe +2","HandAxe +3",
                                            "Long sword","Long sword +1","Long sword +2","Long sword +3",
                                            "Mace","Mace +1","Mace +2","Mace +3",
                                            "Morning star","Morning star +1","Morning star +2","Morning star +3",
                                            "Quarterstaff","Quarterstaff +1","Quarterstaff +2","Quarterstaff +3",
                                            "Scimitar","Scimitar +1","Scimitar +2","Scimitar +3",
                                            "Scythe","Scythe +1","Scythe +2","Scythe +3",
                                            "Short sword","Short sword +1","Short sword +2","Short sword +3",
                                            "Spear","Spear +1","Spear +2","Spear +3",
                                            "War axe","War axe +1","War axe +2","War axe +3",
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // Armor
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Buckler", "Buckler +1", "Buckler +2", "Buckler +3",                    // Shield
                                            "Shield", "Shield +1", "Shield +2", "Shield +3",
                                            "Kite shield", "Kite shield +1", "Kite shield +2", "Kite shield +3",
                                            "Gauntlets", "Gauntlets +1", "Gauntlets +2", "Gauntlets +3",                    // Gauntlets
                                            "Helmet", "Helmet +1", "Helmet +2", "Helmet +3",                    // Helmet
                                            "Mage hat", "Mage hat +1", "Mage hat +2", "Mage hat  +3",
                                            "Bone amulet", "Celtic amulet", "Stone amulet", "Crystal amulet",                    // AMulet
                                            "Idol amulet", "Pentagram amulet",
                                            "Cloak", "Cloak +1", "Cloak +2", "Cloak +3",                    // Cloak
                                            "Boots", "Boots +1", "Boots +2", "Boots +3",                    // Boots
                                            "Staff", "Staff +1", "Staff +2", "Staff +3",                    // Staff
                                            "Staff +4", "Staff +5",
                                            "Initiate wand", "Apprentice wand", "Adept wand", "Master wand",                    // Wand
                                            "Grandmaster wand",
                                            "Bronze ring", "Iron ring", "Silver ring", "Golden ring",                    // Ring
                                            "Jewel ring", "Pearl ring", "Emerald ring", "Opal ring",
                                            "Initiate book", "Apprentice book", "Adept book", "Master book", "Grandmaster book",
                                            "Book of Power",
                                            "Book of Personality",
                                            "Book of Intelligence",
                                            "Book of Toughness",
                                            "Book of Technique",
                                            "Book of Quickness",
                                            "Book of Perception",
                                            "Book of Fitness",                    // Book Scroll
                                            "Book of Lore",
                                            "Book of Persuasion",
                                            "Book of Taming",
                                            "Book of Quickhand",
                                            "Book of Stealth", "Book of Awareness",
                                            "Book of Fire Element",
                                            "Book of Air Element",
                                            "Book of Water Element",
                                            "Book of Earth Element",
                                            "Book of Energy Element",
                                            "Book of Mental Element",
                                            "Book of Soul Element",
                                            "Potion of Healing", "Potion of Healing +1", "Potion of Healing +2", "Potion of Healing +3",                    // Potion
                                            "Potion of Cure Poison", "Potion of Cure Flaming", "Potion of Cure Paralysis", "Potion of Cure Fear",
                                            "Potion of cure Insanity", "Potion of cure Exhaustion", "Potion of cure Curse", "Potion of Poison",
                                            "Torch",                                                                     // Misc
                                            };

    std::vector<std::string> v_ItemNamesShop;

    std::vector<std::string> v_SkillNames = {"Short blade","Long blade","Bow","Bludgeon","Short axe","Long axe","Poleblade","Pole","Shield",
                                            "Leather armor","Chained armor","Scaled armor", "Plated armor","Fitness","Lore","Persuasion",
                                            "Taming","Quickhand","Stealth","Awareness"};

    std::vector<Item> v_Item;
    std::vector<SkillObject> v_Skill;
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
    std::vector<std::string> generalStoreItems;
    std::vector<std::string> jewelleryStoreItems;
    std::vector<std::string> silverStoreItems;
    std::vector<std::string> armsAndArmours;

    std::array<int, 300> armsAndArmoursValue;
    std::vector<SGenericItem> generalShopItems;
    std::vector<SGenericItem> jewelleryShopItems;
    std::vector<SGenericItem> silverShopItems;
    std::vector<SGenericItem> armsAndArmoursShopItems;

    map<string, SDL_Texture*> myTextures;
    weather_engine cweather_engine;

    portal mapPortal[16][16];
    portal savePortal[16][16];

    void initPortal(std::string _dataFilePath)
    {
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

        initPortal("./data/maps/phlan/phlan_portals");
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
                PlayerCoordinate.x = mapPortal[x][y].getX();
        }
        return mapPortal[x][y].active_portal(rotation);
    };

    void read_directory(const std::string& name, std::vector<string>& v)
    {
        DIR* dirp = opendir(name.c_str());
        struct dirent * dp;
        while ((dp = readdir(dirp)) != NULL) {
            v.push_back(dp->d_name);
        }
        closedir(dirp);
    }

    std::vector<std::string> imagesFiles;

    SDL_Rect CurrentLocation{0,0,128,128};
private:
	// the stack of states
	vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;
};



#endif
