#include <stdio.h>
#include <SDL2/SDL.h>
#include "gamestate.h"
#include "gameengine.h"
#include "playstate.h"
#include "menustate.h"
#include "battlestate.h"

CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
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

    MenuChoices.clear();
    MenuChoices.push_back("PLAY STATE");
    MenuChoices.push_back("SAVE");
    MenuChoices.push_back("LOAD");
    MenuChoices.push_back("CHARACTER MANAGER");
    MenuChoices.push_back("SETTINGS");
    MenuChoices.push_back("EXIT");

    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 200);

	printf("CPlayState Init\n");
}

void CPlayState::Cleanup()
{
	printf("CPlayState Cleanup\n");
}

void CPlayState::Pause()
{
	printf("CPlayState Pause\n");
}

void CPlayState::Resume()
{
	printf("CPlayState Resume\n");
}

void CPlayState::HandleEvents(CGameEngine* game)
{
    printf("CPlayState HandleEvents\n");

	SDL_Event event;

	while (SDL_PollEvent(&event)!= 0)
    {
		switch (event.type)
		{
			case SDL_QUIT:
				game->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						game->Quit();
						break;
					case SDLK_m:
						game->PushState( CMenuState::Instance() );
						break;
                    case SDLK_d:
                        rotateClockWise();
                        break;
                    case SDLK_a:
                        rotateCounterClockWise();
                        break;
                    case SDLK_w:
                        {
                            if( Rotation == "N")
                                game->PlayerCoordinate.x--;
                            if( Rotation == "S")
                                game->PlayerCoordinate.x++;
                            if( Rotation == "W")
                                game->PlayerCoordinate.y--;
                            if( Rotation == "E")
                                game->PlayerCoordinate.y++;
                        }
                        break;
                    case SDLK_s:
                        game->PlayerCoordinate.y--;
                        break;
				}
				break;
		}
	}
}

void CPlayState::Update(CGameEngine* game)
{
    printf("CPlayState Update\n");

    ///--- Store the current information to the previous
    m_iPreviousCoordX=m_iCurrentCoordX;
    m_iPreviousCoordY=m_iCurrentCoordY;
    m_uPreviousMouseState=m_uCurrentMouseState;

    ///--- Update the current state of the mouse
    m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

    ///--- Set the wheel back to 0
    m_iWheelX=0;
    m_iWheelY=0;

    getCompassDirection();

    if(Rotation == "N")
        game->PlayerCoordinate.z = NORTH;
    if(Rotation == "S")
        game->PlayerCoordinate.z = SOUTH;
    if(Rotation == "W")
        game->PlayerCoordinate.z = WEST;
    if(Rotation == "E")
        game->PlayerCoordinate.z = EAST;
}

void CPlayState::Draw(CGameEngine* game)
{
    printf("CPlayState Draw\n");
    //TTF_Font* m_font = NULL;
    //m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 200);

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

    SDL_Rect test = {1500,0,500,500};
    SDL_RenderCopy(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][WEST], NULL, &test);
    test = {500,0,500,500};
    SDL_RenderCopy(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][EAST], NULL, &test);
    test = {1000,0,500,500};
    SDL_RenderCopy(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][SOUTH], NULL, &test);
    test = {1000,500,500,500};
    SDL_RenderCopy(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][NORTH], NULL, &test);
    test = {1000,1000,500,500};
    SDL_RenderCopy(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][game->PlayerCoordinate.z], NULL, &test);

    gSurface = TTF_RenderText_Blended(m_font, std::to_string(game->PlayerCoordinate.x).c_str(), Black);
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

    gSurface = TTF_RenderText_Blended(m_font, std::to_string(game->PlayerCoordinate.y).c_str(), Black);
	if( !gSurface )
	{
        exit(-1);
	}
    gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
    texW = 0;
    texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { game->current.w / 2 - (texW / 2) + 200,200- (texH / 2), texW, texH };
    SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);

    gSurface = TTF_RenderText_Blended(m_font, std::to_string(game->PlayerCoordinate.z).c_str(), Black);
	if( !gSurface )
	{
        exit(-1);
	}
    gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
    texW = 0;
    texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { game->current.w / 2 - (texW / 2) + 400,200- (texH / 2), texW, texH };
    SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);

    gSurface = TTF_RenderText_Blended(m_font, Rotation.c_str(), Black);
	if( !gSurface )
	{
        exit(-1);
	}
    gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
    texW = 0;
    texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { game->current.w / 2 - (texW / 2) + 600,200- (texH / 2), texW, texH };
    SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);

//    TTF_CloseFont(m_font);
//    m_font = NULL;
}
