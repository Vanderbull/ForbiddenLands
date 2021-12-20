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
    renderBackground("./images/menus/mainmenu.jpg");
    RenderText("SETTINGS",White,140,180,48);

    for( int i = 0; i < 2; i++)
    {
        std::string ResolutionText = "";
        ResolutionText += std::to_string(monitor[i].w);
        ResolutionText += "x";
        ResolutionText += std::to_string(monitor[i].h);
        ResolutionText += "@";
        ResolutionText += std::to_string(monitor[i].refresh_rate);
        ResolutionText += " ( ";
        ResolutionText += std::to_string(SDL_BITSPERPIXEL(monitor[i].format));
        ResolutionText += " ) ";
        RenderText(ResolutionText.c_str(),White,current.w - 400,210+i*50,fontSize);
        RenderText(std::to_string(SDL_GetNumRenderDrivers()).c_str() ,White,current.w - 1200,390,fontSize);
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i,&info);
        RenderText(std::string(info.name),White,current.w - 800,210+i*50,fontSize);
        bool isHardware      = info.flags & SDL_RENDERER_ACCELERATED;
        bool isSoftware      = info.flags & SDL_RENDERER_SOFTWARE;
        if (isHardware) RenderText("HW",White,current.w - 1200,210+i*50,fontSize);
        if (isSoftware) RenderText("SW",White,current.w - 1200,210+i*50,fontSize);
    }

    SDL_GetRelativeMouseState(&x,&y);
    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        if( mousePosition.y > volumeSlider.y && mousePosition.y < volumeSlider.y + volumeSlider.w )
        {
            triggered = 1;
        }
        if(triggered)
        if( (mousePosition.x > 0 + volumeSlider.w / 2) && (mousePosition.x < current.w - volumeSlider.w / 2) )
        {
            volumeSlider.x = mousePosition.x;
            volumeSlider.x = volumeSlider.x - (volumeSlider.w / 2);
            volumeSlider.x = volumeSlider.x + x;
            if( volumeSlider.x < 0)
                volumeSlider.x = 0;
            if( volumeSlider.x > current.w - volumeSlider.w)
                volumeSlider.x = current.w - volumeSlider.w;
        }
    }

    RenderText("Sound",White,0,volumeSlider.y - 48,32);
    SDL_Rect sliderBar = {0,volumeSlider.y,current.w,volumeSlider.h};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
    SDL_RenderFillRect(renderer, &sliderBar);
    RenderText(std::to_string( Mix_VolumeMusic( volumeSlider.x / 19 ) ).c_str() ,White,0,0,fontSize);
//    if( SDL_PointInRect(&mousePosition, &volumeSlider) & SDL_BUTTON(SDL_BUTTON_LEFT) )
//    {
//        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
//        {
//            volumeSlider.x = mousePosition.x;
//            volumeSlider.x = volumeSlider.x - (volumeSlider.w / 2);
//            volumeSlider.x = volumeSlider.x + x;
//        }
//    }
    SDL_RenderFillRect(renderer, &volumeSlider);
//    int display_count = 0, display_index = 0, mode_index = 0;
//    SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
//
//    static int display_in_use = 0; /* Only using first display */
//    int i;
//    Uint32 f;
//
//    SDL_Log("SDL_GetNumVideoDisplays(): %i", SDL_GetNumVideoDisplays());
//    //SDL_Delay(0);
//
//    SDL_DisplayMode currentDisplayMode;
//    SDL_BlendMode currentBlendMode;
//    SDL_RendererInfo info;
//    SDL_GetCurrentDisplayMode(0, &currentDisplayMode);
//    SDL_GetRenderDrawBlendMode(renderer,&currentBlendMode);
//    SDL_GetRendererInfo(renderer, &info);
//
//
//
//    std::string rendererInfoText = "";
//    rendererInfoText += info.name;
//    std::string blendModeText = "";
//
//    if(currentBlendMode == SDL_BLENDMODE_NONE )
//    {
//        blendModeText += "No blending";
//    }
//    else if(currentBlendMode == SDL_BLENDMODE_BLEND )
//    {
//        blendModeText += "Alpha blending";
//    }
//    else if(currentBlendMode == SDL_BLENDMODE_ADD )
//    {
//        blendModeText += "Additive blending";
//    }
//    else if(currentBlendMode == SDL_BLENDMODE_MOD )
//    {
//        blendModeText += "Color modulate";
//    }
//
//    std::string ResolutionText = "";
//    ResolutionText += std::to_string(currentDisplayMode.w);
//    ResolutionText += "x";
//    ResolutionText += std::to_string(currentDisplayMode.h);
//    ResolutionText += "@";
//    ResolutionText += std::to_string(currentDisplayMode.refresh_rate);
//    ResolutionText += " ( ";
//    ResolutionText += std::to_string(SDL_BITSPERPIXEL(currentDisplayMode.format));
//    ResolutionText += " ) ";
//
//    RenderText("SETTINGS",White,140,180,48);
//
//    RenderText("Graphics",White,current.w - 1200,210,32);
//    RenderText("Blend mode:",White,current.w - 1200,300,24);
//    RenderText(blendModeText.c_str(),White,current.w - 1200,330,fontSize);
//    RenderText(rendererInfoText.c_str(),White,current.w - 1200,360,fontSize);
//    RenderText(std::to_string(SDL_GetNumRenderDrivers()).c_str() ,White,current.w - 1200,390,fontSize);
//
//    SDL_Rect sliderBar = {25,765,current.w - 50,25};
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
//    SDL_RenderFillRect(renderer, &sliderBar);
//
//    RenderText("Sound",White,0,650,32);
//    std::string VolumeText = "";
//    VolumeText += std::to_string(Mix_VolumeMusic(-1));
//    RenderText("Volume:",White,0,700,24);
//    RenderText(VolumeText.c_str(),White,200,700,fontSize);
//
//    RenderText("Resolution",White,current.w - 400,210,32);
//    RenderText("Current resolution:",White,current.w - 400,300,24);
//    RenderText(ResolutionText.c_str(),White,current.w - 400,330,fontSize);
//
//    // Get current display mode of all displays.
//    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
//    {
//        int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);
//
//        if(should_be_zero != 0)
//        {
//          SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
//          RenderText("ERRROR!!!",White,140,240,fontSize);
//        }
//        else
//        {
//            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, current.w, current.h, current.refresh_rate);
//            //std::cout << current.w << " X " << current.h << "@" << current.refresh_rate << " format: " << current.format << std::endl;
//        }
//    }
//
//    if (SDL_GetDisplayMode(display_index, mode_index, &mode) != 0)
//    {
//        SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
//    }
//
//    std::string Resolution = "";
//    Resolution += std::to_string(mode.w);
//
//    if (SDL_GetDisplayMode(0, 0, &mode) != 0)
//    {
//        SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
//    }
//
//    Resolution += std::to_string(mode.w);
//

//
//    SDL_RenderFillRect(renderer, &volumeSlider);
//
//    if( SDL_PointInRect(&mousePosition, &volumeSlider) & SDL_BUTTON(SDL_BUTTON_LEFT) )
//    {
//        int x,y = 0;
//        SDL_GetRelativeMouseState(&x,&y);
//
//        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
//        {
//            //volumeSlider.x += mousePosition.x;
//            volumeSlider.x = mousePosition.x;
//            volumeSlider.x = volumeSlider.x - (volumeSlider.w / 2);
//            volumeSlider.x = volumeSlider.x + x;
//        }
//        RenderText(std::to_string(x).c_str() ,White,current.w - 1200,500,40);
//        RenderText(std::to_string(volumeSlider.x / 100).c_str() ,White,current.w - 1200,550,40);
//    }
//    else
//    {
//        if(activeView == mainmenu && SettingsMenu)
//            if(mousePosition.y > volumeSlider.y && mousePosition.y < volumeSlider.y + volumeSlider.h)
//                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
//                {
//                    volumeSlider.x = mousePosition.x;
//                    volumeSlider.x = volumeSlider.x - (volumeSlider.w / 2);
//                    if( volumeSlider.x < 0 )
//                        volumeSlider.x = 0;
//                    if(volumeSlider.x > current.w)
//                        volumeSlider.x = current.w - volumeSlider.w;
//                }
//        RenderText(std::to_string(volumeSlider.x / 19).c_str() ,White,current.w - 1200,550,40);
//    }
//    if( volumeSlider.x < 0 )
//        volumeSlider.x = 0;
//    if(volumeSlider.x >= current.w - volumeSlider.w)
//        volumeSlider.x = current.w - volumeSlider.w;
//
//    if(activeView == mainmenu && SettingsMenu)
//        if(mousePosition.y > volumeSlider.y && mousePosition.y < volumeSlider.y + volumeSlider.h)
//        {
//            MusicVolume = volumeSlider.x / 20;
//            Mix_VolumeMusic(MusicVolume);
//        }
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
    RenderText("Exit",White,current.w - 150,current.h - 50,fontSize);
};

#endif // RENDER_SETTINGS_H
