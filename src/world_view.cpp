#include "world_view.h"

void worldView()
{
};

void renderWorldViewA()
{
//    std::cout << "renderWorldView" << std::endl;
//
//
//    std::string location, room, position;
//    std::string fileType = ".png";
//
//    std::cout << room << std::endl;
//    std::cout << position << std::endl;
//
//    location += "./images/test_map/";
//    room  = "";
//
//    if(PlayerCoordinate.x < 10)
//    {
//        room += "0";
//    }
//
//    room += std::to_string(PlayerCoordinate.x);
//
//    std::cout << room << std::endl;
//    std::cout << position << std::endl;
//
//    if(PlayerCoordinate.y < 10)
//    {
//        room += "0";
//    }
//
//    room += std::to_string(PlayerCoordinate.y);
//
//    position = room;
//    room += "/";
//
//    room += position;
//    location += position;
//
//    location += Rotation;
//    location += fileType;
//
//    std::cout << room << std::endl;
//    std::cout << location << std::endl;
//    std::cout << position << std::endl;
//
//    currentViewTexture = LoadTexture(location.c_str(),255);
//    SDL_RenderCopy(renderer, currentViewTexture, NULL, NULL);
//    SDL_DestroyTexture(currentViewTexture);
//
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    minimapActive = true;
//    if(minimapActive)
//    {
//        if( mapActive == "phlan")
//        {
//            renderMapPhlan();
//            RenderPhlanEdges();
//        }
//       else if( mapActive == "khutos well")
//        {
//            renderMapKhutosWell();
//            RenderKhutosWellEdges();
//        }
//        else if( mapActive == "slums")
//        {
//            renderMapSlums();
//            RenderSlumsEdges();
//        }
//        else if( mapActive == "mantors library")
//        {
//            renderMapMantorsLibrary();
//            RenderMantorsLibraryEdges();
//        }
//        else if( mapActive == "podal plaza")
//        {
//            renderMapPodalPlaza();
//            RenderPodalPlazaEdges();
//        }
//        else if( mapActive == "cardona textile house")
//        {
//            renderMapCardonaTextileHouse();
//            RenderCardonaTextileHouseEdges();
//        }
//        else if( mapActive == "stojsnow gate")
//        {
//            renderMapStojsnowGate();
//            RenderStojsnowGateEdges();
//        }
//
//        if( Rotation == "N")
//        {
//            gRect.x = PlayerCoordinate.x*15 + OFFSET;
//            gRect.y = PlayerCoordinate.y*15 + OFFSET;
//            gRect.h = 15;
//            gRect.w = 15;
//            SDL_RenderCopy(renderer, North, NULL, &gRect);
//        }
//        if( Rotation == "E")
//        {
//            gRect.x = PlayerCoordinate.x*15 + OFFSET;
//            gRect.y = PlayerCoordinate.y*15 + OFFSET;
//            gRect.h = 15;
//            gRect.w = 15;
//            SDL_RenderCopy(renderer, East, NULL, &gRect);
//        }
//        if( Rotation == "S")
//        {
//            gRect.x = PlayerCoordinate.x*15 + OFFSET;
//            gRect.y = PlayerCoordinate.y*15 + OFFSET;
//            gRect.h = 15;
//            gRect.w = 15;
//            SDL_RenderCopy(renderer, South, NULL, &gRect);
//        }
//        if( Rotation == "W")
//        {
//            gRect.x = PlayerCoordinate.x*15 + OFFSET;
//            gRect.y = PlayerCoordinate.y*15 + OFFSET;
//            gRect.h = 15;
//            gRect.w = 15;
//            SDL_RenderCopy(renderer, West, NULL, &gRect);
//        }
//    }
//
//    if(monster_map[PlayerCoordinate.y][PlayerCoordinate.x] == 'B')
//    {
//        std::string zeros = "";
//        if( frame > 110 )
//            frame = 0;
//        if( frame < 10 )
//            zeros = "000";
//        else if( frame < 100 )
//            zeros = "00";
//        else
//            zeros = "0";
//        std::string frameCount = zeros + std::to_string(frame++);
//        swatTexture = LoadTexture("./images/swat/swat" + frameCount + ".png",255);
//        SDL_RenderCopy(renderer, swatTexture, NULL, NULL);
//        SDL_DestroyTexture(swatTexture);
//    }
//
//    xcoord = std::to_string(PlayerCoordinate.x);
//    ycoord = std::to_string(PlayerCoordinate.y);
//
//    renderHitpoints();
//
//    SDL_Rect coinsBackground = {1890, SCREEN_HEIGHT - 190, 280, 180};
//    SDL_RenderFillRect(renderer, &coinsBackground);
//
//    copperString = "Copper: " + std::to_string(coins_copper);
//    silverString = "Silver: " + std::to_string(coins_silver);
//    electrumString = "Electrum: " + std::to_string(coins_electrum);
//    goldString = "Gold: " + std::to_string(coins_gold);
//    platinumString = "Platinum: " + std::to_string(coins_platinum);
//
//    RenderText(copperString, White, 1900, SCREEN_HEIGHT - 100,12);
//    RenderText(silverString, White, 1900, SCREEN_HEIGHT - 120,12);
//    RenderText(electrumString, White, 1900, SCREEN_HEIGHT - 140,12);
//    RenderText(goldString, White, 1900, SCREEN_HEIGHT - 160,12);
//    RenderText(platinumString, White, 1900, SCREEN_HEIGHT - 180,12);
//
//    rotationString = "Rotation: ";
//    coordinateString = " ( " + xcoord + "," + ycoord + " ) ";
//
//    rotationString += Rotation.c_str();
//    RenderText(rotationString.c_str(),White,160,300,12);
//    RenderText(coordinateString.c_str(),White, 50, 300,12);
//
//    SDL_Rect logBackground = {1402,0,(current.w- 1400)-4,200};
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0,192);
//    SDL_RenderFillRect(renderer, &logBackground);
//
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0,255);
//
//
//    if( mainLog.size() > 9 )
//    {
//        reverse(mainLog.begin(),mainLog.end());  // reverse the order of the vector array
//        mainLog.pop_back();   // now just simple pop_back will give you the results
//        reverse(mainLog.begin(),mainLog.end());  // reverse the order of the vector array
//    }
//
//    unsigned int scrolldown = 0;
//
//    for(auto  mainLogRow : mainLog)
//    {
//        RenderText(mainLogRow.c_str(),White,1400,0 + scrolldown,12);
//        scrolldown += 20;
//    }
//
//    renderPCstatus();
};

