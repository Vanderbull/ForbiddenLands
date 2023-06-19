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
                        game->PushState( CMenuState::Instance() );
						break;
				} break;
		}
	}
}

void CVillageState::Update(CGameEngine* game)
{
    SDL_Log("CVillageState Update\n");

    std::cout << "states: " << game->GetSize() << std::endl;
    game->SActor.PlayerCoordinate = {15,1,0};
    game->SActor.PlayerLastCoordinate = {15,1,0};
    game->SActor.hitpoints_current = 10;
    game->SActor.hitpoints_max = 10;
    game->number_of_enemies = 1;

//    std::random_device rd;
//
//    int z = 0;
//    for(int x = 0; x < 16; x++)
//        for(int y = 0; y < 16; y++)
//        {
//            game->random_events[x][y][z] = rd();
//        }
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

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    SDL_RenderCopy(game->renderer, game->villageState, NULL, NULL);

    game->RenderText("hides: " + std::to_string(game->hides), game->Black, 1680,100,24);
    game->RenderText("slaves: " + std::to_string(game->slaves), game->Black, 1680,132,24);
    game->RenderText("gold: " + std::to_string(game->gold), game->Black, 1680,164,24);
    game->RenderText("silver: " + std::to_string(game->silver), game->Black, 1680,196,24);

    SDL_Rect Leave_Village_Button = { 0,0,90,23};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Leave_Village_Button);
    game->RenderText("Leave village", White, Leave_Village_Button.x,Leave_Village_Button.y,24);
    if( SDL_PointInRect(&mousePosition, &Leave_Village_Button)  )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 128, 128, 192);
        SDL_RenderFillRect(game->renderer, &Leave_Village_Button);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            //game->ChangeState(CWorldMapState::Instance());
            game->PopState();
        }
    }


    SDL_Rect Hides_Button = { 200,300,90,23};
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

    SDL_Rect Buy_Hides_Button = { 400,300,90,23};
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

    SDL_Rect Slaves_Button = { 800, 300,90,23};
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

    SDL_Rect Buy_Slaves_Button = { 1000, 300,90,23};
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

    SDL_Rect Recruit_Soldier_Button = { 1200, 300,90,23};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Recruit_Soldier_Button);
    game->RenderText("recruit soldiers", White, Recruit_Soldier_Button.x,Recruit_Soldier_Button.y,24);

    if( SDL_PointInRect(&mousePosition, &Recruit_Soldier_Button) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 128, 128, 192);
        SDL_RenderFillRect(game->renderer, &Recruit_Soldier_Button);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            if( game->gold > 0 )
            {
                game->gold -= 1;
                game->Raiding_Party.old += 1;
                game->Raiding_Party.middleage += 1;
                game->Raiding_Party.young += 1;
            }
        }
    }

    game->RenderTextWrapped(game->Village_Name.c_str(), game->White, game->current.w / 3 + 200,game->current.h / 3,24,1520);

    game->RenderText("Old: " + std::to_string(game->Raiding_Party.old),game->Black,1680,gRect.y +  220,24);
    game->RenderText("Middleaage: " + std::to_string(game->Raiding_Party.middleage),game->Black,1680,gRect.y +  260,24);
    game->RenderText("Young: " + std::to_string(game->Raiding_Party.young),game->Black,1680,gRect.y +  300,24);

    // Clear the renderer
    //SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    //SDL_RenderClear(renderer);

//    // Draw the buildings
//    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 255);
//    SDL_Rect building1Rect = { 100, 200, 100, 400 };
//    SDL_Rect building2Rect = { 250, 150, 150, 450 };
//    SDL_Rect building3Rect = { 450, 250, 200, 350 };
//    SDL_Rect building4Rect = { 700, 300, 100, 300 };
//    SDL_RenderFillRect(game->renderer, &building1Rect);
//    SDL_RenderFillRect(game->renderer, &building2Rect);
//    SDL_RenderFillRect(game->renderer, &building3Rect);
//    SDL_RenderFillRect(game->renderer, &building4Rect);
//
//    // Draw the park
//    SDL_SetRenderDrawColor(game->renderer, 34, 139, 34, 255);
//    SDL_Rect parkRect = { 50, 500, 200, 100 };
//    SDL_RenderFillRect(game->renderer, &parkRect);
//
//    // Draw the road
//    SDL_SetRenderDrawColor(game->renderer, 105, 105, 105, 255);
//    SDL_Rect roadRect = { 0, 450, game->current.w, 100 };
//    SDL_RenderFillRect(game->renderer, &roadRect);
//
//    // Draw the sun
//    SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 255);
//    SDL_Rect sunRect = { 700, 50, 100, 100 };
//    SDL_RenderFillRect(game->renderer, &sunRect);
}
