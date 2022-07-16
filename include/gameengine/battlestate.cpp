#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "battlestate.h"

using namespace std::chrono;

CBattleState CBattleState::m_BattleState;

void CBattleState::Init()
{
    if( TTF_Init() == -1 )
    {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    gameTitleFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 24);

    if(!gameTitleFont)
    {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

	SDL_Surface* temp = SDL_LoadBMP("menu.bmp");

	SDL_FreeSurface(temp);

	std::cout << "CBattleState Init\n";
}

void CBattleState::Cleanup()
{
	std::cout << "CBattleState Pause\n";
}

void CBattleState::Pause()
{
	std::cout << "CBattleState Pause\n";
}

void CBattleState::Resume()
{
	std::cout << "CBattleState Resume\n";
}

void CBattleState::HandleEvents(CGameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
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
                        game->PopState();
                        break;
                } break;
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
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 200);

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

    MainMenuBackgroundTexture = NULL;

	SDL_Surface* surface = IMG_Load( "./images/wireframe new inventory.png" );
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

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    // ROW 1 START
    SDL_Rect buttonPosition = { 226, 407,119,119};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
    // ROW 1 SEND
    buttonPosition.x = 226;
    buttonPosition.y = buttonPosition.y+244;
    buttonPosition.w = 119;
    buttonPosition.h = 119;

     SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);


    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
    buttonPosition.x = 226;
    buttonPosition.y = buttonPosition.y+244;
    buttonPosition.w = 119;
    buttonPosition.h = 119;

     SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);


    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
    buttonPosition.x = 226;
    buttonPosition.y = buttonPosition.y+244;
    buttonPosition.w = 119;
    buttonPosition.h = 119;

     SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
        SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = buttonPosition.x + 167;
    SDL_RenderFillRect(game->renderer, &buttonPosition);


    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 89;
    buttonPosition.y = 322;
    buttonPosition.w = 64;
    buttonPosition.h = 64;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 89;
    buttonPosition.y = 423;
    buttonPosition.w = 64;
    buttonPosition.h = 64;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 89;
    buttonPosition.y = 525;
    buttonPosition.w = 64;
    buttonPosition.h = 64;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    // WEAPONS
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 1282;
    buttonPosition.y = 349;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 1282+160;
    buttonPosition.y = 349;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 1282;
    buttonPosition.y = 536;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 1282+160;
    buttonPosition.y = 536;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

     //ARMOUR
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2241;
    buttonPosition.y = 356;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2161;
    buttonPosition.y = 543;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2321;
    buttonPosition.y = 543;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2161;
    buttonPosition.y = 729;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2321;
    buttonPosition.y = 729;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    // OTHER

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);

    buttonPosition.x = 2157;
    buttonPosition.y = 981;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = 2327;
    buttonPosition.y = 981;
    buttonPosition.w = 120;
    buttonPosition.h = 120;
    SDL_RenderFillRect(game->renderer, &buttonPosition);

    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);
    }
//  SDL_Vertex vert[8];
//
//  // center
//  vert[0].position.x = 400;
//  vert[0].position.y = 150;
//  vert[0].color.r = 255;
//  vert[0].color.g = 0;
//  vert[0].color.b = 0;
//  vert[0].color.a = 255;
//
//  // left
//  vert[1].position.x = 200;
//  vert[1].position.y = 450;
//  vert[1].color.r = 0;
//  vert[1].color.g = 0;
//  vert[1].color.b = 255;
//  vert[1].color.a = 255;
//
//  // right
//  vert[2].position.x = 600;
//  vert[2].position.y = 450;
//  vert[2].color.r = 0;
//  vert[2].color.g = 255;
//  vert[2].color.b = 0;
//  vert[2].color.a = 255;
//
//  // right
//  vert[3].position.x = 600;
//  vert[3].position.y = 450;
//  vert[3].color.r = 0;
//  vert[3].color.g = 255;
//  vert[3].color.b = 0;
//  vert[3].color.a = 255;
//
//
//static const SDL_Vertex g_vertex_buffer_data[] = {
//    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
//    -1.0f,-1.0f, 1.0f,
//    -1.0f, 1.0f, 1.0f, // triangle 1 : end
//    1.0f, 1.0f,-1.0f, // triangle 2 : begin
//    -1.0f,-1.0f,-1.0f,
//    -1.0f, 1.0f,-1.0f, // triangle 2 : end
//    1.0f,-1.0f, 1.0f,
//    -1.0f,-1.0f,-1.0f,
//    1.0f,-1.0f,-1.0f,
//    1.0f, 1.0f,-1.0f,
//    1.0f,-1.0f,-1.0f,
//    -1.0f,-1.0f,-1.0f,
//    -1.0f,-1.0f,-1.0f,
//    -1.0f, 1.0f, 1.0f,
//    -1.0f, 1.0f,-1.0f,
//    1.0f,-1.0f, 1.0f,
//    -1.0f,-1.0f, 1.0f,
//    -1.0f,-1.0f,-1.0f,
//    -1.0f, 1.0f, 1.0f,
//    -1.0f,-1.0f, 1.0f,
//    1.0f,-1.0f, 1.0f,
//    1.0f, 1.0f, 1.0f,
//    1.0f,-1.0f,-1.0f,
//    1.0f, 1.0f,-1.0f,
//    1.0f,-1.0f,-1.0f,
//    1.0f, 1.0f, 1.0f,
//    1.0f,-1.0f, 1.0f,
//    1.0f, 1.0f, 1.0f,
//    1.0f, 1.0f,-1.0f,
//    -1.0f, 1.0f,-1.0f,
//    1.0f, 1.0f, 1.0f,
//    -1.0f, 1.0f,-1.0f,
//    -1.0f, 1.0f, 1.0f,
//    1.0f, 1.0f, 1.0f,
//    -1.0f, 1.0f, 1.0f,
//    1.0f,-1.0f, 1.0f
//};
//    const std::vector< SDL_Vertex > verts =
//    {
//        { SDL_FPoint{ 400, 150 }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
//        { SDL_FPoint{ 200, 450 }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
//        { SDL_FPoint{ 600, 450 }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
//    };
//
//#define NUM_RECTANGLE_VERTEX 6
//const SDL_Vertex backFace[NUM_RECTANGLE_VERTEX] = {
//	{
//		{ 80.f, 20.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f, 80.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f, 20.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//
//	{
//		{ 80.f, 80.f },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f, 80.f },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f, 20.f },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	}
//};
//
//const SDL_Vertex frontFace[NUM_RECTANGLE_VERTEX] = {
//	{
//		{ 80.f*2, 20.f*2 },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 80.f*2 },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f*2, 20.f*2 },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//
//	{
//		{ 80.f*2, 80.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f*2, 80.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f*2, 20.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	}
//};
//
//const SDL_Vertex bottomFace[NUM_RECTANGLE_VERTEX] = {
//	{
//		{ 80.f, 80.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f, 80.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 80.f*2 },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//
//	{
//		{ 120.f, 80.f },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f*2, 80.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 80.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	}
//};
//const SDL_Vertex leftFace[NUM_RECTANGLE_VERTEX] = {
//	{
//		{ 80.f, 20.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 20.f*2 },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 80.f*2 },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//
//	{
//		{ 80.f, 80.f },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 20.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 80.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	}
//};
//const SDL_Vertex rightFace[NUM_RECTANGLE_VERTEX] = {
//	{
//		{ 80.f, 80.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f, 80.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 80.f*2 },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//
//	{
//		{ 120.f, 80.f },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f*2, 80.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 80.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	}
//};
//const SDL_Vertex topFace[NUM_RECTANGLE_VERTEX] = {
//	{
//		{ 80.f, 20.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f, 20.f },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 20.f*2 },
//		{ 93, 157, 255, 0xFF },
//		{ 0.f, 0.f }
//	},
//
//	{
//		{ 80.f, 80.f },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 120.f*2, 20.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	},
//	{
//		{ 80.f*2, 20.f*2 },
//		{ 22, 106, 197, 0xFF },
//		{ 0.f, 0.f }
//	}
//};
//  SDL_RenderGeometry(game->renderer, NULL, g_vertex_buffer_data, 36, NULL, 0);
//   SDL_RenderGeometry(game->renderer, NULL, vert, 3, NULL, 0);
//SDL_RenderGeometry(game->renderer, NULL, backFace, NUM_RECTANGLE_VERTEX, NULL, 0);
//SDL_RenderGeometry(game->renderer, NULL, bottomFace, NUM_RECTANGLE_VERTEX, NULL, 0);
//SDL_RenderGeometry(game->renderer, NULL, leftFace, NUM_RECTANGLE_VERTEX, NULL, 0);
//SDL_RenderGeometry(game->renderer, NULL, rightFace, NUM_RECTANGLE_VERTEX, NULL, 0);
//SDL_RenderGeometry(game->renderer, NULL, topFace, NUM_RECTANGLE_VERTEX, NULL, 0);
//SDL_RenderGeometry(game->renderer, NULL, frontFace, NUM_RECTANGLE_VERTEX, NULL, 0);

}
