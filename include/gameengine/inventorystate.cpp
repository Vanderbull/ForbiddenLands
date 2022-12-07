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
	SDL_Log("CBattleState Init\n");
}

void CInventoryState::Cleanup()
{
	SDL_Log("CBattleState Pause\n");
}

void CInventoryState::Pause()
{
	SDL_Log("CBattleState Pause\n");
}

void CInventoryState::Resume()
{
	SDL_Log("CBattleState Resume\n");
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

    if(scrolling){
      if(scroll_acceleration > 0) scroll_acceleration -= scroll_friction;
      if(scroll_acceleration < 0) scroll_acceleration += scroll_friction;
      if(abs(scroll_acceleration) < 0.0005) scroll_acceleration = 0;
      scroll_Y += scroll_sensitivity * scroll_acceleration;
      // Here you have to set your scrolling bounds i.e. if(scroll_Y < 0) scroll_Y = 0;
      if(scroll_Y < 0) scroll_Y = 0;
      if(scroll_Y > 1040) scroll_Y = 1040;
    }
    scrolling = 0;

    if (scroll_range_min < 0 )
    {
        scroll_range_min = 0;
        scroll_range_max = scroll_range_min + 10;
    }

    if (scroll_range_max > game->v_Skill.size() )
    {
        scroll_range_min = game->v_Skill.size() -10;
        scroll_range_max = game->v_Skill.size();
    }
}

void CInventoryState::Draw(CGameEngine* game)
{
    SDL_Log("CInventoryState Draw");
    game->SActor.coins_gold = 30;
    static int shop_coins = 10;

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    int localCounter = 0;
    SDL_Rect TextFrame = {0, 0, 0, 0};
    SDL_Rect TextFrame2 = {0, 0, 0, 0};

    std::vector<SDL_Rect> raceElements;
    std::vector<SDL_Rect> professionElements;

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

//    SDL_Texture* backgroundTexture = game->LoadTexture("./images/shops/shop3.jpg",255);
//    SDL_RenderCopy(game->renderer, backgroundTexture, NULL, NULL);
//    SDL_DestroyTexture(backgroundTexture);
//
//    SDL_Texture* backgroundTexture = game->LoadTexture("./images/ui/inventory.png",255);
//    int texW = 0;
//    int texH = 0;
//    SDL_QueryTexture(backgroundTexture, NULL, NULL, &texW, &texH);
//    SDL_Rect InventoryPosition = {0, 0, texW, texH};
//
//    SDL_RenderCopy(game->renderer, backgroundTexture, NULL, &InventoryPosition);
//
//    SDL_DestroyTexture(backgroundTexture);
//
//    backgroundTexture = game->LoadTexture("./images/ui/inventory.png",255);
//    SDL_QueryTexture(backgroundTexture, NULL, NULL, &texW, &texH);
//    InventoryPosition = {0, texH + 64, texW, texH};
//
//    SDL_RenderCopy(game->renderer, backgroundTexture, NULL, &InventoryPosition);
//
//    SDL_DestroyTexture(backgroundTexture);

    //game->RenderText("GENERAL SHOP", White, game->current.w - 400, 20,48);
    //game->RenderText(std::to_string(game->v_ItemNames.size()).c_str(), White, game->current.w - 400, 60,48);
    game->RenderText(std::to_string(shop_coins).c_str(), White, game->current.w - 40, 20,24);
    game->RenderText(std::to_string(game->SActor.coins_gold).c_str(), White, game->current.w - 40, 40,24);

    // Skills ////////////////////////////
    int counter = 0;

    int slide =0;
    game->SkillRect.clear();

    int x_counter = 0;
    int y_counter = 0;

    SDL_Texture* iconImage = game->LoadTexture("./assets/data/textures/shield.png",255);
    SDL_Texture* iconImage2 = game->LoadTexture("./assets/data/textures/shield.jpg",255);

//    vector<string>::iterator itr;
//    cout << "Searching for \"NONE\"\n";
//    itr = find(game->v_ItemNames.begin(), game->v_ItemNames.end(), "NONE");
//    if(itr != game->v_ItemNames.end()) {
//      cout << "Found \"NONE\", Replacing with \"NONE\"\n";
//      *itr = "NONE";
//      game->v_ItemNames.erase(itr);
//    }
//
//   cout << endl;
//   // Find all strings that are less than 4 characters long.
//   cout << "Searching for all strings that have 3 or fewer characters.\n";
//   itr = game->v_ItemNames.begin();
//   do {
//      itr = find_if(itr, game->v_ItemNames.end(), is_short_str);
//      if(itr != game->v_ItemNames.end()) {
//         cout << "Found " << *itr << endl;
//         ++itr;
//      }
//   } while(itr != game->v_ItemNames.end());

    for (std::string textElement : game->v_ItemNames)
    {
        SDL_Rect icon;

        icon.x = 64 * x_counter;
        icon.y = 64 * y_counter;
        icon.w = 64;
        icon.h = 64;

        if(game->v_ItemNames.at(counter) != "NONE")
        SDL_RenderCopy(game->renderer, iconImage, NULL, &icon);

        if( SDL_PointInRect(&mousePosition, &icon) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(game->renderer, &icon);
            game->RenderText2(textElement.c_str(),White,icon.x,icon.y,24);

            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( game->v_ItemNames.at(counter) != "NONE" && game->SActor.coins_gold > 0 )
                {
                    game->v_ItemNamesShop.push_back(game->v_ItemNames.at(counter).c_str());
                    game->v_ItemNames.at(counter) = "NONE";
                    shop_coins++;
                    game->SActor.coins_gold--;
                }
            }
        }

        x_counter++;
        if( x_counter >= 20)
        {
            y_counter++;
            x_counter = 0;
        }

        counter++;
    };
    counter = 0;
    x_counter = 0;
    y_counter = 0;
    if( !game->v_ItemNamesShop.empty() )
    for (std::string textElement : game->v_ItemNamesShop)
    {
        SDL_Rect icon;

        icon.x = 64 * x_counter;
        icon.y = 640 + 64 + 64 * y_counter;
        icon.w = 64;
        icon.h = 64;

        if(game->v_ItemNamesShop.at(counter) != "NONE")
        SDL_RenderCopy(game->renderer, iconImage, NULL, &icon);

        if( SDL_PointInRect(&mousePosition, &icon) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(game->renderer, &icon);
            game->RenderText2(textElement.c_str(),White,icon.x,icon.y,24);
//
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if(game->v_ItemNamesShop.at(counter) != "NONE" && shop_coins > 0)
                {
                    int search_index = 0;
                    for (std::string textElement : game->v_ItemNames)
                    {
                        if(game->v_ItemNames.at(search_index) == "NONE" && game->v_ItemNamesShop.at(counter) != "NONE")
                        {
                            game->v_ItemNames.at(search_index) = game->v_ItemNamesShop.at(counter);
                            game->v_ItemNamesShop.at(counter) = "NONE";
                            shop_coins--;
                            game->SActor.coins_gold++;
                        }
                        search_index++;
                    }
                }
            }
        }
        x_counter++;
        if( x_counter >= 20)
        {
            y_counter++;
            x_counter = 0;
        }

        counter++;
    };

    vector<string>::iterator itr;
    cout << "Searching for \"NONE\"\n";
    if( !game->v_ItemNames.empty() )
        itr = find(game->v_ItemNames.begin(), game->v_ItemNames.end(), "NONE");

    if(itr != game->v_ItemNames.end())
    {
      cout << "Found \"NONE\", Replacing with \"NONE\"\n";
      //*itr = "NONE";
      game->v_ItemNames.erase(itr);
      game->v_ItemNames.push_back("NONE");
    }

    cout << "Searching for \"NONE\"\n";
    if( !game->v_ItemNamesShop.empty() )
        itr = find(game->v_ItemNamesShop.begin(), game->v_ItemNamesShop.end(), "NONE");

    if(itr != game->v_ItemNames.end())
    {
      cout << "Found \"NONE\", Replacing with \"NONE\"\n";
      //*itr = "NONE";
      game->v_ItemNamesShop.erase(itr);
      game->v_ItemNamesShop.push_back("NONE");
    }

    SDL_DestroyTexture(iconImage);
}
