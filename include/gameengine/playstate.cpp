#include <stdio.h>
#include <SDL2/SDL.h>
#include "gamestate.h"
#include "gameengine.h"
#include "playstate.h"
#include "menustate.h"
#include "battlestate.h"
#include "characterstate.h"
#include "shopstate.h"

CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
    if( TTF_Init() == -1 )
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 200);
    if(!m_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    breadFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 24);
    if(!breadFont)
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
						game->ChangeState( CMenuState::Instance() );
						break;
					case SDLK_m:
                        game->ChangeState( CShopState::Instance() );
						//game->PushState( CCharacterState::Instance() );
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
                                if( game->PlayerCoordinate.y > 0 )
                                    game->PlayerCoordinate.y--;
                            if( Rotation == "S")
                                if( game->PlayerCoordinate.y < 15 )
                                    game->PlayerCoordinate.y++;
                            if( Rotation == "W")
                                if( game->PlayerCoordinate.x > 0 )
                                    game->PlayerCoordinate.x--;
                            if( Rotation == "E")
                                if( game->PlayerCoordinate.x < 15 )
                                    game->PlayerCoordinate.x++;
                        }
                        break;
                    case SDLK_s:
                        {
                            if( Rotation == "N")
                                if( game->PlayerCoordinate.y > 0 )
                                    game->PlayerCoordinate.y++;
                            if( Rotation == "S")
                                if( game->PlayerCoordinate.y < 15 )
                                    game->PlayerCoordinate.y--;
                            if( Rotation == "W")
                                if( game->PlayerCoordinate.x > 0 )
                                    game->PlayerCoordinate.x++;
                            if( Rotation == "E")
                                if( game->PlayerCoordinate.x < 15 )
                                    game->PlayerCoordinate.x--;
                        }
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

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

    SDL_Rect test = {0,500,500,500};
    //SDL_RenderCopy(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][WEST], NULL, &test);
    test = {1000,500,500,500};
    //SDL_RenderCopy(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][EAST], NULL, &test);

    test = {500,1000,500,500};
    SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_NONE);//(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    //SDL_RenderCopyEx(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][SOUTH], NULL, &test, 0, NULL, flip);

    //SDL_RenderCopy(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][SOUTH], NULL, &test);
    test = {500,0,500,500};
    //flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    //SDL_RenderCopyEx(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][NORTH], NULL, &test, 0, NULL, flip);
    //SDL_RenderCopy(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][NORTH], NULL, &test);


    test = {500,500,500,500};
    SDL_RenderCopyEx(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][game->PlayerCoordinate.z], NULL, NULL, 0, NULL, flip);
//    static int rotate = 0;
//    if( rotate >359)
//        rotate = 0;
//    SDL_RenderCopyEx(game->renderer, game->mapTexture[game->PlayerCoordinate.x][game->PlayerCoordinate.y][game->PlayerCoordinate.z], NULL, NULL,rotate,NULL,flip);
//    rotate++;
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

    gSurface = TTF_RenderText_Blended(breadFont, game->mapTextureFile[game->PlayerCoordinate.x][game->PlayerCoordinate.y][game->PlayerCoordinate.z].c_str(), Black);
	if( !gSurface )
	{
        exit(-1);
	}
    gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
    texW = 0;
    texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { 0,0, texW, texH };
    SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);

    renderDaytime(game);
    renderCompass(game);
    renderMinimap(game);

    North = game->LoadTexture("./images/compass/north.png",255);
    West = game->LoadTexture("./images/compass/west.png",255);
    South = game->LoadTexture("./images/compass/south.png",255);
    East = game->LoadTexture("./images/compass/east.png",255);

    renderMinimapCharacterLocation(game);

    static int goblinmovey = 0;
    SDL_Texture* goblin = game->LoadTexture("./images/goblin.png",255);
        texW = 0;
    texH = 0;
    SDL_QueryTexture(goblin, NULL, NULL, &texW, &texH);

    gRect = { game->current.w / 2 - texW/2,game->current.h / 2 + texH*2+ goblinmovey, texW, texH };
    SDL_RenderCopy(game->renderer, goblin, NULL, &gRect);
    if(goblinmovey < game->current.h - texH)
        goblinmovey++;

    SDL_Rect left_weapon = {0,game->current.h - 120, 120,120};
    SDL_Rect right_weapon = {game->current.w - 120,game->current.h - 120, 120,120};
    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0,255);
    SDL_RenderFillRect(game->renderer, &left_weapon);
    SDL_RenderFillRect(game->renderer, &right_weapon);
    game->renderDaytime();
}
