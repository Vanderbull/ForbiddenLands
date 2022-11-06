#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>
#include "gamestate.h"

class CCharacterState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CCharacterState* Instance() {
		return &m_CharacterState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

protected:
	CCharacterState() { }

private:
	static CCharacterState m_CharacterState;

	SDL_Surface* gSurface;
	SDL_Texture* gTexture;
	SDL_Rect gRect;
	int iX;
	int iY;
	SDL_Texture* MainMenuBackgroundTexture;
	SDL_Color White = {255, 255, 255, 255};
	SDL_Color Black = {0, 0, 0, 255};

    /// Information about the state of the mouse
    SDL_Point m_iCurrentCoord;
    SDL_Point m_iPreviousCoord;
    SDL_Point m_iWheelCoord;

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

    std::vector<std::string> MenuChoices;

// 	map<string, int> AbilityScore = {
//		{"POWER", 0},
//    	{"INTELLIGENCE", 0},
//    	{"PERSONALITY", 0},
//    	{"THOUGHNESS", 0},
//    	{"TECHNOLOGY", 0},
//    	{"QUICKNESS", 0},
//    	{"PERCEPTION", 0}
//  	};
//
//  	map<string, int> AbilityMod = {
//		{"POWER", 0},
//    	{"INTELLIGENCE", 0},
//    	{"PERSONALITY", 0},
//    	{"THOUGHNESS", 0},
//    	{"TECHNOLOGY", 0},
//    	{"QUICKNESS", 0},
//    	{"PERCEPTION", 0}
//  	};

  	SDL_Rect ExitButton{1846,10,64,64};
  	SDL_Rect ExitButton2{2467,13,80,80};

};

#endif
