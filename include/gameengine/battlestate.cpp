#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "battlestate.h"

CBattleState CBattleState::m_BattleState;

void CBattleState::Init()
{
    if( TTF_Init() == -1 )
    {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    gameTitleFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 24);

    if(!gameTitleFont)
    {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

	SDL_Surface* temp = SDL_LoadBMP("menu.bmp");

	SDL_FreeSurface(temp);

	std::cout << "CBattleState Init\n";
}

void CBattleState::Cleanup()
{
	std::cout << "CBattleState Pause\n";
}

void CBattleState::Pause()
{
	std::cout << "CBattleState Pause\n";
}

void CBattleState::Resume()
{
	std::cout << "CBattleState Resume\n";
}

void CBattleState::HandleEvents(CGameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
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
                        game->PopState();
                        break;
                } break;
		}
	}
}

void CBattleState::Update(CGameEngine* game)
{
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

void CBattleState::Draw(CGameEngine* game)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 200);

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

    MainMenuBackgroundTexture = NULL;

	SDL_Surface* surface = IMG_Load( "./images/wireframe new inventory.png" );
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

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    SDL_Rect buttonPosition = { 226, 407,119,119};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);




    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
}
