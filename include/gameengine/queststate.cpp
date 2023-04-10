#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "createcharacterstate.h"
#include "loadmenustate.h"
#include "savemenustate.h"
#include "queststate.h"

CQuestState CQuestState::m_QuestState;

void CQuestState::Init()
{
	SDL_Log("CQuestState Init\n");

    MenuChoices.clear();
    MenuChoices.push_back("BREAK UP CAMP");
}

void CQuestState::Cleanup()
{
	SDL_Log("CQuestState Cleanup\n");
}

void CQuestState::Pause()
{
	SDL_Log("CQuestState Pause\n");
}

void CQuestState::Resume()
{
	SDL_Log("CQuestState Resume\n");
}

void CQuestState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CQuestState HandleEvents\n");

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
						game->ChangeState(CPlayState::Instance());
						break;
				} break;
		}
	}
}

void CQuestState::Update(CGameEngine* game)
{
    SDL_Log("CQuestState Update\n");

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

void CQuestState::Draw(CGameEngine* game)
{
    SDL_Log("CQuestState Draw\n");

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);
    game->renderQuests();
}
