#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "createcharacterstate.h"
#include "loadmenustate.h"
#include "savemenustate.h"
#include "menustate.h"
#include "gameoverstate.h"

CGameoverState CGameoverState::m_GameoverState;

void CGameoverState::Init()
{
	SDL_Log("CGameoverState Init\n");
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
						game->ChangeState(CMenuState::Instance());
						break;
				} break;
		}
	}
}

void CGameoverState::Update(CGameEngine* game)
{
    SDL_Log("CGameoverState Update\n");

    game->SActor.PlayerCoordinate = {15,1,0};
    game->SActor.PlayerLastCoordinate = {15,1,0};
    game->SActor.hitpoints_current = 10;
    game->SActor.hitpoints_max = 10;
    game->number_of_enemies = 1;
    game->SActor.PlayerCoordinate.z = game->WEST;

std::random_device rd;


            int z = 0;
        for(int x = 0; x < 16; x++)
            for(int y = 0; y < 16; y++)
            {
                game->random_events[x][y][z] = rd();//dice();
            }
}

void CGameoverState::Draw(CGameEngine* game)
{
    SDL_Log("CGameoverState Draw\n");

    SDL_RenderCopy(game->renderer, game->gameoverState, NULL, NULL);
}
