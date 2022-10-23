#ifndef LOADMENUSTATE_H
#define LOADMENUSTATE_H

#include <string>
#include <vector>
using namespace std;

#include <SDL2/SDL.h>
#include "gamestate.h"

class CLoadMenuState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CLoadMenuState* Instance() {
		return &m_LoadMenuState;
	}

    bool IsButtonReleased(const Uint32 uButton)
    {
        return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
    }

    void loadingGameData( std::string saveFile, CGameEngine* game )
    {
        game->newGame = false;
        std::string saveFilePath = "./assets/data/savegames/";
        std::string loadThisFile = saveFilePath + saveFile;
        FILE *infile;

        // Open person.dat for reading
        infile = fopen (loadThisFile.c_str(), "r");
        if (infile == NULL)
        {
            std::cout << loadThisFile << std::endl;

            fprintf(stderr, "\nError opening file\n");
            exit (1);
        }

        // read file contents till end of file
        size_t ret_code = fread(&game->SActor, sizeof(struct ACTOR), 1, infile);

        std::cout << game->SActor.uid << std::endl << std::endl;
        std::cout << game->SActor.current_stats[0] << std::endl;
        std::cout << game->SActor.current_stats[1] << std::endl;
        std::cout << game->SActor.current_stats[2] << std::endl;
        std::cout << game->SActor.current_stats[3] << std::endl;
        std::cout << game->SActor.current_stats[4] << std::endl;
        std::cout << game->SActor.current_stats[5] << std::endl;

        puts("Array read successfully, contents: ");
           if (feof(infile))
          printf("Error reading loadThisFile unexpected end of file\n");
       else if (ferror(infile)) {
           perror("Error reading loadThisFile");
       }
        // close file
        fclose (infile);
    }

protected:
	CLoadMenuState() { }

private:
	static CLoadMenuState m_LoadMenuState;

	SDL_Surface* gSurface;
	SDL_Texture* gTexture;
	SDL_Rect gRect;
	int iX;
	int iY;
	SDL_Texture* MainMenuBackgroundTexture;
	SDL_Color White = {255, 255, 255, 255};
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
