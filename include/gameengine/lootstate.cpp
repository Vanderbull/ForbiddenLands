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
#include "villagestate.h"
#include "lootstate.h"

CLootState CLootState::m_LootState;

void CLootState::Init()
{
	SDL_Log("CLootState Init\n");
}

void CLootState::Cleanup()
{
	SDL_Log("CLootState Cleanup\n");
}

void CLootState::Pause()
{
	SDL_Log("CLootState Pause\n");
}

void CLootState::Resume()
{
	SDL_Log("CLootState Resume\n");
}

void CLootState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CLootState HandleEvents\n");

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
						game->ChangeState(CVillageState::Instance());
						break;
				} break;
		}
	}
}

void CLootState::Update(CGameEngine* game)
{
    SDL_Log("CLootState Update\n");

    game->SActor.PlayerCoordinate = {15,1,0};
    game->SActor.PlayerLastCoordinate = {15,1,0};
    game->SActor.hitpoints_current = 10;
    game->SActor.hitpoints_max = 10;
    game->number_of_enemies = 1;

std::random_device rd;


            int z = 0;
        for(int x = 0; x < 16; x++)
            for(int y = 0; y < 16; y++)
            {
                game->random_events[x][y][z] = rd();//dice();
            }
}

void CLootState::Draw(CGameEngine* game)
{
    SDL_Log("CLootState Draw\n");

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);
    game->RenderTextWrapped("LOOT LOOT LOOT", game->Black, game->current.w / 3 + 200,game->current.h / 3,24,1520);
}
