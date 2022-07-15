#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "portals.h"

int testing = 0;

void CGameEngine::Init(const char* title, int width, int height,
						 int bpp, bool fullscreen)
{
    std::cout << "Game engine initializing..." << "\n";

	int flags = 0;

	SDL_SetMainReady();

    if( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    else
    {
        SDL_Log("initialize SDL and all its subsystems: Success");
    }

    if(!TTF_WasInit() && TTF_Init()==-1)
    {
        SDL_Log("TTF_Init: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    else
    {
        SDL_Log("TTF_Init: Success!");
    }

    // Get current display mode of all displays.
    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
    {
        int should_be_zero = SDL_GetCurrentDisplayMode(i, &monitor[i]);

        current = monitor[0];

        if(should_be_zero != 0)
        {
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
            exit(EXIT_FAILURE);
        }
        else
        {
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, monitor[i].w, monitor[i].h, monitor[i].refresh_rate);
        }
    }

    window = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        current.w, current.h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == NULL)
    {
        SDL_Log("Could not create window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    else
    {
        SDL_Log("SDL Window creation: SUCCESS");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_Log("SDL Renderer creation: SUCCESS");

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderSetScale(renderer,1.0,1.0);

        // load support for the JPG and PNG image formats
        int flags=IMG_INIT_JPG|IMG_INIT_PNG;
        int initted=IMG_Init(flags);

        if((initted&flags) != flags)
        {
            printf("IMG_Init: %s\n", IMG_GetError());
            exit(EXIT_FAILURE);
        }

        if( strcmp(uts.machine, "x86_64") == 0 )
            gSurface = IMG_Load( "./icons/64-bit-100.png" );
        else
            gSurface = IMG_Load( "./icons/64-bit-100-filled.png" );

        if(!gSurface)
        {
            SDL_Log("Setting Window Icon: %s\n", IMG_GetError());
            exit(EXIT_FAILURE);
        }
        else
        {
            SDL_Log("Loading Window Icon initiated...");
            SDL_Log("Version: %s",AutoVersion::FULLVERSION_STRING);
        }

        SDL_SetWindowIcon(window, gSurface);
        SDL_FreeSurface(gSurface);

        SDL_StopTextInput();

        // Replace this with the new SDL2 OpenAudio
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            SDL_Log("Audio broke down: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        else
        {
            SDL_Log("Audio successfully initiated...");
        }
    }

	m_fullscreen = fullscreen;
	m_running = true;
	loadMapTextures();
}

void CGameEngine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() )
    {
		states.back()->Cleanup();
		states.pop_back();
	}

	printf("CGameEngine Cleanup\n");

	// shutdown SDL
	SDL_Quit();
}

void CGameEngine::ChangeState(CGameState* state)
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CGameEngine::PushState(CGameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CGameEngine::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}

void CGameEngine::HandleEvents()
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void CGameEngine::Update()
{
	// let the state update the game
	states.back()->Update(this);
}

void CGameEngine::Draw()
{
	// let the state draw the screen
	states.back()->Draw(this);
}

int CGameEngine::RenderText(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", fontSize);

    gSurface = TTF_RenderText_Blended(m_font, renderText.c_str(), colorValue);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX, iY, texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    TTF_CloseFont(m_font);
    m_font = NULL;
    fontSize = 0;
    return 0;
}

int CGameEngine::RenderTitle(std::string renderText, SDL_Color colorValue, int iX, int iY)
{
    gSurface = TTF_RenderText_Blended(gameTitleFont, renderText.c_str(), colorValue);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    return 0;
}

int CGameEngine::RenderBreadText(std::string renderText, SDL_Color colorValue, int iX, int iY)
{
    gSurface = TTF_RenderText_Blended(gameBreadTextFont, renderText.c_str(), colorValue);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    return 0;
}

int CGameEngine::RenderText2(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", fontSize);

    gSurface = TTF_RenderText_Blended(m_font, renderText.c_str(), colorValue);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    TTF_CloseFont(m_font);
    m_font = NULL;
    fontSize = 0;
    return 0;
}

int CGameEngine::RenderText3(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", fontSize);

    gSurface = TTF_RenderText_Blended_Wrapped(m_font, renderText.c_str(), colorValue,1000);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    TTF_CloseFont(m_font);
    m_font = NULL;
    fontSize = 0;
    return 0;
}

int CGameEngine::RenderTextWrapped(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize, int wrapped)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", fontSize);

    gSurface = TTF_RenderText_Blended_Wrapped(m_font, renderText.c_str(), colorValue,wrapped);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    TTF_CloseFont(m_font);
    m_font = NULL;
    fontSize = 0;
    return 0;
}

SDL_Texture* CGameEngine::LoadTexture( const std::string &str, int alpha )
{
	SDL_Surface* surface = IMG_Load( str.c_str() );
	if( !surface )
	{
        SDL_Log("LoadTexture failed to load image named: %s",str.c_str());
        std::cout << "LoadTexture failed to load image named: " << str.c_str() << std::endl;
        exit(-1);
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( texture, alpha );
    SDL_FreeSurface(surface);
	return texture;
};

void CGameEngine::loadMapTextures()
{
    std::string location, room, position;
    std::string fileType = ".png";

    for(int x = 0; x < 16; x++ )
    {
        for(int y = 0; y < 16; y++ )
        {
            for(int z = 0; z < 4; z++ ) // ESWN directions
            {
                location = "";
                room = "";
                position = "";

                location += "./images/test_map/";
                room  = "";

                if(x < 10)
                {
                    room += "0";
                }

                room += std::to_string(x);

                if(y < 10)
                {
                    room += "0";
                }

                room += std::to_string(y);

                position = room;
                room += "/";

                room += position;
                location += position;

                //location += Rotation;
                if(z == 0)
                    location += "E";
                if(z == 1)
                    location += "W";
                if(z == 2)
                    location += "N";
                if(z == 3)
                    location += "S";

                location += fileType;
                //std::cout << "mapTexture[x][y][z] = " << location << " : " << "(" << x << ")"<< "(" << y << ")"<< "(" << z << ")" << std::endl;
                mapTextureFile[x][y][z] = location;
                mapTexture[x][y][z] = LoadTexture(location.c_str(),255);
                SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                SDL_RenderClear(renderer);

                SDL_Rect aButton = {0,0,500,500};
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 128);
                SDL_RenderFillRect(renderer, &aButton);
                RenderText(location.c_str(),Black,500,180,48);
                SDL_RenderPresent(renderer);
            }
        }
    }

};
