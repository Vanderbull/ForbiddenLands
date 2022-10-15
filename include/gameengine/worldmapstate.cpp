#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>

#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "playstate.h"
#include "worldmapstate.h"

CWorldMapState CWorldMapState::m_WorldMapState;

void CWorldMapState::Init()
{
	SDL_Log("CWorldMapState Init\n");
}

void CWorldMapState::Cleanup()
{
	SDL_Log("CWorldMapState Cleanup\n");
}

void CWorldMapState::Pause()
{
	SDL_Log("CWorldMapState Pause\n");
}

void CWorldMapState::Resume()
{
	SDL_Log("CWorldMapState Resume\n");
}

void CWorldMapState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CWorldMapState");
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
                        game->ChangeState( CPlayState::Instance() );
						break;
				}
				break;
		}
	}
}

void CWorldMapState::Update(CGameEngine* game)
{
    SDL_Log("CWorldMapState Update");
}

void CWorldMapState::Draw(CGameEngine* game)
{
    SDL_Log("CWorldMapState Draw");
    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );

    SDL_RenderClear(game->renderer);

	SDL_Texture* texture = game->LoadTexture("./assets/data/textures/jordenheim.jpg",255);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( texture, 255 );
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);

    // Sweden
    SDL_Rect Kustenstad{0,0,128,128};
    SDL_Rect Vallentuna{256,0,128,128};
    SDL_Rect Mora{512,0,128,128};
    //Danmark
    SDL_Rect Marlmo{0,256,128,128};
    SDL_Rect Saeby{256,256,128,128};
    SDL_Rect Odense{512,256,128,128};
    SDL_Rect Zealfort{768,256,128,128};
    //Norway
    SDL_Rect Trollheim{0,512,128,128};
    SDL_Rect Trondeland{256,512,128,128};
    SDL_Rect Aerendal{512,512,128,128};
    //Finland
    SDL_Rect Kiiri{0,768,128,128};
    SDL_Rect Kamilarvi{256,768,128,128};
    SDL_Rect Muoni{512,768,128,128};

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);

    // Sweden
    SDL_RenderFillRect(game->renderer, &Kustenstad);
    SDL_RenderFillRect(game->renderer, &Vallentuna);
    SDL_RenderFillRect(game->renderer, &Mora);
    //Danmark
    SDL_RenderFillRect(game->renderer, &Marlmo);
    SDL_RenderFillRect(game->renderer, &Saeby);
    SDL_RenderFillRect(game->renderer, &Odense);
    SDL_RenderFillRect(game->renderer, &Zealfort);
    //Norway
    SDL_RenderFillRect(game->renderer, &Trollheim);
    SDL_RenderFillRect(game->renderer, &Trondeland);
    SDL_RenderFillRect(game->renderer, &Aerendal);
    //Finland
    SDL_RenderFillRect(game->renderer, &Kiiri);
    SDL_RenderFillRect(game->renderer, &Kamilarvi);
    SDL_RenderFillRect(game->renderer, &Muoni);

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    if( SDL_PointInRect(&mousePosition, &Kustenstad) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &Kustenstad);

        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            game->RenderText("KUSTENSTAD", White, Kustenstad.x, Kustenstad.y,48);
        }
    }
}
