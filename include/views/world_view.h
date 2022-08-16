#ifndef WORLD_VIEW_H
#define WORLD_VIEW_H

#include <regex>

#include "common.h"

int OFFSET = 50;

/**
 * @brief Tokenize the given vector
   according to the regex
 * and remove the empty tokens.
 *
 * @param str
 * @param re
 * @return std::vector<std::string>
 */
std::vector<std::string> tokenize(
                     const std::string str,
                          const std::regex re)
{
    std::sregex_token_iterator it{ str.begin(),
                             str.end(), re, -1 };
    std::vector<std::string> tokenized{ it, {} };

    // Additional check to remove empty strings
    tokenized.erase(
        std::remove_if(tokenized.begin(),
                            tokenized.end(),
                       [](std::string const& s) {
                           return s.size() == 0;
                       }),
        tokenized.end());

    return tokenized;
}

int writeSaveFile( std::string mapActive, std::string fileName )
{
    if( mapActive == "phlan")
    {
        std::ofstream ofs (fileName.c_str(), std::ofstream::out);
        for( int y = 0; y < 16; y++)
            for( int x = 0; x < 16; x++)
            {
                ofs << x << " " << y << " ";
                ofs << save_portals[x][y].west << " " << save_portals[x][y].east << " ";
                ofs << save_portals[x][y].south << " " << save_portals[x][y].north << " ";
                ofs << save_portals[x][y].west_map << " " << save_portals[x][y].east_map << " " << save_portals[x][y].north_map << " " << save_portals[x][y].south_map << " ";
                ofs << save_portals[x][y].warp_x << " " << save_portals[x][y].warp_y << " " << save_portals[x][y].description;
                ofs << std::endl;
            }
        ofs.close();

        std::string oldname = "./data/maps/";
        oldname += mapActive.c_str();
        oldname += "/";
        oldname += mapActive.c_str();
        oldname += "_portals_out";

        std::string newname = "./data/maps/";
        newname += mapActive.c_str();
        newname += "/";
        newname += mapActive.c_str();
        newname += "_portals";

        /*	Deletes the file if exists */
        if (rename(oldname.c_str(), newname.c_str()) != 0)
            perror("Error renaming file");
        else
            cout << "File renamed successfully";

        mainLog.push_back(newname.c_str());
    }
    else
    {
        mainLog.push_back("Failed to write the map save file...");
    }
};

void savePortals()
{
    if( mapActive == "phlan")
    {
        writeSaveFile("phlan", "./data/maps/phlan/phlan_portals_out");
    }
    else if( mapActive == "slums")
    {
        writeSaveFile("slums", "./data/maps/slums/slums_portals_out");
    }
    else if( mapActive == "khutos_well")
    {
        writeSaveFile("khutos_well", "./data/maps/khutos_well/khutos_well_portals_out");
    }
    else if( mapActive == "podal_plaza")
    {
        writeSaveFile("podal_plaza", "./data/maps/podal_plaza/podal_plaza_portals_out");
    }
};

void navigationButtons()
{
    SDL_Rect west = {0,current.h - 100,50,50};
    SDL_Rect east = {100,current.h - 100,50,50};
    SDL_Rect north = {50,current.h - 150,50,50};
    SDL_Rect south = {50,current.h - 50,50,50};

    SDL_Rect save = {200,current.h - 50,50,50};
    SDL_Rect load = {200,current.h - 150,50,50};

    SDL_Rect randomEncounterButton = {current.w / 2,350,200,50};

    SDL_Rect hunger = {250,current.h - 350,playerCharacter[playerCharacterSelected].hunger*1,25};
    SDL_Rect thirst = {250,current.h - 300,playerCharacter[playerCharacterSelected].thirst*1,25};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    SDL_RenderFillRect(renderer, &hunger);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255,255);
    SDL_RenderFillRect(renderer, &thirst);

    SDL_Rect health[6];
    SDL_Rect experience[6];

    float theValue = ( 105.0f / playerCharacter[0].hitpoints_max ) * playerCharacter[0].hitpoints_current;
    std::cout << "theValue: " << theValue << std::endl;

    health[0] = {610,current.h - 225, ( 105.0f / playerCharacter[0].hitpoints_max ) * playerCharacter[0].hitpoints_current, 25};
     experience[0] = {610,current.h - 200,105,25};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    SDL_RenderFillRect(renderer, &health[0]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255,255);
    SDL_RenderFillRect(renderer, &experience[0]);

     health[1] = {720,current.h - 225,( 105.0f / playerCharacter[1].hitpoints_max ) * playerCharacter[1].hitpoints_current,25};
     experience[1] = {720,current.h - 200,105,25};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    SDL_RenderFillRect(renderer, &health[1]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255,255);
    SDL_RenderFillRect(renderer, &experience[1]);

     health[2] = {830,current.h - 225,( 105.0f / playerCharacter[2].hitpoints_max ) * playerCharacter[2].hitpoints_current,25};
     experience[2] = {830,current.h - 200,105,25};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    SDL_RenderFillRect(renderer, &health[2]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255,255);
    SDL_RenderFillRect(renderer, &experience[2]);

     health[3] = {940,current.h - 225,( 105.0f / playerCharacter[3].hitpoints_max ) * playerCharacter[3].hitpoints_current,25};
     experience[3] = {940,current.h - 200,105,25};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    SDL_RenderFillRect(renderer, &health[3]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255,255);
    SDL_RenderFillRect(renderer, &experience[3]);

     health[4] = {1050,current.h - 225,( 105.0f / playerCharacter[4].hitpoints_max ) * playerCharacter[4].hitpoints_current,25};
     experience[4] = {1050,current.h - 200,105,25};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    SDL_RenderFillRect(renderer, &health[4]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255,255);
    SDL_RenderFillRect(renderer, &experience[4]);

     health[5] = {1160,current.h - 225,( 105.0f / playerCharacter[5].hitpoints_max ) * playerCharacter[5].hitpoints_current,25};
     experience[5] = {1160,current.h - 200,105,25};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    SDL_RenderFillRect(renderer, &health[5]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255,255);
    SDL_RenderFillRect(renderer, &experience[5]);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    SDL_RenderFillRect(renderer, &save);
    SDL_RenderFillRect(renderer, &load);

    if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].encounter )
    {
        SDL_RenderFillRect(renderer, &randomEncounterButton);
        randomEncounterButton.x += 2;
        randomEncounterButton.y += 2;
        randomEncounterButton.w -= 4;
        randomEncounterButton.h -= 4;
        SDL_SetRenderDrawColor(renderer, 255, 0, 255,255);
        SDL_RenderFillRect(renderer, &randomEncounterButton);

        RenderText("BATTLE IT", White, randomEncounterButton.x +10, randomEncounterButton.y +10 / 2,20);
        if( SDL_PointInRect(&mousePosition, &randomEncounterButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                activeView = BATTLE;
                randomEncounters = 1;
                SDL_Delay(50);
            }
        }
    }

    if( SDL_PointInRect(&mousePosition, &save) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            savePortals();
        }
    }
    //loadPortals();
    if( SDL_PointInRect(&mousePosition, &load) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            loadPortals();
        }
    }

    if( SDL_PointInRect(&mousePosition, &west) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].west == 1)
            {
                save_portals[PlayerCoordinate.x][PlayerCoordinate.y].west = 0;
            }
            else
            {
                save_portals[PlayerCoordinate.x][PlayerCoordinate.y].west = 1;
            }
        }
        SDL_Delay(50);
    }
    if( SDL_PointInRect(&mousePosition, &east) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].east == 1)
            {
                save_portals[PlayerCoordinate.x][PlayerCoordinate.y].east = 0;
            }
            else
            {
                save_portals[PlayerCoordinate.x][PlayerCoordinate.y].east = 1;
            }
        }
        SDL_Delay(50);
    }
    if( SDL_PointInRect(&mousePosition, &north) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].north == 1)
            {
                save_portals[PlayerCoordinate.x][PlayerCoordinate.y].north = 0;
            }
            else
            {
                save_portals[PlayerCoordinate.x][PlayerCoordinate.y].north = 1;
            }
        }
        SDL_Delay(50);
    }
    if( SDL_PointInRect(&mousePosition, &south) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].south == 1)
            {
                save_portals[PlayerCoordinate.x][PlayerCoordinate.y].south = 0;
            }
            else
            {
                save_portals[PlayerCoordinate.x][PlayerCoordinate.y].south = 1;
            }
        }
        SDL_Delay(50);
    }

    if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].west == 1)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    }
    SDL_RenderFillRect(renderer, &west);

    if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].east == 1)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    }
    SDL_RenderFillRect(renderer, &east);

    if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].north == 1)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    }
    SDL_RenderFillRect(renderer, &north);

    if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].south == 1)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    }
    SDL_RenderFillRect(renderer, &south);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);

    RenderText("W", Black, west.x, west.y,12);
    RenderText("E", Black, east.x, east.y,12);
    RenderText("N", Black, north.x, north.y,12);
    RenderText("S", Black, south.x, south.y,12);

    RenderText("SAVE", Black, save.x, save.y,12);
    RenderText("LOAD", Black, load.x, load.y,12);
    RenderText(save_portals[PlayerCoordinate.x][PlayerCoordinate.y].east_map, Black, load.x + 200, load.y - 200,24);
    RenderText(save_portals[PlayerCoordinate.x][PlayerCoordinate.y].west_map, Black, load.x - 200, load.y - 200,24);
    RenderText(save_portals[PlayerCoordinate.x][PlayerCoordinate.y].north_map, Black, load.x, load.y - 300,24);
    RenderText(save_portals[PlayerCoordinate.x][PlayerCoordinate.y].south_map, Black, load.x, load.y - 100,24);

    RenderText(std::to_string(worldMap), Black, load.x, load.y - 50,24);
    RenderText("Encounter: " + std::to_string(save_portals[PlayerCoordinate.x][PlayerCoordinate.y].encounter), Black, 0, load.y - 450,24);

    renderQuests();
};

// Should preload all the images here to speedup framerate

void loadMapTextures()
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
                    location += "N";
                if(z == 1)
                    location += "S";
                if(z == 2)
                    location += "W";
                if(z == 3)
                    location += "E";

                location += fileType;
                //std::cout << "mapTexture[x][y][z] = " << location << " : " << "(" << x << ")"<< "(" << y << ")"<< "(" << z << ")" << std::endl;
                mapTextureFile[x][y][z] = location;
                mapTexture[x][y][z] = LoadTexture(location.c_str(),255);
            }
        }
    }
};

std::string generateImagePath()
{
    std::string location, room, position;
    std::string fileType = ".png";

    location += "./images/test_map/";
    room  = "";

    if(PlayerCoordinate.x < 10)
    {
        room += "0";
    }

    room += std::to_string(PlayerCoordinate.x);

    if(PlayerCoordinate.y < 10)
    {
        room += "0";
    }

    room += std::to_string(PlayerCoordinate.y);

    position = room;
    room += "/";

    room += position;
    location += position;

    location += Rotation;
    location += fileType;

    return location;
};

void renderMinimapCharacterLocation()
{
    gRect.x = PlayerCoordinate.x*16 + OFFSET;
    gRect.y = PlayerCoordinate.y*16 + OFFSET;
    gRect.h = 16;
    gRect.w = 16;

    if( Rotation == "N")
    {
        SDL_RenderCopy(renderer, North, NULL, &gRect);
    }
    if( Rotation == "E")
    {
        SDL_RenderCopy(renderer, East, NULL, &gRect);
    }
    if( Rotation == "S")
    {
        SDL_RenderCopy(renderer, South, NULL, &gRect);
    }
    if( Rotation == "W")
    {
        SDL_RenderCopy(renderer, West, NULL, &gRect);
    }
}

void renderFaces()
{
    SDL_Rect faceBox[6];
    faceBox[0] = {500 + 110,current.h - 165,105,165};
    faceBox[1] = {500 + 110*2,current.h - 165,105,165};
    faceBox[2] = {500 + 110*3,current.h - 165,105,165};
    faceBox[3] = {500 + 110*4,current.h - 165,105,165};
    faceBox[4] = {500 + 110*5,current.h - 165,105,165};
    faceBox[5] = {500 + 110*6,current.h - 165,105,165};

    SDL_Texture* faceTexture = LoadTexture("./icons/faces/11.png",255);
    SDL_RenderCopy(renderer, playerCharacter[0].faceImage, NULL, &faceBox[0]);
    SDL_RenderCopy(renderer, playerCharacter[1].faceImage, NULL, &faceBox[1]);
    SDL_RenderCopy(renderer, playerCharacter[2].faceImage, NULL, &faceBox[2]);
    SDL_RenderCopy(renderer, playerCharacter[3].faceImage, NULL, &faceBox[3]);
    SDL_RenderCopy(renderer, playerCharacter[4].faceImage, NULL, &faceBox[4]);
    SDL_RenderCopy(renderer, playerCharacter[5].faceImage, NULL, &faceBox[5]);
    SDL_DestroyTexture(faceTexture);

    for( int i = 0; i < 6; i++ )
    {
        if( SDL_PointInRect(&mousePosition, &faceBox[i]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255,128);
            SDL_RenderFillRect(renderer, &faceBox[i]);
            RenderText("MORE", Green, faceBox[i].x, faceBox[i].y,fontSize);
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacterSelected = i;
                offset2 = 0;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255,128);
    SDL_RenderDrawRect(renderer, &faceBox[playerCharacterSelected]);
}

void renderWorldViewA()
{
    std::string location = generateImagePath();

    if( PlayerCoordinate.x > 15 )
    {
        std::cout << "There was some strange error please check" << std::endl;
        exit(16);
    }

    int z = 0;
    if(Rotation == "N")
        z= 0;
    if(Rotation == "S")
        z= 1;
    if(Rotation == "W")
        z = 2;
    if(Rotation == "E")
        z=3;
    //currentViewTexture = LoadTexture(location.c_str(),255);
    //std::cout << location << " = " << mapTextureFile[PlayerCoordinate.x][PlayerCoordinate.y][z] << std::endl;

    SDL_RenderCopy(renderer, mapTexture[PlayerCoordinate.x][PlayerCoordinate.y][z], NULL, NULL);
    //SDL_RenderCopy(renderer, currentViewTexture, NULL, NULL);
    //SDL_DestroyTexture(currentViewTexture);

    if( activeView != BATTLE )
    {
        renderCompass();

        if(minimapActive)
        {
            renderMinimap(mapActive);
            renderMinimapCharacterLocation();
        }
        navigationButtons();
        adventureMenu();
    }

    renderFaces();

    // add a item array for storqge of dropped loot here
    if( lootDropped )
    {
        save_portals[PlayerCoordinate.x][PlayerCoordinate.y].droppedLoot = lootDropped;
        resetLootDropped();
    }

    if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].droppedLoot )
    {
        RenderText("LOOT HERE!!",Green,600,0,48);
    }
};

#endif
