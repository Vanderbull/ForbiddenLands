
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>

#include "gameengine.h"
#include "gamestate.h"
#include "introstate.h"
#include "playstate.h"

CIntroState CIntroState::m_IntroState;

void CIntroState::Init()
{
	printf("CIntroState Init\n");
}

void CIntroState::Cleanup()
{
	printf("CIntroState Cleanup\n");
}

void CIntroState::Pause()
{
	printf("CIntroState Pause\n");
}

void CIntroState::Resume()
{
	printf("CIntroState Resume\n");
}

void CIntroState::HandleEvents(CGameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_SPACE:
						game->ChangeState( CPlayState::Instance() );
						break;

					case SDLK_ESCAPE:
						game->Quit();
						break;
				}
				break;
		}
	}
}

void CIntroState::Update(CGameEngine* game)
{
}

void CIntroState::Draw(CGameEngine* game)
{
    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );

    SDL_RenderClear(game->renderer);
    MainMenuBackgroundTexture = NULL;

	SDL_Surface* surface = IMG_Load( "./images/menus/mainmenu.jpg" );
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
}
