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

	for( int i=0; i <10; i++)
	{
        Point_Of_Interest[i].x = (30 + rand()%10)*32;
        Point_Of_Interest[i].y = rand()%33*32;
        Point_Of_Interest[i].h = 32;
        Point_Of_Interest[i].w = 32;
	}

	float scale  = 1.0f;
	SDL_Rect offset;

    for(int x = 0; x < 10; ++x)
    {
        for(int y = 0; y < 33; ++y)
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
                            game->SActor.WorldmapCoordinate.y--;
                        game->SActor.hunger++;
                        game->SActor.thirst++;
                        break;
                    case SDLK_d:
                        if( game->SActor.WorldmapCoordinate.x < 39 )
                            game->SActor.WorldmapCoordinate.x++;
                        game->SActor.hunger++;
                        game->SActor.thirst++;
                        break;
                    case SDLK_s:
                        if( game->SActor.WorldmapCoordinate.y < (1080 / 32) - 1 )
                            game->SActor.WorldmapCoordinate.y++;
                        game->SActor.hunger++;
                        game->SActor.thirst++;
                        break;
                    case SDLK_a:
                        if( game->SActor.WorldmapCoordinate.x > 30 )
                            game->SActor.WorldmapCoordinate.x--;
                        game->SActor.hunger++;
                        game->SActor.thirst++;
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

//    game->fog_of_war_worldmap[0][0] = 1;
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
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 255);
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);

    for(int x = 30; x < 40; x++ )
    {
        for(int y = 0; y < game->current.h / 31; y++ )
        {
            SDL_Rect gRect = { x*32,y*32, 32, 32 };
            SDL_RenderFillRect(game->renderer, &gRect);
        }
    }
//	SDL_Texture* water_texture = game->LoadTexture("./assets/data/textures/backgrounds/water.png",255);
//	SDL_Texture* water_texture2 = game->LoadTexture("./assets/data/textures/backgrounds/water.png",255);
//
//	SDL_SetTextureBlendMode(water_texture,SDL_BLENDMODE_NONE);
//
//	SDL_SetTextureBlendMode(water_texture2,SDL_BLENDMODE_BLEND);
//    SDL_RenderCopy(game->renderer, water_texture, NULL, &water_x_rect);
//    //SDL_DestroyTexture(water_texture);
//    SDL_RenderCopy(game->renderer, water_texture, NULL, &water_x_rect2);
//    SDL_DestroyTexture(water_texture);
//
//    SDL_RenderCopy(game->renderer, water_texture2, NULL, &water_y_rect);
//    //SDL_DestroyTexture(water_texture2);
//    SDL_RenderCopy(game->renderer, water_texture2, NULL, &water_y_rect2);
//    SDL_DestroyTexture(water_texture2);


    water_x_rect.x+=2;
    if(water_x_rect.x > 1919)
        water_x_rect.x = 0;
    water_x_rect2.x+=2;
    if(water_x_rect2.x > 1919)
        water_x_rect2.x = -1919;

    water_y_rect.y++;
    if(water_y_rect.y > 1079)
        water_y_rect.y = 0;
    water_y_rect2.y++;
    if(water_y_rect2.y > 1079)
        water_y_rect2.y = -1079;

	SDL_Texture* texture = game->LoadTexture("./assets/data/textures/sweden.png",255);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

    SDL_Rect gRect = { game->current.w/2,0, 300, 1080 };

    SDL_RenderCopy(game->renderer, texture, NULL, &gRect);
    SDL_DestroyTexture(texture);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

//    for(int x = 30; x < 40; x++ )
//    {
//        for(int y = 0; y < game->current.h / 32; y++ )
//        {
//            SDL_Rect gRect = { x*32,y*32, 32, 32 };
//            SDL_RenderDrawRect(game->renderer, &gRect);
//        }
//    }
    //game->renderWorldMapTiles();
    SDL_Rect WorldmapLocation;
    SDL_Rect moraMapLocation = {35*32,5*32,32,32};
    SDL_Rect vallentunaMapLocation = {35*32,25*32,32,32};
    SDL_Rect kustenstadMapLocation = {35*32,15*32,32,32};



    SDL_RenderFillRect(game->renderer, &moraMapLocation);
    SDL_RenderFillRect(game->renderer, &vallentunaMapLocation);
    SDL_RenderFillRect(game->renderer, &kustenstadMapLocation);

    OFFSET = 0;
    WorldmapLocation.x = game->SActor.WorldmapCoordinate.x*32 + OFFSET;
    WorldmapLocation.y = game->SActor.WorldmapCoordinate.y*32 + OFFSET;
    WorldmapLocation.h = 32;
    WorldmapLocation.w = 32;

    //SDL_RenderCopy(game->renderer, game->North, NULL, &WorldmapLocation);

    SDL_Texture* Raiding_Party_Icon = game->LoadTexture("./assets/data/textures/icons/army-32.png",255);

    SDL_RenderCopy(game->renderer, Raiding_Party_Icon, NULL, &WorldmapLocation);

    if( SDL_RectEquals(&WorldmapLocation, &moraMapLocation) )
    {
        game->Village_Name = "Mora";
        game->SActor.cityMap = 2;
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }
    if( SDL_RectEquals(&WorldmapLocation, &vallentunaMapLocation) )
    {
        game->Village_Name = "Vallentuna";
        game->SActor.cityMap = 1;
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }
    if( SDL_RectEquals(&WorldmapLocation, &kustenstadMapLocation) )
    {
        game->Village_Name = "Kustenstad";
        game->SActor.cityMap = 0;
        game->ChangeState( CVillageState::Instance() );
        game->SActor.WorldmapCoordinate.x += 1;
    }

    SDL_Rect Forage_Button = { 200, 32,90,23};
    SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 192);
    SDL_RenderFillRect(game->renderer, &Forage_Button);
    game->RenderText("forage", White, Forage_Button.x,Forage_Button.y,24);

    if( SDL_PointInRect(&mousePosition, &Forage_Button) )
    {
        SDL_SetRenderDrawColor(game->renderer, 255, 128, 128, 192);
        SDL_RenderFillRect(game->renderer, &Forage_Button);
        if( IsButtonReleased(SDL_BUTTON(SDL_BUTTON_LEFT)) )
        {
            if( game->SActor.thirst > 0 || game->SActor.hunger > 0)
            {
                game->gameTime.tm_hour += 24;
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

	for( int i=0; i <10; i++)
	{
        //SDL_RenderFillRect(game->renderer, &Point_Of_Interest[i]);
        SDL_RenderCopy(game->renderer, game->North, NULL, &Point_Of_Interest[i]);


        if( SDL_RectEquals(&WorldmapLocation, &Point_Of_Interest[i]) )
        {
            game->SActor.cityMap = 2;
            game->ChangeState( CPlayState::Instance() );
            game->SActor.WorldmapCoordinate.x += 1;
        }
        if( SDL_PointInRect(&mousePosition, &Point_Of_Interest[i]) )
        {
            game->RenderText("Point of interest: " + std::to_string(i),White,game->current.w - 300,gRect.y +  80,24);
        }
	}

    if( SDL_PointInRect(&mousePosition, &moraMapLocation) )
    {
        game->RenderText("Mora city location",White,game->current.w - 300,gRect.y +  80,24);
    }
    if( SDL_PointInRect(&mousePosition, &vallentunaMapLocation) )
    {
        game->RenderText("Vallentuna city location",White,game->current.w - 300,gRect.y +  80,24);
    }
    if( SDL_PointInRect(&mousePosition, &kustenstadMapLocation) )
    {
        game->RenderText("Kustenstad city location",White,game->current.w - 300,gRect.y +  80,24);
    }

    game->RenderText(std::to_string(game->SActor.WorldmapCoordinate.x),White,gRect.x,gRect.y,24);
    game->RenderText(std::to_string(game->SActor.WorldmapCoordinate.y),White,gRect.x + 40,gRect.y,24);
    game->RenderText("Hunger: " + std::to_string(game->SActor.hunger),White,80,gRect.y +  40,24);
    game->RenderText("Thirst: " + std::to_string(game->SActor.thirst),White,80,gRect.y +  80,24);

    game->RenderText("Old: " + std::to_string(game->Raiding_Party.old),White,80,gRect.y +  120,24);
    game->RenderText("Middleaage: " + std::to_string(game->Raiding_Party.middleage),White,80,gRect.y +  160,24);
    game->RenderText("Young: " + std::to_string(game->Raiding_Party.young),White,80,gRect.y +  200,24);

    game->currentTimeElapse(true);
    game->renderDaytime();
//
//   for (int x = 0; x < GRID_WIDTH; x++) {
//        for (int y = 0; y < GRID_HEIGHT; y++) {
//            SDL_Rect rect = {x * CELL_SIZE,y * CELL_SIZE ,CELL_SIZE ,CELL_SIZE };
//            if (grid[x][y] == WATER) {
//                SDL_SetRenderDrawColor(game->renderer ,0x00 ,0x00 ,0xFF ,0xFF );
//            } else if (grid[x][y] == LAND) {
//                SDL_SetRenderDrawColor(game->renderer ,0x00 ,0xFF ,0x00 ,0xFF );
//            }
//            SDL_RenderFillRect(game->renderer ,&rect );
//        }
//    }



    for(int x = 0; x < 10; x++ )
    {
        for(int y = 0; y < 35; y++ )
        {
            if( game->fog_of_war_worldmap[x][y] == 0 )
            {
                SDL_Rect imageSize = {x*32+30*32, y*32,32,32};
                SDL_SetRenderDrawColor(game->renderer, 128,128, 128, 255);
                SDL_RenderFillRect(game->renderer, &imageSize);
            }
//            else
//            {
//                SDL_Rect imageSize = {x*32+30*32, y*32,32,32};
//                SDL_SetRenderDrawColor(game->renderer, 0,255, 0, 255);
//                SDL_RenderFillRect(game->renderer, &imageSize);
//            }
        }
    }
}
