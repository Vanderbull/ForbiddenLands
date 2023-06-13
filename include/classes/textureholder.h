/// @file textureholder.h
#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include <string>
#include <vector>
#include <map>
using namespace std;

#include <SDL2/SDL.h>

#include "randomizer.h"

class TextureHolder
{
private:
    // A pointer of the same type as the class itself
    // the one and only instance
    //static TextureHolder* m_s_Instance;
public:
    // A map container from the STL,
    // that holds related pairs of String and Texture
    map<string, SDL_Texture*> m_Textures;

    // Texture textureBackground = TextureHolder::GetTexture(
    // "graphics/background_sheet.png");

    TextureHolder(){};
    //static Texture& GetTexture(string const& filename);
};

#endif
