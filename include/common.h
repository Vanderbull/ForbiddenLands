#ifndef COMMON_H
#define COMMON_H

#include <bits/stdc++.h>

#include "colors.h"
#include "coordinates.h"
#include "player_characters.h"
#include "savegame.h"

int randomEncounters = 0;

int two_d[15][15];

int healingPotion[6] = {1,1,1,1,1,1};
// Quest states
enum { PENDING,UNLOCKED,IN_PROGRESS,COMPLETED,DONE,CANCELED };

int mouse_counter = 0;

playerCharacters playerCharacter[6];

SDL_Rect volumeSlider = {0,750,50,50};

int removeIndex = 0;
int triggerRemove = 0;

unsigned char MusicVolume = 0;
int gHighTriggered = 0;
int disableSound = 0;

int spawn = 0;

std::string generated;

int LoadMenu = 0;
int SaveMenu = 0;
int CreateCharacter = 0;
int MenuCounter = 0;
int MenuCounterSwitch = 0;

std::vector<std::string> MenuChoices;

// VIEWS CONSTANTS
const int mainmenu = 2;
const int dungeon = 4;
const int wilderness = 5;
const int battle = 17;

int activeView = mainmenu;

int SettingsMenu = 0;

int looping = 0;

SDL_Rect encampButton;
SDL_Rect lookButton;
SDL_Rect backpackButton;
SDL_Rect itemsButton;
SDL_Rect spellsButton;
SDL_Rect tradeButton;
SDL_Rect dropButton;
SDL_Rect exitButton;
SDL_Rect readyButton;
SDL_Rect decreaseButton;

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

void renderBackground(std::string image)
{
    currentViewTexture = LoadTexture(image.c_str(),255);
    SDL_RenderCopy(renderer, currentViewTexture, NULL, NULL);
    SDL_DestroyTexture(currentViewTexture);
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

void renderCharacterViewItems()
{
    rowcounter = 0;
    int row = 0;

    rowcounter = 0;
    for(const auto& s: readyCharacterInventory[playerCharacterSelected])
    {
        SDL_Rect itemBox = {0,0,0,0};
        itemBox.h = 20;
        itemBox.w = 40;
        itemBox.x = 1500;
        itemBox.y = 200 + (20*rowcounter);
        if( SDL_PointInRect(&mousePosition, &itemBox) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            RenderText(s.c_str(),Green,itemBox.x,itemBox.y,fontSize);

            RenderText(playerCharacterInventory[playerCharacterSelected].at(rowcounter).c_str(),Green,current.w - 500,itemBox.y,fontSize);
            RenderText("AC: " + std::to_string(playerCharacter[playerCharacterSelected].readyCharacterInventoryAC.at(rowcounter)),Green,current.w - 500,itemBox.y + 25,fontSize);
            RenderText("THACO: " + std::to_string(playerCharacter[playerCharacterSelected].readyCharacterInventoryTHACO.at(rowcounter)),Green,current.w - 500,itemBox.y + 50,fontSize);
            RenderText("COST: " + std::to_string(playerCharacter[playerCharacterSelected].readyCharacterInventoryCost.at(rowcounter)),Green,current.w - 500,itemBox.y + 75,fontSize);
            RenderText("DAMAGE: " + std::to_string(playerCharacter[playerCharacterSelected].readyCharacterInventoryDamage.at(rowcounter)),Green,current.w - 500,itemBox.y + 100,fontSize);
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if( readyCharacterInventory[playerCharacterSelected].at(rowcounter) == "YES" )
                {
                    readyCharacterInventory[playerCharacterSelected].at(rowcounter) = "NO";
                    playerCharacter[playerCharacterSelected].readyCharacterInventoryAC.at(rowcounter) = 0;
                    playerCharacter[playerCharacterSelected].readyCharacterInventoryTHACO.at(rowcounter) = 0;
                }
                else
                {
                    readyCharacterInventory[playerCharacterSelected].at(rowcounter) = "YES";
                    playerCharacter[playerCharacterSelected].readyCharacterInventoryAC.at(rowcounter) = 1;
                    playerCharacter[playerCharacterSelected].readyCharacterInventoryTHACO.at(rowcounter) = 1;
                }
                SDL_Delay(75);
            }
        }
        rowcounter++;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    SDL_Rect exitButton = {current.w - 210, current.h - 40, 200, 30};
    SDL_RenderFillRect(renderer, &exitButton);
    RenderText("EXIT", Black, current.w - 200, current.h - 37,fontSize);

    if( SDL_PointInRect(&mousePosition, &exitButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            viewItems = !viewItems;
        }
    }
}

void renderShopCoins();

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

    RenderText("LVL " + std::to_string(playerCharacter[playerCharacterSelected].level_cleric) + " " + playerCharacter[playerCharacterSelected].getClass(),Blue, 512,70, 48);

    std::stringstream genderRaceAge;
    genderRaceAge << playerCharacter[playerCharacterSelected].getRace() << " " << playerCharacter[playerCharacterSelected].getGender();

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

    RenderText("DAMAGE VS SMALL "+std::to_string(playerCharacter[playerCharacterSelected].damage_vs_small),Green, 512,670, 24);
    RenderText("DAMAGE VS LARGE "+std::to_string(playerCharacter[playerCharacterSelected].damage_vs_large),Green, 512,720, 24);

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

void renderPCstatus()
{
    SDL_Texture* Texture = NULL;
    SDL_Rect Button[6];
    std::string pc[6];
    int offset_x = current.w / 2;
    int offset_x_border = current.w / 2 - 5;
    int offset_x_pc = current.w / 2 - 10;

    Button[0] = {current.w - offset_x_pc, current.h - 140, 200 ,20};
    Button[1] = {current.w - offset_x_pc, current.h - 120, 200 ,20};
    Button[2] = {current.w - offset_x_pc, current.h - 100, 200, 20};
    Button[3] = {current.w - offset_x_pc, current.h - 80, 200, 20};
    Button[4] = {current.w - offset_x_pc, current.h - 60, 200, 20};
    Button[5] = {current.w - offset_x_pc, current.h - 40, 200, 20};

    std::string pcTitles = pad_right("NAME",20) + pad_right("AC",8)+"HP";
    pc[0] = pad_right(playerCharacter[0].getName(),20) + pad_right(std::to_string(playerCharacter[0].getArmourClass()),8) + std::to_string(playerCharacter[0].getHitpoints()) + "/" + std::to_string(playerCharacter[0].hitpoints_max);
    pc[1] = pad_right(playerCharacter[1].getName(),20) + pad_right(std::to_string(playerCharacter[1].getArmourClass()),8) + std::to_string(playerCharacter[1].getHitpoints()) + "/" + std::to_string(playerCharacter[1].hitpoints_max);
    pc[2] = pad_right(playerCharacter[2].getName(),20) + pad_right(std::to_string(playerCharacter[2].getArmourClass()),8) + std::to_string(playerCharacter[2].getHitpoints()) + "/" + std::to_string(playerCharacter[2].hitpoints_max);
    pc[3] = pad_right(playerCharacter[3].getName(),20) + pad_right(std::to_string(playerCharacter[3].getArmourClass()),8) + std::to_string(playerCharacter[3].getHitpoints()) + "/" + std::to_string(playerCharacter[3].hitpoints_max);
    pc[4] = pad_right(playerCharacter[4].getName(),20) + pad_right(std::to_string(playerCharacter[4].getArmourClass()),8) + std::to_string(playerCharacter[4].getHitpoints()) + "/" + std::to_string(playerCharacter[4].hitpoints_max);
    pc[5] = pad_right(playerCharacter[5].getName(),20) + pad_right(std::to_string(playerCharacter[5].getArmourClass()),8) + std::to_string(playerCharacter[5].getHitpoints()) + "/" + std::to_string(playerCharacter[5].hitpoints_max);

    encampButton = {current.w - 168*2, 0,160,160};
    lookButton = {current.w - 168, 0,160,160};
    backpackButton = {current.w - 168*3, 0,160,160};
    SDL_Rect cogButton = {current.w - 168*4, 0,160,160};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 192);
    SDL_RenderFillRect(renderer, &encampButton);

    Texture = LoadTexture("./icons/uiAtlas/smxlib_ui_game_element_panel_background_dense.png",255);
    SDL_RenderCopy(renderer, Texture, NULL, &encampButton);
    SDL_DestroyTexture(Texture);

    Texture = LoadTexture("./icons/uiAtlas/ui_game_symbol_campfire.png",255);
    SDL_RenderCopy(renderer, Texture, NULL, &encampButton);
    SDL_DestroyTexture(Texture);

    RenderText("ENCAMP", Black, encampButton.x, encampButton.y,20);

    if( SDL_PointInRect(&mousePosition, &encampButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 192);
    SDL_RenderFillRect(renderer, &lookButton);

    Texture = LoadTexture("./icons/uiAtlas/smxlib_ui_game_element_panel_background_dense.png",255);
    SDL_RenderCopy(renderer, Texture, NULL, &lookButton);
    SDL_DestroyTexture(Texture);

    Texture = LoadTexture("./icons/uiAtlas/ui_game_symbol_character.png",255);
    SDL_RenderCopy(renderer, Texture, NULL, &lookButton);
    SDL_DestroyTexture(Texture);

    RenderText("CHARACTER", Black, lookButton.x, lookButton.y,20);
    if( SDL_PointInRect(&mousePosition, &lookButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
    }

    if( SDL_PointInRect(&mousePosition, &lookButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            playerCharacterSelected2 = 0;
            viewingCharacter = 1;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 192);
    SDL_RenderFillRect(renderer, &backpackButton);

    Texture = LoadTexture("./icons/uiAtlas/smxlib_ui_game_element_panel_background_dense.png",255);
    SDL_RenderCopy(renderer, Texture, NULL, &backpackButton);
    SDL_DestroyTexture(Texture);

    Texture = LoadTexture("./icons/uiAtlas/ui_game_symbol_fetch_loot.png",255);
    SDL_RenderCopy(renderer, Texture, NULL, &backpackButton);
    SDL_DestroyTexture(Texture);

    RenderText("INVENTORY", Black, backpackButton.x, backpackButton.y,20);

    if( SDL_PointInRect(&mousePosition, &backpackButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
    }

    if( SDL_PointInRect(&mousePosition, &backpackButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            playerCharacterSelected2 = 0;
            viewingCharacter = 1;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 192);
    SDL_RenderFillRect(renderer, &cogButton);

    Texture = LoadTexture("./icons/uiAtlas/smxlib_ui_game_element_panel_background_dense.png",255);
    SDL_RenderCopy(renderer, Texture, NULL, &cogButton);
    SDL_DestroyTexture(Texture);

    Texture = LoadTexture("./icons/uiAtlas/ui_game_symbol_modded.png",255);
    SDL_RenderCopy(renderer, Texture, NULL, &cogButton);
    SDL_DestroyTexture(Texture);

    RenderText("SETTINGS", Black, cogButton.x, cogButton.y,20);

    if( SDL_PointInRect(&mousePosition, &cogButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
    }

    if( SDL_PointInRect(&mousePosition, &cogButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            //playerCharacterSelected2 = 0;
            //viewingCharacter = 1;
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
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame << playerCharacter[i].getClericLevel() << std::endl;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame << playerCharacter[i].getEncumbrance() << std::endl;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame << playerCharacter[i].getExperience() << std::endl;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame << playerCharacter[i].getFighterLevel() << std::endl;
    }
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
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame >> playerCharacter[i].level_cleric;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame >> playerCharacter[i].encumbrance;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame >> playerCharacter[i].experience;
    }
    for( int i = 0; i < sizeof(playerCharacter)/sizeof(playerCharacter[0]); i++ )
    {
        SaveGame >> playerCharacter[i].level_fighter;
    }

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

void renderShopScrollbars()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &leftScrollButtonUp);
    SDL_RenderFillRect(renderer, &leftScrollButtonDown);
    SDL_RenderFillRect(renderer, &rightScrollButtonUp);
    SDL_RenderFillRect(renderer, &rightScrollButtonDown);

    RenderText(std::to_string(offsetPlayerCharacterList),Black,rightScrollButtonUp.x,rightScrollButtonUp.y,FontSize);
    RenderText(std::to_string(offsetPlayerCharacterList + showEntries),Black,rightScrollButtonDown.x,rightScrollButtonDown.y,FontSize);

    RenderText(std::to_string(scrollOffsetShop),Black,leftScrollButtonUp.x,leftScrollButtonUp.y,FontSize);
    RenderText(std::to_string(scrollOffsetShop + showEntriesInShop),Black,leftScrollButtonDown.x,leftScrollButtonDown.y,FontSize);
}

void renderShopCoins()
{
    SDL_Rect poolBackground = {current.w / 4,0,1000,50};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer,&poolBackground);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &poolBackground);

    RenderText("Copper: " + std::to_string(playerCharacter[playerCharacterSelected].coins_copper),Black,poolBackground.x,poolBackground.y + 10,FontSize);
    RenderText("Electrum: " + std::to_string(playerCharacter[playerCharacterSelected].coins_electrum),Black,poolBackground.x + 200,poolBackground.y + 10,FontSize);
    RenderText("Gold: " + std::to_string(playerCharacter[playerCharacterSelected].coins_gold),Black,poolBackground.x + 400,poolBackground.y + 10,FontSize);
    RenderText("Platinum: " + std::to_string(playerCharacter[playerCharacterSelected].coins_platinum),Black,poolBackground.x + 600,poolBackground.y + 10,FontSize);
    RenderText("Silver: " + std::to_string(playerCharacter[playerCharacterSelected].coins_silver),Black,poolBackground.x + 800,poolBackground.y + 10,FontSize);
};

int currentCharacter = 0;
int statPoints[6] = {5,5,5,5,5,5};

void renderCharacterCreation()
{
    int localCounter = 0;
    SDL_Rect TextFrame = {0, 0, 0, 0};
    SDL_Rect TextFrame2 = {0, 0, 0, 0};
    std::vector<std::string> textElements = { "STR ", "INT ", "WIS ", "DEX ", "CON ", "CHA "};
    std::vector<SDL_Rect> raceElements;
    std::vector<std::string> raceTextElements = { "DWARF", "ELF", "GNOME", "HALFELF", "HALFLING", "HALFORC", "HUMAN"};
    std::vector<SDL_Rect> classElements;
    std::vector<std::string> classTextElements = { "ASSASSIN", "CLERIC", "DRUID", "FIGHTER", "ILLUSIONIST", "PALADIN", "RANGER", "THIEF", "MAGIC USER"};
    SDL_Rect Gender[2];

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    playerCharacter[currentCharacter].renderFace();

    renderShopCoins();
    RenderText(std::to_string(statPoints[currentCharacter]) + " Stat Points Left",White, 150,100, 24);
    counter = 0;

    for (std::string textElement : textElements)
    {
        RenderText(textElement.c_str()+std::to_string(playerCharacter[currentCharacter].current_stats[counter]),Green, 150,370+(counter*50), 24);

        TextFrame = FrameText("+",300, 370+(counter*50), 24);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &TextFrame);
        RenderText("+",White, 300,370+(counter*50), 24);

        TextFrame2 = FrameText("-",340, 370+(counter*50), 24);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &TextFrame2);
        RenderText("-",White, 340,370+(counter*50), 24);

        if( statPoints[currentCharacter] >= 0 )
        {
            if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
            {
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    if( statPoints[currentCharacter] > 0)
                    {
                        playerCharacter[currentCharacter].current_stats[counter]++;
                        statPoints[currentCharacter]--;
                        SDL_Delay(50);
                    }
                }
            }
            else
            if( SDL_PointInRect(&mousePosition, &TextFrame2) & SDL_BUTTON(SDL_BUTTON_LEFT) )
            {
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    if( playerCharacter[currentCharacter].current_stats[counter] > 3)
                    {
                        playerCharacter[currentCharacter].current_stats[counter]--;
                        statPoints[currentCharacter]++;
                        SDL_Delay(50);
                    }
                }
            }
        }
        counter++;
    }

    if( currentCharacter > 5 )
        currentCharacter = 0;

    RenderText("Number: " + std::to_string(currentCharacter),White,800,100,FontSize);
    int HorizontalPosition = current.w - 400;

    counter = 0;

    for (std::string textElement : raceTextElements)
    {
        SDL_Rect rect;
        rect.x = 400;
        rect.y = 220+(counter*40);
        rect.w = 300;
        rect.h = 30;
        raceElements.push_back(rect);
        counter++;
    }

    counter = 0;
    for (std::string textElement : classTextElements)
    {
        SDL_Rect rect;
        rect.x = 720;
        rect.y = 220+(counter*40);
        rect.w = 300;
        rect.h = 30;
        classElements.push_back(rect);
        counter++;
    }

    counter = 0;
    for (std::string textElement : classTextElements)
    {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderFillRect(renderer, &classElements[counter]);
        RenderText(textElement.c_str()+std::to_string(playerCharacter[currentCharacter].characterClass),Black,classElements[counter].x,classElements[counter].y,FontSize);

        if( SDL_PointInRect(&mousePosition, &classElements[counter]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &classElements[counter]);
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacter[currentCharacter].characterClass = counter;
            }
        }
        counter++;
    }

    Gender[0] = {current.w / 2,220,600,30};
    Gender[1] = {current.w / 2,260,600,30};

    SDL_Rect nextCharacter = {current.w / 2,300,600,30};
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &nextCharacter);
    RenderText("NEXT CHARACTER",Black,current.w / 2,300,FontSize);

    counter = 0;
    for (std::string textElement : raceTextElements)
    {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderFillRect(renderer, &raceElements[counter]);
        RenderText(textElement.c_str()+std::to_string(playerCharacter[currentCharacter].race),Black,raceElements[counter].x,raceElements[counter].y,FontSize);
        counter++;
    }

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &Gender[0]);
    RenderText("MALE",Black,current.w / 2,Gender[0].y,FontSize);

    SDL_RenderFillRect(renderer, &Gender[1]);
    RenderText("FEMALE",Black,current.w / 2,Gender[1].y,FontSize);

    if( SDL_PointInRect(&mousePosition, &nextCharacter) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            currentCharacter++;
            if( currentCharacter > 5)
            {
                LoadMenu = 0;
                SaveMenu = 0;
            }
            SDL_Delay(100);
        }
    }

    for( int i = 0; i < 9; i++ )
    {
        if( playerCharacter[currentCharacter].characterClass == i )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &classElements[i]);
        }
    }
    for( int i = 0; i < 7; i++ )
    {
        if( playerCharacter[currentCharacter].race == i )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &raceElements[i]);

            if( playerCharacter[currentCharacter].race == 0)
            {
            std::string dwarfs;
             dwarfs = "Dwarfs\n" \
             "Dwarfs are a short and burly race, living in mountain fastnesses"\
             "underground. They are loyal friends and fierce adversaries,"\
             "known for their steadfastness in all things."\
             "\n"\
             "The dwarfs are inherently resistant to many spells and spell-like"\
             "effects. Dwarfish characters gain bonuses against the use of"\
             "most magic, including all spells, wands, rods, and staves. The"\
             "amount of the bonus depends upon the dwarf’s constitution:"\
             "every 3.5 points of constitution (rounding down fractions)"\
             "grants a bonus of +1 against such magic. Moreover, the hardy"\
             "dwarfish nature imparts a similar bonus on any saving throws"\
             "against poison.Dwarfs are not a numerous folk, but they are adventurous,"\
             "loving the lustre of gold, the glitter of gems, and the quality"\
             "of well-wrought metals. Dwarfs can live to an age of 350 years"\
             "or more.";
             RenderText3(dwarfs.c_str(),White, 500,900, 24);

                 std::string stats = "Strength 8/18\n"\
                                    "Dexterity 3/17\n"\
                                    "Constitution 12/19\n"\
                                    "Intelligence 3/18\n"\
                                    "Wisdom 3/18\n"\
                                    "Charisma 3/16";
                RenderText3(stats.c_str(),White, current.w - 1000,900, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 1)
            {
            std::string dwarfs;
             dwarfs = "Elves\n"\
"Elves are thinner and generally smaller in stature than humans."\
"The elves have a powerful bond with nature and do not have"\
"souls; their thinking and motives are quite alien to those of"\
"humankind, and in any dealings with elves, it is perilous to"\
"forget this."\
"Some elven clans have built elaborate civilisations, remote and"\
"beautiful places of profound learning, master craftsmanship, and"\
"long history. Such elves tend to be chaotic good in alignment and"\
"friendly, if aloof, from humans. More numerous are the wilder"\
"friendly to other races, inclining even toward hostility."\
"Intruding into the territory of such elves is inadvisable, for their"\
"sense of humour with regard to humans is, at best, arbitrary"\
"and, at worst, cruel. Different as they are, these varied elven cul-"\
"tures all share the same racial abilities, unless the GM chooses"\
"otherwise. Elves can live to an age of 1,000 years or more.";
             RenderText3(dwarfs.c_str(),White, 500,900, 24);
                 std::string stats = "Strength 8/18\n"\
                                    "Dexterity 3/17\n"\
                                    "Constitution 12/19\n"\
                                    "Intelligence 3/18\n"\
                                    "Wisdom 3/18\n"\
                                    "Charisma 3/16";
                RenderText3(stats.c_str(),White, current.w - 1000,900, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 2)
            {
            std::string dwarfs;
             dwarfs = "GnOmeS\n"\
"Gnomes are small folk imbued with the wilding power of il-"\
"lusion and misdirection. They are inveterate burrowers, often"\
"seeking hilly lands where gems and precious metals may be"\
"found. On average, they are shorter and slimmer of build than"\
"dwarfs, with larger noses and longer beards."\
"Like dwarfs, who are perhaps related to gnomes from some"\
"time in the distant and mythical past, gnomes are quite re-"\
"sistant to magic and sensitive to the nuances of construction."\
"Gnomes can live to an age of 650 years or more.";
             RenderText3(dwarfs.c_str(),White, 500,900, 24);
                 std::string stats = "Strength 8/18\n"\
                                    "Dexterity 3/17\n"\
                                    "Constitution 12/19\n"\
                                    "Intelligence 3/18\n"\
                                    "Wisdom 3/18\n"\
                                    "Charisma 3/16";
                RenderText3(stats.c_str(),White, current.w - 1000,900, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 3)
            {
            std::string dwarfs;
             dwarfs = "Halflings\n"\
"Halﬂings are a small and unprepossessing race, often living"\
"near human settlements at an agreeable remove from the bus-"\
"tle and hurriedness characteristic of humans. Halﬂ ing society"\
"is comfortable and staid, rooted in polite, placid, well-fed life."\
"Halﬂ ing adventurers are thought aberrant, even lunatic, but"\
"also dashing and heroic fi gures, a charming and amusing con-"\
"tradiction of logic."\
"Halﬂ ings value learning and craftsmanship, as long as nothing"\
"is taken to an embarrassing extreme. They are capable of mov-"\
"ing very quietly and are excellent marksmen; given the right"\
"personality, halﬂ ings can become excellent thieves. Halﬂ ings"\
"live to be 150 or more years old.";
             RenderText3(dwarfs.c_str(),White, 500,900, 24);
                 std::string stats = "Strength 8/18\n"\
                                    "Dexterity 3/17\n"\
                                    "Constitution 12/19\n"\
                                    "Intelligence 3/18\n"\
                                    "Wisdom 3/18\n"\
                                    "Charisma 3/16";
                RenderText3(stats.c_str(),White, current.w - 1000,900, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 4)
            {
            std::string dwarfs;
             dwarfs = "half elVeS\n"\
"It is possible for elves and humans to interbreed, although el-"\
"ven fastidiousness makes this a fairly uncommon occurrence."\
"Half elves do not have a separate culture or civilisation of their"\
"own, usually assimilating into the elven or human society in"\
"which they were raised.";
             RenderText3(dwarfs.c_str(),White, 500,900, 24);
                 std::string stats = "Strength 8/18\n"\
                                    "Dexterity 3/17\n"\
                                    "Constitution 12/19\n"\
                                    "Intelligence 3/18\n"\
                                    "Wisdom 3/18\n"\
                                    "Charisma 3/16";
                RenderText3(stats.c_str(),White, current.w - 1000,900, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 5)
            {
            std::string dwarfs;
             dwarfs = "half-ORcS\n"\
"The progeny of human/orc breeding are normally indistin-"\
"guishable from orcs. However, a few are suffi ciently human"\
"to gain levels in a character class, although they are severely"\
"limited in classes that do not focus upon violence and death."\
"Orcish blood runs strong in these half-breeds, and most of"\
"them are shifty, morally questionable, and unsophisticated."\
"They are typically ugly, carrying the mark of orcish ancestry,"\
"but the same ancestry makes them deadly adversaries when"\
"the chips are down and the swords are out. Half-orcs can live"\
"to be 70 years old or older.";
             RenderText3(dwarfs.c_str(),White, 500,900, 24);
                 std::string stats = "Strength 8/18\n"\
                                    "Dexterity 3/17\n"\
                                    "Constitution 12/19\n"\
                                    "Intelligence 3/18\n"\
                                    "Wisdom 3/18\n"\
                                    "Charisma 3/16";
                RenderText3(stats.c_str(),White, current.w - 1000,900, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 6)
            {
            std::string dwarfs;
             dwarfs = "hUmanS\n"\
"Humans are the standard for the game, and as such, humans"\
"have no unusual abilities or limitations in game terms. Because"\
"of their potential for unlimited progression in all the character"\
"classes save assassin and druid, humans are a popular choice"\
"for most players. This is an intentional feature of the rules."\
"A common house rule in OSRIC-compatible games is the"\
"adjustment or removal of demi-human level limits. This will"\
"unbalance the game in favour of demi-humans unless humans"\
"are given some corresponding advantage. GMs considering"\
"such a house rule for their own OSRIC-compatible games are"\
"advised to ensure that in most campaigns, humans should still"\
"represent an attractive choice for their players.";
             RenderText3(dwarfs.c_str(),White, 500,900, 24);
                 std::string stats = "Strength 8/18\n"\
                                    "Dexterity 3/17\n"\
                                    "Constitution 12/19\n"\
                                    "Intelligence 3/18\n"\
                                    "Wisdom 3/18\n"\
                                    "Charisma 3/16";
                RenderText3(stats.c_str(),White, current.w - 1000,900, 24);
            }
        }
        if( SDL_PointInRect(&mousePosition, &raceElements[i]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &raceElements[i]);
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacter[currentCharacter].race = i;
            }
        }
    }

    if( playerCharacter[currentCharacter].gender == 1 )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(renderer, &Gender[0]);
    }
    if( playerCharacter[currentCharacter].gender == 2 )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(renderer, &Gender[1]);
    }

    if( SDL_PointInRect(&mousePosition, &Gender[0]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(renderer, &Gender[0]);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            playerCharacter[currentCharacter].gender = 1;
        }
    }
    if( SDL_PointInRect(&mousePosition, &Gender[1]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
        SDL_RenderFillRect(renderer, &Gender[1]);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            playerCharacter[currentCharacter].gender = 2;
        }
    }

    SDL_Rect ExitButton = {current.w - 220,current.h - 50,200,30};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ExitButton);

    if( SDL_PointInRect(&mousePosition, &ExitButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &ExitButton);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            LoadMenu = 0;
            SaveMenu = 0;
            CreateCharacter = 0;
            SettingsMenu = 0;
        }
    }
    RenderText("EXIT",Black,ExitButton.x + 10,ExitButton.y + 5,FontSize);
};

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
