#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
#include <filesystem>
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

        std::string xcoord = std::to_string(game->PlayerCoordinate.x);
        std::string ycoord = std::to_string(game->PlayerCoordinate.y);

        std::string rotationString = "";
        std::string coordinateString = " ( " + xcoord + "," + ycoord + " ) ";

        rotationString += Rotation.c_str();
        game->RenderText2(rotationString.c_str(),Black,game->current.w / 2,40,20);
        game->RenderText2(coordinateString.c_str(),Black, game->current.w / 2, 60,20);
    };

    void renderMinimapCharacterLocation(CGameEngine* game)
    {
        gRect.x = game->PlayerCoordinate.x*16 + OFFSET;
        gRect.y = game->PlayerCoordinate.y*16 + OFFSET;
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
//        if( !std::filesystem::exists("./assets/data/textures/maps/phlan/phlan.png") )
//        {
//            SDL_Log("verifying ./data/maps/phlan/phlan.png exists failed");
//            exit(999);
//        }
        SDL_Texture* gTexture = game->LoadTexture("./assets/data/textures/maps/phlan/phlan.png",255);

        SDL_Rect imageSize = {0, 0,256,256};
        SDL_Rect renderLocation = {50, 50,256,256};
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 128);
        SDL_RenderCopy(game->renderer, gTexture, &imageSize, &renderLocation);
        SDL_DestroyTexture(gTexture);
    }

    SDL_Point mousePosition;

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
