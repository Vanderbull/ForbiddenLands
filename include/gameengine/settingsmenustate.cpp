#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "settingsmenustate.h"

CSettingsMenuState CSettingsMenuState::m_SettingsMenuState;

void CSettingsMenuState::Init()
{
	SDL_Log("CSettingsMenuState Init\n");

    MenuChoices.clear();
    MenuChoices.push_back("EXIT");
}

void CSettingsMenuState::Cleanup()
{
	SDL_Log("CSettingsMenuState Cleanup\n");
}

void CSettingsMenuState::Pause()
{
	SDL_Log("CSettingsMenuState Pause\n");
}

void CSettingsMenuState::Resume()
{
	SDL_Log("CSettingsMenuState Resume\n");
}

void CSettingsMenuState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CSettingsMenuState HandleEvents\n");

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

void CSettingsMenuState::Update(CGameEngine* game)
{
    SDL_Log("CSettingsMenuState Update\n");

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

float angle = 0.0f;
void CSettingsMenuState::Draw(CGameEngine* game)
{
    SDL_Log("CSettingsMenuState Draw");
    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
    SDL_RenderClear(game->renderer);

    int Repeat = 0;
    int buttonWidth = 600;
    int buttonHeight = 60;

    for(auto MenuChoice : MenuChoices)
    {
        SDL_Rect buttonPosition = { (game->current.w / 2) - (buttonWidth / 2), 300 + (Repeat*(buttonPosition.h+15)),buttonWidth,buttonHeight};

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

    Mix_Volume(-1, -1);
    game->RenderText("Resolution: " + std::to_string(game->current.w) + " x " + std::to_string(game->current.h) + " @ " + std::to_string(SDL_BITSPERPIXEL(game->current.format)), game->Black, 50,50,48);
    game->RenderText("Volume: " + std::to_string( Mix_Volume(-1, -1) ), game->Black, 50,100,48);

    std::ifstream status_file("/proc/self/status");
    std::string line;

    while (std::getline(status_file, line)) {
        if (line.substr(0, 6) == "VmSize") {
            double VmSize = std::stod(line.substr(7));
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << VmSize/1024;
            std::string VmSize_String = ss.str();
            //VmSize = std::round(static_cast<double>(VmSize) / 1024.0);
            //VmSize = std::round(VmSize * 100) / 100;
            game->RenderText("Virtual memory size: " + VmSize_String + " MB", game->Black, 50,150,48);
        }
        else if (line.substr(0, 5) == "VmRSS") {
            game->RenderText("Resident set size: " + line.substr(6), game->Black, 50,200,48);
        }
    }

    // Get system information
    int num_cpus = SDL_GetCPUCount();
    int ram_mb = SDL_GetSystemRAM();
    std::string platform_str = SDL_GetPlatform();

    // Get power info
    int secs_left = -1;
    int percent_left = -1;

    if (SDL_GetPowerInfo(&secs_left, &percent_left) == SDL_POWERSTATE_ON_BATTERY) {
    game->RenderText("Battery: " + std::to_string(percent_left) + "%", game->Black, 50,450,48);
    }
    if (SDL_GetPowerInfo(&secs_left, &percent_left) == SDL_POWERSTATE_CHARGING) {
    game->RenderText("Charging: " + std::to_string(percent_left) + "%", game->Black, 50,450,48);
    }
    if (SDL_GetPowerInfo(&secs_left, &percent_left) == SDL_POWERSTATE_CHARGED) {
    game->RenderText("Charged: " + std::to_string(percent_left) + "%", game->Black, 50,450,48);
    }
#ifdef _WIN32
    SYSTEM_INFO sys_info;

    GetSystemInfo(&sys_info);

    int num_logical_cpus = sys_info.dwNumberOfProcessors;
#else
    int num_logical_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#endif

    game->RenderText("Number of CPUs: " + std::to_string(num_cpus), game->Black, 50,250,48);
    game->RenderText("Number of logical CPUs: " + std::to_string(num_logical_cpus), game->Black, 50,300,48);
    game->RenderText("System RAM: " + std::to_string(ram_mb), game->Black, 50,350,48);
    game->RenderText("Platform: " + platform_str, game->Black, 50,400,48);

	const SDL_Vertex triangleVertex[3] = {
		{
			{ 600.f, 10.f },
			{ 220, 220, 220, 0xFF },
			{ 0.f, 0.f }
		},
		{
			{ 600.f, 310.f },
			{ 220, 220, 220, 0xFF },
			{ 0.f, 0.f }
		},
		{
			{ 910.f, 120.f },
			{ 220, 220, 220, 0xFF },
			{ 0.f, 0.f }
		}
	};

        // Set up the model matrix
        float model_matrix[16];
        model_matrix[0] = std::cos(angle);
        model_matrix[1] = -std::sin(angle);
        model_matrix[4] = std::sin(angle);
        model_matrix[5] = std::cos(angle);
        model_matrix[10] = 1.0f;
        model_matrix[15] = 1.0f;

		if ( SDL_RenderGeometry(game->renderer, NULL, triangleVertex, 3, NULL, 0) < 0 )
		{
			SDL_Log("%s\n", SDL_GetError());
		}

}
