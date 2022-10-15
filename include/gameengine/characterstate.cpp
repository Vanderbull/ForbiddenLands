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
        game->BackgroundTexture = game->LoadTexture("./images/menus/menu_backdrop.png",255);

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
}
