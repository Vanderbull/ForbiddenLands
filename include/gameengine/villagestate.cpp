#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "createcharacterstate.h"
#include "loadmenustate.h"
#include "savemenustate.h"
#include "menustate.h"
#include "gameoverstate.h"
#include "lootstate.h"
#include "worldmapstate.h"
#include "villagestate.h"

CVillageState CVillageState::m_VillageState;

void CVillageState::Init()
{
	SDL_Log("CVillageState Init\n");
}

void CVillageState::Cleanup()
{
	SDL_Log("CVillageState Cleanup\n");
}

void CVillageState::Pause()
{
	SDL_Log("CVillageState Pause\n");
}

void CVillageState::Resume()
{
	SDL_Log("CVillageState Resume\n");
}

void CVillageState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CVillageState HandleEvents\n");

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
						game->ChangeState(CWorldMapState::Instance());
						break;
				} break;
		}
	}
}

void CVillageState::Update(CGameEngine* game)
{
    SDL_Log("CVillageState Update\n");

    game->SActor.PlayerCoordinate = {15,1,0};
    game->SActor.PlayerLastCoordinate = {15,1,0};
    game->SActor.hitpoints_current = 10;
    game->SActor.hitpoints_max = 10;
    game->number_of_enemies = 1;

    std::random_device rd;

    int z = 0;
    for(int x = 0; x < 16; x++)
        for(int y = 0; y < 16; y++)
        {
            game->random_events[x][y][z] = rd();
        }
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

void CVillageState::Draw(CGameEngine* game)
{
    SDL_Log("CVillageState Draw\n");

    game->RenderText("hides: " + std::to_string(game->hides), game->White, 0,0,24);
    game->RenderText("slaves: " + std::to_string(game->slaves), game->White, 0,32,24);
    game->RenderText("gold: " + std::to_string(game->gold), game->White, 0,64,24);
    game->RenderText("silver: " + std::to_string(game->silver), game->White, 0,96,24);

    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    SDL_Rect Hides_Button = { 100,0,90,23};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Hides_Button);
    game->RenderText("sell hides", White, Hides_Button.x,Hides_Button.y,24);

    if( SDL_PointInRect(&mousePosition, &Hides_Button)  )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Hides_Button);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            if( game->hides > 0 )
            {
                game->gold += game->hides;
                game->hides = 0;
            }
        }
    }

    SDL_Rect Buy_Hides_Button = { 200,0,90,23};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Buy_Hides_Button);
    game->RenderText("buy hides", White, Buy_Hides_Button.x,Buy_Hides_Button.y,24);

    if( SDL_PointInRect(&mousePosition, &Buy_Hides_Button)  )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Buy_Hides_Button);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            if( game->gold > 0 )
            {
                game->gold -= 1;
                game->hides += 1;
            }
        }
    }

    SDL_Rect Slaves_Button = { 100, 32,90,23};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Slaves_Button);
    game->RenderText("sell slaves", White, Slaves_Button.x,Slaves_Button.y,24);

    if( SDL_PointInRect(&mousePosition, &Slaves_Button) )
    {
            SDL_SetRenderDrawColor(game->renderer, 255, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Slaves_Button);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            if( game->slaves > 0 )
            {
                game->gold += game->slaves;
                game->slaves = 0;
            }
        }
    }

    SDL_Rect Buy_Slaves_Button = { 200, 32,90,23};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Buy_Slaves_Button);
    game->RenderText("buy slaves", White, Buy_Slaves_Button.x,Buy_Slaves_Button.y,24);

    if( SDL_PointInRect(&mousePosition, &Buy_Slaves_Button) )
    {
            SDL_SetRenderDrawColor(game->renderer, 255, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Buy_Slaves_Button);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            if( game->gold > 0 )
            {
                game->gold -= 1;
                game->slaves += 1;
            }
        }
    }
    game->RenderTextWrapped("Village", game->White, game->current.w / 3 + 200,game->current.h / 3,24,1520);
}
