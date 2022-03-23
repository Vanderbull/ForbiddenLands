#ifndef RENDER_SETTINGS_H
#define RENDER_SETTINGS_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

int x,y = 0;
int triggered = 0;
void renderSettings()
{
    //renderBackground("./images/menus/mainmenu.jpg");
    //RenderText("SETTINGS",White,140,180,48);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, MainMenuBackgroundTexture, NULL, NULL);

    RenderTitle("SETTINGS",White,500,180);

    static int display_in_use = 0; /* Only using first display */

    int i, display_mode_count;
    SDL_DisplayMode mode, last_display_mode;
    Uint32 f;
    SDL_Rect aButton;

    //SDL_Log("SDL_GetNumVideoDisplays(): %i", SDL_GetNumVideoDisplays());

    display_mode_count = SDL_GetNumDisplayModes(display_in_use);

    if (display_mode_count < 1)
    {
        SDL_Log("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
    }
    //SDL_Log("SDL_GetNumDisplayModes: %i", display_mode_count);

    for (i = 0; i < display_mode_count; ++i)
    {
        if (SDL_GetDisplayMode(display_in_use, i, &mode) != 0)
        {
            SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
        }
        f = mode.format;

        if( last_display_mode.w != mode.w )
        {
            aButton = {current.w - 800,210+i*50,750,40};
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &aButton);
        }

        if( SDL_PointInRect(&mousePosition, &aButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &aButton);
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                loadedBackground = false;

                std::string Resolution = "";
                Resolution += std::to_string(mode.w);
                Resolution += "x";
                Resolution += std::to_string(mode.h);
                Resolution += " ( ";
                Resolution += std::to_string(SDL_BITSPERPIXEL(f));
                Resolution += " ) ";

                SDL_DestroyWindow(window);
                window = SDL_CreateWindow(Resolution.c_str(),
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    mode.w, mode.h,
                    SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

                SDL_DestroyRenderer(renderer);
                SDL_DestroyRenderer(renderer2);
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                renderer2 = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_RenderSetScale(renderer,1.0,1.0);
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                current = mode;
            }

            std::string ResolutionText = "";
            ResolutionText += std::to_string(mode.w);
            ResolutionText += "x";
            ResolutionText += std::to_string(mode.h);
            ResolutionText += " ( ";
            ResolutionText += std::to_string(SDL_BITSPERPIXEL(f));
            ResolutionText += " ) ";

            //RenderBreadText(ResolutionText.c_str(),Red,300,0);
            //RenderText(ResolutionText.c_str(),Red,300,0,48);
        }

        if( last_display_mode.w != mode.w )
        {
            SDL_Log("Mode %i\tbpp %i\t%s\t%i x %i", i,
            SDL_BITSPERPIXEL(f), SDL_GetPixelFormatName(f), mode.w, mode.h);

            std::string ResolutionText = "";
            ResolutionText += std::to_string(mode.w);
            ResolutionText += "x";
            ResolutionText += std::to_string(mode.h);
            ResolutionText += " ( ";
            ResolutionText += std::to_string(SDL_BITSPERPIXEL(f));
            ResolutionText += " ) ";

            RenderBreadText(ResolutionText.c_str(),White,aButton.x + (aButton.w / 2),aButton.y + (aButton.h / 2));
            //RenderText(ResolutionText.c_str(),Red,current.w - 400,210+i*50,fontSize);
        }
        last_display_mode = mode;
    }

//    SDL_GetRelativeMouseState(&x,&y);
//    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
//    {
//        if( mousePosition.y > volumeSlider.y && mousePosition.y < volumeSlider.y + volumeSlider.w )
//        {
//            triggered = 1;
//        }
//        if(triggered)
//        if( (mousePosition.x > 0 + volumeSlider.w / 2) && (mousePosition.x < current.w - volumeSlider.w / 2) )
//        {
//            volumeSlider.x = mousePosition.x;
//            volumeSlider.x = volumeSlider.x - (volumeSlider.w / 2);
//            volumeSlider.x = volumeSlider.x + x;
//            if( volumeSlider.x < 0)
//                volumeSlider.x = 0;
//            if( volumeSlider.x > current.w - volumeSlider.w)
//                volumeSlider.x = current.w - volumeSlider.w;
//        }
//    }
//
//    RenderText("Sound",White,0,volumeSlider.y - 48,32);
//    SDL_Rect sliderBar = {0,volumeSlider.y,current.w,volumeSlider.h};
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
//    SDL_RenderFillRect(renderer, &sliderBar);
//    RenderText(std::to_string( Mix_VolumeMusic( volumeSlider.x / 19 ) ).c_str() ,White,0,0,fontSize);
//    SDL_RenderFillRect(renderer, &volumeSlider);
//
    SDL_Rect ExitButton = {current.w - 220,current.h - 50,200,30};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
    SDL_RenderFillRect(renderer, &ExitButton);

    if( SDL_PointInRect(&mousePosition, &ExitButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &ExitButton);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SettingsMenu = 0;
        }
    }

    RenderBreadText("Exit",White,ExitButton.x + (ExitButton.w / 2),ExitButton.y + (ExitButton.h / 2) );
    //RenderText("Exit",White,current.w - 150,current.h - 50,fontSize);
};

#endif // RENDER_SETTINGS_H
