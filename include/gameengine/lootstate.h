#ifndef LOOTSTATE_H
#define LOOTSTATE_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>
#include "gamestate.h"

class CLootState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CLootState* Instance() {
		return &m_LootState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

    SDL_Point mousePosition;

protected:
	CLootState() { }

private:
	static CLootState m_LootState;

	SDL_Surface* gSurface;
	SDL_Texture* gTexture;
	SDL_Rect gRect;
	int iX;
	int iY;
	SDL_Texture* MainMenuBackgroundTexture;
	SDL_Color White = {255, 255, 255, 255};
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
};

#endif
