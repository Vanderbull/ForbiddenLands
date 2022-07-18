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

#include "../version.h"
//#include "actor.h"

extern int testing;

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

    std::vector<std::string> Skill = { "Fitness", "Dwarvish","Lore","Persuation","Taming","Quickand","Stealth","Awareness","ShortBlade","LongBlade","Bow","Bludgeon","ShortAxe","LongAxe","PoleBlade","Pole","Shield","Leather armour","Chained armour","Scaled armour","Plated armour"};

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

private:
	// the stack of states
	vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;
};

#endif
