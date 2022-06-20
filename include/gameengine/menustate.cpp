#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "createcharacterstate.h"
#include "loadmenustate.h"
#include "savemenustate.h"
#include "menustate.h"

CMenuState CMenuState::m_MenuState;

void CMenuState::Init()
{
    if( TTF_Init() == -1 )
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(-1);
    }

    gameTitleFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 24);

    if(!gameTitleFont)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(-1);
    }

	SDL_Surface* temp = SDL_LoadBMP("menu.bmp");

	SDL_FreeSurface(temp);

    MenuChoices.clear();
    MenuChoices.push_back("PLAY");
    MenuChoices.push_back("SAVE");
    MenuChoices.push_back("LOAD");
    MenuChoices.push_back("CHARACTER MANAGER");
    MenuChoices.push_back("SETTINGS");
    MenuChoices.push_back("EXIT");

	printf("CMenuState Init\n");
}

void CMenuState::Cleanup()
{
	printf("CMenuState Cleanup\n");
}

void CMenuState::Pause()
{
	printf("CMenuState Pause\n");
}

void CMenuState::Resume()
{
	printf("CMenuState Resume\n");
}

void CMenuState::HandleEvents(CGameEngine* game)
{
    printf("CMenuState HandleEvents\n");

	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						game->PopState();
						break;
				} break;
		}
	}
}

void CMenuState::Update(CGameEngine* game)
{
    printf("CMenuState Update\n");

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

void CMenuState::Draw(CGameEngine* game)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 200);

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

    MainMenuBackgroundTexture = NULL;

	SDL_Surface* surface = IMG_Load( "./images/battleBackground.png" );
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

    gSurface = TTF_RenderText_Blended(m_font, "Forbidden Lands", White);
	if( !gSurface )
	{
        exit(-1);
	}
    gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
    int texW = 0;
    int texH = 0;
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

        gSurface = TTF_RenderText_Blended(gameTitleFont, MenuChoice.c_str(), White);
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { buttonPosition.x + (buttonWidth / 2) - (texW / 2), buttonPosition.y + (buttonHeight / 2) - (texH / 2), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

        //Destroy resources
        SDL_FreeSurface(gSurface);
        SDL_DestroyTexture(gTexture);

        SDL_Point mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(game->renderer, &buttonPosition);

            if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
            {
                if( MenuChoice == "LOAD")
                    game->ChangeState( CLoadMenuState::Instance() );
                if( MenuChoice == "SAVE")
                    game->ChangeState( CSaveMenuState::Instance() );
                if( MenuChoice == "PLAY")
                    game->ChangeState( CPlayState::Instance() );
                if( MenuChoice == "CHARACTER MANAGER")
                    game->ChangeState( CCreateCharacterState::Instance() );
            }

            SDL_PumpEvents();
            SDL_GetMouseState(NULL, NULL);
            if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
            {
                if( game->SettingsMenu != 1)
                {
                    if(MenuChoice == "PLAY")
                    {
                        game->activeView = 1;
                        game->LoadMenu = 0;
                        game->SaveMenu = 0;
                        game->CreateCharacter = 0;
                    }
                    if(MenuChoice == "SAVE")
                    {
                        game->SaveMenu = 1;
                        game->LoadMenu = 0;
                        game->SettingsMenu = 0;
                        game->CreateCharacter = 0;
                    }
                    if(MenuChoice == "LOAD")
                    {
                        game->SaveMenu = 0;
                        game->LoadMenu = 1;
                        game->SettingsMenu = 0;
                        game->CreateCharacter = 0;
                    }
                    if(MenuChoice == "CHARACTER MANAGER")
                    {
                        game->SaveMenu = 0;
                        game->LoadMenu = 0;
                        game->SettingsMenu = 0;
                        game->CreateCharacter = 1;
                    }
                    if(MenuChoice == "SETTINGS")
                    {
                        game->SettingsMenu = 1;
                        game->SaveMenu = 0;
                        game->LoadMenu = 0;
                        game->CreateCharacter = 0;
                    }
                    if(MenuChoice == "EXIT")
                    {
                        game->LoadMenu = 0;
                        game->SaveMenu = 0;
                        game->SettingsMenu = 0;
                        game->CreateCharacter = 0;

                        // Destroy resources
                        //SDL_DestroyTexture(currentViewTexture);
                        //SDL_DestroyTexture(gTexture);
                        //atexit(SDL_Quit);
                        //quit = 1;
                    }
                }
            }
        }
        ++Repeat;
    }

    TTF_CloseFont(m_font);
    m_font = NULL;
}
