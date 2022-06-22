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
}
