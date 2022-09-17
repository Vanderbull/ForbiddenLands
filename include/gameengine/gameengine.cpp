#include <stdio.h>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <SDL2/SDL.h>


#include "gameengine.h"
#include "gamestate.h"
//#include "portals.h"


int testing = 0;

Item::Item(void)
{

};
Item::Item(std::string,char,int)
{

};

SkillObject::SkillObject(void)
{

};
SkillObject::SkillObject(std::string,char,int)
{

};

void CGameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen)
{
    g_myglobal = 10;
    SDL_Log("CGameEngine::Init()");

	int flags = 0;

	SDL_SetMainReady();

    if( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    else
    {
        SDL_Log("initialize SDL and all its subsystems: Success");
    }

    if(!TTF_WasInit() && TTF_Init()==-1)
    {
        SDL_Log("TTF_Init: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    else
    {
        SDL_Log("TTF_Init: Success!");
    }

    // Get current display mode of all displays.
    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
    {
        int should_be_zero = SDL_GetCurrentDisplayMode(i, &monitor[i]);

        current = monitor[0];

        if(should_be_zero != 0)
        {
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
            exit(EXIT_FAILURE);
        }
        else
        {
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, monitor[i].w, monitor[i].h, monitor[i].refresh_rate);
        }
    }

    window = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        current.w, current.h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);


    SDL_GLContext Context = SDL_GL_CreateContext(window);

    if (window == NULL)
    {
        SDL_Log("Could not create window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    else
    {
        SDL_Log("SDL Window creation: SUCCESS");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_Log("SDL Renderer creation: SUCCESS");

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderSetScale(renderer,1.0,1.0);

        // load support for the JPG and PNG image formats
        int flags=IMG_INIT_JPG|IMG_INIT_PNG;
        int initted=IMG_Init(flags);

        if((initted&flags) != flags)
        {
            printf("IMG_Init: %s\n", IMG_GetError());
            exit(EXIT_FAILURE);
        }

        if( strcmp(uts.machine, "x86_64") == 0 )
            gSurface = IMG_Load( "./icons/64-bit-100.png" );
        else
            gSurface = IMG_Load( "./icons/64-bit-100-filled.png" );

        if(!gSurface)
        {
            SDL_Log("Setting Window Icon: %s\n", IMG_GetError());
            exit(EXIT_FAILURE);
        }
        else
        {
            SDL_Log("Loading Window Icon initiated...");
            SDL_Log("Version: %s",AutoVersion::FULLVERSION_STRING);
        }

        SDL_SetWindowIcon(window, gSurface);
        SDL_FreeSurface(gSurface);

        SDL_StopTextInput();

        // Replace this with the new SDL2 OpenAudio
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            SDL_Log("Audio broke down: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        else
        {
            SDL_Log("Audio successfully initiated...");
        }
    }

	m_fullscreen = fullscreen;
	m_running = true;
	SDL_Log("Loading items...");
	AddItem();
	SDL_Log("Loading skills...");
	AddSkill();
	SDL_Log("Loading textures...");
	loadMapTextures();
	SDL_Log("Loading shop...");
    initShop();


    gameTitleFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", g_breadTextFontSize);

    if(!gameTitleFont)
    {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    gameBreadTextFont = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", g_breadTextFontSize);

    if(!gameBreadTextFont)
    {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void CGameEngine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() )
    {
		states.back()->Cleanup();
		states.pop_back();
	}

    SDL_Log("CGameEngine Cleanup\n");

	// shutdown SDL
	SDL_Quit();
}

void CGameEngine::ChangeState(CGameState* state)
{
    SDL_Log("CGameEngine ChangeState\n");
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CGameEngine::PushState(CGameState* state)
{
    SDL_Log("CGameEngine PushState\n");
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void CGameEngine::PopState()
{
    SDL_Log("CGameEngine PopState\n");
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}

void CGameEngine::HandleEvents()
{
    SDL_Log("CGameEngine HandleEvents\n");
	// let the state handle events
	states.back()->HandleEvents(this);
}

void CGameEngine::Update()
{
    SDL_Log("CGameEngine Update\n");
	// let the state update the game
	states.back()->Update(this);
}

void CGameEngine::Draw()
{
    SDL_Log("CGameEngine Draw\n");
	// let the state draw the screen
	states.back()->Draw(this);
}

int CGameEngine::RenderText(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
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

int CGameEngine::RenderTitle(std::string renderText, SDL_Color colorValue, int iX, int iY)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", 48);

    gSurface = TTF_RenderText_Blended(gameTitleFont, renderText.c_str(), colorValue);
    gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gTexture, NULL, NULL, &texW, &texH);

    gRect = { iX - (texW / 2), iY - (texH / 2), texW, texH };
    SDL_RenderCopy(renderer, gTexture, NULL, &gRect);

    //Destroy resources
    SDL_FreeSurface(gSurface);
    SDL_DestroyTexture(gTexture);
    TTF_CloseFont(m_font);
    m_font = NULL;

    return 0;
}

int CGameEngine::RenderBreadText(std::string renderText, SDL_Color colorValue, int iX, int iY)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./font/droid-sans-mono/DroidSansMono.ttf", g_breadTextFontSize);

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
    TTF_CloseFont(m_font);
    m_font = NULL;

    return 0;
}

int CGameEngine::RenderText2(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
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

int CGameEngine::RenderText3(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
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

int CGameEngine::RenderTextWrapped(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize, int wrapped)
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

SDL_Texture* CGameEngine::LoadTexture( const std::string &str, int alpha )
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, str.c_str() );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( texture, alpha );
	return texture;
};

void CGameEngine::loadMapTextures()
{
    std::chrono::time_point<std::chrono::steady_clock> starter;
    std::chrono::time_point<std::chrono::steady_clock> ender;

    starter = std::chrono::steady_clock::now();

    std::string location, room, position;
    std::string fileType = "-fs8.png";
    int progress_value = 0;

    for (auto i = v_ItemNames.begin(); i != v_ItemNames.end(); i++)
    {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Surface* surface = IMG_Load( "./images/ui/rest_no_rune.png" );
        if( !surface )
        {
            exit(-1);
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod( texture, 255 );
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_Rect progressbar_border = {current.w / 2 - v_ItemNames.size()/2,current.h - 200,v_ItemNames.size(),25};
        SDL_RenderFillRect(renderer, &progressbar_border);

        SDL_Rect progressbar = {current.w / 2 - v_ItemNames.size()/2,current.h - 200,progress_value,25};
        progress_value++;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
        SDL_RenderFillRect(renderer, &progressbar);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
        SDL_RenderDrawRect(renderer, &progressbar);

        //RenderText(std::to_string(progress_value).c_str(),White,current.w / 6,current.h - 200, 24);

        RenderText("Loading ItemNames...",White,current.w / 2 - 100,current.h - 245, 24);
        RenderText(*i,White,current.w / 2 - 100,current.h - 205, 24);

        SDL_RenderPresent(renderer);
        //SDL_Delay(10);
    }

    progress_value = 0;
    for(int x = 0; x < 16; x++ )
    {
        for(int y = 0; y < 16; y++ )
        {
            for(int z = 0; z < 4; z++ ) // ESWN directions
            {
                location = "";
                room = "";
                position = "";

                location += "./images/test_map/";
                room  = "";

                if(x < 10)
                {
                    room += "0";
                }

                room += std::to_string(x);

                if(y < 10)
                {
                    room += "0";
                }

                room += std::to_string(y);

                position = room;
                room += "/";

                room += position;
                location += position;

                //location += Rotation;
                if(z == 0)
                    location += "E";
                if(z == 1)
                    location += "W";
                if(z == 2)
                    location += "N";
                if(z == 3)
                    location += "S";

                location += fileType;
                //std::cout << "mapTexture[x][y][z] = " << location << " : " << "(" << x << ")"<< "(" << y << ")"<< "(" << z << ")" << std::endl;
                //location = "./images/profile_photo3.png";
                mapTextureFile[x][y][z] = location;

                mapTexture[x][y][z] = IMG_LoadTexture(renderer,location.c_str());

                //exit(1);
                //myTextures[std::to_string(progress_value).c_str()] = IMG_LoadTexture(renderer,location.c_str());
                SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                SDL_RenderClear(renderer);

                SDL_Surface* surface = IMG_Load( "./images/ui/rest_no_rune.png" );
                if( !surface )
                {
                    exit(-1);
                }

                SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
                SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
                SDL_SetTextureAlphaMod( texture, 255 );
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);

                SDL_Rect progressbar_border = {current.w / 2 - 1024/2,current.h - 200,1024,25};
                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                SDL_RenderFillRect(renderer, &progressbar_border);

                SDL_Rect progressbar = {current.w / 2 - 1024/2,current.h - 200,progress_value,25};
                progress_value++;
                SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
                SDL_RenderFillRect(renderer, &progressbar);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
                SDL_RenderDrawRect(renderer, &progressbar);

                RenderText("Loading Level...",White,current.w / 2 - 100,current.h - 245, 24);
                RenderText(location.c_str(),White,current.w / 3,current.h - 205,24);
                SDL_RenderPresent(renderer);
            }
        }
    }
    ender = std::chrono::steady_clock::now();
    std::cout << "Millisecond loading time: " << double(std::chrono::duration_cast<std::chrono::nanoseconds>(ender - starter).count()) / 1000000 << std::endl;
    // 20357 milliseconds
    //exit(99);
};

void CGameEngine::AddItem()
{
    SDL_Log("CGameEngine AddItem\n");

    for (auto i = v_ItemNames.begin(); i != v_ItemNames.end(); i++)
    {
        Item tempObject;
        tempObject.Name = *i;


        SDL_Log("Adding '%s'\n",tempObject.Name.c_str());
        SDL_Log("   Setting Efficiency: '%i'\n",tempObject.Efficiency = 0);
        SDL_Log("   Setting MinDamage: '%i'\n",tempObject.MinDamage = 0);
        SDL_Log("   Setting MaxDamage: '%i'\n",tempObject.MaxDamage = 0);
        SDL_Log("   Setting DmgType: '%i'\n",tempObject.DmgType = 0);
        SDL_Log("   Setting NumHands: '%i'\n",tempObject.NumHands = 0);
        SDL_Log("   Setting Bodypart: '%i'\n",tempObject.Bodypart = 0);
        SDL_Log("   Setting UsedBy: '%i'\n",tempObject.UsedBy = 0);
        SDL_Log("   Setting Skill: '%i'\n",tempObject.Skill = 0);
        SDL_Log("   Setting BaseWorth: '%i'\n",tempObject.BaseWorth = 0);
        SDL_Log("   Setting Price: '%i'\n",tempObject.Price = 0);
        SDL_Log("   Setting Protection: '%i'\n",tempObject.Protection = 0);
        SDL_Log("   Setting Enchantments: '%i'\n",tempObject.Enchantments = 0);
        SDL_Log("   Setting Effect: '%i'\n",tempObject.Effect = 0);
        SDL_Log("   Setting EffectCharges: '%i'\n",tempObject.EffectCharges = 0);
        SDL_Log("   Setting MinEffect: '%i'\n",tempObject.MinEffect = 0);
        SDL_Log("   Setting MaxEffect: '%i'\n",tempObject.MaxEffect = 0);
        SDL_Log("   Setting Features: '%i'\n",tempObject.Features = 0);
        v_Item.push_back(tempObject);
    }
};

void CGameEngine::AddSkill()
{
    SDL_Log("CGameEngine AddSkill\n");

    for (auto i = v_SkillNames.begin(); i != v_SkillNames.end(); i++)
    {
        SkillObject tempObject;
        tempObject.Name = *i;


        SDL_Log("Adding '%s'\n",tempObject.Name.c_str());
        SDL_Log("Adding '%s'\n",tempObject.MaximumExpertise = 0);
        SDL_Log("Adding '%s'\n",tempObject.InitialRequirementsAttribute = 0);
        SDL_Log("Adding '%s'\n",tempObject.InitialRequirementsValue = 0);
        SDL_Log("Adding '%s'\n",tempObject.Group = 0);
        SDL_Log("Adding '%s'\n",tempObject.Description.c_str());

//        int MaximumExpertise;
//        int InitialRequirementsAttribute;
//        int InitialRequirementsValue;
//        int Group;
//        std::vector<std::string> UtilizedBy;
//        std::string Description;

        v_Skill.push_back(tempObject);
    }
};

void LoadShopData(std::string in_file, std::vector<SGenericItem> &out_data)
{
    std::string line;
    std::ifstream shop_data_file (in_file.c_str());
    SGenericItem tempItem;

    std::cout << in_file << std::endl;

    if (shop_data_file.is_open())
    {
        while ( getline (shop_data_file,line) )
        {
            if( line == "#TYPE")
            {
                getline (shop_data_file,line);
                tempItem.type = line.c_str();
                SDL_Log("Adding type: '%s'\n",line.c_str());
            }
            if( line == "#WEIGHT")
            {
                getline (shop_data_file,line);
                std::cout << line << std::endl;
                int integer_data = std::stoi(line);
                std::cout << integer_data << std::endl;
                tempItem.weight = integer_data;
                SDL_Log("Adding weight: '%s'\n",line.c_str());
            }
            if( line == "#COST")
            {
                getline (shop_data_file,line);
                tempItem.value = std::stoi(line);
                SDL_Log("Adding cost: '%s'\n",line.c_str());
            }
            if( line == "#ITEM")
            {
                getline (shop_data_file,line);
                tempItem.name = line.c_str();
                SDL_Log("Adding item: '%s'\n",line.c_str());
                out_data.push_back(tempItem);
            }
        }
        shop_data_file.close();
    }
    else std::cout << "Unable to open file";
};

void CGameEngine::initShop()
{
    generalShopItems.push_back(SGenericItem());
    generalShopItems.push_back(SGenericItem());
    generalShopItems.push_back(SGenericItem());
    generalShopItems.push_back(SGenericItem());
    generalShopItems.push_back(SGenericItem());
    generalShopItems.push_back(SGenericItem());

    LoadShopData("./data/general_shop_data",generalShopItems);
    LoadShopData("./data/jewellery_shop_data",jewelleryShopItems);
    LoadShopData("./data/silver_shop_data",silverShopItems);
    LoadShopData("./data/arms_and_armours_data",armsAndArmoursShopItems);
    string line;
};

void CGameEngine::renderDaytime()
{
        SDL_Rect dayTimeBox = {current.w - 1150,25,50,50};

        SDL_Texture* dayTimeTexture = NULL;

        if( currentTimeElapse() == night )
            dayTimeTexture = LoadTexture("./icons/night.png",255);
        else
            dayTimeTexture = LoadTexture("./icons/day.png",255);

        SDL_RenderCopy(renderer, dayTimeTexture, NULL, &dayTimeBox);
        SDL_DestroyTexture(dayTimeTexture);

        RenderText("Season: " + cweather_engine.get_season(), White, current.w - 1050,100,24);
        RenderText("Temperature: " + std::to_string(cweather_engine.get_temperature()), White, current.w - 1050,124,24);
        RenderText("currentTime: " + std::to_string(currentTime),White, current.w - 1050, 170,24);
        RenderText("currentDay: " + std::to_string(currentDay),White, current.w - 1050, 190,24);
}
