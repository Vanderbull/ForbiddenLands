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

    SDL_Rect InRect(SDL_Point inPoint, SDL_Rect inRect, CGameEngine* game, std::string inText)
    {
        if( SDL_PointInRect(&inPoint, &inRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(game->renderer, &inRect);
            game->RenderText(inText.c_str(), game->Black, inRect.x, inRect.y,48);

            if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
            {
                game->CurrentLocation = inRect;
                return inRect;
            }
        }
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
};

#endif
