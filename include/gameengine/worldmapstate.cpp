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

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    if( SDL_PointInRect(&mousePosition, &Kustenstad) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 128);
        SDL_RenderFillRect(game->renderer, &Kustenstad);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            game->SActor.worldMap = 0;
        }
    }
    else
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(game->renderer, &Kustenstad);
    }

    if( SDL_PointInRect(&mousePosition, &Vallentuna) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 128);
        SDL_RenderFillRect(game->renderer, &Vallentuna);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            game->SActor.worldMap = 1;
        }
    }
    else
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(game->renderer, &Vallentuna);
    }

    if( SDL_PointInRect(&mousePosition, &Mora) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 128);
        SDL_RenderFillRect(game->renderer, &Mora);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            game->SActor.worldMap = 2;
        }
    }
    else
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(game->renderer, &Mora);
    }

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 255);
    if( game->SActor.worldMap == 0)
        SDL_RenderFillRect(game->renderer, &Kustenstad);
    if( game->SActor.worldMap == 1)
        SDL_RenderFillRect(game->renderer, &Vallentuna);
    if( game->SActor.worldMap == 2)
        SDL_RenderFillRect(game->renderer, &Mora);

	SDL_Texture* texture = game->LoadTexture("./assets/data/textures/sweden.png",255);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

    SDL_Rect gRect = { game->current.w/2,0, 300, 1080 };

    SDL_RenderCopy(game->renderer, texture, NULL, &gRect);
    SDL_DestroyTexture(texture);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

    for(int x = 0; x < game->current.w / 32; x++ )
    {
        for(int y = 0; y < game->current.h / 32; y++ )
        {
            SDL_Rect gRect = { x*32,y*32, 32, 32 };
            SDL_RenderDrawRect(game->renderer, &gRect);
        }
    }
    //game->renderWorldMapTiles();
}
