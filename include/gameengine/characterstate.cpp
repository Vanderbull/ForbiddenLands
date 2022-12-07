#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "playstate.h"
#include "characterstate.h"
#include "inventorystate.h"
#include "worldmapstate.h"

CCharacterState CCharacterState::m_CharacterState;

void CCharacterState::Init()
{
    SDL_Log("CCharacterState Init\n");
    MenuChoices.clear();
    MenuChoices.push_back("INVENTORY");
    MenuChoices.push_back("CHARACTER");
    MenuChoices.push_back("JOURNAL");
    MenuChoices.push_back("MAP");
}

void CCharacterState::Cleanup()
{
	SDL_Log("CCharacterState Cleanup\n");
}

void CCharacterState::Pause()
{
	SDL_Log("CCharacterState Pause\n");
}

void CCharacterState::Resume()
{
	SDL_Log("CCharacterState Resume\n");
}

void CCharacterState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CCharacterState HandleEvents\n");

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

void CCharacterState::Update(CGameEngine* game)
{
    SDL_Log("CCharacterState Update\n");

    ///--- Store the current information to the previous
    m_iPreviousCoord.x = m_iCurrentCoord.x;
    m_iPreviousCoord.y = m_iCurrentCoord.y;

    //m_iPreviousCoordX=m_iCurrentCoordX;
    //m_iPreviousCoordY=m_iCurrentCoordY;
    m_uPreviousMouseState=m_uCurrentMouseState;

    ///--- Update the current state of the mouse
    m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoord.x, &m_iCurrentCoord.y);

    //m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

    ///--- Set the wheel back to 0
    m_iWheelCoord.x = 0;
    m_iWheelCoord.y = 0;

    //m_iWheelX=0;
    //m_iWheelY=0;
}

void CCharacterState::Draw(CGameEngine* game)
{
    SDL_Log("CCharacterState Draw");
    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    int counter = 0;

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    if( game->BackgroundTexture == NULL )
        game->BackgroundTexture = game->LoadTexture("./assets/data/textures/backgrounds/characterstate.png",255);

    SDL_RenderCopy(game->renderer, game->BackgroundTexture, NULL, NULL);

    game->RenderText(game->SActor.name.c_str(),White,300,90,48);

    std::string Experience = std::to_string(game->SActor.experience) + " / 10000";
    game->RenderBreadText(Experience.c_str(),game->White,300, 150 );

  	game->RenderBreadText(std::to_string(game->SActor.current_stats[0]).c_str(),game->White,610, 225 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[1]).c_str(),game->White,610, 269 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[2]).c_str(),game->White,610, 310 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[3]).c_str(),game->White,610, 350 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[4]).c_str(),game->White,610, 390 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[5]).c_str(),game->White,610, 430 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[6]).c_str(),game->White,610, 470 );

  	game->RenderBreadText(game->SActor.professionTextElements[game->ChoosenProfession].c_str(),game->White,444, 530 );

//  	game->RenderBreadText(std::to_string(game->SActor.uid).c_str(),game->White,game->current.w - 100, 0 );
  	game->RenderBreadText(std::to_string(game->SActor.armour_class).c_str(),game->White,338,600 );
  	game->RenderBreadText(std::to_string(game->SActor.coins_gold).c_str(),game->White,338, 790 );

  	game->RenderBreadText(std::to_string(game->SActor.damage).c_str(),game->White,338, 670 );
  	game->RenderBreadText(std::to_string(game->SActor.encumbrance).c_str(),game->White,400, 670 );

  	game->RenderBreadText(std::to_string(game->SActor.hitpoints_current).c_str(),game->White,120, 540 );
  	game->RenderBreadText("/",game->White,135, 540 );
  	game->RenderBreadText(std::to_string(game->SActor.hitpoints_max).c_str(),game->White,150, 540 );
//  	game->RenderBreadText(std::to_string(game->SActor.hunger).c_str(),game->White,game->current.w - 100, 475 );
//  	game->RenderBreadText(std::to_string(game->SActor.thirst).c_str(),game->White,game->current.w - 100, 575 );
//    game->RenderBreadText(game->SActor.name.c_str(),game->White,game->current.w - 100, 600 );

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255,128);
    SDL_RenderFillRect(game->renderer,&ExitButton2);

    if( SDL_PointInRect(&mousePosition, &ExitButton2) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CPlayState::Instance() );
        }
    }

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255,128);
    SDL_RenderFillRect(game->renderer,&InventoryButton);

    if( SDL_PointInRect(&mousePosition, &InventoryButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CInventoryState::Instance() );
        }
    }

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255,128);
    SDL_RenderFillRect(game->renderer,&CharacterButton);

    if( SDL_PointInRect(&mousePosition, &CharacterButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CCharacterState::Instance() );
        }
    }

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255,128);
    SDL_RenderFillRect(game->renderer,&MapButton);

    if( SDL_PointInRect(&mousePosition, &MapButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CWorldMapState::Instance() );
        }
    }
}
