#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
#include <filesystem>
#include <string>
#include <random>
#include <time.h>
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
        std::random_device rd;
        SDL_Texture* gTexture = game->LoadTexture("./assets/data/textures/maps/kustenstad/kustenstad.png",255);

        SDL_Rect imageSize = {0, 0,256,256};
        SDL_Rect renderLocation = {50, 50,256,256};
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 128);
        SDL_RenderCopy(game->renderer, gTexture, &imageSize, &renderLocation);
        SDL_DestroyTexture(gTexture);

        int z = 0;
        for(int x = 0; x < 16; x++)
            for(int y = 0; y < 16; y++)
            {
                if( game->random_events[x][y][z] <= ( rd.max() / 4) )
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
        int counterx,countery;
        int index = 0;
        int west,east,south,north;
        fstream file ("./assets/data/maps/kustenstad/kustenstad_portals", ios::in);
        if(file.is_open())
        {
            while(getline(file, line))
            {
                index = 0;
                counterx = 0;
                countery = 0;
                west = east = north = south = 0;
                //row.clear();
                stringstream str(line);
                while(getline(str, word, ' '))
                {
                    if( index == 0)
                        counterx = std::stoi(word);
                    if( index == 1)
                        countery = std::stoi(word);
                    if( index == 2)
                        west = std::stoi(word);
                    if( index == 3)
                        east = std::stoi(word);
                    if( index == 4)
                        south = std::stoi(word);
                    if( index == 5)
                        north = std::stoi(word);

                    //row.push_back(word);
                    std::cout << word <<  "¦";
                    index++;
                    //counterx++;
                }

                //std::cout << counterx << " " << countery << " " << west << " " << east << " "<< south << " "<< north << std::endl;
                //exit(99);
                mapExits[counterx][countery].Direction[Passable::WEST] = west;
                mapExits[counterx][countery].Direction[Passable::EAST] = east;
                mapExits[counterx][countery].Direction[Passable::NORTH] = north;
                mapExits[counterx][countery].Direction[Passable::SOUTH] = south;


                std::cout << "counterx:" << counterx << std::endl;
                std::cout << "countery:" << countery<< std::endl;
                std::cout << " WEST:" << mapExits[counterx][countery].Direction[Passable::WEST] << std::endl;
                std::cout << " EAST:" << mapExits[counterx][countery].Direction[Passable::EAST] << std::endl;
                std::cout << " NORTH:" << mapExits[counterx][countery].Direction[Passable::NORTH] << std::endl;
                std::cout << " SOUTH" << mapExits[counterx][countery].Direction[Passable::SOUTH] << std::endl;


                std::cout << std::endl;
                //content.push_back(row);
                //countery++;
            }
        }
    //exit(99);
    };

    void renderPassable(CGameEngine* game)
    {
        SDL_Rect WEST = {0, 64,64,64};
        SDL_Rect EAST = {128, 64,64,64};
        SDL_Rect NORTH = {64, 0,64,64};
        SDL_Rect SOUTH = {64, 128,64,64};
        SDL_SetRenderDrawColor(game->renderer, 255, 0, 255, 128);

        std::cout << " game->SActor.PlayerCoordinate.x:" << game->SActor.PlayerCoordinate.x << std::endl;
        std::cout << " game->SActor.PlayerCoordinate.y:" << game->SActor.PlayerCoordinate.y << std::endl;
        std::cout << " WEST:" << mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::WEST] << std::endl;
        std::cout << " EAST:" << mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::EAST] << std::endl;
        std::cout << " NORTH:" << mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::NORTH] << std::endl;
        std::cout << " SOUTH" << mapExits[game->SActor.PlayerCoordinate.x][game->SActor.PlayerCoordinate.y].Direction[Passable::SOUTH] << std::endl;
        //exit(99);

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
