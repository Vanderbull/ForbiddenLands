
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

//#include "SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>

#include <vector>
#include <sys/utsname.h>
using namespace std;

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

	SDL_Surface* screen;
    SDL_Window * window;
    SDL_DisplayMode monitor[6];
    SDL_DisplayMode current;
    SDL_Surface* gSurface;
    struct utsname uts;
    	SDL_Renderer * renderer;
	SDL_Renderer * renderer2;

	int SettingsMenu = 0;
    int activeView = 0;
    int LoadMenu = 0;
    int SaveMenu = 0;
    int CreateCharacter = 0;

private:
	// the stack of states
	vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;
};

#endif
