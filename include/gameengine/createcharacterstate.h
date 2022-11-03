#ifndef CREATECHARACTERSTATE_H
#define CREATECHARACTERSTATE_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>
#include "gamestate.h"

class CCreateCharacterState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CCreateCharacterState* Instance() {
		return &m_CreateCharacterState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

protected:
	CCreateCharacterState() { }

private:
	static CCreateCharacterState m_CreateCharacterState;

	string input;

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

    int Repeat = 0;
    int buttonWidth = 600;
    int buttonHeight = 60;

    std::vector<std::string> abilityElements = { "POW ", "INT ", "PERS ", "TOU ", "TECH ", "QUI ", "PERC "};
    std::vector<std::string> abilityModElements = { "POW MOD", "INT MOD", "PERS MOD", "TOU MOD", "TECH MOD", "QUI MOD", "PERC MOD"};
    std::vector<std::string> professionTextElements = { "Viking", "Marauder","Wizard"};

    int    scrolling;               // flag (scrolling or not)
    int    scroll_sensitivity = 40; // how fast we want to scroll
    double scroll_Y = 0;            // current scrolling amount (on Y-Axis)
    double scroll_acceleration;     // scrolling speed
    double scroll_friction = 0.001; // how fast we decelerate
    double scroll_prev_pos;         // previous event's position

    int scroll_range_min = 0;
    int scroll_range_max = scroll_range_min + 10;
};

#endif
