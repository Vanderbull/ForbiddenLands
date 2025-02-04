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
//#include "menustate.h"
#include "playstate.h"
#include "villagestate.h"
#include "loadingstate.h"

CLoadingState CLoadingState::m_LoadingState;

void CLoadingState::Init()
{
    SDL_Log("CLoadingState Init");

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

                location += "./assets/data/textures/test_map/";
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

void CLoadingState::Cleanup()
{
	SDL_Log("CLoadingState Cleanup\n");
    SDL_DestroyTexture(texture);
}

void CLoadingState::Pause()
{
	SDL_Log("CLoadingState Pause\n");
}

void CLoadingState::Resume()
{
	SDL_Log("CLoadingState Resume\n");
}

void CLoadingState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CLoadingState HandleEvents\n");

	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						game->Quit();
						break;
				}
				break;
		}
	}
}

void CLoadingState::Update(CGameEngine* game)
{
    SDL_Log("CLoadingState Update\n");
}

void CLoadingState::Draw(CGameEngine* game)
{
	SDL_Log("CLoadingState Draw\n");

    for( auto& [name, item] : game->ItemObject)
    {
        std::cout << name << item.Icon << std::endl;
    }

    // Extract the x,y,z position from the filename
    // ./assets/data/textures/test_map/0000E-fs8.png
    // EWNS

//    std::cout << "Character starting position: " << game->SActor.PlayerCoordinate.x << ","
//                                                << game->SActor.PlayerCoordinate.y << ","
//                                                << game->SActor.PlayerCoordinate.z << ",";

    game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][0] = IMG_LoadTexture(game->renderer,"./assets/data/textures/test_map/1501E-fs8.png");
    game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][1] = IMG_LoadTexture(game->renderer,"./assets/data/textures/test_map/1501W-fs8.png");
    game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][2] = IMG_LoadTexture(game->renderer,"./assets/data/textures/test_map/1501N-fs8.png");
    game->mapTexture[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y][3] = IMG_LoadTexture(game->renderer,"./assets/data/textures/test_map/1501S-fs8.png");

    //game->mapTexture[game->SActor.PlayerCoordinate.x-1][game->SActor.PlayerCoordinate.y][0] = IMG_LoadTexture(game->renderer,"./assets/data/textures/test_map/1401E-fs8.png");
    //game->mapTexture[game->SActor.PlayerCoordinate.x-1][game->SActor.PlayerCoordinate.y][1] = IMG_LoadTexture(game->renderer,"./assets/data/textures/test_map/1401W-fs8.png");
    //game->mapTexture[game->SActor.PlayerCoordinate.x-1][game->SActor.PlayerCoordinate.y][2] = IMG_LoadTexture(game->renderer,"./assets/data/textures/test_map/1401N-fs8.png");
    //game->mapTexture[game->SActor.PlayerCoordinate.x-1][game->SActor.PlayerCoordinate.y][3] = IMG_LoadTexture(game->renderer,"./assets/data/textures/test_map/1401S-fs8.png");

    game->ChangeState( CVillageState::Instance() );

    static int progress_value = 0;
    static int finished = 0;

    if( finished > 0 )
        game->ChangeState( CPlayState::Instance() );

    std::string load_location = "";
    load_location = imagesFiles.front();
    //game->mapTextureFile[x][y][z] = load_location;
    game->mapTexture[x][y][z] = IMG_LoadTexture(game->renderer,load_location.c_str());
    imagesFiles.erase(imagesFiles.begin());

    if( texture == NULL )
        texture = game->LoadTexture("./assets/data/textures/menus/menu_backdrop.png",255);

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
        finished = 1;
        game->ChangeState( CPlayState::Instance() );
    }

}
