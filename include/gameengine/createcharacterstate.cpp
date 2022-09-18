#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "createcharacterstate.h"

CCreateCharacterState CCreateCharacterState::m_CreateCharacterState;

void CCreateCharacterState::Init()
{
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

	if (SDL_PollEvent(&game->event))
    {
		switch (game->event.type)
		{
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
				switch (game->event.key.keysym.sym) {
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
    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    int localCounter = 0;
    SDL_Rect TextFrame = {0, 0, 0, 0};
    SDL_Rect TextFrame2 = {0, 0, 0, 0};

    std::vector<SDL_Rect> raceElements;
    std::vector<SDL_Rect> professionElements;

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

//	SDL_Surface* surface = IMG_Load( "./images/ui/karaktärsboktom.png" );
//	if( !surface )
//	{
//        exit(-1);
//	}
//
//    SDL_RWops *rw = SDL_RWFromFile("./images/ui/skilltree.svg","r"); //SDL_RWFromConstMem(svg.c_str(), svg.size());
//    surface = IMG_Load_RW(rw, 1);
//    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, surface);
//
//	texture = SDL_CreateTextureFromSurface( game->renderer, surface );
//    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//    SDL_SetTextureAlphaMod( texture, 255 );
//    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
//    SDL_FreeSurface(surface);
//    SDL_DestroyTexture(texture);

//	surface = IMG_Load( "./images/ui/female.png" );
//	if( !surface )
//	{
//        exit(-1);
//	}

	//texture = SDL_CreateTextureFromSurface( game->renderer, surface );


    //SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    //SDL_SetTextureAlphaMod( texture, 255 );

    //SDL_FreeSurface(surface);

    SDL_Texture *texture = game->LoadTexture("./images/ui/gearslots.png",255);
	int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect SrcR;

    SrcR.x = game->current.w / 3;
    SrcR.y = game->current.h / 3;
    SrcR.w = w*2;
    SrcR.h = h*2;
    SDL_RenderCopy(game->renderer, texture, NULL, &SrcR);
    SDL_DestroyTexture(texture);
//
//    texture = game->LoadTexture("./images/ui/gearslots.png",255);
//    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
//
//    SrcR.x = game->current.w / 4;
//    SrcR.y = game->current.h / 43;
//    SrcR.w = w*2;
//    SrcR.h = h*2;
//    SDL_RenderCopy(game->renderer, texture, NULL, &SrcR);
//    SDL_DestroyTexture(texture);


    // Abilities ///////////////////////////////////

    std::string StatPoints_String = std::to_string(game->StartAbilityPoints) + " Points Left";

    game->RenderText2(StatPoints_String,White,600,970,24);

    int counter = 0;

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

        // Profession /////////////////////////////
        counter = 0;

        for (std::string textElement : professionTextElements)
        {
            SDL_Rect rect;
            rect.x = 1200;
            rect.y = 225+(counter*50);
            rect.w = 300;
            rect.h = 30;
            professionElements.push_back(rect);
            counter++;
        };

        counter = 0;

        gRect = { 1200,170, 0, 0 };
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &gRect);
        game->RenderText2(professionTextElements[game->ChoosenProfession].c_str(),White,gRect.x,gRect.y,24);

        counter = 0;

        for (std::string textElement : professionTextElements)
        {
            game->RenderText2(textElement.c_str(),White,professionElements[counter].x,professionElements[counter].y,24);

            professionElements[counter].x -= professionElements[counter].w / 2;
            professionElements[counter].y -= professionElements[counter].h / 2;

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
