#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "characterstate.h"

CCharacterState CCharacterState::m_CharacterState;

void CCharacterState::Init()
{
    SDL_Log("CCharacterState Init\n");
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
						game->PopState();
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
    std::string raceDescriptions;

    int localCounter = 0;
    SDL_Rect TextFrame = {0, 0, 0, 0};
    SDL_Rect TextFrame2 = {0, 0, 0, 0};
    std::vector<std::string> textElements = { "POW ", "INT ", "PERS ", "TOU ", "TECH ", "QUI ", "PERC "};

    std::vector<std::string> abilityModElements = { "POW MOD", "INT MOD", "PERS MOD", "TOU MOD", "TECH MOD", "QUI MOD", "PERC MOD"};

    std::vector<SDL_Rect> raceElements;
    std::vector<SDL_Rect> professionElements;
    std::vector<std::string> raceTextElements = { "DWARF", "HUMAN"};
    std::vector<std::string> professionTextElements = { "KNIGHT", "CLERIC","WIZARD"};

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    SDL_Rect FaceFrame = {64,64, 256, 256};
    SDL_RenderCopy(game->renderer, SActor.faceImage, NULL, &FaceFrame);

    std::string StatPoints_String = std::to_string(game->StartAbilityPoints) + " Points Left";
    gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, StatPoints_String.c_str(), White);
	if( !gSurface )
	{
        exit(-1);
	}
    gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { 50,325, texW, texH };
    SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

    int counter = 0;

    for (std::string textElement : abilityModElements)
    {
        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, std::to_string(game->AbilityMod[counter]).c_str(), White);
        if( !gSurface )
        {
            exit(-1);
        }
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 200,370+(counter*50), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

        counter++;
    }

    counter = 0;

    for (std::string textElement : professionTextElements)
    {
        SDL_Rect rect;
        rect.x = 400;
        rect.y = 370+(counter*50);
        rect.w = 300;
        rect.h = 30;
        professionElements.push_back(rect);
        counter++;
    };

    counter = 0;
    for (std::string textElement : professionTextElements)
    {

        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &professionElements[counter]);

        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, textElement.c_str(), Black);
        if( !gSurface )
        {
            exit(-1);
        }
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 400,370+(counter*50), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);


        if( SDL_PointInRect(&m_iCurrentCoord, &professionElements[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                SDL_RenderFillRect(game->renderer, &professionElements[counter]);
            }
        }
        counter++;
    }

    counter = 0;
    game->SkillRect.clear();
    for (std::string textElement : game->Skill)
    {
        SDL_Rect rect;
        rect.x = 1200;
        rect.y = 370+(counter*50);
        rect.w = 300;
        rect.h = 30;
        game->SkillRect.push_back(rect);
        counter++;
    };

    counter = 0;

    static int choosen = -1;

    if( !game->Skill.empty())
    for (std::string textElement : game->Skill)
    {

        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &game->SkillRect[counter]);

        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, textElement.c_str(), Black);
        if( !gSurface )
        {
            exit(-1);
        }
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 1200,370+(counter*50), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);


        if( SDL_PointInRect(&m_iCurrentCoord, &game->SkillRect[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                SDL_RenderFillRect(game->renderer, &game->SkillRect[counter]);
                choosen = counter;
                SDL_Delay(50);
            }
        }
        //choosen = -1;
        counter++;
    }
    if( !game->Skill.empty())
        if( SDL_PointInRect(&m_iCurrentCoord, &game->SkillRect[choosen]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                auto size = game->LearnedSkill.size();
                if( size < 3 )
                {
                    game->LearnedSkill.push_back(game->Skill.at(choosen));
                    game->Skill.erase(game->Skill.begin() + choosen);
                    SDL_Delay(50);
                }
            }
        }


    counter = 0;
    game->SkillRect.clear();
    for (std::string textElement : game->LearnedSkill)
    {
        SDL_Rect rect;
        rect.x = 1600;
        rect.y = 370+(counter*50);
        rect.w = 300;
        rect.h = 30;
        game->SkillRect.push_back(rect);
        counter++;
    };

    counter = 0;
    choosen = -1;
    for (std::string textElement : game->LearnedSkill)
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &game->SkillRect[counter]);

        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, textElement.c_str(), Black);
        if( !gSurface )
        {
            exit(-1);
        }
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 1600,370+(counter*50), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);


        if( SDL_PointInRect(&m_iCurrentCoord, &game->SkillRect[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                SDL_RenderFillRect(game->renderer, &game->SkillRect[counter]);
                choosen = counter;
                SDL_Delay(50);
            }
        }
        //choosen = -1;
        counter++;
    }

    if( !game->LearnedSkill.empty() )
        if( SDL_PointInRect(&m_iCurrentCoord, &game->SkillRect[choosen]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                game->Skill.push_back(game->LearnedSkill.at(choosen));
                game->LearnedSkill.erase(game->LearnedSkill.begin() + choosen);
                SDL_Delay(50);
            }
        }

    counter = 0;

    for (std::string textElement : textElements)
    {
        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, std::to_string(game->Ability[counter]).c_str(), White);
        if( !gSurface )
        {
            exit(-1);
        }
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 50,370+(counter*50), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

        StatPoints_String = textElements[counter];
        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, StatPoints_String.c_str(), White);
        if( !gSurface )
        {
            exit(-1);
        }
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 100,370+(counter*50), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

        StatPoints_String = "[+]";
        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, StatPoints_String.c_str(), White);
        if( !gSurface )
        {
            exit(-1);
        }
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 300,370+(counter*50), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

       if( SDL_PointInRect(&m_iCurrentCoord, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                StatPoints_String = "Pressing the matter" + std::to_string(counter);
                gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, StatPoints_String.c_str(), White);
                if( !gSurface )
                {
                    exit(-1);
                }
                gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
                SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

                gRect = { 0,0, texW, texH };
                SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);
                game->StartAbilityPoints--;
            }
        }

        StatPoints_String = "[-]";
        gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, StatPoints_String.c_str(), White);
        if( !gSurface )
        {
            exit(-1);
        }
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 340,370+(counter*50), texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

       if( SDL_PointInRect(&m_iCurrentCoord, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                StatPoints_String = "Pressing the matter" + std::to_string(counter);
                gSurface = TTF_RenderText_Blended(game->gameBreadTextFont, StatPoints_String.c_str(), White);
                if( !gSurface )
                {
                    exit(-1);
                }
                gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
                SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

                gRect = { 0,0, texW, texH };
                SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);
                game->StartAbilityPoints++;
            }
        }
        counter++;
    }

    counter = 0;

    for (std::string textElement : raceTextElements)
    {
        SDL_Rect rect;
        rect.x = 800;
        rect.y = 370+(counter*50);
        rect.w = 300;
        rect.h = 30;
        raceElements.push_back(rect);
        counter++;
    }

    counter = 0;
    for (std::string textElement : raceTextElements)
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &raceElements[counter]);

        StatPoints_String = textElement.c_str();
        gSurface = TTF_RenderText_Blended(gameBreadTextFont, StatPoints_String.c_str(), Black);
        if( !gSurface )
        {
            exit(-1);
        }
        gTexture = SDL_CreateTextureFromSurface(game->renderer, gSurface);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { raceElements[counter].x,raceElements[counter].y, texW, texH };
        SDL_RenderCopy(game->renderer, gTexture, NULL, &gRect);

        if( SDL_PointInRect(&m_iCurrentCoord, &raceElements[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                SDL_RenderFillRect(game->renderer, &raceElements[counter]);
            }
        }
        counter++;
    }
}
