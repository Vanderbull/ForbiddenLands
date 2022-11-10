#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "playstate.h"
#include "battlestate.h"

using namespace std::chrono;

CBattleState CBattleState::m_BattleState;

void CBattleState::Init()
{
    SDL_Log("CBattleState Init\n");
}

void CBattleState::Cleanup()
{
	SDL_Log("CBattleState Pause\n");
}

void CBattleState::Pause()
{
	SDL_Log("CBattleState Pause\n");
}

void CBattleState::Resume()
{
	SDL_Log("CBattleState Resume\n");
}

void CBattleState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CBattleState HandleEvents\n");
	SDL_Event event;

	if (SDL_PollEvent(&event))
    {
		switch (event.type)
		{
			case SDL_QUIT:
				game->Quit();
				break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        game->ChangeState(CMenuState::Instance());
                        break;
                } break;
		}
	}
}

void CBattleState::Update(CGameEngine* game)
{
    SDL_Log("CBattleState Update\n");
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

void CBattleState::Draw(CGameEngine* game)
{
    SDL_Log("CBattleState Draw");
    SDL_SetRenderDrawColor( game->renderer, 0, 0, 0, 255 );
    SDL_RenderClear(game->renderer);

    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    SDL_Rect buttonPosition = { 0, (0.33*game->current.h) / 2,256,0.66*game->current.h};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);

        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            game->SNpc.hitpoints_current--;

        }
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = game->current.w - 256;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            game->SActor.hitpoints_current--;
        }
    }
    game->RenderText("NPC HP: " + std::to_string(game->SNpc.hitpoints_current) + " / " + std::to_string(game->SNpc.hitpoints_max), White, game->current.w - 200,50,24);
    game->RenderText("PC HP: " + std::to_string(game->SActor.hitpoints_current) + " / " + std::to_string(game->SActor.hitpoints_max), White, game->current.w - 200,100,24);
}
