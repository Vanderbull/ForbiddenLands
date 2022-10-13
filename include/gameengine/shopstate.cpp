#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "shopstate.h"

CShopState CShopState::m_ShopState;

void CShopState::Init()
{
	SDL_Log("CShopState Init\n");
}

void CShopState::Cleanup()
{
	SDL_Log("CShopState Cleanup\n");
}

void CShopState::Pause()
{
	SDL_Log("CShopState Pause\n");
}

void CShopState::Resume()
{
	SDL_Log("CShopState Resume\n");
}

void CShopState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CShopState HandleEvents\n");

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
						game->PopState();
						break;
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

void CShopState::Update(CGameEngine* game)
{
    SDL_Log("CShopState Update\n");

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

    if (scroll_range_max > game->Skill.size() )
    {
        scroll_range_min = game->Skill.size() -10;
        scroll_range_max = game->Skill.size();
    }
}

void CShopState::Draw(CGameEngine* game)
{
    SDL_Log("CShopState Draw");
    static int player_coins = 30;
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

    SDL_Texture* backgroundTexture = game->LoadTexture("./images/shops/shop3.jpg",255);
    SDL_RenderCopy(game->renderer, backgroundTexture, NULL, NULL);
    SDL_DestroyTexture(backgroundTexture);

    backgroundTexture = game->LoadTexture("./images/ui/inventory.png",255);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &texW, &texH);
    SDL_Rect InventoryPosition = {0, 0, texW, texH};

    SDL_RenderCopy(game->renderer, backgroundTexture, NULL, &InventoryPosition);

    SDL_DestroyTexture(backgroundTexture);

    backgroundTexture = game->LoadTexture("./images/ui/inventory.png",255);
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &texW, &texH);
    InventoryPosition = {0, texH + 64, texW, texH};

    SDL_RenderCopy(game->renderer, backgroundTexture, NULL, &InventoryPosition);

    SDL_DestroyTexture(backgroundTexture);

    game->RenderText("GENERAL SHOP", White, game->current.w - 400, 20,48);
    game->RenderText(std::to_string(game->v_ItemNames.size()).c_str(), White, game->current.w - 400, 60,48);

    // Skills ////////////////////////////
    int counter = 0;

    int slide =0;
    game->SkillRect.clear();

    int x_counter = 0;
    int y_counter = 0;

    SDL_Texture* iconImage = game->LoadTexture("./images/shield.png",255);
    //game->v_ItemNamesShop.clear();
    for (std::string textElement : game->v_ItemNames)
    {

        //game->v_ItemNamesShop.push_back("NONE");
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
//
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( game->v_ItemNames.at(counter) != "NONE" && shop_coins > 0 )
                {
                    game->v_ItemNamesShop.push_back(game->v_ItemNames.at(counter).c_str());
                    game->v_ItemNames.at(counter) = "NONE";
                    shop_coins--;
                    player_coins++;
                }
                //SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                //SDL_RenderFillRect(game->renderer, &icon);
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
                if(game->v_ItemNamesShop.at(counter) != "NONE" && player_coins > 0)
                {
                    int search_index = 0;
                    for (std::string textElement : game->v_ItemNames)
                    {
                        if(game->v_ItemNames.at(search_index) == "NONE" && game->v_ItemNamesShop.at(counter) != "NONE")
                        {
                            game->v_ItemNames.at(search_index) = game->v_ItemNamesShop.at(counter);
                            game->v_ItemNamesShop.at(counter) = "NONE";
                            shop_coins++;
                            player_coins--;
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

    game->RenderText(std::to_string(player_coins).c_str(), White, game->current.w - 200, 0,24);
    game->RenderText(std::to_string(shop_coins).c_str(), White, game->current.w - 200, 200,24);

    SDL_DestroyTexture(iconImage);
}
