#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H

#include <chrono>

#include <SDL2/SDL.h>

#include "gamestate.h"

class CLoadingState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CLoadingState* Instance() {
		return &m_LoadingState;
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
	CLoadingState() { }

private:
	static CLoadingState m_LoadingState;
	SDL_Color White = {255, 255, 255, 255};
    std::vector<std::string> imagesFiles;

    int x,y,z;
    int counter = 0;
    SDL_Texture* texture;
};

#endif
