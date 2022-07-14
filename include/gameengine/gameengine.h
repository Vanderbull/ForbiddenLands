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

private:
	// the stack of states
	vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;
};

#endif
