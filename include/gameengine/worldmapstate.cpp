#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>

#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "playstate.h"
#include "worldmapstate.h"

CWorldMapState CWorldMapState::m_WorldMapState;

void CWorldMapState::Init()
{
	SDL_Log("CWorldMapState Init\n");
}

void CWorldMapState::Cleanup()
{
	SDL_Log("CWorldMapState Cleanup\n");
}

void CWorldMapState::Pause()
{
	SDL_Log("CWorldMapState Pause\n");
}

void CWorldMapState::Resume()
{
	SDL_Log("CWorldMapState Resume\n");
}

void CWorldMapState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CWorldMapState");
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
                        game->ChangeState( CPlayState::Instance() );
						break;
				}
				break;
		}
	}
}

void CWorldMapState::Update(CGameEngine* game)
{
    SDL_Log("CWorldMapState Update");
    ///--- Store the current information to the previous
    m_iPreviousCoordX=m_iCurrentCoordX;
    m_iPreviousCoordY=m_iCurrentCoordY;
    m_uPreviousMouseState=m_uCurrentMouseState;

    ///--- Update the current state of the mouse
    m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

    ///--- Set the wheel back to 0
    m_iWheelX=0;
    m_iWheelY=0;
}

void CWorldMapState::Draw(CGameEngine* game)
{
    SDL_Log("CWorldMapState Draw");
    SDL_SetRenderDrawColor( game->renderer, 0, 0, 0, 255 );

    SDL_RenderClear(game->renderer);

    SDL_SetRenderDrawColor(game->renderer, 0, 255, 255, 128);

    //Danmark
    SDL_RenderFillRect(game->renderer, &Marlmo);
    SDL_RenderFillRect(game->renderer, &Saeby);
    SDL_RenderFillRect(game->renderer, &Odense);
    SDL_RenderFillRect(game->renderer, &Zealfort);
    //Norway
    SDL_RenderFillRect(game->renderer, &Trollheim);
    SDL_RenderFillRect(game->renderer, &Trondeland);
    SDL_RenderFillRect(game->renderer, &Aerendal);
    //Finland
    SDL_RenderFillRect(game->renderer, &Kiiri);
    SDL_RenderFillRect(game->renderer, &Kamilarvi);
    SDL_RenderFillRect(game->renderer, &Muoni);

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    if( SDL_PointInRect(&mousePosition, &Kustenstad) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 128);

        // Sweden
        SDL_RenderFillRect(game->renderer, &Kustenstad);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
        }
    }
    else
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);

        // Sweden
        SDL_RenderFillRect(game->renderer, &Kustenstad);
    }

    if( SDL_PointInRect(&mousePosition, &Vallentuna) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 128);

        // Sweden
        SDL_RenderFillRect(game->renderer, &Vallentuna);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
        }
    }
    else
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);

        // Sweden
        SDL_RenderFillRect(game->renderer, &Vallentuna);
    }

    if( SDL_PointInRect(&mousePosition, &Mora) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 128);

        // Sweden
        SDL_RenderFillRect(game->renderer, &Mora);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
        }
    }
    else
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);

        // Sweden
        SDL_RenderFillRect(game->renderer, &Mora);
    }
}
