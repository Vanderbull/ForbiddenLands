#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
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
					case SDLK_SPACE:
						break;

					case SDLK_ESCAPE:
						game->Quit();
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

	SDL_Texture* texture = game->LoadTexture("./images/menus/mainmenu.jpg",255);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( texture, 255 );
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
}
