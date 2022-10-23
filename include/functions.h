#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <random>
using namespace std;

#include "texture_resource.h"

SDL_Rect gRect;
SDL_Surface* gSurface;
//SDL_Surface *screen;
//SDL_Texture* gTexture;
SDL_Renderer * renderer;
SDL_Renderer * renderer2;
FILE * pFile;
SDL_Rect rect;
const Uint8 *keystate;

int Generate(const int from, const int to)
{
    // Create a random device and use it to generate a random seed
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();

    // Initialize a default_random_engine with the seed
    std::default_random_engine myRandomEngine(seed);

    // Initialize a uniform_int_distribution to produce values between -10 and 10
    std::uniform_int_distribution<int> myUnifIntDist(from, to);

    // Create and print 5 randomly generated values
    for (int i = 0; i < 5; i++)
    {
        int number = myUnifIntDist(myRandomEngine);
        std::cout << number << std::endl;
    }
    return myUnifIntDist(myRandomEngine);
};

SDL_Rect FrameText(std::string renderText, int x, int y, int fontSize)
{
    int textWidth = 0;
    int textHeight = 0;
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", fontSize);

    if(!m_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    if( TTF_SizeText(m_font, renderText.c_str(), &textWidth, &textHeight) )
    {
    }
    else
    {
        //printf("width=%d height=%d\n",textWidth,textHeight);
    }
    TTF_CloseFont(m_font);
    m_font = NULL;

    SDL_Rect nameFrame = {x, y,textWidth,textHeight};
    return nameFrame;
}

void RenderFillRect(int x, int y, int w, int h )
{
    SDL_Rect tmpRect = {x,y,w,h};
    SDL_RenderFillRect(renderer, &tmpRect);
}

int RenderText(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", fontSize);

    gSurface = TTF_RenderText_Blended(m_font, renderText.c_str(), colorValue);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX, iY, texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    TTF_CloseFont(m_font);
    m_font = NULL;
    fontSize = 0;
    return 0;
}

void initGameTitleFont(std::string file, int fontSize)
{
    gameTitleFont = TTF_OpenFont(file.c_str(), fontSize);
};

void initGameBreadTextFont(std::string file, int fontSize)
{
    gameBreadTextFont = TTF_OpenFont(file.c_str(), fontSize);
};

int RenderTitle(std::string renderText, SDL_Color colorValue, int iX, int iY)
{
    gSurface = TTF_RenderText_Blended(gameTitleFont, renderText.c_str(), colorValue);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    return 0;
}

int RenderBreadText(std::string renderText, SDL_Color colorValue, int iX, int iY)
{
    gSurface = TTF_RenderText_Blended(gameBreadTextFont, renderText.c_str(), colorValue);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    return 0;
}

int RenderText2(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", fontSize);

    gSurface = TTF_RenderText_Blended(m_font, renderText.c_str(), colorValue);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    TTF_CloseFont(m_font);
    m_font = NULL;
    fontSize = 0;
    return 0;
}

int RenderText3(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", fontSize);

    gSurface = TTF_RenderText_Blended_Wrapped(m_font, renderText.c_str(), colorValue,1000);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    TTF_CloseFont(m_font);
    m_font = NULL;
    fontSize = 0;
    return 0;
}


int RenderTextWrapped(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize, int wrapped)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", fontSize);

    gSurface = TTF_RenderText_Blended_Wrapped(m_font, renderText.c_str(), colorValue,wrapped);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

//    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    TTF_CloseFont(m_font);
    m_font = NULL;
    fontSize = 0;
    return 0;
}

SDL_Texture* LoadTexture( const std::string &str, int alpha )
{
	SDL_Surface* surface = IMG_Load( str.c_str() );
	if( !surface )
	{
        SDL_Log("LoadTexture failed to load image named: %s",str.c_str());
        exit(-1);
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( texture, alpha );
    SDL_FreeSurface(surface);
	return texture;
};

//void Highlight(SDL_Point location, SDL_Rect triggerArea, SDL_Renderer* renderer)
//{
//  if( SDL_PointInRect(&location, &triggerArea) & SDL_BUTTON(SDL_BUTTON_LEFT) )
//  {
//      SDL_PumpEvents();
//      if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
//      {
//          SDL_RenderDrawRect(renderer, &triggerArea);
//      }
//  }
//}

// copy in binary mode
//bool copyFile(const char *SRC, const char* DEST)
//{
//    std::ifstream src(SRC, std::ios::binary);
//    std::ofstream dest(DEST, std::ios::binary);
//    dest << src.rdbuf();
//    return src && dest;
//}

void LogSDL(void *userdata, int category, SDL_LogPriority priority, const char *message)
{
    char *ctime_no_newline;
    time_t tm = time(NULL);

    ctime_no_newline = strtok(ctime(&tm), "\n");

    fprintf(pFile,"[Log] %s %s\n", ctime_no_newline, message);
};

//std::string random_string( size_t length )
//{
//    auto randchar = []() -> char
//    {
//        const char charset[] =
//        "0123456789"
//        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//        "abcdefghijklmnopqrstuvwxyz";
//        const size_t max_index = (sizeof(charset) - 1);
//        return charset[ rand() % max_index ];
//    };
//    std::string str(length,0);
//    std::generate_n( str.begin(), length, randchar );
//    return str;
//};

#endif // FUNCTIONS_H
