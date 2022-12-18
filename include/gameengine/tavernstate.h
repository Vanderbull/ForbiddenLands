#ifndef TAVERNSTATE_H
#define TAVERNSTATE_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>
#include "gamestate.h"

class CTavernState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CTavernState* Instance() {
		return &m_TavernState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

    SDL_Point mousePosition;

protected:
	CTavernState() { }

private:
	static CTavernState m_TavernState;

	SDL_Color White = {255, 255, 255, 255};
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

    bool m_PlayerActive = true;
    bool m_PlayerDefending = false;
};

#endif
