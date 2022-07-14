#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>
#include "gamestate.h"

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CPlayState* Instance() {
		return &m_PlayState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

    void getCompassDirection()
    {
        std::cout << compassDirection.at(compassNeedle) << std::endl;
        Rotation = compassDirection.at(compassNeedle);
    };

    void rotateCounterClockWise()
    {
        if( compassNeedle == 0 )
            compassNeedle = compassDirection.size()-1;
        else
            compassNeedle--;
    };

    void rotateClockWise()
    {
        if( compassNeedle == compassDirection.size()-1 )
            compassNeedle = 0;
        else
            compassNeedle++;
    };

protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;

	SDL_Surface* playerCoordinateSurface;
	SDL_Texture* playerCoordinateTexture;
    TTF_Font* m_font = NULL;

	SDL_Surface* gSurface;
	SDL_Texture* gTexture;
	SDL_Rect gRect;
	int iX;
	int iY;
	SDL_Texture* MainMenuBackgroundTexture;
	SDL_Color White = {255, 255, 255, 255};
	SDL_Color Black = {0, 0, 0, 255};
	TTF_Font* gameTitleFont = NULL;
    std::vector<std::string> MenuChoices;

    /// Information about the state of the mouse
    int m_iCurrentCoordX;
    int m_iCurrentCoordY;
    Uint32 m_uCurrentMouseState;

    int m_iPreviousCoordX;
    int m_iPreviousCoordY;
    Uint32 m_uPreviousMouseState;

    ///information about the state of thw wheel
    Sint32 m_iWheelX;
    Sint32 m_iWheelY;

//    int SettingsMenu = 0;
//    int activeView = 1;
//    int LoadMenu = 0;
//    int SaveMenu = 0;
//    int CreateCharacter = 0;
//    int quit = 0;

    int Repeat = 0;
    int buttonWidth = 600;
    int buttonHeight = 60;

    std::string compassDirection = "NESW";
    int compassNeedle = 0;
    std::string Rotation = "W";
    int z = 0;
    enum {EAST,WEST,NORTH,SOUTH};

};

#endif
