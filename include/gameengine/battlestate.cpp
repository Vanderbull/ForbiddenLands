#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "battlestate.h"

using namespace std::chrono;

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
    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

    SDL_Texture* texture = game->LoadTexture("./images/wireframe new inventory.png",255);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( texture, 255 );
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    // ROW 1 START
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
    // ROW 1 SEND
    buttonPosition.x = 226;
    buttonPosition.y = buttonPosition.y+244;
    buttonPosition.w = 119;
    buttonPosition.h = 119;

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
    buttonPosition.x = 226;
    buttonPosition.y = buttonPosition.y+244;
    buttonPosition.w = 119;
    buttonPosition.h = 119;

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
    buttonPosition.x = 226;
    buttonPosition.y = buttonPosition.y+244;
    buttonPosition.w = 119;
    buttonPosition.h = 119;

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

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 89;
    buttonPosition.y = 322;
    buttonPosition.w = 64;
    buttonPosition.h = 64;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 89;
    buttonPosition.y = 423;
    buttonPosition.w = 64;
    buttonPosition.h = 64;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 89;
    buttonPosition.y = 525;
    buttonPosition.w = 64;
    buttonPosition.h = 64;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    // WEAPONS
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 1282;
    buttonPosition.y = 349;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 1282+160;
    buttonPosition.y = 349;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 1282;
    buttonPosition.y = 536;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 1282+160;
    buttonPosition.y = 536;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

     //ARMOUR
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2241;
    buttonPosition.y = 356;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2161;
    buttonPosition.y = 543;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2321;
    buttonPosition.y = 543;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2161;
    buttonPosition.y = 729;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2321;
    buttonPosition.y = 729;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    // OTHER

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);

    buttonPosition.x = 2157;
    buttonPosition.y = 981;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2327;
    buttonPosition.y = 981;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
}
