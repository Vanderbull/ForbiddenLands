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
#include "lootstate.h"
#include "battlestate.h"

using namespace std::chrono;

CBattleState CBattleState::m_BattleState;

void CBattleState::Init()
{
    SDL_Log("CBattleState Init\n");
}

void CBattleState::Cleanup()
{
	SDL_Log("CBattleState Pause\n");
}

void CBattleState::Pause()
{
	SDL_Log("CBattleState Pause\n");
}

void CBattleState::Resume()
{
	SDL_Log("CBattleState Resume\n");
}

void CBattleState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CBattleState HandleEvents\n");
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

void CBattleState::Update(CGameEngine* game)
{
    SDL_Log("CBattleState Update\n");
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
    SDL_Log("CBattleState Draw");

    SDL_Rect AttackButtonPosition = { 16, 16, 64, 64};
    SDL_Rect DefendButtonPosition = { 88, 16, 64, 64};
    SDL_Rect FleeButtonPosition = { 160, 16, 64, 64};

    SDL_RenderCopy(game->renderer, game->battleState, NULL, NULL);

    int texW = 0;
    int texH = 0;
    int ScalingFactor = 4;
    SDL_Texture* goblin = game->LoadTexture("./assets/data/textures/viking.png",255);
    SDL_QueryTexture(goblin, NULL, NULL, &texW, &texH);

    SDL_Rect gRect = { game->current.w / 2 - texW * ScalingFactor / 3,game->current.h / 2 - texH * ScalingFactor / 2, texW*ScalingFactor, texH*ScalingFactor };
    SDL_RenderCopy(game->renderer, goblin, NULL, &gRect);

    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    game->RenderText("HP: " + std::to_string(game->SNpc.hitpoints_current) + " / " + std::to_string(game->SNpc.hitpoints_max), Black, 864, 176,64);
    game->RenderText("HP: " + std::to_string(game->SActor.hitpoints_current) + " / " + std::to_string(game->SActor.hitpoints_max), White, 864, 964,64);

    if(!m_PlayerActive)
    {
        if(m_PlayerDefending)
        {
            if( game->SActor.Profession.Choosen == game->SActor.Profession.VIKING )
                game->SActor.hitpoints_current -= GenerateNumber(0,3) / 2;
            else if( game->SActor.Profession.Choosen == game->SActor.Profession.MARAUDER )
                game->SActor.hitpoints_current -= GenerateNumber(0,3);
            else if( game->SActor.Profession.Choosen == game->SActor.Profession.SHIELDMAIDEN )
                game->SActor.hitpoints_current -= GenerateNumber(0,3) / 3;

            m_PlayerDefending = false;
        }
        else
        {
            if( game->SActor.Profession.Choosen == game->SActor.Profession.VIKING )
                game->SActor.hitpoints_current -= GenerateNumber(0,3) / 2;
            else if( game->SActor.Profession.Choosen == game->SActor.Profession.MARAUDER )
                game->SActor.hitpoints_current -= GenerateNumber(0,3);
            else if( game->SActor.Profession.Choosen == game->SActor.Profession.SHIELDMAIDEN )
                game->SActor.hitpoints_current -= GenerateNumber(0,3) / 3;

            m_PlayerDefending = false;
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

            if( game->SActor.Profession.Choosen == game->SActor.Profession.VIKING )
                game->SNpc.hitpoints_current -= GenerateNumber(0,3) / 2;
            else if( game->SActor.Profession.Choosen == game->SActor.Profession.MARAUDER )
                game->SNpc.hitpoints_current -= GenerateNumber(0,3);
            else if( game->SActor.Profession.Choosen == game->SActor.Profession.SHIELDMAIDEN )
                game->SNpc.hitpoints_current -= GenerateNumber(0,3) / 3;

            m_PlayerActive = false;
            if(game->SNpc.hitpoints_current <= 0)
            {
                game->number_of_enemies--;
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
            m_PlayerActive = false;
            m_PlayerDefending = true;
        }
    }
    else if( SDL_PointInRect(&mousePosition, &FleeButtonPosition) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);
        SDL_RenderFillRect(game->renderer, &FleeButtonPosition);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            game->SActor.PlayerCoordinate.x = GenerateNumber(0,16);
            game->SActor.PlayerCoordinate.y = GenerateNumber(0,16);
            game->ChangeState(CPlayState::Instance());
        }
    }

    if(game->number_of_enemies <= 0)
    {
        game->ChangeState(CLootState::Instance());
    }
}
