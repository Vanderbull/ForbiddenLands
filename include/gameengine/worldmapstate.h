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

    // Sweden
    SDL_Rect Kustenstad{0,0,128,128};
    SDL_Rect Vallentuna{256,0,128,128};
    SDL_Rect Mora{512,0,128,128};
    //Danmark
    SDL_Rect Marlmo{0,256,128,128};
    SDL_Rect Saeby{256,256,128,128};
    SDL_Rect Odense{512,256,128,128};
    SDL_Rect Zealfort{768,256,128,128};
    //Norway
    SDL_Rect Trollheim{0,512,128,128};
    SDL_Rect Trondeland{256,512,128,128};
    SDL_Rect Aerendal{512,512,128,128};
    //Finland
    SDL_Rect Kiiri{0,768,128,128};
    SDL_Rect Kamilarvi{256,768,128,128};
    SDL_Rect Muoni{512,768,128,128};

    SDL_Rect water_x_rect = { 0,0, 1920, 1080 };
    SDL_Rect water_x_rect2 = { -1919,0, 1920, 1080 };

    SDL_Rect water_y_rect = { 0,0, 1920, 1080 };
    SDL_Rect water_y_rect2 = { 0,-1079, 1920, 1080 };

    SDL_Rect Point_Of_Interest[10];
};

#endif
