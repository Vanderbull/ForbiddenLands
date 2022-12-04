#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
#include <filesystem>
#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include "gamestate.h"

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CPlayState* Instance() {
		return &m_PlayState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

    void getCompassDirection()
    {
        Rotation = compassDirection.at(compassNeedle);
    };

    void rotateCounterClockWise()
    {
        if( compassNeedle == 0 )
            compassNeedle = compassDirection.size()-1;
        else
            compassNeedle--;
    };

    void rotateClockWise()
    {
        if( compassNeedle == compassDirection.size()-1 )
            compassNeedle = 0;
        else
            compassNeedle++;
    };

    void renderDaytime(CGameEngine* game)
    {
        SDL_Rect dayTimeBox = {game->current.w - 1150,25,500,500};
        game->RenderText("Season: ", White, game->current.w - 1050,100,24);
        game->RenderText("Temperature: ", White, game->current.w - 1050,124,24);
        game->RenderText("currentTime: ",White, game->current.w - 1050, 170,24);
        game->RenderText("currentDay: ",White, game->current.w - 1050, 190,24);
    }

    void renderCompass(CGameEngine* game)
    {
        SDL_Rect square = {game->current.w / 2 - 90, 20, 180, 60};
        SDL_Rect needle = {game->current.w / 2, 10, 2, 10};
        SDL_Rect needleLeft = {game->current.w / 2 - 90, 10, 2, 5};
        SDL_Rect needleRight = {game->current.w / 2 + 90, 10, 2, 5};
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &square);
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(game->renderer, &square);
        SDL_RenderFillRect(game->renderer, &needleLeft);
        SDL_RenderFillRect(game->renderer, &needle);
        SDL_RenderFillRect(game->renderer, &needleRight);

        std::string xcoord = std::to_string(game->SActor.PlayerCoordinate.x);
        std::string ycoord = std::to_string(game->SActor.PlayerCoordinate.y);

        std::string rotationString = "";
        std::string coordinateString = " ( " + xcoord + "," + ycoord + " ) ";

        rotationString += Rotation.c_str();
        game->RenderText2(rotationString.c_str(),Black,game->current.w / 2,40,20);
        game->RenderText2(coordinateString.c_str(),Black, game->current.w / 2, 60,20);
    };

    void renderMinimapCharacterLocation(CGameEngine* game)
    {
        gRect.x = game->SActor.PlayerCoordinate.x*16 + OFFSET;
        gRect.y = game->SActor.PlayerCoordinate.y*16 + OFFSET;
        gRect.h = 16;
        gRect.w = 16;

        if( Rotation == "N")
        {
            SDL_RenderCopy(game->renderer, game->North, NULL, &gRect);
        }
        if( Rotation == "E")
        {
            SDL_RenderCopy(game->renderer, game->East, NULL, &gRect);
        }
        if( Rotation == "S")
        {
            SDL_RenderCopy(game->renderer, game->South, NULL, &gRect);
        }
        if( Rotation == "W")
        {
            SDL_RenderCopy(game->renderer, game->West, NULL, &gRect);
        }
    };

    void renderMinimap(CGameEngine* game)
    {
        SDL_Texture* gTexture = game->LoadTexture("./assets/data/textures/maps/kustenstad/kustenstad.png",255);

        SDL_Rect imageSize = {0, 0,256,256};
        SDL_Rect renderLocation = {50, 50,256,256};
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 128);
        SDL_RenderCopy(game->renderer, gTexture, &imageSize, &renderLocation);
        SDL_DestroyTexture(gTexture);

        for(int x = 0; x < 16; x++)
            for(int y = 0; y < 16; y++)
            {
                if( random_events[x][y] <= (RAND_MAX / 2) )
                {
                    SDL_Rect imageSize = {x*16 + 50, y*16 + 50,8,8};
                    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 128);
                    SDL_RenderFillRect(game->renderer, &imageSize);
                }
            }
    }

    void LoadMapExits()
    {
        std::vector<vector<string>> content;
        std::vector<string> row;
        std::string line, word;
        fstream file ("./assets/data/maps/kustenstad/kustenstad_portals", ios::in);
        if(file.is_open())
        {
            while(getline(file, line))
            {
                row.clear();
                stringstream str(line);
                while(getline(str, word, ' '))
                    row.push_back(word);
                content.push_back(row);
            }

            for(int i=0; i < content.size(); i++)
            {
                for(int j=0; j < content[i].size(); j++)
                {
//                    if( j == 2)
//                    mapExits[i][j].Direction[mapExits[i][j].WEST] = std::stoi(content[i][j]);
//                    if( j == 3)
//                    mapExits[i][j].Direction[mapExits[i][j].EAST] = std::stoi(content[i][j]);
//                    if( j == 4)
//                    mapExits[i][j].Direction[mapExits[i][j].NORTH] = std::stoi(content[i][j]);
//                    if( j == 5)
//                    mapExits[i][j].Direction[mapExits[i][j].SOUTH] = std::stoi(content[i][j]);
                    cout << content[i][j] << " ";
                }
                cout << endl;
            }
        }

//        for(int x = 0; x < 16; x++)
//            for(int y = 0; y < 16; y++)
//            {
//                mapExits[x][y].Direction[mapExits[x][y].WEST] = rand();
//                mapExits[x][y].Direction[mapExits[x][y].EAST] = rand();
//                mapExits[x][y].Direction[mapExits[x][y].NORTH] = rand();
//                mapExits[x][y].Direction[mapExits[x][y].SOUTH] = rand();
//            }
    };

    void renderPassable(CGameEngine* game)
    {
        return;
        SDL_Rect WEST = {0, 64,64,64};
        SDL_Rect EAST = {128, 64,64,64};
        SDL_Rect NORTH = {64, 0,64,64};
        SDL_Rect SOUTH = {64, 128,64,64};
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);
        if( mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::WEST] == 1 )
            SDL_RenderFillRect(game->renderer, &WEST);
        if( mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::EAST] == 1 )
            SDL_RenderFillRect(game->renderer, &EAST);
        if( mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::NORTH] == 1 )
            SDL_RenderFillRect(game->renderer, &NORTH);
        if( mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::SOUTH] == 1 )
            SDL_RenderFillRect(game->renderer, &SOUTH);
    }

    SDL_Point mousePosition;

    int random_events[16][16] =  {
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()},
    {rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand()}
    };

    Passable mapExits[16][16];

protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;

	SDL_Surface* gSurface;
	SDL_Texture* gTexture;
	SDL_Rect gRect;
	int iX,iY;

	SDL_Color White = {255, 255, 255, 255};
	SDL_Color Black = {0, 0, 0, 255};

    std::vector<std::string> MenuChoices;

    /// Information about the state of the mouse
    int m_iCurrentCoordX;
    int m_iCurrentCoordY;
    Uint32 m_uCurrentMouseState;

    int m_iPreviousCoordX;
    int m_iPreviousCoordY;
    Uint32 m_uPreviousMouseState;

    ///information about the state of thw wheel
    Sint32 m_iWheelX;
    Sint32 m_iWheelY;

    int Repeat = 0;
    int buttonWidth = 600;
    int buttonHeight = 60;

    std::string compassDirection = "NESW";
    int compassNeedle = 0;
    std::string Rotation = "W";

    int z = 0;
    enum {EAST,WEST,NORTH,SOUTH};
};

#endif
