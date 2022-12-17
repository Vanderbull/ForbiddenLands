#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "playstate.h"
#include "gameoverstate.h"
#include "crapstate.h"

using namespace std::chrono;

CCrapState CCrapState::m_CrapState;

void CCrapState::Init()
{
    SDL_Log("CCrapState Init\n");
}

void CCrapState::Cleanup()
{
	SDL_Log("CCrapState Pause\n");
}

void CCrapState::Pause()
{
	SDL_Log("CCrapState Pause\n");
}

void CCrapState::Resume()
{
	SDL_Log("CCrapState Resume\n");
}

void CCrapState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CCrapState HandleEvents\n");
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
                        game->ChangeState(CPlayState::Instance());
                        break;
                } break;
		}
	}
}

void CCrapState::Update(CGameEngine* game)
{
    SDL_Log("CCrapState Update\n");
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

void CCrapState::Draw(CGameEngine* game)
{
    SDL_Log("CCrapState Draw");

    SDL_Rect AttackButtonPosition = { 0, 0, 64, 64};
    SDL_Rect DefendButtonPosition = { 65, 0, 64, 64};

    SDL_SetRenderDrawColor( game->renderer, 0, 0, 0, 255 );
    SDL_RenderClear(game->renderer);

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderFillRect(game->renderer, &AttackButtonPosition);
    SDL_RenderFillRect(game->renderer, &DefendButtonPosition);

    game->RenderText("A", game->Black, AttackButtonPosition.x,AttackButtonPosition.y,24);
    game->RenderText("D", game->Black, DefendButtonPosition.x,DefendButtonPosition.y,24);

    int texW = 0;
    int texH = 0;
    int ScalingFactor = 4;
    SDL_Texture* goblin = game->LoadTexture("./assets/data/textures/goblin.png",255);
    SDL_QueryTexture(goblin, NULL, NULL, &texW, &texH);

    SDL_Rect gRect = { game->current.w / 2 - texW * ScalingFactor / 3,game->current.h / 2 - texH * ScalingFactor / 2, texW*ScalingFactor, texH*ScalingFactor };
    SDL_RenderCopy(game->renderer, goblin, NULL, &gRect);

    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    SDL_Rect buttonPosition = { 0, (0.33*game->current.h) / 2,256,0.66*game->current.h};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    game->RenderText("NPC HP: " + std::to_string(game->SNpc.hitpoints_current) + " / " + std::to_string(game->SNpc.hitpoints_max), White, buttonPosition.x,buttonPosition.y,24);

    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    buttonPosition.x = game->current.w - 256;
    SDL_RenderFillRect(game->renderer, &buttonPosition);
    game->RenderText("PC HP: " + std::to_string(game->SActor.hitpoints_current) + " / " + std::to_string(game->SActor.hitpoints_max), White, buttonPosition.x,buttonPosition.y,24);

    if(!m_PlayerActive)
    {
        if(m_PlayerDefending)
        {
            game->SActor.hitpoints_current;
            m_PlayerDefending = false;
        }
        else
        {
            m_PlayerDefending = false;
            game->SActor.hitpoints_current -= GenerateNumber(0,3);
        }

        m_PlayerActive = true;
        if(game->SActor.hitpoints_current <= 0)
        {
            m_PlayerActive = true;
            game->SNpc.hitpoints_current = game->SNpc.hitpoints_max;
            game->ChangeState(CGameoverState::Instance());
        }
    }
    else if(m_PlayerActive)
    if( SDL_PointInRect(&mousePosition, &AttackButtonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);
        SDL_RenderFillRect(game->renderer, &AttackButtonPosition);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            Mix_PlayChannel(-1, game->_sample[3], 0);
            //Mix_PlayChannel(-1, game->_sample[2], 0);
            game->SNpc.hitpoints_current -= GenerateNumber(0,3);
            m_PlayerActive = false;
            if(game->SNpc.hitpoints_current <= 0)
            {
                m_PlayerActive = true;
                game->SNpc.hitpoints_current = game->SNpc.hitpoints_max;
                game->SActor.hitpoints_current = game->SActor.hitpoints_max;
                game->ChangeState(CPlayState::Instance());
            }
        }
    }
    else if( SDL_PointInRect(&mousePosition, &DefendButtonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);
        SDL_RenderFillRect(game->renderer, &DefendButtonPosition);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            Mix_PlayChannel(-1, game->_sample[3], 0);
            //Mix_PlayChannel(-1, game->_sample[2], 0);
            m_PlayerActive = false;
            m_PlayerDefending = true;
        }
    }
    else if(m_PlayerActive)
    if( SDL_PointInRect(&mousePosition, &buttonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);
        SDL_RenderFillRect(game->renderer, &buttonPosition);

        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            Mix_PlayChannel(-1, game->_sample[3], 0);
            Mix_PlayChannel(-1, game->_sample[2], 0);
            game->SNpc.hitpoints_current -= GenerateNumber(0,3);
            m_PlayerActive = false;
            if(game->SNpc.hitpoints_current <= 0)
            {
                m_PlayerActive = true;
                game->SNpc.hitpoints_current = game->SNpc.hitpoints_max;
                game->SActor.hitpoints_current = game->SActor.hitpoints_max;
                game->ChangeState(CPlayState::Instance());
            }
        }
    }
}
