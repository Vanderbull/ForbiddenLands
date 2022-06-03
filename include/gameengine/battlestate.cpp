
#include <stdio.h>

#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "battlestate.h"

CBattleState CBattleState::m_BattleState;

void CBattleState::Init()
{
   //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    gameTitleFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 24);

    if(!gameTitleFont)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

	SDL_Surface* temp = SDL_LoadBMP("menu.bmp");

	SDL_FreeSurface(temp);

	printf("CBattleState Init\n");
}

void CBattleState::Cleanup()
{
	printf("CBattleState Cleanup\n");
}

void CBattleState::Pause()
{
	printf("CBattleState Pause\n");
}

void CBattleState::Resume()
{
	printf("CBattleState Resume\n");
}

void CBattleState::HandleEvents(CGameEngine* game)
{
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
				}
				break;
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

    MainMenuBackgroundTexture = NULL;

	SDL_Surface* surface = IMG_Load( "./images/battleBackground.png" );
	if( !surface )
	{
        SDL_Log("Loading surface ./images/BattleBackground.png failed\n");
        exit(EXIT_FAILURE);
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( game->renderer, surface );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( texture, 255 );
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    gSurface = TTF_RenderText_Blended(gameTitleFont, "Forbidden Lands", White);
	if( !gSurface )
	{
        SDL_Log("RenderText_Blended for gameTitleFont failed");
        exit(EXIT_FAILURE);
	}
    gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    SDL_Rect buttonPosition = { 0, 0,500,500};

    gRect = { buttonPosition.x + (buttonWidth / 2 - (texW / 2)), buttonPosition.y + (buttonHeight / 2) - (texH / 2), texW, texH };
    SDL_RenderCopy(game->renderer, gTexture, NULL, &buttonPosition);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);


    for(auto MenuChoice : MenuChoices)
    {
        SDL_Rect buttonPosition = { (1920 / 2) - (buttonWidth / 2), 500 + (Repeat*(buttonPosition.h+15)),buttonWidth,buttonHeight};

        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderDrawRect(game->renderer,&buttonPosition);

        gSurface = TTF_RenderText_Blended(gameTitleFont, MenuChoice.c_str(), White);
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

        //Destroy resources
        SDL_FreeSurface(gSurface);
        SDL_DestroyTexture(gTexture);

        SDL_Point mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);

            SDL_PumpEvents();
            //state = SDL_GetMouseState(NULL, NULL);
            if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
            {
                if( SettingsMenu != 1)
                {
                    if(MenuChoice == "PLAY")
                    {
                        activeView = 1;
                        LoadMenu = 0;
                        SaveMenu = 0;
                        CreateCharacter = 0;
                    }
                    if(MenuChoice == "SAVE")
                    {
                        SaveMenu = 1;
                        LoadMenu = 0;
                        SettingsMenu = 0;
                        CreateCharacter = 0;
                    }
                    if(MenuChoice == "LOAD")
                    {
                        SaveMenu = 0;
                        LoadMenu = 1;
                        SettingsMenu = 0;
                        CreateCharacter = 0;
                    }
                    if(MenuChoice == "CHARACTER MANAGER")
                    {
                        SaveMenu = 0;
                        LoadMenu = 0;
                        SettingsMenu = 0;
                        CreateCharacter = 1;
                    }
                    if(MenuChoice == "SETTINGS")
                    {
                        SettingsMenu = 1;
                        SaveMenu = 0;
                        LoadMenu = 0;
                        CreateCharacter = 0;
                    }
                    if(MenuChoice == "EXIT")
                    {
                        LoadMenu = 0;
                        SaveMenu = 0;
                        SettingsMenu = 0;
                        CreateCharacter = 0;
                        quit = 1;
                    }
                }
            }
        }
        ++Repeat;
    }
}
