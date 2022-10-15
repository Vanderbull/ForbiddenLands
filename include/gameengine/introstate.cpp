#include <stdio.h>

#include <sys/types.h>
#include <sys/sysinfo.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>

#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "introstate.h"

CIntroState CIntroState::m_IntroState;

struct sysinfo memInfo;

void CIntroState::Init()
{
    SDL_Log("CIntroState Init");

    /* Conversion constants. */
     const long minute = 60;
     const long hour = minute * 60;
     const long day = hour * 24;
     const double megabyte = 1024 * 1024;
     /* Obtain system statistics. */
     struct sysinfo si;
     sysinfo (&si);
     /* Summarize interesting values. */
     SDL_Log("system uptime : %ld days, %ld:%02ld:%02ld\n",
         si.uptime / day, (si.uptime % day) / hour,
         (si.uptime % hour) / minute, si.uptime % minute);
     SDL_Log("total RAM : %5.1f MB\n", si.totalram / megabyte);
     SDL_Log("free RAM : %5.1f MB\n", si.freeram / megabyte);
     SDL_Log("process count : %d\n", si.procs);

    sysinfo (&memInfo);
    long long totalVirtualMem = memInfo.totalram;
    //Add other values in next statement to avoid int overflow on right hand side...
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;

    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
    //Add other values in next statement to avoid int overflow on right hand side...
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;

    SDL_Log("Total Virtual Memory: %llu",totalVirtualMem);
    SDL_Log("Virtual Memory Used: %llu",virtualMemUsed);

    std::string location, room, position;
    std::string fileType = "-fs8.png";
    int progress_value = 0;

    ofstream myfile;
    myfile.open ("example.txt");
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

                myfile << location << "\n";
                imagesFiles.push_back(location);
            }
        }
    }
    myfile.close();
    x=y=z=0;
}

void CIntroState::Cleanup()
{
	SDL_Log("CIntroState Cleanup\n");
    SDL_DestroyTexture(texture);
}

void CIntroState::Pause()
{
	SDL_Log("CIntroState Pause\n");
}

void CIntroState::Resume()
{
	SDL_Log("CIntroState Resume\n");
}

void CIntroState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CIntroState HandleEvents\n");

	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_SPACE:
						break;

					case SDLK_ESCAPE:
						game->Quit();
						break;
				}
				break;
		}
	}
}

void CIntroState::Update(CGameEngine* game)
{
    SDL_Log("CIntroState Update\n");
}

void CIntroState::Draw(CGameEngine* game)
{
	SDL_Log("CIntroState Draw\n");
    static int progress_value = 0;

    std::string load_location = "";
    load_location = imagesFiles.front();
    game->mapTextureFile[x][y][z] = load_location;
    game->mapTexture[x][y][z] = IMG_LoadTexture(game->renderer,load_location.c_str());
    imagesFiles.erase(imagesFiles.begin());

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );

    SDL_RenderClear(game->renderer);

    if( texture == NULL )
        texture = game->LoadTexture("./images/menus/menu_backdrop.png",255);

    SDL_RenderCopy(game->renderer, texture, NULL, NULL);

    SDL_Rect progressbar_border = {game->current.w / 2 - 1024/2,game->current.h - 200,1024,25};
    SDL_SetRenderDrawColor( game->renderer, 0, 0, 0, 255 );
    SDL_RenderFillRect(game->renderer, &progressbar_border);

    SDL_Rect progressbar = {game->current.w / 2 - 1024/2,game->current.h - 200,progress_value,25};
    progress_value++;
    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0,255);
    SDL_RenderFillRect(game->renderer, &progressbar);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255,255);
    SDL_RenderDrawRect(game->renderer, &progressbar);

    game->RenderText("Loading Level...",White,game->current.w / 2 - 100,game->current.h - 245, 24);
    game->RenderText(load_location.c_str(),White,game->current.w / 3,game->current.h - 205,24);

    if( z < 3 )
    {
        z++;
    }
    else
    {
        z = 0;

        if( y < 15 )
        {
            y++;
        }
        else
        {
            y = 0;
            x++;
        }
    }

    if( x == 16 )
    {
        game->ChangeState( CMenuState::Instance() );
    }
}
