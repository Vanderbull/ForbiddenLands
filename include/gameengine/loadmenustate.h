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

    void loadingGameData( std::string saveFile )
    {
        FILE *infile;

        // Open person.dat for reading
        infile = fopen (saveFile.c_str(), "r");
        if (infile == NULL)
        {
            fprintf(stderr, "\nError opening file\n");
            exit (1);
        }

        // read file contents till end of file
        while(fread(&SActor, sizeof(struct ACTOR), 1, infile))
        {
            std::cout << SActor.action_stamina << "\n";
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
