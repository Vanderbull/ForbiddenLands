#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "loadingstate.h"
#include "playstate.h"
#include "createcharacterstate.h"
#include "loadmenustate.h"
#include "savemenustate.h"
#include "settingsmenustate.h"
#include "menustate.h"

CMenuState CMenuState::m_MenuState;

void CMenuState::Init()
{
    MenuChoices.clear();
    MenuChoices.push_back("NEW COLONY");
    MenuChoices.push_back("SAVE");
    MenuChoices.push_back("LOAD");
    MenuChoices.push_back("CHARACTER MANAGER");
    MenuChoices.push_back("SETTINGS");
    MenuChoices.push_back("EXIT");

	SDL_Log("CMenuState Init\n");
}

void CMenuState::Cleanup()
{
	SDL_Log("CMenuState Cleanup\n");
}

void CMenuState::Pause()
{
	SDL_Log("CMenuState Pause\n");
}

void CMenuState::Resume()
{
	SDL_Log("CMenuState Resume\n");
}

void CMenuState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CMenuState HandleEvents\n");

	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
            case SDL_MOUSEMOTION:
            {
                SDL_GetMouseState( &mousePosition.x, &mousePosition.y );
            } break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
                        game->Quit();
                    }break;
				} break;
		}
	}
}

void CMenuState::Update(CGameEngine* game)
{
    SDL_Log("CMenuState Update\n");

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

void CMenuState::Draw(CGameEngine* game)
{
    SDL_Log("CMenuState Draw\n");

    SDL_Texture* texture = game->LoadTexture("./assets/data/textures/menus/menu_backdrop.png",255);
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);

    int Repeat = 0;
    int buttonWidth = 600;
    int buttonHeight = 60;

    std::cout << game->current.w << std::endl;
    std::cout << game->current.h << std::endl;
    std::cout << game->current.refresh_rate << std::endl;
    std::cout << game->current.format << std::endl;
    //exit(2);

    for(auto MenuChoice : MenuChoices)
    {
        SDL_Rect buttonPosition = { (game->current.w / 2) - (buttonWidth / 2), 300 + (Repeat*(buttonPosition.h+15)),buttonWidth,buttonHeight};

        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(game->renderer, &buttonPosition);

            if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
            {
                if( MenuChoice == "NEW COLONY")
                {
                    Mix_PlayChannel(-1, game->_sample[4], 0);
                    game->ChangeState( CLoadingState::Instance() );
                }
                else if( MenuChoice == "LOAD")
                {
                    Mix_PlayChannel(-1, game->_sample[4], 0);
                    game->ChangeState( CLoadMenuState::Instance() );
                }
                else if( MenuChoice == "SAVE")
                {
                    Mix_PlayChannel(-1, game->_sample[4], 0);
                    game->ChangeState( CSaveMenuState::Instance() );
                }
                else if( MenuChoice == "CHARACTER MANAGER")
                {
                    Mix_PlayChannel(-1, game->_sample[4], 0);
                    game->ChangeState( CCreateCharacterState::Instance() );
                }
                else if( MenuChoice == "SETTINGS")
                {
                    Mix_PlayChannel(-1, game->_sample[4], 0);
                    game->ChangeState( CSettingsMenuState::Instance() );
                }
                else if( MenuChoice == "EXIT")
                {
                    Mix_PlayChannel(-1, game->_sample[4], 0);
                    game->Quit();

                }
            }
        }
        ++Repeat;
    }
}
