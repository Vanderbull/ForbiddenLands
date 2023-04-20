#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "settingsmenustate.h"

CSettingsMenuState CSettingsMenuState::m_SettingsMenuState;

void CSettingsMenuState::Init()
{
	SDL_Log("CSettingsMenuState Init\n");

    MenuChoices.clear();
    MenuChoices.push_back("EXIT");
}

void CSettingsMenuState::Cleanup()
{
	SDL_Log("CSettingsMenuState Cleanup\n");
}

void CSettingsMenuState::Pause()
{
	SDL_Log("CSettingsMenuState Pause\n");
}

void CSettingsMenuState::Resume()
{
	SDL_Log("CSettingsMenuState Resume\n");
}

void CSettingsMenuState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CSettingsMenuState HandleEvents\n");

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

void CSettingsMenuState::Update(CGameEngine* game)
{
    SDL_Log("CSettingsMenuState Update\n");

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

void CSettingsMenuState::Draw(CGameEngine* game)
{
    SDL_Log("CSettingsMenuState Draw");
    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

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

        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, MenuChoice.c_str(), White);
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
            }

            SDL_PumpEvents();
            SDL_GetMouseState(NULL, NULL);
        }
        ++Repeat;
    }

    Mix_Volume(-1, -1);
    game->RenderText("Resolution: " + std::to_string(game->current.w) + " x " + std::to_string(game->current.h) + " @ " + std::to_string(SDL_BITSPERPIXEL(game->current.format)), game->Black, 50,50,48);
    game->RenderText("Volume: " + std::to_string( Mix_Volume(-1, -1) ), game->Black, 50,100,48);

}
