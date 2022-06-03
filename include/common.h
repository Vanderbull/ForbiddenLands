#ifndef COMMON_H
#define COMMON_H

#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;

#include "colors.h"
#include "coordinates.h"
#include "player_characters.h"
//#include "savegame.h"

void renderShopCoins();

auto start = high_resolution_clock::now(), stop = high_resolution_clock::now();

int randomEncounters = 0;

// Quest states
enum { PENDING,UNLOCKED,IN_PROGRESS,COMPLETED,DONE,CANCELED };

playerCharacters playerCharacter[6];

int removeIndex = 0;
int triggerRemove = 0;

unsigned char MusicVolume = 0;
int gHighTriggered = 0;
int disableSound = 0;

int LoadMenu = 0;
int SaveMenu = 0;
int CreateCharacter = 0;
int MenuCounter = 0;
int MenuCounterSwitch = 0;

std::vector<std::string> MenuChoices;

// VIEWS CONSTANTS
enum { MAIN_MENU,DUNGEON,WILDERNESS,BATTLE,SETTINGS };

int activeView = MAIN_MENU;
int SettingsMenu = 0;
int looping = 0;

SDL_Rect exitButton;
SDL_Rect readyButton;

bool newGame = true;

std::string phlanTourCoordinateN[100];

std::string xcoord = "";
std::string ycoord = "";

std::string rotationString = "";
std::string coordinateString = "";

bool Clicked = false;

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

char cCurrentPath[FILENAME_MAX];

std::ifstream itemFileData;

std::string line;

SDL_Rect gButtonExit{0,0,0,0};

//X,Y,W,H
SDL_Rect gTileID{0,-10,150,160};

std::string compassDirection = "NESW";
int compassNeedle = 0;
int inGameTime = 0;

int frame = 0;
class InputComponent;

SDL_Window * window;

std::vector<std::string> mainLog;

bool minimapActive = true;
std::string Rotation = "W";
std::string mapActive = "phlan";

#define PHLAN, SLUMS
int worldMap = 0;

SDL_Rect square = {0,0,15,15};

int playerCharacterSelected = 0;
int playerCharacterSelected2 = -1;

SDL_Point mousePosition;

extern int quit;
Uint32 state;

SDL_Event event;

SDL_DisplayMode monitor[6];
SDL_DisplayMode current;
SDL_Rect** modes;

int quit = 0;
int counter = 0;

struct fsobject
{
    std::string fqname; //Fully Qualified Name of File incl extension
    std::string type;   //Type of Object, Either Directory or File
    std::string data;   //contents of file. Directories have no data.
};

std::vector<fsobject> driveA;//Drive A

std::vector<std::string> generalStoreItems;
std::vector<std::string> jewelleryStoreItems;
std::vector<std::string> silverStoreItems;
std::vector<std::string> armsAndArmours;

std::array<int, 300> armsAndArmoursValue;

int offset = 0;
int offset2 = 0;

int offsetShopList = 0;
int offsetPlayerCharacterList = 0;

int showEntries = 15;
int showEntriesInShop = 15;
int FontSize = 20;
int scrollOffsetShop = 0;

SDL_Rect upArrow = {800,200,25,25};
SDL_Rect downArrow = {800,620,25,25};
SDL_Rect upArrow2 = {1900,200,25,25};
SDL_Rect downArrow2 = {1900,620,25,25};

bool templeShop = 0;
bool rolf = 0;
bool trainingHall = 0;
bool shop = 0;
bool armsAndarmourShop = 0;
bool jewelleryShop = 0;
bool generalShop = 0;
bool silverShop = 0;
bool tavern = 0;
bool encamped = 0;
bool viewingCharacter = 0;

int loadingScreen = 1;

int fontSize = 20;
bool viewItems = false;

//To store matrix cell cordinates
struct Point
{
    int x;
    int y;
};

void naturalHealing();

enum timeOfDay
{
    day,
    night
};

int currentDay = 0;
int currentTime = 0;
int currentTimeOfDay = day;

int currentTimeElapse(bool tick = false )
{
    if( tick )
    {
        currentTime++;
        if( currentTime > 24 )
        {
            currentTime = 0;
            currentDay++;
            naturalHealing();
        }
        if( currentTime > 6 && currentTime < 18 )
        {
            currentTimeOfDay = day;
        }
        else
        {
            currentTimeOfDay = night;
        }
    }
    return currentTimeOfDay;
};

//std::string getTimeOfDay()
//{
//    if( inGameTime > 24 )
//    {
//        naturalHealing();
//        inGameTime = 0;
//    }
//
//    if( inGameTime > 6 && inGameTime < 18 )
//    {
//        return "Day time";
//    }
//    else
//    {
//        return "Night time";
//    }
//};

// need to fix traversing subfolders

static int countFiles(const char *dir)
{
    std::cout << "COUNT DAMIT" << std::endl;
	DIR *d;
	struct dirent *ent;
	char *path;
	int i;

	i = 0;

	if ((d = opendir(dir)) != NULL)
	{
		while ((ent = readdir(d)) != NULL)
		{
			if (ent->d_type == DT_DIR)
			{
				if (ent->d_name[0] != '.')
				{
                    std::cout << "MORE MORE MORE" << std::endl;

					//path = malloc(strlen(dir) + strlen(ent->d_name) + 2);
					//sprintf(path, "%s/%s", dir, ent->d_name);
					//i += countFiles(path);
					//free(path);
				}
			}
			else
			{
				i++;
			}
		}

		closedir(d);
	}
	else
    {
        std::cout << "ERROR OPNEDIR COUNT DAMIT" << std::endl;
    }

	return i;
}

#define MAX 5

uint32_t GetTickCount()
{
    struct timespec ts;
    unsigned theTick = 0U;
    clock_gettime( CLOCK_REALTIME, &ts );
    theTick  = ts.tv_nsec / 1000000;
    theTick += ts.tv_sec * 1000;
    return theTick;
}

class Interval
{
private:
    unsigned int initial_;

public:
    // Ctor
    inline Interval() : initial_(GetTickCount())
    {
    }

    // Dtor
    virtual ~Interval()
    {
    }

    inline unsigned int value() const
    {
        return GetTickCount()-initial_;
    }
};

class Fps
{
protected:
    unsigned int m_fps;
    unsigned int m_fpscount;
    Interval m_fpsinterval;

public:
    // Constructor
    Fps() : m_fps(0), m_fpscount(0)
    {
    }

    // Update
    void update()
    {
        // increase the counter by one
        m_fpscount++;

        // one second elapsed? (= 1000 milliseconds)
        if (m_fpsinterval.value() > 1000)
        {
            // save the current counter value to m_fps
            m_fps         = m_fpscount;

            // reset the counter and the interval
            m_fpscount    = 0;
            m_fpsinterval = Interval();
        }
    }

    // Get fps
    unsigned int get() const
    {
        return m_fps;
    }
};

void scaleObject(SDL_Rect _inRect, float _inScale)
{
    // calculate new x and y
    int new_x = (_inRect.x + _inRect.w/2) - (_inRect.w/2 * _inScale);
    int new_y = (_inRect.y + _inRect.h/2) - (_inRect.h/2 * _inScale);
    // form new destination rect
    SDL_Rect dest_rect = { new_x, new_y, _inRect.w * _inScale, _inRect.h * _inScale };
    // render
    SDL_RenderFillRect(renderer, &dest_rect);
};

bool IsButtonReleased(const Uint32 uButton)
{
    return ((SDL_BUTTON(uButton) & m_uCurrentMouseState)==0)&&((SDL_BUTTON(uButton) & m_uPreviousMouseState)!=0);
}

void mouseUpdate(void)
{
    ///--- Store the current information to the previous
    m_iPreviousCoordX=m_iCurrentCoordX;
    m_iPreviousCoordY=m_iCurrentCoordY;
    m_uPreviousMouseState=m_uCurrentMouseState;

    ///--- Update the current state of the mouse
    m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

    ///--- Set the wheel back to 0
    m_iWheelX=0;
    m_iWheelY=0;
}

SDL_Texture *backgroundTexture = NULL;

static bool loadedBackground = false;
void loadBackground(std::string image)
{
    backgroundTexture = LoadTexture(image.c_str(),255);
};

void renderBackground(std::string image)
{
    start = high_resolution_clock::now();

    if( !loadedBackground )
    {
        loadBackground(image);
        loadedBackground = true;
    }

    SDL_RenderClear(renderer);
    //currentViewTexture = LoadTexture(image.c_str(),255);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    //SDL_DestroyTexture(currentViewTexture);

    stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "microseconds: " << duration.count() << endl;
};

int rowcounter = 0;

void print(std::vector<std::string> const &readyInventory,int x, int y, int fontsize)
{
    rowcounter = 0;
    for (auto const& item: readyInventory)
    {
        RenderText(item.c_str(),White,x,y + (20*rowcounter),fontSize);
        rowcounter++;
    }
}

void renderFPS(unsigned int fps)
{
    RenderText("FPS: " + std::to_string(fps),Green,0,0,48);
};

void renderCharacterView()
{
    SDL_Rect StatsFraming = {20, 70,1200,800};
    SDL_Rect StatsFraming2 = {130, 260,200,310};
    SDL_Rect currencyFraming = {730, 260,200,310};
    SDL_Rect StatsFraming3 = {1220, 70,1200,800};

    SDL_Rect Button[8];

    Button[0] = {0, current.h - 60,50,50};
    Button[1] = {100, current.h - 60,50,50};
    Button[2] = {200, current.h - 60,50,50};
    Button[3] = {300, current.h - 60,50,50};
    Button[4] = {400, current.h - 60,50,50};
    Button[5] = {500, current.h - 60,50,50};
    Button[6] = {0, 0,50,50};
    Button[7] = {current.w - 50, 0,50,50};

    SDL_Rect Button7 = {0, 0,50,50};
    SDL_Rect Button8 = {current.w - 50, 0,50,50};

    SDL_Rect background = {0, 0, current.w,current.h};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &background);
    SDL_SetRenderDrawColor(renderer, 255,255, 255, 255);
    SDL_RenderDrawRect(renderer, &background);

    SDL_Rect TextFrame = {0, 0, 0, 0};

    std::stringstream genderRaceAge;
    genderRaceAge << playerCharacter[playerCharacterSelected].getRace();

    RenderText(genderRaceAge.str(),White, 512,120, 24);
    RenderText("XP: " + std::to_string(playerCharacter[playerCharacterSelected].getExperience()),White, 512,170, 24);
    RenderText("HP: " + std::to_string(playerCharacter[playerCharacterSelected].getHitpoints()) + " / " + std::to_string(playerCharacter[playerCharacterSelected].hitpoints_max),White, 512,270, 48);

    playerCharacter[playerCharacterSelected].renderFace();
    renderShopCoins();

    RenderText("STR "+std::to_string(playerCharacter[playerCharacterSelected].current_stats[0]),Green, 512,370, 24);
    TextFrame = FrameText("+",600, 370, 24);
    SDL_RenderDrawRect(renderer, &TextFrame);
    RenderText("+",White, 600,370, 24);
    if( playerCharacter[playerCharacterSelected].getExperience() > 999 )
    {
        if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacter[playerCharacterSelected].current_stats[0]++;
                playerCharacter[playerCharacterSelected].experience -= 1000;
                SDL_Delay(50);
            }
        }
    }

    RenderText("INT "+std::to_string(playerCharacter[playerCharacterSelected].current_stats[1]),Green, 512,420, 24);
    TextFrame = FrameText("+",600, 420, 24);
    SDL_RenderDrawRect(renderer, &TextFrame);
    RenderText("+",White, 600,420, 24);
    if( playerCharacter[playerCharacterSelected].getExperience() > 999 )
    {
        if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacter[playerCharacterSelected].current_stats[1]++;
                playerCharacter[playerCharacterSelected].experience -= 1000;
                SDL_Delay(50);
            }
        }
    }

    RenderText("WIS "+std::to_string(playerCharacter[playerCharacterSelected].current_stats[2]),Green, 512,470, 24);
    TextFrame = FrameText("+",600, 470, 24);
    SDL_RenderDrawRect(renderer, &TextFrame);
    RenderText("+",White, 600,470, 24);
    if( playerCharacter[playerCharacterSelected].getExperience() > 999 )
    {
        if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacter[playerCharacterSelected].current_stats[2]++;
                playerCharacter[playerCharacterSelected].experience -= 1000;
                SDL_Delay(50);
            }
        }
    }

    RenderText("DEX "+std::to_string(playerCharacter[playerCharacterSelected].current_stats[3]),Green, 512,520, 24);
    TextFrame = FrameText("+",600, 520, 24);
    SDL_RenderDrawRect(renderer, &TextFrame);
    RenderText("+",White, 600,520, 24);
    if( playerCharacter[playerCharacterSelected].getExperience() > 999 )
    {
        if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacter[playerCharacterSelected].current_stats[3]++;
                playerCharacter[playerCharacterSelected].experience -= 1000;
                SDL_Delay(50);
            }
        }
    }

    RenderText("CON "+std::to_string(playerCharacter[playerCharacterSelected].current_stats[4]),Green, 512,570, 24);
    TextFrame = FrameText("+",600, 570, 24);
    SDL_RenderDrawRect(renderer, &TextFrame);
    RenderText("+",White, 600,570, 24);
    if( playerCharacter[playerCharacterSelected].getExperience() > 999 )
    {
        if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacter[playerCharacterSelected].current_stats[4]++;
                playerCharacter[playerCharacterSelected].experience -= 1000;
                SDL_Delay(50);
            }
        }
    }

    RenderText("CHA "+std::to_string(playerCharacter[playerCharacterSelected].current_stats[5]),Green, 512,620, 24);
    TextFrame = FrameText("+",600, 620, 24);
    SDL_RenderDrawRect(renderer, &TextFrame);
    RenderText("+",White, 600,620, 24);
    if( playerCharacter[playerCharacterSelected].getExperience() > 999 )
    {
        if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacter[playerCharacterSelected].current_stats[5]++;
                playerCharacter[playerCharacterSelected].experience -= 1000;
                SDL_Delay(50);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    viewItems = true;

    // Render left and right switch buttons for switching character
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &Button7);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &Button8);

    RenderText(std::to_string(playerCharacterSelected),White, current.w / 2,0, 48);
    RenderText("<",White, 10,-5, 48);
    RenderText(">",White, current.w - 40,-5, 48);

    if( SDL_PointInRect(&mousePosition, &Button7) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderDrawRect(renderer, &Button7);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if( playerCharacterSelected <= 0 )
                playerCharacterSelected = (sizeof playerCharacter / sizeof playerCharacter[0])-1;
            else
                playerCharacterSelected--;
            SDL_Delay(50);
        }
    }
    if( SDL_PointInRect(&mousePosition, &Button8) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderDrawRect(renderer, &Button8);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if( playerCharacterSelected < (sizeof playerCharacter / sizeof playerCharacter[0]) - 1 )
                playerCharacterSelected++;
            else
                playerCharacterSelected = 0;
            SDL_Delay(50);
        }
    }

    if( viewItems )
    {
        playerCharacter[playerCharacterSelected].renderCharacterViewItems();
    }

    SDL_DestroyTexture(currentViewTexture);
};

std::string pad_left(std::string const& str, size_t s)
{
    if ( str.size() < s )
        return std::string(s-str.size(), ' ') + str;
    else
        return str;
}

std::string pad_right(std::string const& str, size_t s)
{
    if ( str.size() < s )
        return str + std::string(s-str.size(), ' ');
    else
        return str;
}

enum buttonName {ENCAMP,BACKPACK};

SDL_Texture* Texture[100];
SDL_Rect button[4];

void loadPCstatusData()
{
    Texture[ENCAMP] = LoadTexture("./icons/uiAtlas/ui_game_symbol_campfire.png",255);
    Texture[BACKPACK] = LoadTexture("./icons/uiAtlas/ui_game_symbol_fetch_loot.png",255);
    button[ENCAMP] = {current.w - 168*2, 0,160,160};
    button[BACKPACK] = {1260, current.h - 160,160,160};
};

void unloadPCstatusData()
{
    SDL_DestroyTexture(Texture[ENCAMP]);
    SDL_DestroyTexture(Texture[BACKPACK]);
};

void renderPCstatus()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 192);
    SDL_RenderFillRect(renderer, &button[ENCAMP]);

    SDL_RenderCopy(renderer, Texture[ENCAMP], NULL, &button[ENCAMP]);

    SDL_SetTextureColorMod(Texture[BACKPACK], 0, 255, 0); //set yellow letters
    SDL_RenderCopy(renderer, Texture[BACKPACK], NULL, &button[BACKPACK]);
    SDL_RenderCopy(renderer, Texture[BACKPACK], NULL, &button[BACKPACK]);

    RenderText("ENCAMP", Black, button[ENCAMP].x, button[ENCAMP].y,20);

    if( SDL_PointInRect(&mousePosition, &button[ENCAMP]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if( mapActive == "phlan" )
            {
                RenderText("The guards kick on you and tells you to move on", Red, current.w / 3, current.h / 2,48);
            }
            else
            {
                encamped = 1;
            }
        }
    }

    if( SDL_PointInRect(&mousePosition, &button[BACKPACK]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            playerCharacterSelected2 = 0;
            viewingCharacter = 1;
        }
    }
};

void savingGameData( std::string saveFile )
{
    std::ofstream SaveGame;
    SaveGame.open(saveFile.c_str());

    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame << playerCharacter[i].getName() << std::endl;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame << playerCharacter[i].getArmourClass() << std::endl;
    }
//    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
//    {
//        SaveGame << playerCharacter[i].getClericLevel() << std::endl;
//    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame << playerCharacter[i].getEncumbrance() << std::endl;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame << playerCharacter[i].getExperience() << std::endl;
    }
//    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
//    {
//        SaveGame << playerCharacter[i].getFighterLevel() << std::endl;
//    }
    SaveGame << PlayerCoordinate.x << std::endl;
    SaveGame << PlayerCoordinate.y << std::endl;
    SaveGame.close();
}

void loadingGameData( std::string saveFile )
{
    std::ifstream SaveGame;
    SaveGame.open(saveFile.c_str());
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame >> playerCharacter[i].name;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame >> playerCharacter[i].ac_current;
    }
//    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
//    {
//        SaveGame >> playerCharacter[i].level_cleric;
//    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame >> playerCharacter[i].encumbrance;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame >> playerCharacter[i].experience;
    }
//    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
//    {
//        SaveGame >> playerCharacter[i].level_fighter;
//    }

    SaveGame >> PlayerCoordinate.x;
    SaveGame >> PlayerCoordinate.y;

    SaveGame.close();
}

int encumbranceIncoins(int coins)
{
    if(coins <= 350)
        return 12;
    if(coins <= 700)
        return 9;
    if(coins <= 1050)
        return 6;
    if(coins > 1050)
        return 3;
}

void phlanTour()
{
    std::ifstream dataFile ("./data/phlan_tour/data");

    std::string line;

    while(std::getline(dataFile, line))
    {
        if (line.length() == 0 || line[0] == '#')
        {
            //cout << "IGNORE LINE\n";
        }
        else
        {
            // cache the line
            std::istringstream tokenizer(line);

            std::getline(tokenizer, phlanTourCoordinateN[0], ','); // then get the tokens from it
            std::getline(tokenizer, phlanTourCoordinateN[1]); // last token: get the remainder of the line.

            if(tokenizer)
            {
                //std::cout << phlanTourCoordinateN[0] << std::endl;
                //std::cout << phlanTourCoordinateN[1] << std::endl;
                // success!
            }
            else
            {
                std::cout << "There were fewer than one commas in the line" << std::endl;
            }
        }
    }
};

// The auto versioning does not work, so maybe rewrite this code or remove it
void renderVersion()
{
    Uint8 r,g,b,a;
    Uint8 fontSize = 20;
    std::string versionText = "";

    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

    r = Black.r;
    g = Black.g;
    b = Black.b;
    a = Black.a;

    SDL_Color invertedColor;

    invertedColor.r = 255 - r;
    invertedColor.g = 255 - g;
    invertedColor.b = 255 - b;
    invertedColor.a = 255;

    if (uname(&uts) < 0)
    {
        perror("uname() error");
    }
    else
    {
        RenderText(uts.sysname, invertedColor, 20, 20,fontSize);
        RenderText(uts.nodename, invertedColor, 20, 40,fontSize);
        RenderText(uts.release, invertedColor, 20, 60,fontSize);
        RenderText(uts.version, invertedColor, 20, 80,fontSize);
        RenderText(uts.machine, invertedColor, 20, 100,fontSize);
        SDL_RendererInfo rendererInfo;
        SDL_GetRendererInfo(renderer, &rendererInfo);

        RenderText(rendererInfo.name, invertedColor, 20, 120,fontSize);
    }

    versionText += AutoVersion::STATUS;
    versionText += " ";
    versionText += AutoVersion::FULLVERSION_STRING;
    versionText += " (b ";
    versionText += std::to_string(AutoVersion::BUILDS_COUNT);
    versionText += " )";
    RenderText(versionText, invertedColor, 80, current.h - 40,fontSize);
};

int getShopInventorySize()
{
    if( generalShop )
        return (generalStoreItems.size() - 1);
    else if( silverShop )
        return (silverStoreItems.size() - 1);
    else if( jewelleryShop )
        return (jewelleryStoreItems.size() - 1);
    else if( armsAndarmourShop )
        return (armsAndArmours.size() - 1);
};

void initShop()
{
    string line;
    ifstream general_shop_data_file ("./data/general_shop_data");
    int i = 0;
    if (general_shop_data_file.is_open())
    {
        while ( getline (general_shop_data_file,line) )
        {
            if( line == "#TYPE")
            {
                getline (general_shop_data_file,line);
            }
            if( line == "#WEIGHT")
            {
                getline (general_shop_data_file,line);
            }
            if( line == "#COST")
            {
                getline (general_shop_data_file,line);
            }
            if( line == "#ITEM")
            {
                getline (general_shop_data_file,line);
                generalStoreItems.push_back(line);
            }
            i++;
        }
        general_shop_data_file.close();
        std::cout << "./data/general_shop_data loaded" << std::endl;
    }
    else std::cout << "Unable to open file";

    ifstream jewellery_shop_data_file ("./data/jewellery_shop_data");
    i = 0;
    if (jewellery_shop_data_file.is_open())
    {
        std::cout << "./data/jewellery_shop_data starting to load" << std::endl;
        while ( getline (jewellery_shop_data_file,line) )
        {
            std::cout << "parsing line number: " << line << " " << i << std::endl;
            if( line == "#TYPE")
            {
                getline (jewellery_shop_data_file,line);
            }
            if( line == "#WEIGHT")
            {
                getline (jewellery_shop_data_file,line);
            }
            if( line == "#COST")
            {
                getline (jewellery_shop_data_file,line);
            }
            if( line == "#ITEM")
            {
                getline (jewellery_shop_data_file,line);
                std::cout << "parsing line number: " << line << " " << i << std::endl;
                jewelleryStoreItems.push_back(line);
            }
            i++;
        }
        jewellery_shop_data_file.close();
        std::cout << "./data/jewellery_shop_data loaded" << std::endl;
    }
    else cout << "Unable to open file";

    ifstream silver_shop_data_file ("./data/silver_shop_data");
    i = 0;
    if (silver_shop_data_file.is_open())
    {
        std::cout << "./data/silver_shop_data starting to load" << std::endl;
        while ( getline (silver_shop_data_file,line) )
        {
            if( line == "#TYPE")
            {
                getline (silver_shop_data_file,line);
            }
            if( line == "#WEIGHT")
            {
                getline (silver_shop_data_file,line);
            }
            if( line == "#COST")
            {
                getline (silver_shop_data_file,line);
            }
            if( line == "#ITEM")
            {
                getline (silver_shop_data_file,line);
                silverStoreItems.push_back(line);
            }

            i++;
        }
        silver_shop_data_file.close();
        std::cout << "./data/silver_shop_data loaded" << std::endl;
    }
    else cout << "Unable to open file";

    ifstream arms_and_armours_data_file ("./data/arms_and_armours_data");
    i = 0;
    if (arms_and_armours_data_file.is_open())
    {
        std::cout << "./data/arms_and_armours_data starting to load" << std::endl;
        while ( getline (arms_and_armours_data_file,line) )
        {
            if( line == "#TYPE")
            {
                getline (arms_and_armours_data_file,line);
            }
            if( line == "#WEIGHT")
            {
                getline (arms_and_armours_data_file,line);
            }
            if( line == "#COST")
            {
                getline (arms_and_armours_data_file,line);
                armsAndArmoursValue.at(i) = rand()%100;
            }
            if( line == "#ITEM")
            {
                getline (arms_and_armours_data_file,line);
                armsAndArmours.push_back(line);
            }
            i++;
        }
        arms_and_armours_data_file.close();
        std::cout << "./data/arms_and_armours_data loaded" << std::endl;
    }
    else cout << "Unable to open file";
};

SDL_Rect leftScrollButtonUp = {700,200,25,25};
SDL_Rect leftScrollButtonDown = {700,620,25,25};
SDL_Rect rightScrollButtonUp = {1900,200,25,25};
SDL_Rect rightScrollButtonDown = {1900,620,25,25};

void renderShopCoins()
{
    RenderText("Gold: " + std::to_string(playerCharacter[playerCharacterSelected].coins_gold),White,510,210,FontSize);
    RenderText("Hunger: " + std::to_string(playerCharacter[playerCharacterSelected].hunger),White,510,230,FontSize);
    RenderText("Thirst: " + std::to_string(playerCharacter[playerCharacterSelected].thirst),White,510,250,FontSize);
    RenderText("Armour class: " + std::to_string(playerCharacter[playerCharacterSelected].getArmourClass()),White,510,270,FontSize);
};

int currentCharacter = 0;
int statPoints[6] = {5,5,5,5,5,5};

int statPointsRequirements[7][6] = { {5,5,5,5,5,5}, // Elves
                                    {5,5,5,5,5,5},
                                    {5,5,5,5,5,5},
                                    {5,5,5,5,5,5},
                                    {5,5,5,5,5,5},
                                    {5,5,5,5,5,5},
                                    {5,5,5,5,5,5}
                                    };

// Minimum / Maximum Strength,Dexterity,Constitution,Intelligence,Wisdom,Charisma
int racialLimitations[7][12] = { {8,18,3,17,12,19,3,18,3,18,3,16}, // Dwarfs
                                 {3,18,7,19,8,17,8,18,3,18,8,19},   // Elves
                                 {6,18,3,18,8,18,7,18,3,18,3,18},   // Gnomes
                                 {3,18,6,18,6,18,4,18,3,18,3,18},   // Half elves
                                 {6,17,8,19,10,18,6,18,3,17,3,18},  // Halflings
                                 {6,18,3,17,13,19,3,17,3,14,3,12},  // Half orcs
                                 {3,18,3,18,3,18,3,18,3,18,3,18}      // Humans
                            };

int levelLimitations[9][7] = {   {9,1,3,1,1,1,3}, // Assassin
                                 {8,1,7,1,8,1,8},   // Cleric
                                 {-1,1,3,1,8,1,7},   // Druid
                                 {9,1,6,1,6,1,4},   // Fighter
                                 {-1,1,8,1,1,1,6},  // Illusionist
                                 {-1,1,3,1,1,1,3},  // Magic user
                                 {-1,1,3,1,3,1,3},      // Paladin
                                 {-1,1,3,1,3,1,1},      // Ranger
                                 {0,1,3,1,3,1,3}      // Thief
                            };

std::string TITLE = "FORBIDDEN LANDS";
int getThiefLevel( int experience )
{
    if( experience < 1251 )
        return 1;
    if( experience < 2501 )
        return 2;
    if( experience < 5001 )
        return 3;
    if( experience < 10001 )
        return 4;
    if( experience < 20001 )
        return 5;
    if( experience < 42501 )
        return 6;
    if( experience < 70001 )
        return 7;
    if( experience < 110001 )
        return 8;
    if( experience > 110000 )
        return 9;
};

int getMagicUserLevel( int experience )
{
    if( experience < 2501 )
        return 1;
    if( experience < 5001 )
        return 2;
    if( experience < 10001 )
        return 3;
    if( experience < 22501 )
        return 4;
    if( experience < 40001 )
        return 5;
    if( experience > 40000 )
        return 6;
};

int getFighterLevel( int experience )
{
    if( experience < 2001 )
        return 1;
    if( experience < 4001 )
        return 2;
    if( experience < 8001 )
        return 3;
    if( experience < 18001 )
        return 4;
    if( experience < 35001 )
        return 5;
    if( experience < 70001 )
        return 6;
    if( experience < 125001 )
        return 7;
    if( experience > 125000 )
        return 8;
};

int getClericLevel( int experience )
{
    if( experience < 1501 )
        return 1;
    if( experience < 3001 )
        return 2;
    if( experience < 6001 )
        return 3;
    if( experience < 13001 )
        return 4;
    if( experience < 27501 )
        return 5;
    if( experience > 27500 )
        return 6;
};
#endif
