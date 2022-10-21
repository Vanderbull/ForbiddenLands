#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <chrono>

#include <SDL2/SDL.h>

#include "gamestate.h"

class CIntroState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CIntroState* Instance() {
		return &m_IntroState;
	}

    void read_directory(const std::string& name, std::vector<string>& v)
    {
        DIR* dirp = opendir(name.c_str());
        struct dirent * dp;
        while ((dp = readdir(dirp)) != NULL) {
            v.push_back(dp->d_name);
        }
        closedir(dirp);
    }

protected:
	CIntroState() { }

private:
	static CIntroState m_IntroState;
	SDL_Color White = {255, 255, 255, 255};
    std::vector<std::string> imagesFiles;

    int x,y,z;
    int counter = 0;
    SDL_Texture* texture;
};

#endif
