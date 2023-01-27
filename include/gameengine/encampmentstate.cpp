#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "createcharacterstate.h"
#include "loadmenustate.h"
#include "savemenustate.h"
#include "encampmentstate.h"

CEncampmentState CEncampmentState::m_EncampmentState;

//Current time start time
Uint32 startTime = 0;



void CEncampmentState::Init()
{
	SDL_Log("CEncampmentState Init\n");

	startTime = SDL_GetTicks();

    MenuChoices.clear();
    MenuChoices.push_back("BREAK UP CAMP");
}

void CEncampmentState::Cleanup()
{
	SDL_Log("CEncampmentState Cleanup\n");
}

void CEncampmentState::Pause()
{
	SDL_Log("CEncampmentState Pause\n");
}

void CEncampmentState::Resume()
{
	SDL_Log("CEncampmentState Resume\n");
}

void CEncampmentState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CEncampmentState HandleEvents\n");

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
					{
						game->Quit();
                    }break;
				} break;
		}
	}
}

void CEncampmentState::Update(CGameEngine* game)
{
    SDL_Log("CEncampmentState Update\n");

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

void CEncampmentState::Draw(CGameEngine* game)
{
    static int counter = 0;

    SDL_Log("CEncampmenttate Draw\n");

    //game->encampTexture = IMG_LoadTexture(game->renderer,"./assets/data/textures/encamp/encamp0.png");

    SDL_RenderCopy(game->renderer, game->encampTexture[counter], NULL, NULL);
    if( SDL_GetTicks() - startTime > 500)
    {
        counter++;
        startTime = SDL_GetTicks();
    }

    //MainMenuBackgroundTexture = NULL;

//    std::string imageLoaded = "./assets/data/textures/encamp/encamp" + std::to_string(counter) + ".png";
//
    int texW = 0;
    int texH = 0;
//    SDL_Texture* goblin = game->LoadTexture(imageLoaded.c_str(),255);
//    texW = 0;
//    texH = 0;
//    SDL_QueryTexture(goblin, NULL, NULL, &texW, &texH);
//
//    gRect = { 0,0, 128, 128 };
//    SDL_RenderCopy(game->renderer, goblin, NULL, &gRect);

//	SDL_Surface* surface = IMG_Load( imageLoaded.c_str() );
//	if( !surface )
//	{
//        exit(-1);
//	}
//
//	SDL_Texture* texture = SDL_CreateTextureFromSurface( game->renderer, surface );
//    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//    SDL_SetTextureAlphaMod( texture, 255 );
//    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
//    SDL_FreeSurface(surface);
//    SDL_DestroyTexture(texture);

    gSurface = TTF_RenderText_Blended(game->gameTitleFont, "A Viking Saga", White);
	if( !gSurface )
	{
        exit(-1);
	}
    gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
//    int texW = 0;
//    int texH = 0;
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
        SDL_Rect buttonPosition = { (game->current.w / 2) - (buttonWidth / 2), 500 + (Repeat*(buttonPosition.h+15)),buttonWidth,buttonHeight};

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
                if( MenuChoice == "BREAK UP CAMP")
                {
                    game->SActor.hitpoints_current = game->SActor.hitpoints_max;
                    game->ChangeState( CPlayState::Instance() );
                }
            }
        }
        ++Repeat;
    }
    if( counter > 3)
        counter = 0;
}

