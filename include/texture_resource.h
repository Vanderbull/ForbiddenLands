#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

SDL_Texture* North;
SDL_Texture* East;
SDL_Texture* South;
SDL_Texture* West;
//SDL_Texture* menuBackgroundTexture;
SDL_Texture* currentViewTexture;
SDL_Texture* encampTexture;
SDL_Texture* gTexture;

// Make these a blob
SDL_Texture* mapTexture[16][16][4];
std::string mapTextureFile[16][16][4];

SDL_Texture* MainMenuBackgroundTexture;

//Make these a blob
TTF_Font* gameTitleFont;
TTF_Font* gameBreadTextFont;

#endif
