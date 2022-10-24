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

CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
    loadPortals();
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
					case SDLK_1:
                        game->ChangeState( CShopState::Instance() );
						break;
                    case SDLK_m:
                        game->ChangeState( CWorldMapState::Instance() );
                        break;
                    case SDLK_b:
                        game->ChangeState( CBattleState::Instance() );
                        break;
                    case SDLK_d:
                        rotateClockWise();
                        break;
                    case SDLK_a:
                        rotateCounterClockWise();
                        break;
                    case SDLK_w:
                        {
                            if( Rotation == "N")
                            {
                                if( game->PlayerCoordinate.y > 0 )
                                {
                                    game->PlayerCoordinate.y--;
                                    //DateAndTime.tm_min++;
                                }
                            }
                            else if( Rotation == "S")
                            {
                                if( game->PlayerCoordinate.y < 15 )
                                {
                                    game->PlayerCoordinate.y++;
                                    //DateAndTime.tm_min++;
                                }
                            }
                            else if( Rotation == "W")
                            {
                                if( game->PlayerCoordinate.x > 0 )
                                {
                                    game->PlayerCoordinate.x--;
                                    //DateAndTime.tm_min++;
                                }
                            }
                            else if( Rotation == "E")
                            {
                                if( game->PlayerCoordinate.x < 15 )
                                {
                                    game->PlayerCoordinate.x++;
                                    //DateAndTime.tm_min++;
                                }
                            }
                        } break;
                    case SDLK_s:
                        {
                            if( Rotation == "N")
                            {
                                if( game->PlayerCoordinate.y > 0 )
                                    game->PlayerCoordinate.y++;
                            } break;
                            if( Rotation == "S")
                            {
                                if( game->PlayerCoordinate.y < 15 )
                                    game->PlayerCoordinate.y--;
                            } break;
                            if( Rotation == "W")
                            {
                                if( game->PlayerCoordinate.x > 0 )
                                    game->PlayerCoordinate.x++;
                            } break;
                            if( Rotation == "E")
                            {
                                if( game->PlayerCoordinate.x < 15 )
                                    game->PlayerCoordinate.x--;
                            } break;
                        } break;
				} break;
		}
	}
}

void CPlayState::Update(CGameEngine* game)
{
    SDL_Log("CPlayState Update\n");
    if( game->newGame )
    {
        game->SActor.calculateStats();
        game->newGame = false;
    }

    getCompassDirection();

    if(Rotation == "N")
        game->PlayerCoordinate.z = NORTH;
    if(Rotation == "S")
        game->PlayerCoordinate.z = SOUTH;
    if(Rotation == "W")
        game->PlayerCoordinate.z = WEST;
    if(Rotation == "E")
        game->PlayerCoordinate.z = EAST;
}

void CPlayState::Draw(CGameEngine* game)
{
    SDL_Log("CPlayState Draw\n");

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

    SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_NONE);//(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

    SDL_RenderCopyEx(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][game->PlayerCoordinate.z], NULL, NULL, 0, NULL, flip);
//    static int rotate = 0;
//    if( rotate >359)
//        rotate = 0;
//    SDL_RenderCopyEx(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][game->PlayerCoordinate.z], NULL, NULL,rotate,NULL,flip);
//    rotate++;
    int texW = 0;
    int texH = 0;

    renderDaytime(game);
    renderCompass(game);
    renderMinimap(game);
    renderMinimapCharacterLocation(game);

    static int goblinmovey = 0;
    SDL_Texture* goblin = game->LoadTexture("./images/goblin.png",255);
    texW = 0;
    texH = 0;
    SDL_QueryTexture(goblin, NULL, NULL, &texW, &texH);

    gRect = { game->current.w / 2 - texW/2,game->current.h / 2 + texH*2+ goblinmovey, texW, texH };
    SDL_RenderCopy(game->renderer, goblin, NULL, &gRect);
    if(goblinmovey < game->current.h - texH)
        goblinmovey++;

    SDL_Rect left_weapon = {0,game->current.h - 120, 120,120};
    SDL_Rect right_weapon = {game->current.w - 120,game->current.h - 120, 120,120};
    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0,255);
    SDL_RenderFillRect(game->renderer, &left_weapon);
    SDL_RenderFillRect(game->renderer, &right_weapon);
    game->renderDaytime();

    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    if( SDL_PointInRect(&mousePosition, &left_weapon) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &left_weapon);

        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
        }
    }
    if( SDL_PointInRect(&mousePosition, &right_weapon) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &right_weapon);

        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
        }
    }

    game->RenderText("HP: " + std::to_string(game->SActor.hitpoints_current) + " / " + std::to_string(game->SActor.hitpoints_max), White, game->current.w - 200,50,24);
}
