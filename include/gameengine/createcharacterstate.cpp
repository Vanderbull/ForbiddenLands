#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "loadingstate.h"
#include "playstate.h"
#include "createcharacterstate.h"

CCreateCharacterState CCreateCharacterState::m_CreateCharacterState;

void CCreateCharacterState::Init()
{
	SDL_Log("CCreateCharacterState Init\n");
    MenuChoices.clear();
    MenuChoices.push_back("EXIT");

	// Start sending SDL_TextInput events
	SDL_StartTextInput();
}

void CCreateCharacterState::Cleanup()
{
	SDL_Log("CCreateCharacterState Cleanup\n");
	SDL_StopTextInput();
}

void CCreateCharacterState::Pause()
{
	SDL_Log("CCreateCharacterState Pause\n");
}

void CCreateCharacterState::Resume()
{
	SDL_Log("CCreateCharacterState Resume\n");
}

void CCreateCharacterState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CCreateCharacterState HandleEvents\n");

	if (SDL_PollEvent(&game->event))
    {
		switch (game->event.type)
		{
			case SDL_TEXTINPUT:
				game->SActor.name += game->event.text.text;
				break;
            case SDL_MOUSEBUTTONDOWN:
                switch (game->event.button.button)
                {
                case SDL_BUTTON_RIGHT:
                default:
                {
                m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);
                } break;
            } break;
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (game->event.key.keysym.sym)
				{
                    case SDLK_BACKSPACE:
                    {
                        if(game->SActor.name.size() > 0)
                        {
                            game->SActor.name.pop_back();
                        }
                    } break;
					case SDLK_ESCAPE:
						game->PopState();
						break;
                    case SDLK_UP:
                        {
                              scroll_acceleration = 1;
                              scrolling = 1;
                        }break;
                    case SDLK_DOWN:
                        {
                            scroll_acceleration = -1;
                            scrolling = 1;
                        } break;
				} break;
            case SDL_KEYUP:
                switch (game->event.key.keysym.sym) {
                    case SDLK_UP:
                        {
                            scroll_range_min--;
                            scroll_range_max--;
                              scroll_acceleration = 0;
                              scrolling = 0;
                        }break;
                    case SDLK_DOWN:
                        {
                            scroll_range_min++;
                            scroll_range_max++;
                              scroll_acceleration = 0;
                              scrolling = 0;
                        }break;
                } break;
		}
	}
}

void CCreateCharacterState::Update(CGameEngine* game)
{
    SDL_Log("CCreateCharacterState Update\n");

    ///--- Store the current information to the previous
    m_iPreviousCoordX=m_iCurrentCoordX;
    m_iPreviousCoordY=m_iCurrentCoordY;
    m_uPreviousMouseState=m_uCurrentMouseState;

    ///--- Update the current state of the mouse
    m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

    ///--- Set the wheel back to 0
    m_iWheelX=0;
    m_iWheelY=0;

    if(scrolling){
      if(scroll_acceleration > 0) scroll_acceleration -= scroll_friction;
      if(scroll_acceleration < 0) scroll_acceleration += scroll_friction;
      if(abs(scroll_acceleration) < 0.0005) scroll_acceleration = 0;
      scroll_Y += scroll_sensitivity * scroll_acceleration;
      // Here you have to set your scrolling bounds i.e. if(scroll_Y < 0) scroll_Y = 0;
      if(scroll_Y < 0) scroll_Y = 0;
      if(scroll_Y > 1040) scroll_Y = 1040;
    }
    scrolling = 0;

    if (scroll_range_min < 0 )
    {
        scroll_range_min = 0;
        scroll_range_max = scroll_range_min + 10;
    }

    if (scroll_range_max > game->Skill.size() )
    {
        scroll_range_min = game->Skill.size() -10;
        scroll_range_max = game->Skill.size();
    }
}

void CCreateCharacterState::Draw(CGameEngine* game)
{
    SDL_Log("CCreateCharacterState Draw");
    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    int localCounter = 0;
    int counter = 0;
    SDL_Rect TextFrame = {0, 0, 0, 0};
    SDL_Rect TextFrame2 = {0, 0, 0, 0};

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    gRect = { 0,0, 64, 64 };
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(game->renderer, &gRect);
    game->RenderText("Portrait",White,gRect.x,gRect.y,24);

    if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            ScreenName = "Portrait";
        }
    }

    gRect = { 0,65, 64, 64 };
    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(game->renderer, &gRect);
    game->RenderText("Class",White,gRect.x,gRect.y,24);

    if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            ScreenName = "Class";
        }
    }

    gRect = { 0,129, 64, 64 };
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(game->renderer, &gRect);
    game->RenderText("Skills",White,gRect.x,gRect.y,24);

    if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            ScreenName = "Skills";
        }
    }

    gRect = { 0,193, 64, 64 };
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(game->renderer, &gRect);
    game->RenderText("Abilities",White,gRect.x,gRect.y,24);

    if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            ScreenName = "Abilities";
        }
    }

    gRect = { 0,257, 64, 64 };
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(game->renderer, &gRect);
    game->RenderText("Character",White,gRect.x,gRect.y,24);

    if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            ScreenName = "Character";
        }
    }

    gRect = { 0,321, 64, 64 };
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(game->renderer, &gRect);
    game->RenderText("Total",White,gRect.x,gRect.y,24);

    // Back and Next
    gRect = { 0 ,game->current.h - gRect.h , 128, 64 };
    SDL_SetRenderDrawColor(game->renderer, game->current.h - gRect.h, 0, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(game->renderer, &gRect);
    game->RenderText("Back",White,gRect.x,gRect.y,24);

    gRect = { game->current.w - gRect.w , game->current.h - gRect.h, 128, 64 };
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(game->renderer, &gRect);
    game->RenderText("Next",White,gRect.x,gRect.y,24);

    if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CLoadingState::Instance() );
        }
    }

    // Exit
    gRect = { game->current.w - 64, 0, 64, 64 };
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(game->renderer, &gRect);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(game->renderer, &gRect);
    game->RenderText("X",White,gRect.x,gRect.y,24);

    if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            game->ChangeState( CMenuState::Instance() );
        }
    }

    if( ScreenName == "Portrait")
    {
        game->RenderText("Protrait",White,game->current.w / 2,game->current.h / 2,24);
    }
    else if( ScreenName == "Class")
    {
        game->RenderText("Class",White,game->current.w / 2,game->current.h / 2,24);

        gRect = { 1200,170, 0, 0 };
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &gRect);
        game->RenderText2(game->SActor.professionTextElements[game->ChoosenProfession].c_str(),White,gRect.x,gRect.y,24);

        counter = 0;

        for (std::string textElement : game->SActor.professionTextElements)
        {
            //game->RenderText2("CRAP",White,500,game->SActor.professionElements[counter].y,24);

            game->RenderText2(textElement.c_str(),White,game->SActor.professionElements[counter].x + game->SActor.professionElements[counter].w / 2,game->SActor.professionElements[counter].y + game->SActor.professionElements[counter].h / 2,24);

            //game->SActor.professionElements[counter].x -= game->SActor.professionElements[counter].w / 2;
            //game->SActor.professionElements[counter].y -= game->SActor.professionElements[counter].h / 2;

            if( SDL_PointInRect(&mousePosition, &game->SActor.professionElements[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
            {
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                    SDL_RenderFillRect(game->renderer, &game->SActor.professionElements[counter]);
                    game->ChoosenProfession = counter;
                }
            }
            counter++;
        }
    }
    else if( ScreenName == "Skills")
    {
        game->RenderText("Skills",White,game->current.w / 2,game->current.h / 2,24);

           // Skills ////////////////////////////
            counter = 0;

            int slide =0;
            game->SkillRect.clear();
            for (std::string textElement : game->Skill)
            {
                SDL_Rect rect;
                rect.h = 30;
                if(counter > 10)
                {
                    counter = 0;
                    slide++;
                }
                //else
                    rect.x = 1400 +( 200*slide);
                rect.y = 225+(counter*50);

                rect.w = 300;

                game->SkillRect.push_back(rect);
                counter++;
            };

            counter = 0;

            static int choosen = -1;

            gRect = { 1400,170, 0, 0 };
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(game->renderer, &gRect);

            game->RenderText2("Skills",White,gRect.x,gRect.y,24);

            if( !game->Skill.empty())
            for (std::string textElement : game->Skill)
            {
                game->RenderText2(textElement.c_str(),White,game->SkillRect[counter].x,game->SkillRect[counter].y,24);

                game->SkillRect[counter].x -= game->SkillRect[counter].w / 2;
                game->SkillRect[counter].y -= game->SkillRect[counter].h / 2;

                if( SDL_PointInRect(&mousePosition, &game->SkillRect[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
                {
                    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                    gRect = { 1800,225, 500, 800 };
                    SDL_RenderFillRect(game->renderer, &gRect);
                    game->RenderText2(textElement.c_str(),Black,1920,390,24);
                    game->RenderText2("Inital requirements stat: " + std::to_string(game->v_Skill.at(counter).InitialRequirementsAttribute),Black,1920,410,24);
                    game->RenderText2("Inital requirements value: " + std::to_string(game->v_Skill.at(counter).InitialRequirementsValue),Black,1920,430,24);
                    game->RenderText2("Group: " + std::to_string(game->v_Skill.at(counter).Group),Black,1920,450,24);
                    game->RenderText2("Description: " + game->v_Skill.at(counter).Description,Black,1920,470,24);

                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                        SDL_RenderFillRect(game->renderer, &game->SkillRect[counter]);

                        choosen = counter;
                        SDL_Delay(50);
                    }
                }
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

            gRect = { 1400,970, 0, 0 };
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(game->renderer, &gRect);

            game->RenderText2("Learned skills",White,gRect.x,gRect.y,24);

            game->SkillRect.clear();
            for (std::string textElement : game->LearnedSkill)
            {
                SDL_Rect rect;
                rect.x = 1400;
                rect.y = 1000+(counter*50);
                rect.w = 300;
                rect.h = 30;
                game->SkillRect.push_back(rect);
                counter++;
            };

            counter = 0;
            choosen = -1;
            for (std::string textElement : game->LearnedSkill)
            {
                game->RenderText2(textElement.c_str(),White,game->SkillRect[counter].x,game->SkillRect[counter].y,24);

                game->SkillRect[counter].x -= game->SkillRect[counter].w / 2;
                game->SkillRect[counter].y -= game->SkillRect[counter].h / 2;

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
    }
    else if( ScreenName == "Abilities")
    {
        game->RenderText("Abilities",White,game->current.w / 2,game->current.h / 2,24);

        // Abilities ///////////////////////////////////

        std::string StatPoints_String = std::to_string(game->StartAbilityPoints) + " Points Left";

        game->RenderText2(StatPoints_String,White,600,970,24);

        counter = 0;

        for (std::string textElement : abilityElements)
        {
            gRect = { 400,225+(counter*50), 0, 0 };
            game->RenderText2(std::to_string(game->Ability[counter]).c_str(),White,gRect.x,gRect.y,24);

            StatPoints_String = "[+]";

            SDL_Point TextSize;
            TTF_SizeText(game->gameBreadTextFont, StatPoints_String.c_str(), &TextSize.x, &TextSize.y);

            gRect = { 450-(TextSize.x/2),225+(counter*50) - TextSize.y/2, TextSize.x, TextSize.y };
            SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(game->renderer, &gRect);

            game->RenderText2(StatPoints_String.c_str(),White,gRect.x + TextSize.x /2,gRect.y + TextSize.y / 2,24);

            if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
            {
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    StatPoints_String = "Pressing the matter" + std::to_string(counter);
                    game->RenderText2(StatPoints_String.c_str(),White,gRect.x,gRect.y,24);
                    if( game->Ability[counter] >= 0 && game->StartAbilityPoints > 0)
                    {
                        game->StartAbilityPoints--;
                        game->Ability[counter]++;
                    }
                }
            }

            StatPoints_String = "[-]";

            TTF_SizeText(game->gameBreadTextFont, StatPoints_String.c_str(), &TextSize.x, &TextSize.y);

            gRect = { 490-(TextSize.x/2),225+(counter*50) - TextSize.y/2, TextSize.x, TextSize.y };
            SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(game->renderer, &gRect);

            game->RenderText2(StatPoints_String.c_str(),White,gRect.x + TextSize.x /2,gRect.y + TextSize.y / 2,24);

            if( SDL_PointInRect(&mousePosition, &gRect) & SDL_BUTTON(SDL_BUTTON_LEFT) )
                {
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        StatPoints_String = "Pressing the matter" + std::to_string(counter);
                        game->RenderText2(StatPoints_String.c_str(),White,gRect.x,gRect.y,24);
                        if( game->Ability[counter] > 5 && game->StartAbilityPoints >= 0)
                        {
                            game->StartAbilityPoints++;
                            game->Ability[counter]--;
                        }
                    }
                }
                counter++;
            }
    }
    else if( ScreenName == "Character")
    {
        game->RenderText(game->SActor.name.c_str(),White,game->current.w / 2,game->current.h / 2,24);
    }
    else
    {
        SDL_Texture *texture = game->LoadTexture("./assets/data/textures/ui/gearslots.png",255);
        int w, h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        SDL_Rect SrcR;

        SrcR.x = game->current.w / 3;
        SrcR.y = game->current.h / 3;
        SrcR.w = w*2;
        SrcR.h = h*2;
        SDL_RenderCopy(game->renderer, texture, NULL, &SrcR);
        SDL_DestroyTexture(texture);

        int Repeat = 0;
        int buttonWidth = 600;
        int buttonHeight = 60;

        for(auto MenuChoice : MenuChoices)
        {
            SDL_Rect buttonPosition = { (game->current.w - buttonWidth) - 20, (game->current.h - buttonHeight) - 20,buttonWidth,buttonHeight};

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
    }
}
