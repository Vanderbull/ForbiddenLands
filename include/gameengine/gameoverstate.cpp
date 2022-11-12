#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "createcharacterstate.h"
#include "loadmenustate.h"
#include "savemenustate.h"
#include "gameoverstate.h"

CGameoverState CGameoverState::m_GameoverState;

void CGameoverState::Init()
{
	SDL_Log("CGameoverState Init\n");

    MenuChoices.clear();
    MenuChoices.push_back("BREAK UP CAMP");
}

void CGameoverState::Cleanup()
{
	SDL_Log("CGameoverState Cleanup\n");
}

void CGameoverState::Pause()
{
	SDL_Log("CGameoverState Pause\n");
}

void CGameoverState::Resume()
{
	SDL_Log("CGameoverState Resume\n");
}

void CGameoverState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CGameoverState HandleEvents\n");

	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
            case SDL_MOUSEMOTION:
            {
                SDL_GetMouseState( &mousePosition.x, &mousePosition.y );
            } break;
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						game->PopState();
						break;
				} break;
		}
	}
}

void CGameoverState::Update(CGameEngine* game)
{
    SDL_Log("CGameoverState Update\n");

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

void CGameoverState::Draw(CGameEngine* game)
{
    SDL_Log("CGameoverState Draw\n");

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);
}
