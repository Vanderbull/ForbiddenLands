#include <stdio.h>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;
namespace pt = boost::property_tree;

#include "gameengine.h"
#include "gamestate.h"
#include "classes/questobject.h"
//#include "portals.h"


int testing = 0;

int CGameEngine::Generate(const int from, const int to)
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

void CGameEngine::CreateItem(int index = 0, std::string Name = "",int Efficiency = 0,int MinDamage = 0,int MaxDamage = 0,
    int DmgType = 0,int NumHands = 0,int Bodypart = 0,int UsedBy = 0,int Skill = 0,
    int BaseWorth = 0,int Price = 0,int Protection = 0,int Enchantments = 0,int Effect = 0,
    int EffectCharges = 0,int MinEffect = 0,int MaxEffect = 0,int Features = 0)
{
    v_Item.at(index).Name = Name;

    // Test item in inventory
    v_InventoryItem.at(0).Name = Name;
};

Item CGameEngine::SpawnRandomItem()
{
    return v_Item.at(GenerateNumber(0,89));
};

boost::property_tree::ptree foo()
{
  boost::property_tree::ptree retval;
  retval.put("moo","12345");
  //retval.put("zoo",12345);
  return retval;
}

void CGameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen)
{
    atexit( SDL_Quit );

    ItemObject["Bronze Ring"] = ItemRecord{"Bronze Ring"};
    ItemObject["Iron Ring"] = ItemRecord{"Iron Ring"};
    ItemObject["Silver Ring"] = ItemRecord{"Silver Ring"};
    ItemObject["Golden Ring"] = ItemRecord{"Golden Ring"};
    ItemObject["Jewel Ring"] = ItemRecord{"Jewel Ring"};

    ItemRecord& Bronze_Ring_Data = ItemObject["Bronze Ring"];

//    for( auto& [name, item] : ItemObject)
//    {
//        std::cout << name << item.Icon << std::endl;
//    }
//    exit(99);

    Quests.addQuest("Raid", "Raid a nearby village to gather resources and loot.");

    Raiding_Party.young = rand()%6 + 1;
    Raiding_Party.middleage = rand()%6 +1;
    Raiding_Party.old = rand()%6 +1;
    std::random_device rnd;  // a source of machine-wide entropy
    std::default_random_engine eng(rnd()); // use it to initialise the psuedo-random engine

    std::array<int, 100> arr;
    fill_array(eng, arr);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,RAND_MAX);

    std::random_device rd;

    //auto dice = std::bind ( rd, generator );

    //int wisdom = dice()+dice()+dice();

            int z = 0;
        for(int x = 0; x < 16; x++)
            for(int y = 0; y < 16; y++)
            {
                random_events[x][y][z] = rd();//dice();
                fog_of_war_raiding[x][y][z] = 0;
            }

        for(int x = 0; x < 10; x++)
            for(int y = 0; y < 35; y++)
            {
                fog_of_war_worldmap[x][y] = 0;
            }

    boost::property_tree::ptree root;
    boost::property_tree::read_json("file.json", root);

    for (pt::ptree::value_type & v : root.get_child("volume"))
    {

        if( v.first == "music" )
            music_volume = v.second.get_value<int>();
        if( v.first == "sfx" )
            sfx_volume = v.second.get_value<int>();
    }

    for (pt::ptree::value_type & v : root.get_child("npc_hitpoints"))
    {
        if( v.first == "current" )
            SNpc.hitpoints_current = v.second.get_value<int>();//npc_hitpoints_current = v.second.get_value<int>();
        if( v.first == "max" )
            SNpc.hitpoints_max = v.second.get_value<int>();
    }

    //SNpc.hitpoints_current = npc_hitpoints_current;
    //SNpc.hitpoints_max = npc_hitpoints_max;

    root.put_child("foo", foo() );
    boost::property_tree::write_json("file.json", root );


    CreateItem(0,"Bardiche");
    CreateItem(1,"Battle Axe");
    CreateItem(2,"Bow");
    CreateItem(3,"Broad Axe");
    CreateItem(4,"Club");
    CreateItem(5,"Crossbow");
    CreateItem(6,"Dagger");
    CreateItem(7,"Falchion");
    CreateItem(8,"Flail");
    CreateItem(9,"Greatsword");
    CreateItem(10,"Halberd");
    CreateItem(11,"Hammer");
    CreateItem(12,"HandAxe");
    CreateItem(13,"Long sword");
    CreateItem(14,"Mace");
    CreateItem(15,"Morning star");
    CreateItem(16,"Quarterstaff");
    CreateItem(17,"Scimitar");
    CreateItem(18,"Scythe");
    CreateItem(19,"Short sword");
    CreateItem(20,"Spear");
    CreateItem(21,"War axe");
    CreateItem(22,"Chainmail");
    CreateItem(23,"Leather armor");
    CreateItem(24,"Plate mail");
    CreateItem(25,"Ring mail");
    CreateItem(26,"Robe");
    CreateItem(27,"Buckler");
    CreateItem(28,"Shield");
    CreateItem(29,"Kite shield");
    CreateItem(30,"Gauntlets");
    CreateItem(31,"Helmet");
    CreateItem(32,"Mage hat");
    CreateItem(33,"Bone amulet");
    CreateItem(34,"Celtic amulet");
    CreateItem(35,"Stone amulet");
    CreateItem(36,"Crystal amulet");
    CreateItem(36,"Idol amulet");
    CreateItem(36,"Pentagram amulet");
    CreateItem(36,"Cloak");
    CreateItem(36,"Boots");
    CreateItem(36,"Staff");

//    TextureManager.m_Textures.insert(pair<string,SDL_Texture*>("./images/compass/north.png", LoadTexture("./images/compass/north.png",255) ));
//    TextureManager.m_Textures.insert(pair<string,SDL_Texture*>("./images/compass/south.png", LoadTexture("./images/compass/south.png",255) ));
//    TextureManager.m_Textures.insert(pair<string,SDL_Texture*>("./images/compass/west.png", LoadTexture("./images/compass/west.png",255) ));
//    TextureManager.m_Textures.insert(pair<string,SDL_Texture*>("./images/compass/east.png", LoadTexture("./images/compass/east.png",255) ));
//
//    TextureManager.m_Textures.insert(pair<string,SDL_Texture*>("./images/encamp/encamp0.png", LoadTexture("./images/encamp/encamp0.png",255) ));
//    TextureManager.m_Textures.insert(pair<string,SDL_Texture*>("./images/encamp/encamp1.png", LoadTexture("./images/encamp/encamp1.png",255) ));
//    TextureManager.m_Textures.insert(pair<string,SDL_Texture*>("./images/encamp/encamp2.png", LoadTexture("./images/encamp/encamp2.png",255) ));
//    TextureManager.m_Textures.insert(pair<string,SDL_Texture*>("./images/encamp/encamp3.png", LoadTexture("./images/encamp/encamp3.png",255) ));
//
//    TextureManager.m_Textures.insert(pair<string,SDL_Texture*>("./images/menus/menu_backdrop.png", LoadTexture("./images/menus/menu_backdrop.png",255) ));
//
//    SoundManager.m_Sounds.insert(pair<string,Mix_Chunk*>("./assets/data/sounds/Punch.wav", Mix_LoadWAV("./assets/data/sounds/Punch.wav") ));
//    SoundManager.m_Sounds.insert(pair<string,Mix_Chunk*>("./assets/data/sounds/Pain.wav", Mix_LoadWAV("./assets/data/sounds/Pain.wav") ));
//    SoundManager.m_Sounds.insert(pair<string,Mix_Chunk*>("./assets/data/sounds/Hit.wav", Mix_LoadWAV("./assets/data/sounds/Hit.wav") ));
//    SoundManager.m_Sounds.insert(pair<string,Mix_Chunk*>("./assets/data/sounds/153_Secret_Garden.ogg", Mix_LoadWAV("./assets/data/sounds/153_Secret_Garden.ogg") ));
//
//    SoundManager.m_Sounds.insert(pair<string,Mix_Chunk*>("./assets/data/sounds/tavern/1_Black Moon Tavern by Ean Grimm.mp3", Mix_LoadWAV("./assets/data/sounds/tavern/1_Black Moon Tavern by Ean Grimm.mp3") ));
//    SoundManager.m_Sounds.insert(pair<string,Mix_Chunk*>("./assets/data/sounds/tavern/2_The Ranger's Tavern by Ean Grimm.mp3", Mix_LoadWAV("./assets/data/sounds/tavern/2_The Ranger's Tavern by Ean Grimm.mp3") ));
//    SoundManager.m_Sounds.insert(pair<string,Mix_Chunk*>("./assets/data/sounds/tavern/3_Old King Tavern by Ean Grimm.mp3", Mix_LoadWAV("./assets/data/sounds/tavern/3_Old King Tavern by Ean Grimm.mp3") ));
//    SoundManager.m_Sounds.insert(pair<string,Mix_Chunk*>("./assets/data/sounds/tavern/4_Night Owl Tavern by Ean Grimm.mp3", Mix_LoadWAV("./assets/data/sounds/tavern/4_Night Owl Tavern by Ean Grimm.mp3") ));
//    SoundManager.m_Sounds.insert(pair<string,Mix_Chunk*>("./assets/data/sounds/tavern/5_Dark Woods Tavern by Ean Grimm.mp3", Mix_LoadWAV("./assets/data/sounds/tavern/5_Dark Woods Tavern by Ean Grimm.mp3") ));

    g_myglobal = 10;

	int flags = 0;

	SDL_SetMainReady();

    if( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    {
        SDL_Log("Unable to initialize SDL: %s %s %d", SDL_GetError(), __FILE__, __LINE__);
        throw runtime_error("Unable to initialize SDL: " + string(SDL_GetError()));
    }
    else
    {
        SDL_Log("initialize SDL and all its subsystems: Success %s, %d", __FILE__, __LINE__);
    }

    if(!TTF_WasInit() && TTF_Init()==-1)
    {
        SDL_Log("TTF_Init: %s %s %d", TTF_GetError(), __FILE__, __LINE__);
        throw runtime_error("TTF_Init: " + string(SDL_GetError()));
    }
    else
    {
        SDL_Log("TTF_Init: Success! %s %d", __FILE__, __LINE__);
    }

    // Get current display mode of all displays.
    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
    {
        int should_be_zero = SDL_GetCurrentDisplayMode(i, &monitor[i]);

        current = monitor[0];

        if(should_be_zero != 0)
        {
            SDL_Log("Could not get display mode for video display #%d: %s 5s %d", i, SDL_GetError(), __FILE__, __LINE__);
            throw runtime_error("Could not get display mode for video display: " + string(SDL_GetError()));
        }
        else
        {
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. %s %d", i, monitor[i].w, monitor[i].h, monitor[i].refresh_rate, __FILE__, __LINE__);
        }
    }
    current.w = width;
    current.h = height;

    window = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        current.w, current.h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    //SDL_GLContext Context = SDL_GL_CreateContext(window);
    //SDL_GL_SetSwapInterval(1);

    if (window == NULL)
    {
        SDL_Log("Could not create window: %s %s %d", SDL_GetError(), __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    else
    {
        string version = AutoVersion::FULLVERSION_STRING; //C++ example

        SDL_Log("Version: %s FILE:%s LINE:%d",version , __FILE__, __LINE__);

        SDL_Log("SDL Window creation: SUCCESS %s %d", __FILE__, __LINE__);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_Log("SDL Renderer creation: SUCCESS %s %d", __FILE__, __LINE__);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderSetScale(renderer,1.0,1.0);

        // load support for the JPG and PNG image formats
        int flags=IMG_INIT_JPG|IMG_INIT_PNG;
        int initted=IMG_Init(flags);

        if((initted&flags) != flags)
        {
            SDL_Log("IMG_Init: %s %s %d", IMG_GetError(), __FILE__, __LINE__);
            exit(EXIT_FAILURE);
        }

        if( strcmp(uts.machine, "x86_64") == 0 )
            gSurface = IMG_Load( "./assets/data/textures/icons/64-bit-100.png" );
        else
            gSurface = IMG_Load( "./assets/data/textures/icons/64-bit-100-filled.png" );

        if(!gSurface)
        {
            SDL_Log("Setting Window Icon: %s %s %d", IMG_GetError(), __FILE__, __LINE__);
            exit(EXIT_FAILURE);
        }
        else
        {
            SDL_Log("Loading Window Icon initiated... %s %d", __FILE__, __LINE__);
            SDL_Log("Version: %s %s %d",AutoVersion::FULLVERSION_STRING, __FILE__, __LINE__);
        }

        SDL_SetWindowIcon(window, gSurface);
        SDL_FreeSurface(gSurface);

        SDL_StopTextInput();

        // Replace this with the new SDL2 OpenAudio
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            SDL_Log("Audio broke down: %s %s %d", SDL_GetError(), __FILE__, __LINE__);
            exit(EXIT_FAILURE);
        }
        else
        {
            SDL_Log("Audio successfully initiated... %s %d", __FILE__, __LINE__);
        }

        int result = Mix_AllocateChannels(4);
        if( result < 0 )
        {
            fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
            exit(-1);
        }
    }

    // Get the version of SDL_mixer
    const SDL_version* version = Mix_Linked_Version();

    cout << "SDL_mixer version: "
         << static_cast<int>(version->major) << "."
         << static_cast<int>(version->minor) << "."
         << static_cast<int>(version->patch)
         << endl;

    Mix_VolumeMusic(music_volume);
    Mix_Volume(-1,sfx_volume);

    _sample[0] = Mix_LoadWAV("./assets/data/sounds/153_Secret_Garden.ogg");
    _sample[1] = Mix_LoadWAV("./assets/data/sounds/Hit.wav");
    _sample[2] = Mix_LoadWAV("./assets/data/sounds/Pain.wav");
    _sample[3] = Mix_LoadWAV("./assets/data/sounds/Punch.wav");
    _sample[4] = Mix_LoadWAV("./assets/data/sounds/buttonclick.mp3");
    _sample[5] = Mix_LoadWAV("./assets/data/sounds/interface-click-hover.wav");

    Mix_PlayChannel(-1, _sample[0], 0);

	SDL_Log("Loading items... %s %d", __FILE__, __LINE__);
	AddItem();
	SDL_Log("Loading skills... %w %d", __FILE__, __LINE__);
	AddSkill();

	read_directory("./assets/data/textures",imagesFiles);

	SDL_Log("Loading shop... %s %d", __FILE__, __LINE__);
    initShop();

    gameTitleFont = TTF_OpenFont("./assets/data/fonts/viking-fonts/norse/NorseRegular.otf", g_titleFontSize);

    if(!gameTitleFont)
    {
        SDL_Log("TTF_OpenFont: %s %s %d",TTF_GetError(), __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    gameBreadTextFont = TTF_OpenFont("./assets/data/fonts/viking-fonts/norse/NorseRegular.otf", g_breadTextFontSize);

    if(!gameBreadTextFont)
    {
        SDL_Log("TTF_OpenFont: %s %s %d",TTF_GetError(), __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    North = LoadTexture("./assets/data/textures/compass/north.png",255);
    if( North == NULL)
        exit(99);
    West = LoadTexture("./assets/data/textures/compass/west.png",255);
    South = LoadTexture("./assets/data/textures/compass/south.png",255);
    East = LoadTexture("./assets/data/textures/compass/east.png",255);
    North = LoadTexture("./assets/data/textures/compass/north.png",255);

    encampTexture[0] = LoadTexture("./assets/data/textures/encamp/encamp0.png",255);
    encampTexture[1] = LoadTexture("./assets/data/textures/encamp/encamp1.png",255);
    encampTexture[2] = LoadTexture("./assets/data/textures/encamp/encamp2.png",255);
    encampTexture[3] = LoadTexture("./assets/data/textures/encamp/encamp3.png",255);

    battleState = LoadTexture("./assets/data/textures/backgrounds/battle.png",255);
    gameoverState = LoadTexture("./assets/data/textures/backgrounds/gameover.png",255);

    slot = LoadTexture("./assets/data/textures/ui/slot.png",255);

	m_fullscreen = fullscreen;
	m_running = true;

	generateWorldMapTiles();
}

void CGameEngine::Cleanup()
{
    SDL_Log("CGameEngine Cleanup %s %d", __FILE__, __LINE__);
	// cleanup the all states
	while ( !states.empty() )
    {
		states.back()->Cleanup();
		states.pop_back();
	}
}

void CGameEngine::ChangeState(CGameState* state)
{
    SDL_Log("CGameEngine ChangeState %s %d", __FILE__, __LINE__);
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
    SDL_Log("CGameEngine PushState %s %d", __FILE__, __LINE__);
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
    SDL_Log("CGameEngine PopState %s %d", __FILE__, __LINE__);
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
    SDL_Log("CGameEngine HandleEvents %s %d", __FILE__, __LINE__);
	// let the state handle events
	states.back()->HandleEvents(this);
}

void CGameEngine::Update()
{
    SDL_Log("CGameEngine Update %s %d", __FILE__, __LINE__);
	// let the state update the game
	states.back()->Update(this);
}

void CGameEngine::Draw()
{
    SDL_Log("CGameEngine Draw %s %d", __FILE__, __LINE__);

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer);
	// let the state draw the screen
	states.back()->Draw(this);
}

int CGameEngine::RenderText(std::string renderText, SDL_Color colorValue, int iX, int iY, int fontSize)
{
    TTF_Font* m_font = NULL;
    m_font = TTF_OpenFont("./assets/data/fonts/viking-fonts/norse/NorseRegular.otf", fontSize);

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
    m_font = TTF_OpenFont("./assets/data/fonts/viking-fonts/norse/NorseRegular.otf", 48);

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
    m_font = TTF_OpenFont("./assets/data/fonts/viking-fonts/norse/NorseRegular.otf", g_breadTextFontSize);

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
    m_font = TTF_OpenFont("./assets/data/fonts/viking-fonts/norse/NorseRegular.otf", fontSize);

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
    m_font = TTF_OpenFont("./assets/data/fonts/viking-fonts/norse/NorseRegular.otf", fontSize);

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
    m_font = TTF_OpenFont("./assets/data/fonts/viking-fonts/norse/NorseRegular.otf", fontSize);

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
	std:cout << str.c_str();
	if( texture == NULL)
        exit(88);
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

//    for (auto i = v_ItemNames.begin(); i != v_ItemNames.end(); i++)
//    {
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderClear(renderer);
//
//        SDL_Surface* surface = IMG_Load( "./images/ui/rest_no_rune.png" );
//        if( !surface )
//        {
//            exit(-1);
//        }
//
//        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
//        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//        SDL_SetTextureAlphaMod( texture, 255 );
//        SDL_RenderCopy(renderer, texture, NULL, NULL);
//        SDL_FreeSurface(surface);
//        SDL_DestroyTexture(texture);
//
//        SDL_Rect progressbar_border = {current.w / 2 - v_ItemNames.size()/2,current.h - 200,v_ItemNames.size(),25};
//        SDL_RenderFillRect(renderer, &progressbar_border);
//
//        SDL_Rect progressbar = {current.w / 2 - v_ItemNames.size()/2,current.h - 200,progress_value,25};
//        progress_value++;
//        SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
//        SDL_RenderFillRect(renderer, &progressbar);
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
//        SDL_RenderDrawRect(renderer, &progressbar);
//
//        //RenderText(std::to_string(progress_value).c_str(),White,current.w / 6,current.h - 200, 24);
//
//        RenderText("Loading ItemNames...",White,current.w / 2 - 100,current.h - 245, 24);
//        RenderText(*i,White,current.w / 2 - 100,current.h - 205, 24);
//
//        SDL_RenderPresent(renderer);
//        //SDL_Delay(10);
//    }
//
//    progress_value = 0;
//    for(int x = 0; x < 16; x++ )
//    {
//        for(int y = 0; y < 16; y++ )
//        {
//            for(int z = 0; z < 4; z++ ) // ESWN directions
//            {
//                location = "";
//                room = "";
//                position = "";
//
//                location += "./images/test_map/";
//                room  = "";
//
//                if(x < 10)
//                {
//                    room += "0";
//                }
//
//                room += std::to_string(x);
//
//                if(y < 10)
//                {
//                    room += "0";
//                }
//
//                room += std::to_string(y);
//
//                position = room;
//                room += "/";
//
//                room += position;
//                location += position;
//
//                //location += Rotation;
//                if(z == 0)
//                    location += "E";
//                if(z == 1)
//                    location += "W";
//                if(z == 2)
//                    location += "N";
//                if(z == 3)
//                    location += "S";
//
//                location += fileType;
//                //std::cout << "mapTexture[x][y][z] = " << location << " : " << "(" << x << ")"<< "(" << y << ")"<< "(" << z << ")" << std::endl;
//                //location = "./images/profile_photo3.png";
//                mapTextureFile[x][y][z] = location;
//
//                mapTexture[x][y][z] = IMG_LoadTexture(renderer,location.c_str());
//
//                //exit(1);
//                //myTextures[std::to_string(progress_value).c_str()] = IMG_LoadTexture(renderer,location.c_str());
//                SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
//                SDL_RenderClear(renderer);
//
//                SDL_Surface* surface = IMG_Load( "./images/ui/rest_no_rune.png" );
//                if( !surface )
//                {
//                    exit(-1);
//                }
//
//                SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
//                SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//                SDL_SetTextureAlphaMod( texture, 255 );
//                SDL_RenderCopy(renderer, texture, NULL, NULL);
//                SDL_FreeSurface(surface);
//                SDL_DestroyTexture(texture);
//
//                SDL_Rect progressbar_border = {current.w / 2 - 1024/2,current.h - 200,1024,25};
//                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
//                SDL_RenderFillRect(renderer, &progressbar_border);
//
//                SDL_Rect progressbar = {current.w / 2 - 1024/2,current.h - 200,progress_value,25};
//                progress_value++;
//                SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
//                SDL_RenderFillRect(renderer, &progressbar);
//                SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
//                SDL_RenderDrawRect(renderer, &progressbar);
//
//                RenderText("Loading Level...",White,current.w / 2 - 100,current.h - 245, 24);
//                RenderText(location.c_str(),White,current.w / 3,current.h - 205,24);
//                SDL_RenderPresent(renderer);
//            }
//        }
//    }
    ender = std::chrono::steady_clock::now();
    SDL_Log("Millisecond loading time: %d %s %d", double(std::chrono::duration_cast<std::chrono::nanoseconds>(ender - starter).count()) / 1000000, __FILE__, __LINE__ );
    // 20357 milliseconds
};

void CGameEngine::AddItem()
{
    SDL_Log("CGameEngine AddItem %s %d", __FILE__, __LINE__);

    for (auto i = v_ItemNames.begin(); i != v_ItemNames.end(); i++)
    {
        Item tempObject;
        tempObject.Name = *i;

//        SDL_Log("Adding '%s'\n",tempObject.Name.c_str());
//        SDL_Log("   Setting Efficiency: '%i'\n",tempObject.Efficiency = 0);
//        SDL_Log("   Setting MinDamage: '%i'\n",tempObject.MinDamage = 0);
//        SDL_Log("   Setting MaxDamage: '%i'\n",tempObject.MaxDamage = 0);
//        SDL_Log("   Setting DmgType: '%i'\n",tempObject.DmgType = 0);
//        SDL_Log("   Setting NumHands: '%i'\n",tempObject.NumHands = 0);
//        SDL_Log("   Setting Bodypart: '%i'\n",tempObject.Bodypart = 0);
//        SDL_Log("   Setting UsedBy: '%i'\n",tempObject.UsedBy = 0);
//        SDL_Log("   Setting Skill: '%i'\n",tempObject.Skill = 0);
//        SDL_Log("   Setting BaseWorth: '%i'\n",tempObject.BaseWorth = 0);
//        SDL_Log("   Setting Price: '%i'\n",tempObject.Price = 0);
//        SDL_Log("   Setting Protection: '%i'\n",tempObject.Protection = 0);
//        SDL_Log("   Setting Enchantments: '%i'\n",tempObject.Enchantments = 0);
//        SDL_Log("   Setting Effect: '%i'\n",tempObject.Effect = 0);
//        SDL_Log("   Setting EffectCharges: '%i'\n",tempObject.EffectCharges = 0);
//        SDL_Log("   Setting MinEffect: '%i'\n",tempObject.MinEffect = 0);
//        SDL_Log("   Setting MaxEffect: '%i'\n",tempObject.MaxEffect = 0);
//        SDL_Log("   Setting Features: '%i'\n",tempObject.Features = 0);
//        v_Item.push_back(tempObject);
    }
};

void CGameEngine::AddSkill()
{
    SDL_Log("CGameEngine AddSkill %s %d", __FILE__, __LINE__);

    std::vector<SkillObject> test{
    {"Short blade","",0,0},
    {"Long blade","",0,0},
    {"Bow","",0,0},
    {"Bludgeon","",0,0},
    {"Short axe","",0,0},
    {"Long axe","",0,0},
    {"Poleblade","",0,0},
    {"Shield","",0,0},
    {"Leather armor","",0,0},
    {"Chained armor","",0,0},
    {"SCaled armor","",0,0},
    {"Plated armor","",0,0},
    {"Fitness","",0,0},
    {"Lore","",0,0},
    {"Persuasion","",0,0},
    {"Taming","",0,0},
    {"Quickhand","",0,0},
    {"Stealth","",0,0},
    {"Awareness","",0,0}
    };

    int counter = 0;
    for (auto i = test.begin(); i != test.end(); i++)
    {
        SDL_Rect rect;
        rect.x = 500;
        rect.y = 170+(counter*50);
        rect.w = 300;
        rect.h = 30;
        i->Position.x = 500;
        i->Position.y = 170+(counter*50);
        i->Position.w = 300;
        i->Position.h = 30;
        v_Skill.push_back(*i);
        SkillRect.push_back(i->Position);
        counter++;
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
                SDL_Log("Adding type: '%s' %s %d",line.c_str(), __FILE__, __LINE__);
            }
            if( line == "#WEIGHT")
            {
                getline (shop_data_file,line);
                std::cout << line << std::endl;
                int integer_data = std::stoi(line);
                std::cout << integer_data << std::endl;
                tempItem.weight = integer_data;
                SDL_Log("Adding weight: '%s' %s %d",line.c_str(), __FILE__, __LINE__);
            }
            if( line == "#COST")
            {
                getline (shop_data_file,line);
                tempItem.value = std::stoi(line);
                SDL_Log("Adding cost: '%s' %s %d",line.c_str(), __FILE__, __LINE__);
            }
            if( line == "#ITEM")
            {
                getline (shop_data_file,line);
                tempItem.name = line.c_str();
                SDL_Log("Adding item: '%s' %s %d",line.c_str(), __FILE__, __LINE__);
                out_data.push_back(tempItem);
            }
        }
        shop_data_file.close();
    }
    else SDL_Log("Unable to open file %s %d", __FILE__, __LINE__);
};

void CGameEngine::initShop()
{
//    LoadShopData("./data/general_shop_data",generalShopItems);
//    LoadShopData("./data/jewellery_shop_data",jewelleryShopItems);
//    LoadShopData("./data/silver_shop_data",silverShopItems);
//    LoadShopData("./data/arms_and_armours_data",armsAndArmoursShopItems);
};

void CGameEngine::renderDaytime()
{
        SDL_Rect dayTimeBox = {current.w - 75,25,50,50};
        SDL_Rect Season_Position = {current.w - 75,100,50,50};

        SDL_Texture* dayTimeTexture = NULL;
        SDL_Texture* Season_Texture = NULL;

        if( Daytime == 0)
            dayTimeTexture = LoadTexture("./assets/data/textures/icons/day-white.png",128);
        else if ( Daytime == 1)
            dayTimeTexture = LoadTexture("./assets/data/textures/icons/day-white.png",255);
        else if( Daytime == 2)
            dayTimeTexture = LoadTexture("./assets/data/textures/icons/night-white.png",128);
        else if( Daytime == 3)
            dayTimeTexture = LoadTexture("./assets/data/textures/icons/night-white.png",255);

        if( Season == 0)
            Season_Texture = LoadTexture("./assets/data/textures/icons/summer.jpg",128);
        else if ( Season == 1)
            Season_Texture = LoadTexture("./assets/data/textures/icons/spring.jpg",255);
        else if( Season == 2)
            Season_Texture = LoadTexture("./assets/data/textures/icons/fall.jpg",128);
        else if( Season == 3)
            Season_Texture = LoadTexture("./assets/data/textures/icons/winter.png",255);

        SDL_RenderCopy(renderer, dayTimeTexture, NULL, &dayTimeBox);
        SDL_DestroyTexture(dayTimeTexture);
        SDL_RenderCopy(renderer, Season_Texture, NULL, &Season_Position);
        SDL_DestroyTexture(Season_Texture);

        RenderText("Season: " + WeatherEngine.get_season(), White, current.w - 250,0,24);
        RenderText("Temperature: " + std::to_string(WeatherEngine.get_temperature()), White, current.w - 250,50,24);
        RenderText("currentTime: " + std::to_string(gameTime.tm_hour)+std::to_string(gameTime.tm_min)+std::to_string(gameTime.tm_sec),White, current.w - 250, 100,24);
        RenderText("currentDay: " + std::to_string(gameTime.tm_mday),White, current.w - 250, 150,24);
}

void CGameEngine::renderQuests()
{
    int position_y = 0;
    Quest *curr = Quests.head;
    while (curr != nullptr)
    {
        SDL_Rect hooverBox = {0,current.h - 600 + position_y,1000,30};
        unsigned char r, g, b, a;
        SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 128);
        SDL_RenderDrawRect(renderer,&hooverBox);

        SDL_SetRenderDrawColor(renderer, r,g,b,a);

        RenderText(curr->task + ": " + (curr->completed ? "Completed" : "Incomplete"), Black, 0,current.h - 600 + position_y,24);

        RenderText(curr->description, Black, 1000,current.h - 600 + position_y,24);

        curr = curr->next;
        position_y += 30;

    }
}

void CGameEngine::renderQuestsList()
{
    int position_y = 0;
    Quest *curr = Quests.head;
    while (curr != nullptr)
    {
        SDL_Rect hooverBox = {0,current.h - 600 + position_y,500,30};
        unsigned char r, g, b, a;
        SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 128);
        SDL_RenderDrawRect(renderer,&hooverBox);

        SDL_SetRenderDrawColor(renderer, r,g,b,a);

        RenderText(curr->task + ": " + (curr->completed ? "Completed" : "Incomplete"), Black, 0,current.h - 600 + position_y,24);

        curr = curr->next;
        position_y += 30;

    }
}
