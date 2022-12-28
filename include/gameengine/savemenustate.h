#ifndef SAVEMENUSTATE_H
#define SAVEMENUSTATE_H

#include <string>
#include <vector>
#include <dirent.h>
#include <sstream>
#include <iomanip>
using namespace std;

#include <SDL2/SDL.h>
#include "gamestate.h"

class CSaveMenuState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CSaveMenuState* Instance() {
		return &m_SaveMenuState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

    void savingGameData( std::string saveFile,CGameEngine* game )
    {
        // Current date/time based on current system
        time_t now = time(0);

        // Convert now to tm struct for local timezone
        tm* localtm = localtime(&now);
        SDL_Log("The local date and time is: %s",asctime(localtm) );

        // Convert now to tm struct for UTC
        tm* gmtm = gmtime(&now);
        if (gmtm != NULL)
        {
            SDL_Log("The UTC date and time is: %s", asctime(gmtm) );
        }
        else
        {
            SDL_Log("Failed to get the UTC date and time",saveFile);
        }

        if( saveFile == "./assets/data/savegames/new.dat")
        {
            saveFile = "./assets/data/savegames/";
            std::stringstream sstream;
            sstream << std::put_time(gmtm, "%c");
            saveFile += sstream.str();
            FILE *SaveGame;
            // open file for writing
            SaveGame = fopen (saveFile.c_str(), "w");
            if (SaveGame == NULL)
            {
                SDL_Log("CIntroState error opening file %s\n",saveFile);
                exit (1);
            }
            else
            {
                SDL_Log("CIntroState opening file %s\n",saveFile);
                fwrite (&game->SActor, sizeof(struct ACTOR), 1, SaveGame);
                fclose(SaveGame);
            }
            Init();
        }
        else
        {
            FILE *SaveGame;
            SaveGame = fopen (saveFile.c_str(), "w");
            if (SaveGame == NULL)
            {
                SDL_Log("Error opening file: %s", stderr );
            }
            fwrite (&game->SActor, sizeof(struct ACTOR), 1, SaveGame);
            fclose(SaveGame);
            Init();
        }
    }

protected:
	CSaveMenuState() { }

private:
	static CSaveMenuState m_SaveMenuState;

	SDL_Surface* gSurface;
	SDL_Texture* gTexture;
	SDL_Rect gRect;
	int iX;
	int iY;
	SDL_Texture* MainMenuBackgroundTexture;
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
};

#endif

