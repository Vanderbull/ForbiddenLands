
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"

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
        if((initted&flags) != flags) {
            printf("IMG_Init: Failed to init required jpg and png support!\n");
            printf("IMG_Init: %s\n", IMG_GetError());
            exit(EXIT_FAILURE);
            // handle error
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
            //SDL_Log("Version: %s",AutoVersion::FULLVERSION_STRING);
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
	// initialize SDL
	//SDL_Init(SDL_INIT_VIDEO);

	// set the title bar text
//	SDL_WM_SetCaption(title, title);

//	if ( fullscreen ) {
//		flags = SDL_FULLSCREEN;
//	}

	// create the screen surface
//	screen = SDL_SetVideoMode(width, height, bpp, flags);

	m_fullscreen = fullscreen;
	m_running = true;
}

void CGameEngine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// switch back to windowed mode so other
	// programs won't get accidentally resized
//	if ( m_fullscreen ) {
//		screen = SDL_SetVideoMode(640, 480, 0, 0);
//	}

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
