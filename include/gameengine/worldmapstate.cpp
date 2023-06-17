/// @file worldmapstate.cpp
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>

#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "playstate.h"
#include "villagestate.h"
#include "worldmapstate.h"

CWorldMapState CWorldMapState::m_WorldMapState;

void CWorldMapState::Init()
{
	SDL_Log("CWorldMapState Init\n");

	std::cout << std::endl;
    for(int y = 0; y < 34; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            std::cout << grid[y][x] << " ";
            if( grid[y][x] == LAND )
            if( rand()%50 < 3 )
            {
                grid[y][x] = POI;
            }
        }
        std:cout << std::endl;
    }

//	for( int i=0; i <10; i++)
//	{
//        do
//        {
//            Point_Of_Interest[i].x = (rand()%10)*32;
//            Point_Of_Interest[i].y = rand()%33*32;
//            Point_Of_Interest[i].h = 32;
//            Point_Of_Interest[i].w = 32;
//        } while( grid[Point_Of_Interest[i].y][Point_Of_Interest[i].x] == WATER );
//	}

//    for( int i=0; i <10; i++)
//	{
//        if( grid[Point_Of_Interest[i].y][Point_Of_Interest[i].x] == WATER )
//        {
//            exit(99);
//        }
//        else
//        {
//            std::cout << grid[Point_Of_Interest[i].y][Point_Of_Interest[i].x] << std::endl;
//        }
//	}
//	exit(99);

	float scale  = 1.0f;
	SDL_Rect offset;

    for(int x = 0; x < 10; ++x)
    {
        for(int y = 0; y < 34; ++y)
        {
            // calculate the sample positions
            float samplePosX = (float)x * scale + offset.x;
            float samplePosY = (float)y * scale + offset.y;
            float normalization = 0.0f;
            // loop through each wave
            // TODO
            // normalize the value
            Noise_Map[x][y] /= normalization;
        }
    }
}

void CWorldMapState::Cleanup()
{
	SDL_Log("CWorldMapState Cleanup\n");
}

void CWorldMapState::Pause()
{
	SDL_Log("CWorldMapState Pause\n");
}

void CWorldMapState::Resume()
{
	SDL_Log("CWorldMapState Resume\n");
}

void CWorldMapState::HandleEvents(CGameEngine* game)
{
    SDL_Log("CWorldMapState");
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
                        game->ChangeState( CMenuState::Instance() );
						break;
                    case SDLK_w:
                        if( game->SActor.WorldmapCoordinate.y > 0 )
                        {
                            if( grid[game->SActor.WorldmapCoordinate.y - 1][game->SActor.WorldmapCoordinate.x] == LAND)
                            {
                                game->SActor.WorldmapCoordinate.y--;
                                game->Ship.Position_Y--;
                                game->Army_On_Ship = false;
                            }
                            else if( grid[game->SActor.WorldmapCoordinate.y - 1][game->SActor.WorldmapCoordinate.x] == WATER)
                            {
                                game->SActor.WorldmapCoordinate.y--;
                                game->Army_On_Ship = true;
                            }
                        }
                        game->SActor.hunger++;
                        game->SActor.thirst++;
                        game->Daytime++;
                        game->Elapsed_Time++;
                        break;
                    case SDLK_d:
                        if( game->SActor.WorldmapCoordinate.x < 9 )
                        {
                            if( grid[game->SActor.WorldmapCoordinate.y][game->SActor.WorldmapCoordinate.x + 1] == LAND)
                            {
                                game->SActor.WorldmapCoordinate.x++;
                                game->Ship.Position_X++;
                                game->Army_On_Ship = false;
                            }
                            else if( grid[game->SActor.WorldmapCoordinate.y][game->SActor.WorldmapCoordinate.x + 1] == WATER)
                            {
                                game->SActor.WorldmapCoordinate.x++;
                                game->Army_On_Ship = true;
                            }
                        }
                        game->SActor.hunger++;
                        game->SActor.thirst++;
                        game->Daytime++;
                        game->Elapsed_Time++;
                        break;
                    case SDLK_s:
                        if( game->SActor.WorldmapCoordinate.y < 33 )
                        {
                            if( grid[game->SActor.WorldmapCoordinate.y + 1][game->SActor.WorldmapCoordinate.x] == LAND)
                            {
                                game->SActor.WorldmapCoordinate.y++;
                                game->Ship.Position_Y++;
                                game->Army_On_Ship = false;
                            }
                            else if( grid[game->SActor.WorldmapCoordinate.y + 1][game->SActor.WorldmapCoordinate.x] == WATER)
                            {
                                game->SActor.WorldmapCoordinate.y++;
                                game->Army_On_Ship = true;
                            }
                        }
                        game->SActor.hunger++;
                        game->SActor.thirst++;
                        game->Daytime++;
                        game->Elapsed_Time++;
                        break;
                    case SDLK_a:
                        if( game->SActor.WorldmapCoordinate.x > 0 )
                        {
                            if( grid[game->SActor.WorldmapCoordinate.y][game->SActor.WorldmapCoordinate.x -1] == LAND)
                            {
                                game->SActor.WorldmapCoordinate.x--;
                                game->Ship.Position_X--;
                                game->Army_On_Ship = false;
                            }
                            else if( grid[game->SActor.WorldmapCoordinate.y][game->SActor.WorldmapCoordinate.x -1] == WATER)
                            {
                                game->SActor.WorldmapCoordinate.x--;
                                game->Army_On_Ship = true;
                            }
                        }
                        game->SActor.hunger++;
                        game->SActor.thirst++;
                        game->Daytime++;
                        game->Elapsed_Time++;
                        break;
				}
				break;
		}
	}
}

void CWorldMapState::Update(CGameEngine* game)
{
    SDL_Log("CWorldMapState Update");
    ///--- Store the current information to the previous
    m_iPreviousCoordX=m_iCurrentCoordX;
    m_iPreviousCoordY=m_iCurrentCoordY;
    m_uPreviousMouseState=m_uCurrentMouseState;

    ///--- Update the current state of the mouse
    m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

    ///--- Set the wheel back to 0
    m_iWheelX=0;
    m_iWheelY=0;

    if( game->Daytime >3)
        game->Daytime = 0;

    game->fog_of_war_worldmap[game->SActor.WorldmapCoordinate.x-30][game->SActor.WorldmapCoordinate.y] = 1;
    game->fog_of_war_worldmap[game->SActor.WorldmapCoordinate.x-31][game->SActor.WorldmapCoordinate.y] = 1;
    game->fog_of_war_worldmap[game->SActor.WorldmapCoordinate.x-29][game->SActor.WorldmapCoordinate.y] = 1;
    game->fog_of_war_worldmap[game->SActor.WorldmapCoordinate.x-30][game->SActor.WorldmapCoordinate.y-1] = 1;
    game->fog_of_war_worldmap[game->SActor.WorldmapCoordinate.x-30][game->SActor.WorldmapCoordinate.y+1] = 1;

}

void CWorldMapState::Draw(CGameEngine* game)
{
    SDL_Log("CWorldMapState Draw");

    SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
//
//    // Draw water squares
//    for(int x = 30; x < 40; x++ )
//    {
//        for(int y = 0; y < game->current.h / 31; y++ )
//        {
//            SDL_Rect gRect = { x*32,y*32, 32, 32 };
//            SDL_RenderFillRect(game->renderer, &gRect);
//        }
//    }

    // Draw sweden
	SDL_Texture* texture = game->LoadTexture("./assets/data/textures/sweden.png",255);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect gRect = { 0,0, texW, texH };

    // Set the desired color modulation (e.g., red)
//    SDL_SetTextureColorMod(texture, 0, 192, 0);  // Set RGB values for red (255, 0, 0)

    SDL_RenderCopy(game->renderer, texture, NULL, &gRect);
    SDL_DestroyTexture(texture);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

    SDL_Rect WorldmapLocation = {0,0,0,0};
    SDL_Rect Uppsala_Location = {32,0,32,32};
    SDL_Rect Sigtuna_Location = {64,0,32,32};
    SDL_Rect Birka_Location = {96,0,32,32};
    SDL_Rect Lund_Location = {128,0,32,32};
    SDL_Rect Soderkoping_Location = {160,0,32,32};
    SDL_Rect Visby_Location = {192,0,32,32};
    SDL_Rect Vastergarn_Location = {288,0,32,32};

    SDL_RenderFillRect(game->renderer, &Uppsala_Location);
    SDL_RenderFillRect(game->renderer, &Birka_Location);
    SDL_RenderFillRect(game->renderer, &Sigtuna_Location);
    SDL_RenderFillRect(game->renderer, &Lund_Location);
    SDL_RenderFillRect(game->renderer, &Soderkoping_Location);
    SDL_RenderFillRect(game->renderer, &Visby_Location);
    SDL_RenderFillRect(game->renderer, &Vastergarn_Location);

    OFFSET = 0;
    WorldmapLocation.x = game->SActor.WorldmapCoordinate.x*32 + OFFSET;
    WorldmapLocation.y = game->SActor.WorldmapCoordinate.y*32 + OFFSET;
    WorldmapLocation.h = 32;
    WorldmapLocation.w = 32;

    if( SDL_RectEquals(&WorldmapLocation, &Uppsala_Location) )
    {
        game->Village_Name = "Uppsala";
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }
    if( SDL_RectEquals(&WorldmapLocation, &Birka_Location) )
    {
        game->Village_Name = "Birka";
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }
    if( SDL_RectEquals(&WorldmapLocation, &Sigtuna_Location) )
    {
        game->Village_Name = "Sigtuna";
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }
    if( SDL_RectEquals(&WorldmapLocation, &Lund_Location) )
    {
        game->Village_Name = "Lund";
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }

    if( SDL_RectEquals(&WorldmapLocation, &Soderkoping_Location) )
    {
        game->Village_Name = "Söderköping";
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }

    if( SDL_RectEquals(&WorldmapLocation, &Visby_Location) )
    {
        game->Village_Name = "Visby";
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }

    if( SDL_RectEquals(&WorldmapLocation, &Vastergarn_Location) )
    {
        game->Village_Name = "Västergarn";
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }

    SDL_Rect Forage_Button = { 400, 32,90,23};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Forage_Button);
    game->RenderText("forage", game->White, Forage_Button.x,Forage_Button.y,24);

    if( SDL_PointInRect(&mousePosition, &Forage_Button) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 128, 128, 192);
        SDL_RenderFillRect(game->renderer, &Forage_Button);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            if( game->SActor.thirst > 0 || game->SActor.hunger > 0)
            {
                game->Elapsed_Time++;
                if(game->SActor.hunger > 0)
                {
                    game->SActor.hunger -= rand()%5;
                    if(game->SActor.hunger < 0)
                    {
                        game->SActor.hunger = 0;
                    }
                }
                if(game->SActor.thirst > 0)
                {
                    game->SActor.thirst -= rand()%5;
                    if(game->SActor.thirst < 0)
                    {
                        game->SActor.thirst = 0;
                    }
                }
            }
        }
    }

    for(int y = 0; y < 34; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            if( grid[y][x] == POI)
            {
                Point_Of_Interest[0].x = x*32;
                Point_Of_Interest[0].y = y*32;
                Point_Of_Interest[0].h = 32;
                Point_Of_Interest[0].w = 32;
                SDL_RenderCopy(game->renderer, game->North, NULL, &Point_Of_Interest[0]);
            }

        }
    }
//	for( int i=0; i <10; i++)
//	{
//        SDL_RenderCopy(game->renderer, game->North, NULL, &Point_Of_Interest[i]);
//
//
//        if( SDL_RectEquals(&WorldmapLocation, &Point_Of_Interest[i]) )
//        {
//            game->ChangeState( CPlayState::Instance() );
//            game->SActor.WorldmapCoordinate.x += 1;
//        }
//        if( SDL_PointInRect(&mousePosition, &Point_Of_Interest[i]) )
//        {
//            game->RenderText("Point of interest: " + std::to_string(i),game->White,game->current.w - 300,gRect.y +  80,24);
//        }
//	}

    if( SDL_PointInRect(&mousePosition, &Uppsala_Location) )
    {
        game->RenderText("Uppsala",game->White,game->current.w - 300,gRect.y +  180,24);
    }
    if( SDL_PointInRect(&mousePosition, &Birka_Location) )
    {
        game->RenderText("Birka",game->White,game->current.w - 300,gRect.y +  180,24);
    }
    if( SDL_PointInRect(&mousePosition, &Sigtuna_Location) )
    {
        game->RenderText("Sigtuna",game->White,game->current.w - 300,gRect.y +  180,24);
    }
    if( SDL_PointInRect(&mousePosition, &Lund_Location) )
    {
        game->RenderText("Lund",game->White,game->current.w - 300,gRect.y +  180,24);
    }
    if( SDL_PointInRect(&mousePosition, &Soderkoping_Location) )
    {
        game->RenderText("Söderköping",game->White,game->current.w - 300,gRect.y +  180,24);
    }
    if( SDL_PointInRect(&mousePosition, &Visby_Location) )
    {
        game->RenderText("Visby",game->White,game->current.w - 300,gRect.y +  180,24);
    }
    if( SDL_PointInRect(&mousePosition, &Vastergarn_Location) )
    {
        game->RenderText("Västergarn",game->White,game->current.w - 300,gRect.y +  180,24);
    }

    std::string Position = "(" + std::to_string(game->SActor.WorldmapCoordinate.x) + "," + std::to_string(game->SActor.WorldmapCoordinate.y) + ")";
    //std::string Position2 = "(" + std::to_string(game->SActor.WorldmapCoordinate.x - 30) + "," + std::to_string(game->SActor.WorldmapCoordinate.y) + ")";

    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    game->RenderText(Position.c_str(),0,0,48);
    //game->RenderText(Position2.c_str(),0,50,48);
//
//    game->RenderText("Hunger: " + std::to_string(game->SActor.hunger),game->White,80,gRect.y +  40,24);
//    game->RenderText("Thirst: " + std::to_string(game->SActor.thirst),game->White,80,gRect.y +  80,24);
//
//    game->RenderText("Old: " + std::to_string(game->Raiding_Party.old),game->White,80,gRect.y +  120,24);
//    game->RenderText("Middleaage: " + std::to_string(game->Raiding_Party.middleage),game->White,80,gRect.y +  160,24);
//    game->RenderText("Young: " + std::to_string(game->Raiding_Party.young),game->White,80,gRect.y +  200,24);
//
//    game->RenderText("Elapsed time: " + std::to_string(game->Elapsed_Time),game->White,80,gRect.y +  250,24);

    //game->renderDaytime();

//    for(int x = 0; x < 10; x++ )
//    {
//        for(int y = 0; y < 35; y++ )
//        {
//            if( game->fog_of_war_worldmap[x][y] == 0 )
//            {
//                SDL_Rect imageSize = {x*32+30*32, y*32,32,32};
//                SDL_SetRenderDrawColor(game->renderer, 128,128, 128, 255);
//                SDL_RenderFillRect(game->renderer, &imageSize);
//            }
//        }
//    }



    if( game->Army_On_Ship == false )
    {
        // Render raiding party
        SDL_Texture* Raiding_Party_Icon = game->LoadTexture("./assets/data/textures/icons/army-32.png",255);
        SDL_RenderCopy(game->renderer, Raiding_Party_Icon, NULL, &WorldmapLocation);
    }
    else
    {
        // Render ship
        SDL_Texture* ship = game->LoadTexture("./assets/data/textures/icons/ship.png",255);
        texW = 0;
        texH = 0;
        SDL_QueryTexture(ship, NULL, NULL, &texW, &texH);

        gRect = { 32*game->SActor.WorldmapCoordinate.x,32*game->SActor.WorldmapCoordinate.y, texW/16, texH/16 };
        SDL_RenderCopy(game->renderer, ship, NULL, &gRect);
    }

//        // Render the button
//        SDL_Rect buttonRect;
//        buttonRect.x = (1920 - 200) / 2;
//        buttonRect.y = (1080 - 100) / 2;
//        buttonRect.w = 200;
//        buttonRect.h = 100;
//
//        // Render the button with a gradient
//        for (int i = 0; i < 100; i++)
//        {
//            // Calculate gradient color
//            Uint8 r = 255 - (i * 255 / 100);
//            Uint8 g = i * 255 / 100;
//            Uint8 b = 0;
//
//            // Set the color
//            SDL_SetRenderDrawColor(game->renderer, r, g, b, 255);
//
//            // Render the row of the button
//            SDL_Rect rowRect = { buttonRect.x, buttonRect.y + i, buttonRect.w, 1 };
//            SDL_RenderFillRect(game->renderer, &rowRect);
//        }
//
//        buttonRect.x = 0;
//        buttonRect.y = 0;
//        buttonRect.w = 200;
//        buttonRect.h = 100;
//
//        // Render the button with a pulsating effect
//        Uint8 r = 255;
//        Uint8 g = 0;
//        Uint8 b = 0;
//        Uint8 alpha = 255;
//
//        // Calculate the alpha value based on time for the pulsating effect
//        alpha = static_cast<Uint8>((SDL_GetTicks() / 10) % 255);
//
//        // Set the color and alpha
//        SDL_SetRenderDrawColor(game->renderer, r, g, b, alpha);
//
//        // Render the button
//        SDL_RenderFillRect(game->renderer, &buttonRect);
// Calculate the position of the rectangle
// Screen dimensions
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    // Rectangle dimensions
    const int RECT_WIDTH = 200;
    const int RECT_HEIGHT = 150;

    // Border color
    SDL_Color borderColor = { 255, 255, 255 };

    // Centered text
//    int rectX = (SCREEN_WIDTH - RECT_WIDTH) / 2;
//    int rectY = (SCREEN_HEIGHT - RECT_HEIGHT) / 2;

    int rectX = (SCREEN_WIDTH - RECT_WIDTH);
    int rectY = 0;

    // Draw the filled rectangle
    SDL_Rect filledRect = { rectX, rectY, RECT_WIDTH, RECT_HEIGHT };
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); // Fill color: red
    SDL_RenderFillRect(game->renderer, &filledRect);

    // Draw the border
    SDL_Rect borderRect = { rectX, rectY, RECT_WIDTH, RECT_HEIGHT };
    SDL_SetRenderDrawColor(game->renderer, borderColor.r, borderColor.g, borderColor.b, 255); // Border color
    SDL_RenderDrawRect(game->renderer, &borderRect);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

    game->RenderText("Old: " + std::to_string(game->Raiding_Party.old),rectX,rectY,24);
    game->RenderText("Middleaage: " + std::to_string(game->Raiding_Party.middleage),rectX,rectY + 50,24);
    game->RenderText("Young: " + std::to_string(game->Raiding_Party.young),rectX,rectY + 100,24);

    // Rectangle dimensions
    const int RECT_WIDTH2 = 200;
    const int RECT_HEIGHT2 = 150;

    // Border color
    //SDL_Color borderColor = { 255, 255, 255 };

    // Centered text
//    int rectX = (SCREEN_WIDTH - RECT_WIDTH) / 2;
//    int rectY = (SCREEN_HEIGHT - RECT_HEIGHT) / 2;

    int rectX2 = (SCREEN_WIDTH - RECT_WIDTH2);
    int rectY2 = RECT_HEIGHT;

    // Draw the filled rectangle
    SDL_Rect filledRect2 = { rectX2, rectY2, RECT_WIDTH2, RECT_HEIGHT2 };
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); // Fill color: red
    SDL_RenderFillRect(game->renderer, &filledRect2);

    // Draw the border
    SDL_Rect borderRect2 = { rectX2, rectY2, RECT_WIDTH2, RECT_HEIGHT2 };
    SDL_SetRenderDrawColor(game->renderer, borderColor.r, borderColor.g, borderColor.b, 255); // Border color
    SDL_RenderDrawRect(game->renderer, &borderRect2);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

    game->RenderText("Hunger: " + std::to_string(game->SActor.hunger),rectX2,rectY2,24);
    game->RenderText("Thirst: " + std::to_string(game->SActor.thirst),rectX2,rectY2 + 50,24);
    game->RenderText("Elapsed time: " + std::to_string(game->Elapsed_Time),rectX2,rectY2 + 100,24);

    if( grid[game->SActor.WorldmapCoordinate.y][game->SActor.WorldmapCoordinate.x] == WATER)
    {
        game->RenderText("WATER",game->SActor.WorldmapCoordinate.x*32 + 100,game->SActor.WorldmapCoordinate.y*32,24);
    }

    game->RenderText("debug_array: " + std::to_string(debug_array_2[game->SActor.WorldmapCoordinate.x][game->SActor.WorldmapCoordinate.y]),0,1000,48);
}
