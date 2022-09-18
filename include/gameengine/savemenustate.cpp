#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "savemenustate.h"

CSaveMenuState CSaveMenuState::m_SaveMenuState;

void CSaveMenuState::Init()
{
    if( TTF_Init() == -1 )
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    gameBreadTextFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 24);

    if(!gameBreadTextFont)
    {
        printf("TTF_OpenFont savemenuState: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    gameTitleFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 200);

    if(!gameTitleFont)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    MenuChoices.clear();
    DIR *dpdf;
    struct dirent *epdf;
    std::vector<std::string> filenames;
    dpdf = opendir("./data/savegames");
    if (dpdf != NULL) {
       while (epdf = readdir(dpdf))
       {
             if (epdf->d_name[0] != '.' && epdf->d_name[strlen(epdf->d_name)-1] != '~' )
            {
                MenuChoices.push_back(std::string(epdf->d_name));
            }

       }
    }
    MenuChoices.push_back("NEW SAVE");
    MenuChoices.push_back("EXIT");

	printf("CSaveMenuState Init\n");
}

void CSaveMenuState::Cleanup()
{
	printf("CSaveMenuState Cleanup\n");
}

void CSaveMenuState::Pause()
{
	printf("CSaveMenuState Pause\n");
}

void CSaveMenuState::Resume()
{
	printf("CSaveMenuState Resume\n");
}

void CSaveMenuState::HandleEvents(CGameEngine* game)
{
    printf("CSaveMenuState HandleEvents\n");

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

void CSaveMenuState::Update(CGameEngine* game)
{
    printf("CSaveMenuState Update\n");

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

void CSaveMenuState::Draw(CGameEngine* game)
{
    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

	SDL_Texture* texture = game->LoadTexture("./images/battleBackground.png",255);
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);

    gSurface = TTF_RenderText_Blended(gameTitleFont, "Save", White);
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
        SDL_Rect buttonPosition = { (game->current.w / 2) - (buttonWidth / 2), 300 + (Repeat*(buttonPosition.h+15)),buttonWidth,buttonHeight};

        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderDrawRect(game->renderer,&buttonPosition);

        gSurface = TTF_RenderText_Blended(gameBreadTextFont, MenuChoice.c_str(), White);
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
                if( MenuChoice == "EXIT")
                    game->ChangeState( CMenuState::Instance() );
                else if( MenuChoice == "NEW SAVE")
                    savingGameData("./data/savegames/new.dat");
                else
                    savingGameData(MenuChoice.c_str());
            }

            SDL_PumpEvents();
            SDL_GetMouseState(NULL, NULL);
        }
        ++Repeat;
    }
}
