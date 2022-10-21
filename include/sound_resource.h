#ifndef SOUND_RESOURCE_H
#define SOUND_RESOURCE_H

const std::string SOUNDBIBLE_PATH = "./assets/data/sounds/";


// Our wave file
Mix_Chunk *wave = NULL;
Mix_Chunk *negative = NULL;
Mix_Chunk *positive = NULL;
// Our music file
Mix_Music *music = NULL;
Mix_Music *main_menu_music = NULL;
Mix_Chunk *gPunch = NULL;

void PlayAndWait(int channel, Mix_Chunk* chunk, int loops)
{
    channel = Mix_PlayChannel(channel, chunk, loops);
    if (channel < 0)
    {
        return; // error
    }
    while (Mix_Playing(channel) != 0)
    {
        SDL_Delay(200);
    }
}

#endif
