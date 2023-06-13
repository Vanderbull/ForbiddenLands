#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "menustate.h"
#include "battlestate.h"
#include "characterstate.h"
#include "shopstate.h"
#include "encampmentstate.h"
#include "worldmapstate.h"
#include "inventorystate.h"
#include "tavernstate.h"
#include "queststate.h"

CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
    LoadMapExits();
	SDL_Log("CPlayState Init\n");
}

void CPlayState::Cleanup()
{
	SDL_Log("CPlayState Cleanup\n");
}

void CPlayState::Pause()
{
	SDL_Log("CPlayState Pause\n");
}

void CPlayState::Resume()
{
	SDL_Log("CPlayState Resume\n");
}

void CPlayState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CPlayState HandleEvents\n");

    game->SActor.PlayerLastCoordinate = game->SActor.PlayerCoordinate;

	SDL_Event event;

	while (SDL_PollEvent(&event)!= 0)
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
						game->ChangeState( CMenuState::Instance() );
						break;
                    case SDLK_TAB:
                        game->ChangeState( CCharacterState::Instance() );
                        break;
                    case SDLK_r:
                        game->ChangeState( CEncampmentState::Instance() );
                        break;
                    case SDLK_m:
                        game->ChangeState( CWorldMapState::Instance() );
                        break;
                    case SDLK_b:
                        game->ChangeState( CBattleState::Instance() );
                        break;
                    case SDLK_q:
                        game->ChangeState( CQuestState::Instance() );
                        break;
                    case SDLK_d:
                        rotateClockWise(game);
                        break;
                    case SDLK_a:
                        rotateCounterClockWise(game);
                        break;
                    case SDLK_w:
                        {
                            if( game->SActor.compassNeedle == game->SActor.NORTH)
                            {
                                if( game->SActor.PlayerCoordinate.y > 0 )
                                {
                                    if( mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::NORTH] == 1 )
                                        game->SActor.PlayerCoordinate.y--;
                                    //game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][game->SActor.PlayerCoordinate.z] = 1;
                                    //game->gameTime.tm_min++;
                                }
                            }
                            else if( game->SActor.compassNeedle == game->SActor.SOUTH)
                            {
                                if( game->SActor.PlayerCoordinate.y < 15 )
                                {
                                    if( mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::SOUTH] == 1 )
                                        game->SActor.PlayerCoordinate.y++;
                                    //game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][game->SActor.PlayerCoordinate.z] = 1;
                                    //game->gameTime.tm_min++;
                                }
                            }
                            else if( game->SActor.compassNeedle == game->SActor.WEST)
                            {
                                if( game->SActor.PlayerCoordinate.x > 0 )
                                {
                                    if( mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::WEST] == 1 )
                                        game->SActor.PlayerCoordinate.x--;
                                    //game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][game->SActor.PlayerCoordinate.z] = 1;
                                    //game->gameTime.tm_min++;
                                }
                            }
                            else if( game->SActor.compassNeedle == game->SActor.EAST)
                            {
                                if( game->SActor.PlayerCoordinate.x < 15 )
                                {
                                    if( mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::EAST] == 1 )
                                        game->SActor.PlayerCoordinate.x++;
                                    //game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][game->SActor.PlayerCoordinate.z] = 1;
                                    //game->gameTime.tm_min++;
                                }
                            }
                        } break;
                    case SDLK_s:
                        {
                            if( game->SActor.compassNeedle == game->SActor.NORTH)
                            {
                                if( game->SActor.PlayerCoordinate.y > 0 )
                                    game->SActor.PlayerCoordinate.y++;
                            } break;
                            if( game->SActor.compassNeedle == game->SActor.SOUTH)
                            {
                                if( game->SActor.PlayerCoordinate.y < 15 )
                                    game->SActor.PlayerCoordinate.y--;
                            } break;
                            if( game->SActor.compassNeedle == game->SActor.WEST)
                            {
                                if( game->SActor.PlayerCoordinate.x > 0 )
                                    game->SActor.PlayerCoordinate.x++;
                            } break;
                            if( game->SActor.compassNeedle == game->SActor.EAST)
                            {
                                if( game->SActor.PlayerCoordinate.x < 15 )
                                    game->SActor.PlayerCoordinate.x--;
                            } break;
                        } break;
				} break;
		}
	}
}

void CPlayState::Update(CGameEngine* game)
{
    std::random_device rd;
    SDL_Log("CPlayState Update\n");

    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][0] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][1] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][2] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][3] = 1;

    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x-1][game->SActor.PlayerCoordinate.y][0] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x-1][game->SActor.PlayerCoordinate.y][1] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x-1][game->SActor.PlayerCoordinate.y][2] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x-1][game->SActor.PlayerCoordinate.y][3] = 1;

    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x+1][game->SActor.PlayerCoordinate.y][0] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x+1][game->SActor.PlayerCoordinate.y][1] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x+1][game->SActor.PlayerCoordinate.y][2] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x+1][game->SActor.PlayerCoordinate.y][3] = 1;

    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y-1][0] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y-1][1] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y-1][2] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y-1][3] = 1;

    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y+1][0] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y+1][1] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y+1][2] = 1;
    game->fog_of_war_raiding[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y+1][3] = 1;

    if( game->number_of_enemies <= 0 )
    {
        game->number_of_enemies = 1;
        game->ChangeState( CWorldMapState::Instance() );
    }

    if( game->newGame )
    {
        game->SActor.calculateStats();
        game->newGame = false;
    }

    if( game->random_events[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][0] <= ( rd.max() / 4) )
    {
        game->random_events[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][0] = rd.max();
        game->ChangeState( CBattleState::Instance() );
    }

    std::string coordinates_modified = "";
    if(game->SActor.PlayerCoordinate.x < 10)
    {
        coordinates_modified += "0";
    }

    coordinates_modified += std::to_string(game->SActor.PlayerCoordinate.x);

    if(game->SActor.PlayerCoordinate.y < 10)
    {
        coordinates_modified += "0";
    }

    coordinates_modified += std::to_string(game->SActor.PlayerCoordinate.y);

    std::string east = "./assets/data/textures/test_map/" + coordinates_modified + "E" + "-fs8.png";
    std::string west = "./assets/data/textures/test_map/" + coordinates_modified + "W" + "-fs8.png";
    std::string north = "./assets/data/textures/test_map/" + coordinates_modified + "N" + "-fs8.png";
    std::string south = "./assets/data/textures/test_map/" + coordinates_modified + "S" + "-fs8.png";

    SDL_DestroyTexture(game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][0]);
    SDL_DestroyTexture(game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][1]);
    SDL_DestroyTexture(game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][2]);
    SDL_DestroyTexture(game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][3]);

    //if( game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][0] == NULL)
    game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][0] = IMG_LoadTexture(game->renderer,east.c_str());
    //if( game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][1] == NULL)
    game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][1] = IMG_LoadTexture(game->renderer,west.c_str());
    //if( game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][2] == NULL)
    game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][2] = IMG_LoadTexture(game->renderer,north.c_str());
    //if( game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][3] == NULL)
    game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][3] = IMG_LoadTexture(game->renderer,south.c_str());
}

void CPlayState::Draw(CGameEngine* game)
{
    int texW = 0;
    int texH = 0;
    std::random_device rd;

    SDL_Log("CPlayState Draw\n");

    SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_NONE);

    SDL_RenderCopyEx(game->renderer, game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][game->SActor.PlayerCoordinate.z], NULL, NULL, 0, NULL, flip);

    game->RenderText("number of enemies: " + std::to_string(game->number_of_enemies), White, 0, 0,24);

    game->RenderText("Hunger: " + std::to_string(game->SActor.hunger),game->White,80,gRect.y +  40,24);
    game->RenderText("Thirst: " + std::to_string(game->SActor.thirst),game->White,80,gRect.y +  80,24);

    game->RenderText("Young: " + std::to_string(game->Raiding_Party.young),White,game->current.w - 300,gRect.y +  50,24);
    game->RenderText("Middle aged: " + std::to_string(game->Raiding_Party.middleage),White,game->current.w - 300,gRect.y +  100,24);
    game->RenderText("Old: " + std::to_string(game->Raiding_Party.old),White,game->current.w - 300,gRect.y +  150,24);

    renderDaytime(game);
    renderCompass(game);
    renderMinimap(game);
    renderMinimapCharacterLocation(game);
    renderPassable(game);

    //static int goblinmovey = 0;
    if( (game->SActor.PlayerCoordinate.z == game->SActor.WEST ) && game->random_events[game->SActor.PlayerCoordinate.x-1][game->SActor.PlayerCoordinate.y][0] <= rd.max() / 2)
    {
        SDL_Texture* goblin = game->LoadTexture("./assets/data/textures/viking.png",255);
        texW = 0;
        texH = 0;
        SDL_QueryTexture(goblin, NULL, NULL, &texW, &texH);

        gRect = { game->current.w / 2 - texW/2,game->current.h / 2 + texH*2, texW, texH };
        SDL_RenderCopy(game->renderer, goblin, NULL, &gRect);
    }
    if( (game->SActor.PlayerCoordinate.z == game->SActor.EAST ) && game->random_events[game->SActor.PlayerCoordinate.x+1][game->SActor.PlayerCoordinate.y][0] <=  rd.max() / 2)
    {
        SDL_Texture* goblin = game->LoadTexture("./assets/data/textures/viking.png",255);
        texW = 0;
        texH = 0;
        SDL_QueryTexture(goblin, NULL, NULL, &texW, &texH);

        gRect = { game->current.w / 2 - texW/2,game->current.h / 2 + texH*2, texW, texH };
        SDL_RenderCopy(game->renderer, goblin, NULL, &gRect);
    }
    if( (game->SActor.PlayerCoordinate.z == game->SActor.SOUTH ) && game->random_events[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y+1][0] <=  rd.max() / 2)
    {
        SDL_Texture* goblin = game->LoadTexture("./assets/data/textures/viking.png",255);
        texW = 0;
        texH = 0;
        SDL_QueryTexture(goblin, NULL, NULL, &texW, &texH);

        gRect = { game->current.w / 2 - texW/2,game->current.h / 2 + texH*2, texW, texH };
        SDL_RenderCopy(game->renderer, goblin, NULL, &gRect);
    }
    if( (game->SActor.PlayerCoordinate.z == game->SActor.NORTH ) && game->random_events[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y-1][0] <=  rd.max() / 2)
    {
        SDL_Texture* goblin = game->LoadTexture("./assets/data/textures/viking.png",255);
        texW = 0;
        texH = 0;
        SDL_QueryTexture(goblin, NULL, NULL, &texW, &texH);

        gRect = { game->current.w / 2 - texW/2,game->current.h / 2 + texH*2, texW, texH };
        SDL_RenderCopy(game->renderer, goblin, NULL, &gRect);
    }

    game->renderQuestsList();
    game->Quests.completeQuest("Retrieve the stolen artifact");

//    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
//
//    if( SDL_PointInRect(&mousePosition, &left_weapon) & SDL_BUTTON(SDL_BUTTON_LEFT) )
//    {
//        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
//        SDL_RenderFillRect(game->renderer, &left_weapon);
//
//        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
//        {
//        }
//    }
//    if( SDL_PointInRect(&mousePosition, &right_weapon) & SDL_BUTTON(SDL_BUTTON_LEFT) )
//    {
//        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
//        SDL_RenderFillRect(game->renderer, &right_weapon);
//
//        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
//        {
//        }
//    }

    game->RenderText("HP: " + std::to_string(game->SActor.hitpoints_current) + " / " + std::to_string(game->SActor.hitpoints_max), White, game->current.w - 200,50,24);
}
