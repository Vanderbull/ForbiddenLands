#ifndef WORLDMAPSTATE_H
#define WORLDMAPSTATE_H

#include <SDL2/SDL.h>
#include "gamestate.h"

class CWorldMapState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CWorldMapState* Instance() {
		return &m_WorldMapState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

protected:
	CWorldMapState() { }

private:
	static CWorldMapState m_WorldMapState;
	int map[20][25];

    SDL_Color White = {255, 255, 255, 255};

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
};

#endif
