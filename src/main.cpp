#include <cassert>
#include <ctime>
#include <iostream>
#include <string>
#include <list>
#include <array>
#include <stack>
#include <deque>
#include <queue>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <sys/utsname.h>
#include <experimental/filesystem>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>  /* defines FILENAME_MAX */
#include <random>
#include <sqlite3.h>
#include "../rapidxml-1.13/rapidxml.hpp"

using namespace std;
using namespace rapidxml;

xml_document<> doc;
xml_node<> * root_node = NULL;

struct utsname uts;

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>
#include "../version.h"

#include "../include/resource.h"
#include "../include/world_view.h"
#include "../include/battle_view.h"

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

namespace fs = std::experimental::filesystem;

uintmax_t ComputeFileSize(const fs::path& pathToCheck)
{
    if (fs::exists(pathToCheck) &&
        fs::is_regular_file(pathToCheck))
    {
        auto err = std::error_code{};
        auto filesize = fs::file_size(pathToCheck, err);
        if (filesize != static_cast<uintmax_t>(-1))
            return filesize;
    }

    return static_cast<uintmax_t>(-1);
}

void DisplayPathInfo(const fs::path& pathToShow)
{
	int i = 0;
	std::cout << "Displaying path info for: " << pathToShow << "\n";
	for (const auto& part : pathToShow)
	{
		std::cout << "path part: " << i++ << " = " << part << "\n";
	}

	std::cout << "exists() = " << fs::exists(pathToShow) << "\n"
		<< "root_name() = " << pathToShow.root_name() << "\n"
		<< "root_path() = " << pathToShow.root_path() << "\n"
		<< "relative_path() = " << pathToShow.relative_path() << "\n"
		<< "parent_path() = " << pathToShow.parent_path() << "\n"
		<< "filename() = " << pathToShow.filename() << "\n"
		<< "stem() = " << pathToShow.stem() << "\n"
		<< "extension() = " << pathToShow.extension() << "\n";

	try
	{
		std::cout << "canonical() = " << fs::canonical(pathToShow) << "\n";
	}
	catch (fs::filesystem_error err)
	{
		std::cout << "exception: " << err.what() << "\n";
	}
}

void DisplayFileInfo(const std::experimental::filesystem::v1::directory_entry & entry, std::string &lead, std::experimental::filesystem::v1::path &filename)
{
	time_t cftime = std::chrono::system_clock::to_time_t(fs::last_write_time(entry));
	std::cout << lead << " " << filename << ", "
		 << ComputeFileSize(entry)
		 << ", time: " << std::asctime(std::localtime(&cftime));
}

void DisplayDirTree(const fs::path& pathToShow, int level)
{
    if (fs::exists(pathToShow) && fs::is_directory(pathToShow))
    {
        auto lead = std::string(level * 3, ' ');
        for (const auto& entry : fs::directory_iterator(pathToShow))
        {
            auto filename = entry.path().filename();
            if (fs::is_directory(entry.status()))
            {
                std::cout << lead << "[+] " << filename << "\n";
                DisplayDirTree(entry, level + 1);
                std::cout << "\n";
            }
            else if (fs::is_regular_file(entry.status()))
                DisplayFileInfo(entry, lead, filename);
            else
                std::cout << lead << " [?]" << filename << "\n";
        }
    }
}

std::string return_current_time_and_date()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

void initFileSystem()
{
    return;
    std::string currentDate;
    currentDate = return_current_time_and_date();

    fs::path cwd = fs::current_path();
    cwd += "/output_log_ ";
    cwd += currentDate.c_str();
    std::ofstream file(cwd.string());

    fs::path pathToShow(".");
    file << "exists() = " << fs::exists(pathToShow) << "\n"
     << "root_name() = " << pathToShow.root_name() << "\n"
     << "root_path() = " << pathToShow.root_path() << "\n"
     << "relative_path() = " << pathToShow.relative_path() << "\n"
     << "parent_path() = " << pathToShow.parent_path() << "\n"
     << "filename() = " << pathToShow.filename() << "\n"
     << "stem() = " << pathToShow.stem() << "\n"
     << "extension() = " << pathToShow.extension() << "\n";

    int i = 0;
    for (const auto& part : pathToShow)
        file << "path part: " << i++ << " = " << part << "\n";

    auto timeEntry = fs::last_write_time(cwd);
    time_t cftime = std::chrono::system_clock::to_time_t(timeEntry);

    file << std::asctime(std::localtime(&cftime));

    file.close();
}

typedef std::vector<std::string> stringvec;

extern char *text;
extern char *composition;
extern Sint32 cursor;
extern Sint32 selection_len;

void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}

Fps fps;

unsigned int randomSeed = 0;

int Generate(const int from, const int to);

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++)
   {
       mainLog.push_back(argv[i]);
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char ** argv)
{
   cout << "\nParsing my students data (sample.xml)....." << endl;

    // Read the sample.xml file
    ifstream theFile ("sample.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse the buffer
    doc.parse<0>(&buffer[0]);

    // Find out the root node
    root_node = doc.first_node("MyStudentsData");

    // Iterate over the student nodes
    for (xml_node<> * student_node = root_node->first_node("Student"); student_node; student_node = student_node->next_sibling())
    {
        cout << "\nStudent Type =   " << student_node->first_attribute("student_type")->value();
        cout << endl;

            // Interate over the Student Names
        for(xml_node<> * student_name_node = student_node->first_node("Name"); student_name_node; student_name_node = student_name_node->next_sibling())
        {
            cout << "Student Name =   " << student_name_node->value();
            cout << endl;
        }
        cout << endl;
    }

    const char* data = "Callback function called";
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3* db;
    int res = sqlite3_open("databaseName.db", &db);
    if(res)
        //database failed to open
        cout << "Database failed to open" << endl;
    else
    {
       /* Create SQL statement */
       sql = "CREATE TABLE COMPANY("  \
          "ID INT PRIMARY KEY     NOT NULL," \
          "NAME           TEXT    NOT NULL," \
          "AGE            INT     NOT NULL," \
          "ADDRESS        CHAR(50)," \
          "SALARY         REAL );";

       /* Execute SQL statement */
       rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

       if( rc != SQLITE_OK ){
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
       } else {
          fprintf(stdout, "Table created successfully\n");
       }
        //your database code here
    }

   /* Create SQL statement */
   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
   /* Create SQL statement */
   sql = "SELECT * from COMPANY";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
    sqlite3_close(db);

    ///////////////////////////////

    srand (time(NULL));
    SDL_SetMainReady();

    std::ofstream soundBibleFile;
    soundBibleFile.open ("soundbible.org");

    std::vector<std::string> soundbibleFiles;
    std::vector<std::string> fontFiles;
    std::vector<std::string> imagesFiles;
    std::vector<std::string> dataFiles;
    std::vector<std::string> logsFiles;

    read_directory("./soundbible", soundbibleFiles);
    read_directory("./font", fontFiles);
    read_directory("./images", imagesFiles);
    read_directory("./data", dataFiles);
    read_directory("./logs", logsFiles);

    std::copy(soundbibleFiles.begin(), soundbibleFiles.end(),
         std::ostream_iterator<std::string>(soundBibleFile, "\n"));

    soundBibleFile.close();

    pFile = fopen ("./logs/GameEngineLOG.log","w");
    SDL_LogSetOutputFunction(&LogSDL, NULL);
    SDL_Log("./logs/GameEngineLOG.txt file opened: Success");

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

    int fw,fh;

    // Get current display mode of all displays.
    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
    {
        int should_be_zero = SDL_GetCurrentDisplayMode(i, &monitor[i]);

        current = monitor[0];

        if(should_be_zero != 0)
        {
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
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
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    if (window == NULL)
    {
        SDL_Log("Could not create window: %s", SDL_GetError());
        return 1;
    }
    else
    {
        SDL_Log("SDL Window creation: SUCCESS");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        renderer2 = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

        //SDL_GLContext glcontext = SDL_GL_CreateContext(window);

        // Once finished with OpenGL functions, the SDL_GLContext can be deleted.
        //SDL_GL_DeleteContext(glcontext);

        SDL_Log("SDL Renderer creation: SUCCESS");

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderSetScale(renderer,1.0,1.0);
        IMG_Init(IMG_INIT_PNG);

        if( strcmp(uts.machine, "x86_64") == 0 )
            gSurface = IMG_Load( "./icons/64-bit-100.png" );
        else
            gSurface = IMG_Load( "./icons/64-bit-100-filled.png" );

        if(!gSurface)
        {
            SDL_Log("Setting Window Icon: %s\n", IMG_GetError());
            return -1;
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
            return -1;
        }
        else
        {
            SDL_Log("Audio successfully initiated...");
        }
    }

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        SDL_Log("GetCurrentDirectory failed: %s", errno);
        return errno;
    }
    else
    {
        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
        SDL_Log("The current working directory is %s", cCurrentPath);
    }

    countFiles("./data");

    initFileSystem();

    initGame();

    initQuests();

    init_portals("./data/maps/phlan/phlan_portals");
    init_portals("./data/maps/slums/slums_portals");
    init_portals("./data/maps/khutos_well/khutos_well_portals");
    init_portals("./data/maps/podal_plaza/podal_plaza_portals");
    init_portals("./data/maps/cardona_textile_house/cardona_textile_house_portals");
    init_portals("./data/maps/kovel_mansion/kovel_mansion_portals");
    init_portals("./data/maps/mendors_library/mendors_library_portals");
    init_portals("./data/maps/sokol_keep/sokol_keep_portals");
    init_portals("./data/maps/stojanov_gate/stojanov_gate_portals");
    init_portals("./data/maps/vahlingen_graveyard/vahlingen_graveyard_portals");
    init_portals("./data/maps/valjevo_castle/valjevo_castle_portals");
    init_portals("./data/maps/wealthy_area/wealthy_area_portals");

    loadPortals();

    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

    initShop();
    generateSmithShopItems();

    while (!quit)
    {
        for( int i=0; i < 6; i++ )
        {
            playerCharacter[i].update();
        }

        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                {
                    SDL_GetMouseState( &mousePosition.x, &mousePosition.y );
                } break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_y:
                        {
                            if( armsAndarmourShop || trainingHall || tavern )
                            {
                                shop = 1;
                            }
                            if( generalShop || jewelleryShop || silverShop )
                            {
                                shop = 1;
                            }
                            if( templeShop )
                            {
                                shop = 1;
                                cureCriticalWounds();
                                cureSeriousWounds();
                                cureLightWounds();
                            };
                        } break;
                        case SDLK_ESCAPE:
                        {
                            if(activeView == mainmenu)
                            {
                                if( SettingsMenu )                                {
                                    SettingsMenu = 0;
                                }
                                else if( SaveMenu )
                                {
                                    SaveMenu = 0;
                                }
                                else if( LoadMenu )
                                {
                                    LoadMenu = 0;
                                }
                                else if( CreateCharacter )
                                {
                                    CreateCharacter = 0;
                                }
                                else
                                {
                                    quit = 1;
                                }
                            }
                            else if(activeView == dungeon)
                            {
                                activeView = mainmenu;
                            }
                        } break;
                    } break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_RIGHT:
                        default:
                        {
                            m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);
                        } break;
                    } break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_F12:
                        {
                            std::cout<<"Fps: "<<fps.get()<<'\n';
                        } break;
                        case SDLK_PLUS:
                        {
                            MusicVolume = Mix_VolumeMusic(Mix_VolumeMusic(-1)+1 );
                        } break;
                        case SDLK_MINUS:
                        {
                            MusicVolume = Mix_VolumeMusic(Mix_VolumeMusic(-1)+1);
                        } break;
                        case SDLK_LEFT:
                        case SDLK_q:
                        {
                            if( activeView == dungeon )
                            {
                                rotateCounterClockWise();
                                getCompassDirection();

                                LastPlayerCoordinate.x = PlayerCoordinate.x;
                                LastPlayerCoordinate.y = PlayerCoordinate.y;
                            }
                        } break;
                        case SDLK_RIGHT:
                        case SDLK_e:
                        {
                            if( activeView == dungeon )
                            {
                                rotateClockWise();
                                getCompassDirection();

                                LastPlayerCoordinate.x = PlayerCoordinate.x;
                                LastPlayerCoordinate.y = PlayerCoordinate.y;
                            }
                        } break;
                        case SDLK_UP:
                        case SDLK_w:
                            inGameTime++;
                            if( activeView == dungeon )
                            {
                                // We are in dungeonMode
                                switch( worldMap )
                                {
                                case 0: // PHLAN
                                    {
                                        if( phlan_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
                                        {
                                            if( Rotation  == "N" )
                                                PlayerCoordinate.y--;
                                            else
                                            if( Rotation  == "S" )
                                                PlayerCoordinate.y++;
                                            else
                                            if( Rotation  == "E" )
                                                PlayerCoordinate.x++;
                                            else
                                            if( Rotation  == "W" )
                                                PlayerCoordinate.x--;
                                        }
                                    } break;
                                case 1: // SLUMS
                                    {
                                        if( slum_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
                                        {
                                            if( Rotation  == "N" )
                                                PlayerCoordinate.y--;
                                            else
                                            if( Rotation  == "S" )
                                                PlayerCoordinate.y++;
                                            else
                                            if( Rotation  == "E" )
                                                PlayerCoordinate.x++;
                                            else
                                            if( Rotation  == "W" )
                                                PlayerCoordinate.x--;
                                        }
                                    } break;
                                case 2: // KHUTOS WELL
                                    {
                                        if( khutos_well_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
                                        {
                                            if( Rotation  == "N" )
                                                PlayerCoordinate.y--;
                                            else
                                            if( Rotation  == "S" )
                                                PlayerCoordinate.y++;
                                            else
                                            if( Rotation  == "E" )
                                                PlayerCoordinate.x++;
                                            else
                                            if( Rotation  == "W" )
                                                PlayerCoordinate.x--;
                                        }
                                    } break;
                                case 3: // PODAL_PLAZA
                                    {
                                        if( podal_plaza_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
                                        {
                                            if( Rotation  == "N" )
                                                PlayerCoordinate.y--;
                                            else
                                            if( Rotation  == "S" )
                                                PlayerCoordinate.y++;
                                            else
                                            if( Rotation  == "E" )
                                                PlayerCoordinate.x++;
                                            else
                                            if( Rotation  == "W" )
                                                PlayerCoordinate.x--;
                                        }
                                    } break;
                                }
                                LastPlayerCoordinate.y = PlayerCoordinate.y;
                                LastPlayerCoordinate.x = PlayerCoordinate.x;
                            }
                            break;
                    } break;
            }
        }

        m_uPreviousMouseState=m_uCurrentMouseState;

        if( activeView == battle )
        {
            battleView();
        }
        else if( activeView == mainmenu )
        {
            MainMenu();
        }
        else if(activeView == wilderness)
        {
            renderWorldViewB();
        }
        else if(activeView == dungeon)
        {
            renderWorldViewA();

            // Clean up this part and make a nice graphics for the TimeOfDay cycle
            if( getTimeOfDay() == "Night time")
            {
                //RenderText("SHOPS ARE CLOSED DURING THE NIGHT",Green,0,0,40);
                shop = 0;
            }
            if(shop)
            {
                if(templeShop)
                {
                    renderTemple();
                }
                else if(trainingHall)
                {
                    renderTrainer();
                }
                else if(armsAndarmourShop)
                {
                    renderSmithShop();
                }
                else if(jewelleryShop)
                {
                    renderJewelleryShop();
                }
                else if(generalShop)
                {
                    renderGeneralShop();
                }
                else if(silverShop)
                {
                    renderSilverShop();
                }
                else if(tavern)
                {
                    renderTavern();
                }
            }
        } // end dungeonView

        if(!mainmenu)
        {
            navigationButtons();
        }

        if( loadingScreen == 1 )
        {
            LoadingScreen();
        };


        // What is this doing here??
        IMG_Quit();
        fps.update();
        if( loadingScreen != 1)
        {
            SDL_Delay(fps.get());
            bestiaryFile.close();
        }

        renderDescription(PlayerCoordinate.x, PlayerCoordinate.y);

        SDL_RenderPresent(renderer);
    }
    bestiaryFile.close();
    return 0;
}
