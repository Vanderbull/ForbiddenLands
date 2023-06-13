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
#include "worldmapstate.h"
#include "lootstate.h"

//std::random_device rd;

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
    std::random_device rd;

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
					{
                        looting = true;
						game->ChangeState(CWorldMapState::Instance());
						game->SActor.compassNeedle = game->SActor.NORTH;
                        for(int x = 0; x < 16; x++)
                            for(int y = 0; y < 16; y++)
                            {
                                game->random_events[x][y][0] = rd();
                                game->fog_of_war_raiding[x][y][0] = 0;
                            }
                        game->SActor.PlayerCoordinate = {15,1,0};
                        game->SActor.PlayerLastCoordinate = {15,1,0};
                        game->SActor.hitpoints_current = 10;
                        game->SActor.hitpoints_max = 10;
                        game->number_of_enemies = 1;
						game->ChangeState(CMenuState::Instance());
					}break;
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
    game->number_of_enemies = rand()%3;
    game->SActor.PlayerCoordinate.z = game->WEST;

    if( looting )
    {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 9);

        game->hides += dist(rd);
        game->slaves += dist(rd);
        game->gold += dist(rd);
        game->silver += dist(rd);
        looting = false;

        game->Raiding_Party.old -= rand()%game->number_of_enemies;
        if( game->Raiding_Party.old < 0)
            game->Raiding_Party.old = 0;
        game->Raiding_Party.middleage -= rand()%game->number_of_enemies;
        if( game->Raiding_Party.middleage < 0)
            game->Raiding_Party.middleage = 0;
        game->Raiding_Party.young -= rand()%game->number_of_enemies;
        if( game->Raiding_Party.young < 0)
            game->Raiding_Party.young = 0;
        game->SActor.thirst -= random()%10;
        if(game->SActor.thirst < 0)
        game->SActor.thirst = 0;
        game->SActor.hunger -= random()%10;
        if(game->SActor.hunger < 0)
        game->SActor.hunger = 0;
        game->Quests.completeQuest("Raid");
    }
}

void CLootState::Draw(CGameEngine* game)
{
    SDL_Log("CLootState Draw\n");

    game->RenderText("hides: " + std::to_string(game->hides), game->White, 0,0,24);
    game->RenderText("slaves: " + std::to_string(game->slaves), game->White, 0,32,24);
    game->RenderText("gold: " + std::to_string(game->gold), game->White, 0,64,24);
    game->RenderText("silver: " + std::to_string(game->silver), game->White, 0,96,24);

    game->RenderText("Old: " + std::to_string(game->Raiding_Party.old),game->White,80,gRect.y +  120,24);
    game->RenderText("Middleaage: " + std::to_string(game->Raiding_Party.middleage),game->White,80,gRect.y +  160,24);
    game->RenderText("Young: " + std::to_string(game->Raiding_Party.young),game->White,80,game->gRect.y +  200,24);

    game->RenderTextWrapped("SPOILS OF WAR", game->White, game->current.w / 3 + 200,game->current.h / 3,24,1520);

    Item randomized("SCRAP");
    game->v_InventoryItem.at(9) = randomized;
}
