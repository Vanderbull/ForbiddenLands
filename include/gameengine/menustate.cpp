#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
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
    MenuChoices.push_back("PLAY");
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
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						game->PopState();
						break;
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

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

	SDL_Surface* surface = IMG_Load( "./images/menu_backdrop.png" );
	if( !surface )
	{
        exit(-1);
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( game->renderer, surface );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( texture, 255 );
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    gSurface = TTF_RenderText_Blended(game->gameTitleFont, "A Viking Saga", White);
	if( !gSurface )
	{
        exit(-1);
	}
    gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { game->current.w / 2 - (texW / 2),200- (texH / 2), texW, texH };
    SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);

    int Repeat = 0;
    int buttonWidth = 600;
    int buttonHeight = 60;

    for(auto MenuChoice : MenuChoices)
    {
        SDL_Rect buttonPosition = { (game->current.w / 2) - (buttonWidth / 2), 300 + (Repeat*(buttonPosition.h+15)),buttonWidth,buttonHeight};

        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderDrawRect(game->renderer,&buttonPosition);

        gSurface = TTF_RenderText_Blended(game->gameTitleFont, MenuChoice.c_str(), White);
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { buttonPosition.x + (buttonWidth / 2) - (texW / 2), buttonPosition.y + (buttonHeight / 2) - (texH / 2), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

        //Destroy resources
        SDL_FreeSurface(gSurface);
        SDL_DestroyTexture(gTexture);


        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(game->renderer, &buttonPosition);

            if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
            {
                if( MenuChoice == "LOAD")
                    game->ChangeState( CLoadMenuState::Instance() );
                if( MenuChoice == "SAVE")
                    game->ChangeState( CSaveMenuState::Instance() );
                if( MenuChoice == "PLAY")
                    game->ChangeState( CPlayState::Instance() );
                if( MenuChoice == "CHARACTER MANAGER")
                    game->ChangeState( CCreateCharacterState::Instance() );
                if( MenuChoice == "SETTINGS")
                    game->ChangeState( CSettingsMenuState::Instance() );
                if( MenuChoice == "EXIT")
                    game->PopState();
            }
        }
        ++Repeat;
    }
}
