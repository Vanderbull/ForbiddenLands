#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "playstate.h"
#include "characterstate.h"

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

    int counter = 0;

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);


    if( game->BackgroundTexture == NULL )
        game->BackgroundTexture = game->LoadTexture("./assets/data/textures/menus/menu_backdrop.png",255);

    SDL_RenderCopy(game->renderer, game->BackgroundTexture, NULL, NULL);

  	for (auto& iter: AbilityScore)
    {
        game->RenderBreadText(iter.first.c_str(),game->White,125,500 + (25*counter) );
        game->RenderBreadText(std::to_string(iter.second).c_str(),game->White,250,500 + (25*counter) );
    	counter++;
  	}
  	counter = 0;

  	for (auto& iter: AbilityMod)
    {
        game->RenderBreadText(std::to_string(iter.second).c_str(),game->White,300,500 + (25*counter) );
    	counter++;
  	}

  	game->RenderBreadText(std::to_string(game->SActor.uid).c_str(),game->White,game->current.w - 100, 0 );
  	game->RenderBreadText(std::to_string(game->SActor.armour_class).c_str(),game->White,game->current.w - 100, 50 );
  	game->RenderBreadText(std::to_string(game->SActor.coins_gold).c_str(),game->White,game->current.w - 100, 100 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[0]).c_str(),game->White,game->current.w - 100, 125 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[1]).c_str(),game->White,game->current.w - 100, 150 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[2]).c_str(),game->White,game->current.w - 100, 175 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[3]).c_str(),game->White,game->current.w - 100, 200 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[4]).c_str(),game->White,game->current.w - 100, 225 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[5]).c_str(),game->White,game->current.w - 100, 250 );
  	game->RenderBreadText(std::to_string(game->SActor.damage).c_str(),game->White,game->current.w - 100, 300 );
  	game->RenderBreadText(std::to_string(game->SActor.encumbrance).c_str(),game->White,game->current.w - 100, 325 );
  	game->RenderBreadText(std::to_string(game->SActor.experience).c_str(),game->White,game->current.w - 100, 350 );
  	game->RenderBreadText(std::to_string(game->SActor.healingPotions).c_str(),game->White,game->current.w - 100, 400 );
  	game->RenderBreadText(std::to_string(game->SActor.hitpoints_current).c_str(),game->White,game->current.w - 100, 425 );
  	game->RenderBreadText(std::to_string(game->SActor.hitpoints_max).c_str(),game->White,game->current.w - 100, 450 );
  	game->RenderBreadText(std::to_string(game->SActor.hunger).c_str(),game->White,game->current.w - 100, 475 );
  	game->RenderBreadText(std::to_string(game->SActor.thirst).c_str(),game->White,game->current.w - 100, 575 );
    game->RenderBreadText(game->SActor.name.c_str(),game->White,game->current.w - 100, 600 );
}
