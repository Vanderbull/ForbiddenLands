#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "createcharacterstate.h"

CCreateCharacterState CCreateCharacterState::m_CreateCharacterState;

void CCreateCharacterState::Init()
{
//    if( TTF_Init() == -1 )
//    {
//        printf("TTF_OpenFont: %s\n", TTF_GetError());
//        exit(-1);
//    }
//
//    gameTitleFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 24);
//
//    if(!gameTitleFont)
//    {
//        printf("TTF_OpenFont: %s\n", TTF_GetError());
//        exit(-1);
//    }

	printf("CCreateCharacterState Init\n");
}

void CCreateCharacterState::Cleanup()
{
	printf("CCreateCharacterState Cleanup\n");
}

void CCreateCharacterState::Pause()
{
	printf("CCreateCharacterState Pause\n");
}

void CCreateCharacterState::Resume()
{
	printf("CCreateCharacterState Resume\n");
}

void CCreateCharacterState::HandleEvents(CGameEngine* game)
{
    printf("CCreateCharacterState HandleEvents\n");

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

void CCreateCharacterState::Update(CGameEngine* game)
{
    printf("CCreateCharacterState Update\n");

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

void CCreateCharacterState::Draw(CGameEngine* game)
{
    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    std::string raceDescriptions;

    int localCounter = 0;
    SDL_Rect TextFrame = {0, 0, 0, 0};
    SDL_Rect TextFrame2 = {0, 0, 0, 0};
    std::vector<std::string> textElements = { "POW ", "INT ", "PERS ", "TOU ", "TECH ", "QUI ", "PERC "};

    std::vector<std::string> abilityModElements = { "POW MOD", "INT MOD", "PERS MOD", "TOU MOD", "TECH MOD", "QUI MOD", "PERC MOD"};

    std::vector<SDL_Rect> raceElements;
    std::vector<SDL_Rect> professionElements;
    std::vector<std::string> raceTextElements = { "DWARF", "HUMAN"};
    std::vector<std::string> professionTextElements = { "VIKING", "MARAUDER","WIZARD"};

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    std::string StatPoints_String = std::to_string(game->StartAbilityPoints) + " Points Left";

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { 50,325, texW, texH };

    game->RenderText2(StatPoints_String,White,gRect.x,gRect.y,24);

    int counter = 0;

    for (std::string textElement : abilityModElements)
    {
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 200,370+(counter*50), texW, texH };
        game->RenderText2(std::to_string(game->AbilityMod[counter]).c_str(),White,gRect.x,gRect.y,24);

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

    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { 400,170, texW, texH };
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    game->RenderText2(professionTextElements[game->ChoosenProfession].c_str(),White,gRect.x,gRect.y,24);

    counter = 0;

    for (std::string textElement : professionTextElements)
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &professionElements[counter]);
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 400,370+(counter*50), texW, texH };
        game->RenderText2(textElement.c_str(),White,gRect.x,gRect.y,24);

        if( SDL_PointInRect(&mousePosition, &professionElements[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                SDL_RenderFillRect(game->renderer, &professionElements[counter]);
                game->ChoosenProfession = counter;
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

        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 1200,370+(counter*50), texW, texH };
        game->RenderText2(textElement.c_str(),White,gRect.x,gRect.y,24);

        if( SDL_PointInRect(&mousePosition, &game->SkillRect[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
            gRect = { 1600,370, 600, 800 };
            SDL_RenderFillRect(game->renderer, &gRect);
            //SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            //SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            game->RenderText2(textElement.c_str(),White,1620,390,24);
            game->RenderText2("Profession: MGG",White,1620,410,24);
            game->RenderText2("Technique: 20",White,1620,430,24);
            game->RenderText2("Group: WE",White,1620,450,24);
            game->RenderText2("Advance: A",White,1620,470,24);
            game->RenderText2("UtilizedBy: Dagger, Short sword",White,1620,490,24);
            game->RenderText2("Description: Small blades;physical",White,1620,510,24);

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
        if( SDL_PointInRect(&mousePosition, &game->SkillRect[choosen]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
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

        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 1600,370+(counter*50), texW, texH };
        game->RenderText2(textElement.c_str(),White,gRect.x,gRect.y,24);

        if( SDL_PointInRect(&mousePosition, &game->SkillRect[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
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
        if( SDL_PointInRect(&mousePosition, &game->SkillRect[choosen]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
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
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 50,370+(counter*50), texW, texH };
        game->RenderText2(std::to_string(game->Ability[counter]).c_str(),White,gRect.x,gRect.y,24);

        StatPoints_String = textElements[counter];

        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 100,370+(counter*50), texW, texH };

        game->RenderText2(StatPoints_String.c_str(),White,gRect.x,gRect.y,2);

        StatPoints_String = "[+]";
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 300,370+(counter*50), texW, texH };

        game->RenderText2(StatPoints_String.c_str(),White,gRect.x,gRect.y,24);

        if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                StatPoints_String = "Pressing the matter" + std::to_string(counter);
                SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

                gRect = { 0,0, texW, texH };
                game->RenderText2(StatPoints_String.c_str(),White,gRect.x,gRect.y,24);
                game->StartAbilityPoints--;
            }
        }

        StatPoints_String = "[-]";
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { 340,370+(counter*50), texW, texH };
        game->RenderText2(StatPoints_String.c_str(),White,gRect.x,gRect.y,24);


       if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                StatPoints_String = "Pressing the matter" + std::to_string(counter);
                SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

                gRect = { 0,0, texW, texH };
                game->RenderText2(StatPoints_String.c_str(),White,gRect.x,gRect.y,24);
                game->StartAbilityPoints++;
            }
        }

        counter++;
    }

    counter = 0;

    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { 800,170, texW, texH };
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);

    game->RenderText2(raceTextElements[game->ChoosenRace].c_str(),White,gRect.x,gRect.y,24);

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
        StatPoints_String = textElement.c_str();
        SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

        gRect = { raceElements[counter].x,raceElements[counter].y, texW, texH };
        game->RenderText2(StatPoints_String.c_str(),White,gRect.x,gRect.y,24);

        if( SDL_PointInRect(&mousePosition, &raceElements[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                SDL_RenderFillRect(game->renderer, &raceElements[counter]);
                game->ChoosenRace = counter;
            }
        }
        counter++;
    }
}
