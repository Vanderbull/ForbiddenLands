#include <stdio.h>

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

void CIntroState::Init()
{
	printf("CIntroState Init\n");
	//read_directory("./images",imagesFiles);

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
	printf("CIntroState Cleanup\n");
	    SDL_DestroyTexture(texture);
}

void CIntroState::Pause()
{
	printf("CIntroState Pause\n");
}

void CIntroState::Resume()
{
	printf("CIntroState Resume\n");
}

void CIntroState::HandleEvents(CGameEngine* game)
{
//	SDL_Event event;
//
//	if (SDL_PollEvent(&event)) {
//		switch (event.type) {
//			case SDL_QUIT:
//				game->Quit();
//				break;
//
//			case SDL_KEYDOWN:
//				switch (event.key.keysym.sym) {
//					case SDLK_SPACE:
//						break;
//
//					case SDLK_ESCAPE:
//						game->Quit();
//						break;
//				}
//				break;
//		}
//	}
}

void CIntroState::Update(CGameEngine* game)
{
	//printf("CIntroState Update\n");
}

void CIntroState::Draw(CGameEngine* game)
{
//    std::cout << x++;
//    if(x == 1024)
//    game->ChangeState( CMenuState::Instance() );
//    return;

	//printf("CIntroState Draw\n");
    static int progress_value = 0;

    //std::chrono::time_point<std::chrono::steady_clock> starter;
    //std::chrono::time_point<std::chrono::steady_clock> ender;

    //starter = std::chrono::steady_clock::now();

    //std::string location, room, position;
    //std::string fileType = "-fs8.png";

    std::string load_location = "";
    load_location = imagesFiles.front();
    game->mapTextureFile[x][y][z] = load_location;
    game->mapTexture[x][y][z] = IMG_LoadTexture(game->renderer,load_location.c_str());
    imagesFiles.erase(imagesFiles.begin());

    SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );

    SDL_RenderClear(game->renderer);

    if( texture == NULL )
        texture = game->LoadTexture("./images/menus/mainmenu.jpg",255);
    //SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    //SDL_SetTextureAlphaMod( texture, 255 );
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    //SDL_SetRenderTarget( game->renderer, texture );

    //SDL_DestroyTexture(texture);

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
    //SDL_RenderPresent(game->renderer);



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
//        std::cout << "x:" << x << " y:" << y << " z:" << z << std::endl;
        //exit(0);
        game->ChangeState( CMenuState::Instance() );
    }

    //game->ChangeState( CMenuState::Instance() );

    //std::cout << "counter: " << counter++ << std::endl;





//    for(int x = 0; x < 16; x++ )
//    {
//        for(int y = 0; y < 16; y++ )
//        {
//            for(int z = 0; z < 4; z++ ) // ESWN directions
//            {
//                location = "";
//                room = "";
//                position = "";
//
//                location += "./images/test_map/";
//                room  = "";
//
//                if(x < 10)
//                {
//                    room += "0";
//                }
//
//                room += std::to_string(x);
//
//                if(y < 10)
//                {
//                    room += "0";
//                }
//
//                room += std::to_string(y);
//
//                position = room;
//                room += "/";
//
//                room += position;
//                location += position;
//
//                //location += Rotation;
//                if(z == 0)
//                    location += "E";
//                if(z == 1)
//                    location += "W";
//                if(z == 2)
//                    location += "N";
//                if(z == 3)
//                    location += "S";
//
//                location += fileType;
//
//                //std::cout << "mapTexture[x][y][z] = " << location << " : " << "(" << x << ")"<< "(" << y << ")"<< "(" << z << ")" << std::endl;
//                //location = "./images/profile_photo3.png";
//                game->mapTextureFile[x][y][z] = location;
//
//                game->mapTexture[x][y][z] = IMG_LoadTexture(game->renderer,location.c_str());
//
//                //exit(1);
//                //myTextures[std::to_string(progress_value).c_str()] = IMG_LoadTexture(renderer,location.c_str());
//                SDL_SetRenderDrawColor( game->renderer, 255, 255, 255, 255 );
//                SDL_RenderClear(game->renderer);
//
//                SDL_Surface* surface = IMG_Load( "./images/ui/rest_no_rune.png" );
//                if( !surface )
//                {
//                    exit(-1);
//                }
//
//                SDL_Texture* texture = SDL_CreateTextureFromSurface( game->renderer, surface );
//                SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//                SDL_SetTextureAlphaMod( texture, 255 );
//                SDL_RenderCopy(game->renderer, texture, NULL, NULL);
//                SDL_FreeSurface(surface);
//                SDL_DestroyTexture(texture);
//
//                SDL_Rect progressbar_border = {game->current.w / 2 - 1024/2,game->current.h - 200,1024,25};
//                SDL_SetRenderDrawColor( game->renderer, 0, 0, 0, 255 );
//                SDL_RenderFillRect(game->renderer, &progressbar_border);
//
//                SDL_Rect progressbar = {game->current.w / 2 - 1024/2,game->current.h - 200,progress_value,25};
//                progress_value++;
//                SDL_SetRenderDrawColor(game->renderer, 0, 255, 0,255);
//                SDL_RenderFillRect(game->renderer, &progressbar);
//                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255,255);
//                SDL_RenderDrawRect(game->renderer, &progressbar);
//
//                game->RenderText("Loading Level...",White,game->current.w / 2 - 100,game->current.h - 245, 24);
//                game->RenderText(location.c_str(),White,game->current.w / 3,game->current.h - 205,24);
//                SDL_RenderPresent(game->renderer);
//            }
//        }
//    }

    //ender = std::chrono::steady_clock::now();
    //std::cout << "Millisecond loading time: " << double(std::chrono::duration_cast<std::chrono::nanoseconds>(ender - starter).count()) / 1000000 << std::endl;
    // 20357 milliseconds
    //exit(99);

    //game->ChangeState( CMenuState::Instance() );
}
