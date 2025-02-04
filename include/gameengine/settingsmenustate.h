#ifndef SETTINGSMENUSTATE_H
#define SETTINGSMENUSTATE_H

#include <string>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <sys/resource.h>
#include <unistd.h>

using namespace std;

#include <SDL2/SDL.h>
#include "gamestate.h"

class CSettingsMenuState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CSettingsMenuState* Instance() {
		return &m_SettingsMenuState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

    void savingGameData( std::string saveFile )
    {
        // Current date/time based on current system
        time_t now = time(0);

        // Convert now to tm struct for local timezone
        tm* localtm = localtime(&now);
        cout << "The local date and time is: " << asctime(localtm) << endl;

        // Convert now to tm struct for UTC
        tm* gmtm = gmtime(&now);
        if (gmtm != NULL) {
        cout << "The UTC date and time is: " << asctime(gmtm) << endl;
        }
        else {
        cerr << "Failed to get the UTC date and time" << endl;
        //return EXIT_FAILURE;
        }

        if( saveFile == "./data/savegames/new.dat")
        {
            saveFile = saveFile + "-" + asctime(gmtm);
            FILE *SaveGame;
            // open file for writing
            SaveGame = fopen (saveFile.c_str(), "w");
            if (SaveGame == NULL)
            {
                fprintf(stderr, "\nError opened file\n");
                exit (1);
            }

//            fwrite (&SActor, sizeof(struct ACTOR), 1, SaveGame);

            fclose(SaveGame);
            Init();
        }
        else
        {
            FILE *SaveGame;
            // open file for writing
            SaveGame = fopen (saveFile.c_str(), "w");
            if (SaveGame == NULL)
            {
                fprintf(stderr, "\nError opened file\n");
                exit (1);
            }
//
//            fwrite (&SActor, sizeof(struct ACTOR), 1, SaveGame);

            fclose(SaveGame);
            Init();
        }
    }

protected:
	CSettingsMenuState() { }

private:
	static CSettingsMenuState m_SettingsMenuState;

	SDL_Surface* gSurface;
	SDL_Texture* gTexture;
	SDL_Rect gRect;
	int iX;
	int iY;
	SDL_Texture* MainMenuBackgroundTexture;
	SDL_Color White = {255, 255, 255, 255};
	TTF_Font* gameBreadTextFont = NULL;
	TTF_Font* gameTitleFont = NULL;
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

