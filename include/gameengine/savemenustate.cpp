#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "savemenustate.h"

CSaveMenuState CSaveMenuState::m_SaveMenuState;

void CSaveMenuState::Init()
{
	SDL_Log("CSaveMenuState Init\n");

    MenuChoices.clear();

    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir("./assets/data/savegames");
    if (dpdf != NULL)
    {
        while (epdf = readdir(dpdf))
        {
            std::string filename;
            filename = epdf->d_name;
            std::cout << filename << std::endl;
            if( filename == "dummy" || filename == ".." || filename == ".")
            {
            }
            else if (epdf->d_name[strlen(epdf->d_name)-1] != '~')
            {
                MenuChoices.push_back(std::string(epdf->d_name));
            }
        }
    }

    MenuChoices.push_back("NEW SAVE");
    MenuChoices.push_back("EXIT");
}

void CSaveMenuState::Cleanup()
{
	SDL_Log("CSaveMenuState Cleanup\n");
}

void CSaveMenuState::Pause()
{
	SDL_Log("CSaveMenuState Pause\n");
}

void CSaveMenuState::Resume()
{
	SDL_Log("CSaveMenuState Resume\n");
}

void CSaveMenuState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CSaveMenuState HandleEvents\n");

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
    SDL_Log("CSaveMenuState Update\n");

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
    SDL_Log("CSaveMentState Draw");

//	SDL_Texture* texture = game->LoadTexture("./assets/data/textures/menus/menu_backdrop.png",255);
//    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
//    SDL_DestroyTexture(texture);

    gSurface = TTF_RenderText_Blended(game->gameTitleFont, "Save", game->White);
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

    vector<string>::iterator q = MenuChoices.begin();

    for(auto MenuChoice : MenuChoices)
    {
        SDL_Rect buttonPosition = { (game->current.w / 2) - (buttonWidth / 2), 300 + (Repeat*(buttonPosition.h+15)),buttonWidth,buttonHeight};

        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderDrawRect(game->renderer,&buttonPosition);

        SDL_Point mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        SDL_Rect buttonPositionDelete = { (game->current.w / 2) - (buttonWidth / 2 ) + buttonWidth, 300 + (Repeat*(buttonPosition.h+15)),buttonWidth/3,buttonHeight};

        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
        SDL_RenderFillRect(game->renderer, &buttonPositionDelete);
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderDrawRect(game->renderer,&buttonPositionDelete);

        if( SDL_PointInRect(&mousePosition, &buttonPositionDelete) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
            {
                if( MenuChoice != "EXIT" || MenuChoice != "NEW SAVE")
                {
                    std::string file_removal = "./assets/data/savegames/" + *q;
                    vector<string>::iterator p = MenuChoices.erase(q);
                    int status = remove(file_removal.c_str());
                    if( status == 0 )
                        SDL_Log("Deleted file");
                    else
                        SDL_Log("Failed to delete file");
                }
            }
        }
        q++;

        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, MenuChoice.c_str(), game->White);
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { buttonPosition.x + (buttonWidth / 2) - (texW / 2), buttonPosition.y + (buttonHeight / 2) - (texH / 2), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

        //Destroy resources
        SDL_FreeSurface(gSurface);
        SDL_DestroyTexture(gTexture);

        if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(game->renderer, &buttonPosition);

            if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
            {
                if( MenuChoice == "EXIT")
                    game->ChangeState( CMenuState::Instance() );
                else if( MenuChoice == "NEW SAVE")
                    savingGameData("./assets/data/savegames/new.dat",game);
                else
                    savingGameData(MenuChoice.c_str(),game);
            }

            SDL_PumpEvents();
            SDL_GetMouseState(NULL, NULL);
        }
        ++Repeat;
    }
}
