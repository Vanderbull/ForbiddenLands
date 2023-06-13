#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "playstate.h"
#include "characterstate.h"
#include "inventorystate.h"
#include "worldmapstate.h"

CCharacterState CCharacterState::m_CharacterState;

void CCharacterState::Init()
{
    SDL_Log("CCharacterState Init\n");
    MenuChoices.clear();
    MenuChoices.push_back("INVENTORY");
    MenuChoices.push_back("CHARACTER");
    MenuChoices.push_back("JOURNAL");
    MenuChoices.push_back("MAP");
}

void CCharacterState::Cleanup()
{
	SDL_Log("CCharacterState Cleanup\n");
}

void CCharacterState::Pause()
{
	SDL_Log("CCharacterState Pause\n");
}

void CCharacterState::Resume()
{
	SDL_Log("CCharacterState Resume\n");
}

void CCharacterState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CCharacterState HandleEvents\n");

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

void CCharacterState::Update(CGameEngine* game)
{
    SDL_Log("CCharacterState Update\n");

    ///--- Store the current information to the previous
    m_iPreviousCoord.x = m_iCurrentCoord.x;
    m_iPreviousCoord.y = m_iCurrentCoord.y;

    //m_iPreviousCoordX=m_iCurrentCoordX;
    //m_iPreviousCoordY=m_iCurrentCoordY;
    m_uPreviousMouseState=m_uCurrentMouseState;

    ///--- Update the current state of the mouse
    m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoord.x, &m_iCurrentCoord.y);

    //m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

    ///--- Set the wheel back to 0
    m_iWheelCoord.x = 0;
    m_iWheelCoord.y = 0;

    //m_iWheelX=0;
    //m_iWheelY=0;
}

void CCharacterState::Draw(CGameEngine* game)
{
    SDL_Log("CCharacterState Draw");
    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    int counter = 0;

    if( game->BackgroundTexture == NULL )
        game->BackgroundTexture = game->LoadTexture("./assets/data/textures/backgrounds/characterstate-new.png",255);

    SDL_RenderCopy(game->renderer, game->BackgroundTexture, NULL, NULL);

    game->RenderText("Hunger: " + std::to_string(game->SActor.hunger),game->White,80,gRect.y +  40,24);
    game->RenderText("Thirst: " + std::to_string(game->SActor.thirst),game->White,80,gRect.y +  80,24);

    game->RenderText(game->SActor.name.c_str(),White,300,115,48);

    std::string Experience = std::to_string(game->SActor.experience) + " / 10000";
    game->RenderBreadText(Experience.c_str(),game->White,300, 175 );

  	game->RenderBreadText(std::to_string(game->SActor.current_stats[0]).c_str(),game->Black,560, 250 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[1]).c_str(),game->Black,560, 295 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[2]).c_str(),game->Black,560, 340 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[3]).c_str(),game->Black,560, 385 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[4]).c_str(),game->Black,560, 430 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[5]).c_str(),game->Black,560, 475 );
  	game->RenderBreadText(std::to_string(game->SActor.current_stats[6]).c_str(),game->Black,560, 520 );

  	game->RenderBreadText(game->SActor.Profession.Names.at(game->SActor.Profession.Choosen).c_str(),game->White,444, 575 );

  	game->RenderBreadText(std::to_string(game->SActor.hitpoints_current).c_str(),game->White,30, 600 );
  	game->RenderBreadText("/",game->White,45, 600 );
  	game->RenderBreadText(std::to_string(game->SActor.hitpoints_max).c_str(),game->White,60, 600 );

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255,128);
    SDL_RenderFillRect(game->renderer,&ExitButton2);

    if( SDL_PointInRect(&mousePosition, &ExitButton2) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CPlayState::Instance() );
        }
    }

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255,128);
    SDL_RenderFillRect(game->renderer,&InventoryButton);

    if( SDL_PointInRect(&mousePosition, &InventoryButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CInventoryState::Instance() );
        }
    }

    SDL_SetRenderDrawColor(game->renderer, 255, 0, 255,128);
    SDL_RenderFillRect(game->renderer,&CharacterButton);

    if( SDL_PointInRect(&mousePosition, &CharacterButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CCharacterState::Instance() );
        }
    }

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255,128);
    SDL_RenderFillRect(game->renderer,&MapButton);

    if( SDL_PointInRect(&mousePosition, &MapButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CWorldMapState::Instance() );
        }
    }

    counter = 0;
    for (SkillObject textElement : game->v_LearnedSkill)
    {
        SDL_Rect skillbox = {1600,300+(64*counter),128,64};
        //game->SkillRect[counter].x -= game->SkillRect[counter].w / 2;
        //game->SkillRect[counter].y -= game->SkillRect[counter].h / 2;

        //SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        //SDL_RenderFillRect(game->renderer, &game->SkillRect[counter]);

        game->RenderText(textElement.Name.c_str(),White,skillbox.x,skillbox.y,24);
        counter++;
    }

    SDL_Texture *texture = game->LoadTexture("./assets/data/textures/ui/gearslots.png",255);
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect SrcR;

    SrcR.x = game->current.w / 3 + 100;
    SrcR.y = game->current.h / 3 - 100;
    SrcR.w = w*2;
    SrcR.h = h*2;
    SDL_RenderCopy(game->renderer, texture, NULL, &SrcR);
    SDL_DestroyTexture(texture);
}
