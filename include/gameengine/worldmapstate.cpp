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

    InRect(mousePosition,Kustenstad, game,"Kustenstad");
    InRect(mousePosition,Vallentuna, game,"Vallentuna");
    InRect(mousePosition,Mora, game,"Mora");
    InRect(mousePosition,Marlmo, game,"Marlmo");
    InRect(mousePosition,Saeby, game,"Saeby");
    InRect(mousePosition,Odense, game,"Odense");
    InRect(mousePosition,Zealfort, game,"Zealfort");
    InRect(mousePosition,Trollheim, game,"Trollheim");
    InRect(mousePosition,Trondeland, game,"Trondeland");
    InRect(mousePosition,Aerendal, game,"Aerendal");
    InRect(mousePosition,Kiiri, game,"Kiiri");
    InRect(mousePosition,Kamilarvi, game,"Kamilarvi");
    InRect(mousePosition,Muoni, game,"Muoni");

    SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(game->renderer, &game->CurrentLocation);
}
