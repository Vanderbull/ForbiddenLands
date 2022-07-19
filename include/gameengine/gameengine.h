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
using namespace std;

#include "globals.h"
#include "../version.h"
//#include "actor.h"

extern int testing;

class Skill {
public:

    std::string Name;
    int MaximumExpertise;
    int InitialRequirementsAttribute;
    int InitialRequirementsValue;
    int Group;
    int Advance;
    std::vector<std::string> UtilizedBy;
    std::string Description;

    Skill(void);
    Skill(std::string,char,int);
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

	int SettingsMenu = 0;
    int activeView = 0;
    int LoadMenu = 0;
    int SaveMenu = 0;
    int CreateCharacter = 0;

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
    SDL_Texture* swatTexture;
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

    // Skills
    int FitnessSkill = 0;
    int DwarvishSkill = 0;
    int LoreSkill = 0;
    int PersuationSKill = 0;
    int TamingSkill = 0;
    int QuickandSkill = 0;
    int StealthSkill = 0;
    int AwarenessSkill = 0;
    int ShortBladeSkill = 0;
    int LongBladeSkill = 0;
    int BowSkill = 0;
    int BludgeonSkill = 0;
    int ShortAxeSkill = 0;
    int LongAxeSkill = 0;
    int PoleBladeSkill = 0;
    int PoleSkill = 0;
    int ShieldSkill = 0;
    int LeatherArmourSkill = 0;
    int ChainedArmourSkill = 0;
    int ScaledArmourSkill = 0;
    int PlatedArmourSkill = 0;
    int FireMagicSkill = 0;
    int AirMagicSkill = 0;
    int WaterMagicSkill = 0;
    int EarthMagicSkill = 0;
    int EnergyMagicSkill = 0;
    int MentalMagicSkill = 0;
    int SoulMagicSkill = 0;

    std::vector<std::string> Skill = { "Fitness", "Dwarvish","Lore","Persuation","Taming","Quickand","Stealth","Awareness","ShortBlade",
                                    "LongBlade","Bow","Bludgeon","ShortAxe","LongAxe","PoleBlade","Pole","Shield","Leather armour",
                                    "Chained armour","Scaled armour","Plated armour","Fire magic","Air Magic","Water magic","Earth magic","Energy magic","Mental magic","Soul magic"};
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

    std::vector<std::string> WeaponItems = {"Bardiche", "Bardiche +1", "Bardiche +2", "Bardiche +3", "Battle Axe", "Battle Axe +1", "Battle Axe +2", "Battle Axe +3", "Bow", "Bow +1", "Bow +2", "Bow +3","Broad Axe",
                                            "Broad Axe +1","Broad Axe +2","Broad Axe +3","Club","Club +1","Club +2","Club +3", "Crossbow", "Cross bow +1","Cross bow +2","Cross bow +3","Dagger","Dagger +1","Dagger +2","Dagger +3",
                                            ""};
    std::vector<std::string> ArmorItems = {"Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3", "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor +3", "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3", "Robe", "Robe +1", "Robe +2", "Robe +3", "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3", ""};
    std::vector<std::string> ShieldItems = {"Buckler","Shield","Kite shield"};
    std::vector<std::string> GauntletItems = {"Gauntlets"};
    std::vector<std::string> HelmetItems = {"Helmet","Mage hat"};
    std::vector<std::string> AmuletItems = {"Bone amulet","Celtic amulet","Stone amulet","Crystal amulet","Idol amulet","Pentagram amulet"};
    std::vector<std::string> CloakItems = {"Cloak","Cloak +1"};
    std::vector<std::string> BootsItems = {"Boots","Boots +1"};
    std::vector<std::string> StaffItems = {"Staff","Staff +1"};
    std::vector<std::string> WandItems = {"Initiate wand","Apprentice wand"};
    std::vector<std::string> RingItems = {"Bronze ring","Iron ring"};
    std::vector<std::string> BookScrollItems = {"Initiate book","Apprentice book"};
    std::vector<std::string> PotionItems = {"Potion of Healing", "Potion of  Healing +1", "Potion of  Healing +2", "Potion of  Healing +3", "Potion of cure poison",
                                    "Potion of cure flaming", "Potion of cure paralysis", "Potion of cure fear", "Potion of cure insanity", "Potion of cure exhaustion", "Potion of cure curse", "Potion of poison"};
    std::vector<std::string> MiscItems = {"Torch"};

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
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // Shield
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // Gauntlets
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // Helmet
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // AMulet
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // Cloak
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // Boots
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // Staff
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // Wand
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Chainmail", "Chainmail +1", "Chainmail +2", "Chainmail +3",                    // Ring
                                            "Leather armor", "Leather armor +1", "Leather armor +2", "Leather armor  +3",
                                            "Plate mail", "Plate mail +1", "Plate mail +2", "Plate mail +3",
                                            "Ring mail", "Ring mail +1", "Ring mail +2", "Ring mail +3",
                                            "Robe", "Robe +1", "Robe +2", "Robe +3",
                                            "Scale mail", "Scale mail +1", "Scale mail +2", "Scale mail +3",
                                            "Book of Technique", "Book of Quickness", "Book of Perception", "Book of Fitness",                    // Book Scroll
                                            "Book of Lore", "Book of Persuasion", "Book of Taming", "Book of Quickhand",
                                            "Book of Stealth", "Book of Awareness", "Book of Fire Element", "Book of Air Element",
                                            "Book of Water Element", "Book of Earth Element", "Book of Energy Element", "Book of Mental Element",
                                            "Book of Soul Element",
                                            "Potion of Healing", "Potion of Healing +1", "Potion of Healing +2", "Potion of Healing +3",                    // Potion
                                            "Potion of Cure Poison", "Potion of Cure Flaming", "Potion of Cure Paralysis", "Potion of Cure Fear",
                                            "Potion of cure Insanity", "Potion of cure Exhaustion", "Potion of cure Curse", "Potion of Poison",
                                            "Torch",                                                                     // Misc
                                            };
    std::vector<Item> v_Item;
	void AddItem();


private:
	// the stack of states
	vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;
};

#endif
