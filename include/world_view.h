#ifndef WORLD_VIEW_H
#define WORLD_VIEW_H

#include <regex>

#include "common.h"

int OFFSET = 50;

struct quest {
        int id;
        std::string name;
        int experience;
        int gold;
};

std::map<int, quest> quests;

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

// Should be able to generate quest items here
quest MakeQuest( int n, const char* s, int experience = 0, int gold = 0 )
{
    quest q = { n, s, experience, gold };
    return q;
};

void initQuests()
{
    quests[0] = MakeQuest( IN_PROGRESS, "Clear the slums immediately west of the Civilized Area.  Reward: 450 XP, 250 gold. 15 Random encounters clears this",450, 250);
    quests[1] = MakeQuest( PENDING, "Clear Sokal Keep of its spectral guardians. (Note: The Keep is considered cleared once Ferran Martinez has been told the truth. The shipping lanes will also be open to traffic. If you leave the Keep before telling the truth to Martinez, the Undead Patrols will be reset.) Reward: 1308 XP, 250 platinum.");
    quests[2] = MakeQuest( PENDING, "Return books, maps, and tomes with useful information.  This is resolved once you clear Mendor's Library (defeat the basilisk and spectre), not when you actually return all the books of interest.  Reward: 208 XP, 250 gold.");
    quests[3] = MakeQuest( PENDING, "Discover what item is to be auctioned in Podal Plaza.  This mission cannot be performed until it is offered.  If you get close enough for the auction to begin, that is enough; you do not need to actually discover what the item is.  Reward: 208 XP, 250 gold.");
    quests[4] = MakeQuest( PENDING, "Speak to Junior Councilman Porphyrys Cadorna, who has a mission; you must resolve commission #2 to be asked this.",833,200);
    quests[5] = MakeQuest( PENDING, "Speak to Bishop Braccio, who has a mission (only asked once).  Completing that mission will be recognized here, but your only reward is praise and getting to keep any items you found in the temple; it will also not negate any anger caused by fighting the city guard, unlike all the other missions here.");
    quests[6] = MakeQuest( PENDING, "Clear old Kovel Mansion of the thieves that operate there; you must resolve commission #2 to receive this.",191,800);
    quests[7] = MakeQuest( PENDING, "Prevent the nomads from joining forces with Phlan's enemies.",983,100);
    quests[8] = MakeQuest( IN_PROGRESS, "Prevent the kobolds from joining forces with Phlan's enemies.",1841,100);
    quests[9] = MakeQuest( PENDING, "Find the source of the Stojanow River's pollution and end it.",5708,2000);
    quests[10] = MakeQuest( PENDING, "Prevent the lizardmen from joining forces with Phlan's enemies.",2466,2300);
    quests[11] = MakeQuest( PENDING, "Rescue the heir to the house of Bivant; this mission cannot be performed until it is offered, and you cannot receive it if commission #2 has not been completed.  if you instead failed the mission, the clerk complains 'By the way, your bungling the Bivant rescue has cost us.'Reward: Two-Handed Sword +1, +3 Vs. Undead and 4 Clerical Scroll (Restoration, Restoration);",3208);
    quests[12] = MakeQuest( PENDING, "Go on a diplomatic mission to the Zhentil Keep Outpost to the west. This mission cannot be performed until it is offered, which requires commission #5 to be resolved.  You will either first be asked to speak to Senior Councilman Porphyrys Cadorna by going through the south door, or be given the mission directly if you have learned that Cadorna is a traitor by visiting Valjevo Castle 26. and if you have not already learned it, you are told that Porphyrys Cadorna is a traitor to New Phlan.  (You are also told he has a bounty upon his head, but none is actually paid.)",2125);
    quests[13] = MakeQuest( PENDING, "If you have resolved commission #13: Visit Head Councilman Urslingen, through the south door of Cadorna's old office, where he will ask you to capture Stojanow Gate.",3666);
    quests[14] = MakeQuest( IN_PROGRESS, "If you have resolved commission #14: Visit the council chambers, where you are asked to lead the assault on Valjevo Castle and defeat Tyranthraxus, which wins the game.",45000,300);
};

void renderQuestProgress()
{
    for (const auto& [key, value] : quests)
    {
        if( value.id == IN_PROGRESS )
        {
            if( randomEncounters >= 1 )
            {
                std::cout << "You finished the first of all quest" << std::endl;
                quests[key].id = DONE;
            }
            if( randomEncounters >= 1 )
            {
                std::cout << "You finished the fourth of all quest" << std::endl;
                quests[key].id = DONE;
            }
        }
    }
};

void renderQuests( bool hidden = true )
{
    if( hidden )
        return;

    int i = 0;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0,128);
    SDL_Rect questBackground = {current.w - 1020,380,1020,500};
    SDL_RenderFillRect(renderer, &questBackground);

    for (const auto& [key, value] : quests)
    {
        if( value.id == IN_PROGRESS )
        {
             RenderTextWrapped(value.name, White, current.w - 490, 500+i*120,24,660);
             RenderText("X", Red, current.w - 50, 500+i*120,24);
             i++;
        }
    }

    renderQuestProgress();
};

void navigationButtons()
{
    SDL_Rect west = {0,current.h - 100,50,50};
    SDL_Rect east = {100,current.h - 100,50,50};
    SDL_Rect north = {50,current.h - 150,50,50};
    SDL_Rect south = {50,current.h - 50,50,50};

    SDL_Rect save = {200,current.h - 50,50,50};
    SDL_Rect load = {200,current.h - 150,50,50};

    SDL_Rect randomEncounterButton = {50,current.h - 850,200,50};

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
        if( activeView == DUNGEON )
        {
            SDL_RenderFillRect(renderer, &randomEncounterButton);
            RenderText("BATTLE IT", Black, randomEncounterButton.x, randomEncounterButton.y,12);
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
    }

if( activeView == DUNGEON )
{
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
}

};

void renderWorldViewA()
{
    if( lootDropped )
    {
    save_portals[PlayerCoordinate.x][PlayerCoordinate.y].droppedLoot = lootDropped;
    resetLootDropped();

    }
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

    if( PlayerCoordinate.x > 15 )
    {
        std::cout << "There was some strange error please check" << std::endl;
        exit(16);
    }

    currentViewTexture = LoadTexture(location.c_str(),255);
    SDL_RenderCopy(renderer, currentViewTexture, NULL, NULL);
    SDL_DestroyTexture(currentViewTexture);
    renderCompass();

    if(minimapActive)
    {
        renderMinimap("./data/maps/phlan/phlan_minimap", mapActive);

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

    if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].encounter )
    {
        std::string zeros = "";
        if( frame > 110 )
            frame = 0;
        if( frame < 10 )
            zeros = "000";
        else if( frame < 100 )
            zeros = "00";
        else
            zeros = "0";
        std::string frameCount = zeros + std::to_string(frame++);
        swatTexture = LoadTexture("./images/swat/swat" + frameCount + ".png",255);
        SDL_RenderCopy(renderer, swatTexture, NULL, NULL);
        SDL_DestroyTexture(swatTexture);
    }

    navigationButtons();
    adventureMenu();

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

    if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].droppedLoot )
    {
        RenderText("LOOT HERE!!",Green,600,0,48);
    }

    if( activeView == DUNGEON && viewingCharacter == 0)
    {
        SDL_Rect dayTimeBox = {current.w - 1150,25,50,50};

        SDL_Texture* dayTimeTexture = NULL;

        if( getTimeOfDay() == "Night time")
            dayTimeTexture = LoadTexture("./icons/ball-48.png",255);
        else
            dayTimeTexture = LoadTexture("./icons/48.png",255);

        SDL_RenderCopy(renderer, dayTimeTexture, NULL, &dayTimeBox);
        SDL_DestroyTexture(dayTimeTexture);

        if( getTimeOfDay() == "Night time")
        {
            dayTimeTexture = LoadTexture("./icons/night.png",128);
            SDL_RenderCopy(renderer, dayTimeTexture, NULL, NULL);
            SDL_DestroyTexture(dayTimeTexture);
        }

        RenderText("Season: " + cweather_engine.get_season(), White, current.w - 1050,100,24);
        RenderText("Temperature: " + std::to_string(cweather_engine.get_temperature()), White, current.w - 1050,124,24);
        RenderText("Time of day: " + getTimeOfDay(),White, current.w - 1050, 148,24);
    }
};

void renderWorldViewB()
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

    currentViewTexture = LoadTexture(location.c_str(),255);
    SDL_RenderCopy(renderer, currentViewTexture, NULL, NULL);
    SDL_DestroyTexture(currentViewTexture);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_Rect minimapBackground = {15,15, 320,320};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255,192);
    SDL_RenderFillRect(renderer, &minimapBackground);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0,192);
    SDL_RenderFillRect(renderer, &minimapBackground);

    if(minimapActive)
    {
        renderMinimap("./data/maps/phlan/phlan_minimap",mapActive);

        gRect.x = PlayerCoordinate.x*15 + OFFSET;
        gRect.y = PlayerCoordinate.y*15 + OFFSET;
        gRect.h = 15;
        gRect.w = 15;

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

    if( save_portals[PlayerCoordinate.x][PlayerCoordinate.y].encounter )
    {
        std::string zeros = "";
        if( frame > 110 )
            frame = 0;
        if( frame < 10 )
            zeros = "000";
        else if( frame < 100 )
            zeros = "00";
        else
            zeros = "0";
        std::string frameCount = zeros + std::to_string(frame++);
        swatTexture = LoadTexture("./images/swat/swat" + frameCount + ".png",255);
        SDL_RenderCopy(renderer, swatTexture, NULL, NULL);
        SDL_DestroyTexture(swatTexture);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);

    adventureMenu();
};

#endif
