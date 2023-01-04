#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "inventorystate.h"

using namespace std::chrono;

CInventoryState CInventoryState::m_InventoryState;

void CInventoryState::Init()
{
	SDL_Log("CInventoryState Init\n");
}

void CInventoryState::Cleanup()
{
	SDL_Log("CInventoryState Pause\n");
}

void CInventoryState::Pause()
{
	SDL_Log("CInventoryState Pause\n");
}

void CInventoryState::Resume()
{
	SDL_Log("CInventoryState Resume\n");
}

void CInventoryState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CInventoryState HandleEvents");

	//SDL_Event event;

	if (SDL_PollEvent(&game->event))
    //while (SDL_PollEvent(&game->event) != 0)
    {
		switch (game->event.type)
		{
            case SDL_MOUSEBUTTONDOWN:
                switch (game->event.button.button)
                {
                case SDL_BUTTON_RIGHT:
                default:
                {
                m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);
                } break;
            } break;
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (game->event.key.keysym.sym) {
					case SDLK_ESCAPE:
					{
                        game->SActor.PlayerCoordinate = game->SActor.PlayerLastCoordinate;
						game->ChangeState( CPlayState::Instance() );
                    } break;
                    case SDLK_UP:
                        {
                              scroll_acceleration = 1;
                              scrolling = 1;
                        }break;
                    case SDLK_DOWN:
                        {
                            scroll_acceleration = -1;
                            scrolling = 1;
                        } break;
				} break;
            case SDL_KEYUP:
                switch (game->event.key.keysym.sym) {
                    case SDLK_UP:
                        {
                            scroll_range_min--;
                            scroll_range_max--;
                              scroll_acceleration = 0;
                              scrolling = 0;
                        }break;
                    case SDLK_DOWN:
                        {
                            scroll_range_min++;
                            scroll_range_max++;
                              scroll_acceleration = 0;
                              scrolling = 0;
                        }break;
                } break;
		}
	}
}

// Return true if the string is 3 characters or less.
bool is_short_str(string str)
{
   if(str.size() <= 3) return true;
   return false;
}

void CInventoryState::Update(CGameEngine* game)
{
    SDL_Log("CInventoryState Update");

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

void CInventoryState::Draw(CGameEngine* game)
{
    SDL_Log("CInventoryState Draw");
    game->SActor.coins_gold = 30;
    static int shop_coins = 10;

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    SDL_Rect Description = {640, 300, 640, 480};
    SDL_Rect DropButton = {640, 1000, 192, 64};

    int counter = 0;
    static int last_counter = 0;
    SDL_Rect icon;
    static SDL_Rect active_icon = {(game->current.w - (64*10)),64,64,64};
    static int active_icon_id = 0;

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);


    for( int y = 0; y < 10; y++ )
    for( int x = 0; x < 9; x++ )
    {
        icon.x = (game->current.w - (64*10)) + 64 * x;
        icon.y = 64 + 64 * y;
        icon.w = 64;
        icon.h = 64;

        SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);
        SDL_RenderFillRect(game->renderer, &icon);
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderDrawRect(game->renderer, &icon);

        if( SDL_PointInRect(&mousePosition, &icon) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(game->renderer, &icon);
            if( game->v_InventoryItem.at(last_counter).Name != "" )
            {
                SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);
                SDL_RenderFillRect(game->renderer, &Description);
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                SDL_RenderDrawRect(game->renderer, &Description);
                game->RenderText(game->v_InventoryItem.at(counter).Name.c_str(), White, 660, 320,48);
                game->RenderText(std::to_string(game->v_InventoryItem.at(counter).Efficiency).c_str(), White, 660, 360,48);
                game->RenderText(std::to_string(game->v_InventoryItem.at(counter).MinDamage).c_str(), White, 660, 400,48);
                game->RenderText(std::to_string(game->v_InventoryItem.at(counter).MaxDamage).c_str(), White, 660, 440,48);
                game->RenderText(std::to_string(game->v_InventoryItem.at(counter).DmgType).c_str(), White, 660, 480,48);
                game->RenderText(std::to_string(game->v_InventoryItem.at(counter).NumHands).c_str(), White, 660, 520,48);
                game->RenderText(std::to_string(game->v_InventoryItem.at(counter).Bodypart).c_str(), White, 660, 560,48);
            }
        }
//        else
//        if(counter == active_icon_id )
//        {
//            if( game->v_InventoryItem.at(last_counter).Name != "" )
//            {
//                game->RenderText(game->v_InventoryItem.at(last_counter).Name.c_str(), White, 660, 320,48);
//                game->RenderText(std::to_string(game->v_InventoryItem.at(last_counter).Efficiency).c_str(), White, 660, 360,48);
//                game->RenderText(std::to_string(game->v_InventoryItem.at(last_counter).MinDamage).c_str(), White, 660, 400,48);
//                game->RenderText(std::to_string(game->v_InventoryItem.at(last_counter).MaxDamage).c_str(), White, 660, 440,48);
//                game->RenderText(std::to_string(game->v_InventoryItem.at(last_counter).DmgType).c_str(), White, 660, 480,48);
//                game->RenderText(std::to_string(game->v_InventoryItem.at(last_counter).NumHands).c_str(), White, 660, 520,48);
//                game->RenderText(std::to_string(game->v_InventoryItem.at(last_counter).Bodypart).c_str(), White, 660, 560,48);
//            }
//        }
        counter++;
    }

    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 128);
    SDL_RenderDrawRect(game->renderer, &active_icon);

    counter = 0;

    for( int y = 0; y < 10; y++ )
    for( int x = 0; x < 9; x++ )
    {
        icon.x = (game->current.w - (64*10)) + 64 * x;
        icon.y = 64 + 64 * y;
        icon.w = 64;
        icon.h = 64;

        if( game->v_InventoryItem.at(counter).Name != "EMPTY")
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(game->renderer, &icon);
        }

        if( SDL_PointInRect(&mousePosition, &icon) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                active_icon = icon;
                last_counter = counter;
                active_icon_id = counter;
            }
        }
        counter++;
    }

    SDL_RenderDrawRect(game->renderer, &DropButton);
    if( SDL_PointInRect(&mousePosition, &DropButton) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if( active_icon_id != -1)
            {
                game->v_InventoryItem.at(active_icon_id) = game->SpawnRandomItem();
                active_icon = {0,0,0,0};
            }
        }
    }
    game->RenderText("DROP", White, DropButton.x, DropButton.y,48);

    game->RenderText(std::to_string(game->v_InventoryItem.size()).c_str(), White, 0, 0,48);
}
