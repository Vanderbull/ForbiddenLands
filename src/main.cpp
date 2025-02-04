#include <chrono>
#include <thread>

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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#include <sqlite3.h>
#include "../rapidxml-1.13/rapidxml.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "../include/doctest.h"

#include "../asciichart-master/include/ascii/ascii.h"

using namespace ascii;
using namespace std;
using namespace rapidxml;
using namespace std::chrono;

xml_document<> doc;
xml_node<> * root_node = NULL;

struct utsname uts;

// SDL  and OpenGL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>
//#include <SDL_opengl.h>
//#include <GL/glut.h>
//#include "../version.h"

#include "../include/gameengine/gameengine.h"
#include "../include/gameengine/introstate.h"
#include "../include/gameengine/menustate.h"

//#include "../include/resource.h"
//#include "../include/views/world_view.h"
//#include "../include/views/battle_view.h"

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

namespace fs = std::experimental::filesystem;

static bool s_Finished = false;

//void DoWork()
//{
//    SDL_Log("DoWork() thread running");
//    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
//    int flags = MIX_INIT_OGG | MIX_INIT_MOD;
//    int initted = Mix_Init(flags);
//    if ((initted & flags) != flags)
//    {
//        printf("Mix_Init: Failed to init required ogg and mod support!\n");
//        printf("Mix_Init: %s\n", Mix_GetError());
//        // handle error
//    }
//    Mix_Music* song = NULL;
//    song = Mix_LoadMUS("assets/data/sound/tavern/1_Black Moon Tavern by Ean Grimm.mp3");
//    if (!song)
//    {
//        SDL_Log("Load music file failed! %s", Mix_GetError());
//        exit(EXIT_FAILURE);
//    }
//    Mix_VolumeMusic(32);
//    SDL_Log("Mix_VolumeMusic = %d",Mix_VolumeMusic(-1));
//    Mix_PlayMusic( song, -1 );
//};

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

//void DisplayPathInfo(const fs::path& pathToShow)
//{
//	int i = 0;
//	std::cout << "Displaying path info for: " << pathToShow << "\n";
//	for (const auto& part : pathToShow)
//	{
//		std::cout << "path part: " << i++ << " = " << part << "\n";
//	}
//
//	std::cout << "exists() = " << fs::exists(pathToShow) << "\n"
//		<< "root_name() = " << pathToShow.root_name() << "\n"
//		<< "root_path() = " << pathToShow.root_path() << "\n"
//		<< "relative_path() = " << pathToShow.relative_path() << "\n"
//		<< "parent_path() = " << pathToShow.parent_path() << "\n"
//		<< "filename() = " << pathToShow.filename() << "\n"
//		<< "stem() = " << pathToShow.stem() << "\n"
//		<< "extension() = " << pathToShow.extension() << "\n";
//
//	try
//	{
//		std::cout << "canonical() = " << fs::canonical(pathToShow) << "\n";
//	}
//	catch (fs::filesystem_error err)
//	{
//		std::cout << "exception: " << err.what() << "\n";
//	}
//}

//void DisplayFileInfo(const std::experimental::filesystem::v1::directory_entry & entry, std::string &lead, std::experimental::filesystem::v1::path &filename)
//{
//	time_t cftime = std::chrono::system_clock::to_time_t(fs::last_write_time(entry));
//	std::cout << lead << " " << filename << ", "
//		 << ComputeFileSize(entry)
//		 << ", time: " << std::asctime(std::localtime(&cftime));
//}
//
//void DisplayDirTree(const fs::path& pathToShow, int level)
//{
//    if (fs::exists(pathToShow) && fs::is_directory(pathToShow))
//    {
//        auto lead = std::string(level * 3, ' ');
//        for (const auto& entry : fs::directory_iterator(pathToShow))
//        {
//            auto filename = entry.path().filename();
//            if (fs::is_directory(entry.status()))
//            {
//                std::cout << lead << "[+] " << filename << "\n";
//                DisplayDirTree(entry, level + 1);
//                std::cout << "\n";
//            }
//            else if (fs::is_regular_file(entry.status()))
//                DisplayFileInfo(entry, lead, filename);
//            else
//                std::cout << lead << " [?]" << filename << "\n";
//        }
//    }
//}

std::string return_current_time_and_date()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

//void initFileSystem()
//{
//    return;
//    std::string currentDate;
//    currentDate = return_current_time_and_date();
//
//    fs::path cwd = fs::current_path();
//    cwd += "/output_log_ ";
//    cwd += currentDate.c_str();
//    std::ofstream file(cwd.string());
//
//    fs::path pathToShow(".");
//    file << "exists() = " << fs::exists(pathToShow) << "\n"
//     << "root_name() = " << pathToShow.root_name() << "\n"
//     << "root_path() = " << pathToShow.root_path() << "\n"
//     << "relative_path() = " << pathToShow.relative_path() << "\n"
//     << "parent_path() = " << pathToShow.parent_path() << "\n"
//     << "filename() = " << pathToShow.filename() << "\n"
//     << "stem() = " << pathToShow.stem() << "\n"
//     << "extension() = " << pathToShow.extension() << "\n";
//
//    int i = 0;
//    for (const auto& part : pathToShow)
//        file << "path part: " << i++ << " = " << part << "\n";
//
//    auto timeEntry = fs::last_write_time(cwd);
//    time_t cftime = std::chrono::system_clock::to_time_t(timeEntry);
//
//    file << std::asctime(std::localtime(&cftime));
//
//    file.close();
//}

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

//Fps fps;

int Generate(const int from, const int to);

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++)
   {
       //mainLog.push_back(argv[i]);
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

//void updatePlayerLocation(std::string Rotation)
//{
//    if( Rotation  == "N" )
//        PlayerCoordinate.y--;
//    else
//    if( Rotation  == "S" )
//        PlayerCoordinate.y++;
//    else
//    if( Rotation  == "E" )
//        PlayerCoordinate.x++;
//    else
//    if( Rotation  == "W" )
//        PlayerCoordinate.x--;
//}

//void updateHungerAndThirst()
//{
//    playerCharacter[playerCharacterSelected].increaseHunger();
//    playerCharacter[playerCharacterSelected].increaseThirst();
//
//    if( playerCharacter[playerCharacterSelected].hunger == 100 )
//        playerCharacter[playerCharacterSelected].hitpoints_current--;
//    if( playerCharacter[playerCharacterSelected].thirst == 100 )
//        playerCharacter[playerCharacterSelected].hitpoints_current--;
//}

//TEST_CASE("updateHungerAndThirst") {
//    if( playerCharacter[playerCharacterSelected].hunger == 100 )
//    CHECK(playerCharacter[playerCharacterSelected].hitpoints_current == 99);
//}
//
//TEST_CASE("[math] basic stuff") {
//    CHECK(6 > 5);
//    CHECK(6 > 7);
//}
//TEST_CASE("[math] basic stuff") {
//    CHECK(6 > 5);
//    CHECK(6 > 7);
//}

//void client()
//{
//    int sock = 0, valread;
//    struct sockaddr_in serv_addr;
//    char *hello = "Hello from client";
//    char buffer[1024] = {0};
//    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//    {
//        printf("\n Socket creation error \n");
//        //return -1;
//    }
//
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_port = htons(8080);
//
//    // Convert IPv4 and IPv6 addresses from text to binary form
//    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
//    {
//        printf("\nInvalid address/ Address not supported \n");
//        //return -1;
//    }
//
//    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//    {
//        printf("\nConnection Failed \n");
//        //return -1;
//    }
//    send(sock , hello , strlen(hello) , 0 );
//    printf("Hello message sent\n");
//    valread = read( sock , buffer, 1024);
//    printf("%s\n",buffer );
//};
//int server()
//{
//    int server_fd, new_socket, valread;
//    struct sockaddr_in address;
//    int opt = 1;
//    int addrlen = sizeof(address);
//    char buffer[1024] = {0};
//    char *hello = "Hello from server";
//
//    // Creating socket file descriptor
//    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//    {
//        perror("socket failed");
//        exit(EXIT_FAILURE);
//    }
//
//    // Forcefully attaching socket to the port 8080
//    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
//                                                  &opt, sizeof(opt)))
//    {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY;
//    address.sin_port = htons( 8080 );
//
//    // Forcefully attaching socket to the port 8080
//    if (bind(server_fd, (struct sockaddr *)&address,
//                                 sizeof(address))<0)
//    {
//        perror("bind failed");
//        exit(EXIT_FAILURE);
//    }
//    if (listen(server_fd, 3) < 0)
//    {
//        perror("listen");
//        exit(EXIT_FAILURE);
//    }
//    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
//                       (socklen_t*)&addrlen))<0)
//    {
//        perror("accept");
//        exit(EXIT_FAILURE);
//    }
//    valread = read( new_socket , buffer, 1024);
//    printf("%s\n",buffer );
//    send(new_socket , hello , strlen(hello) , 0 );
//    printf("Hello message sent\n");
//    return 0;
//}
//
//#define TRUE   1
//#define FALSE  0
//#define PORT 8888

//string convertToString(char* a)
//{
//    string s = a;
//    return s;
//}

CGameEngine game;
FILE * pFile;

void LogSDL(void *userdata, int category, SDL_LogPriority priority, const char *message)
{
    char *ctime_no_newline;
    time_t tm = time(NULL);

    ctime_no_newline = strtok(ctime(&tm), "\n");

    fprintf(pFile,"[Log] %s %s\n", ctime_no_newline, message);
};

// Set up the game loop timer
const int fps = 60;
const int frame_time = 1000 / fps;

Uint32 last_frame_time = SDL_GetTicks();

int main(int argc, char ** argv)
{
    //srand(time(0));
    //mt19937 mt(time(nullptr));
    pFile = fopen ("./logs/GameEngineLOG.log","w");
    SDL_LogSetOutputFunction(&LogSDL, NULL);
    SDL_Log("./logs/GameEngineLOG.txt file opened: Success");

//    int staticAbility = 24;
//    int abilityModifier = 0;
//    int level = 1;
//    int ToughnessMod = 5;
//    int IntelligenceMod = 5;
//
//    SDL_Log("Calculating Knight HP: %d @ level = %d", 40 + (5 * ToughnessMod) + (6 * level),level);
//
//    int amount_hp = GenerateNumber(1, (ToughnessMod / 2) );
//    int amount_sp = GenerateNumber(1, (IntelligenceMod / 2) );
//    for( int i= 5; i < 42; i++)
//    {
//        staticAbility = i;
//        abilityModifier = floor((staticAbility - 20) / 2);
//
//        SDL_Log("%d = abilityModifier: %d",staticAbility,abilityModifier);
//    }
//
//    std::thread worker(DoWork);

    game.Init("A Viking Saga",1920,1080,32,true);

    std::cout << game.GetSize() << std::endl;
    game.PushState( CIntroState::Instance() );
    std::cout << game.GetSize() << std::endl;
    //exit(99);
    //game.ChangeState( CMenuState::Instance() );

//    int opt = TRUE;
//    int master_socket , addrlen , new_socket , client_socket[30] ,
//          max_clients = 30 , activity, i , valread , sd;
//    int max_sd;
//    struct sockaddr_in address;
//
//    char buffer[1025];  //data buffer of 1K
//
//    //set of socket descriptors
//    fd_set readfds;
//
//    //a message
//    char *message = "ECHO Daemon v1.0 \r\n";
//
//    //initialise all client_socket[] to 0 so not checked
//    for (i = 0; i < max_clients; i++)
//    {
//        client_socket[i] = 0;
//    }
//
//    //create a master socket
//    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
//    {
//        perror("socket failed");
//        exit(EXIT_FAILURE);
//    }
//
//    //set master socket to allow multiple connections ,
//    //this is just a good habit, it will work without this
//    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
//          sizeof(opt)) < 0 )
//    {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }
//
//    //type of socket created
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY;
//    address.sin_port = htons( PORT );
//
//    //bind the socket to localhost port 8888
//    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
//    {
//        perror("bind failed");
//        exit(EXIT_FAILURE);
//    }
//    printf("Listener on port %d \n", PORT);
//
//    //try to specify maximum of 3 pending connections for the master socket
//    if (listen(master_socket, 3) < 0)
//    {
//        perror("listen");
//        exit(EXIT_FAILURE);
//    }
//
//    //accept the incoming connection
//    addrlen = sizeof(address);
//    puts("Waiting for connections ...");

//    for(int i = 0; i < argc; i++)
//    {
//        cout << "argv" << i << ": " << argv[i] << endl;
//    }
//    if (argc == 1)
//    {
//        std::cout << "Client" << std::endl;
//        client();
//    }
//    else
//    {
//        std::cout << "Server" << std::endl;
//        server();
//    }
//    if(std::string(argv[1]) == "client")
//    client();
//    else
//        std::cout << "server" << std::endl;
    doctest::Context context;

    // !!! THIS IS JUST AN EXAMPLE SHOWING HOW DEFAULTS/OVERRIDES ARE SET !!!

    // defaults
    context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in the name
    context.setOption("rand-seed", 324);              // if order-by is set to "rand" use this seed
    context.setOption("order-by", "file");            // sort the test cases by file and line

    context.applyCommandLine(argc, argv);

    // overrides
    context.setOption("no-breaks", true); // don't break in the debugger when assertions fail

    int resu = context.run(); // run queries, or run tests unless --no-run is specified

    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return resu;          // propagate the result of the tests

    context.clearFilters(); // removes all filters added up to this point

    //int client_stuff_return_code = program();
    //some_program_code(argc, argv);
    // your program - if the testing framework is integrated in your production code

    //return resu + client_stuff_return_code; // the result from doctest is propagated here as well

    //SDL_Delay(10000);



//   cout << "\nParsing my students data (sample.xml)....." << endl;
//
//    // Read the sample.xml file
//    ifstream theFile ("sample.xml");
//    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
//    buffer.push_back('\0');
//
//    // Parse the buffer
//    doc.parse<0>(&buffer[0]);
//
//    // Find out the root node
//    root_node = doc.first_node("MyStudentsData");
//
//    // Iterate over the student nodes
//    for (xml_node<> * student_node = root_node->first_node("Student"); student_node; student_node = student_node->next_sibling())
//    {
//        cout << "\nStudent Type =   " << student_node->first_attribute("student_type")->value();
//        cout << endl;
//
//            // Interate over the Student Names
//        for(xml_node<> * student_name_node = student_node->first_node("Name"); student_name_node; student_name_node = student_name_node->next_sibling())
//        {
//            cout << "Student Name =   " << student_name_node->value();
//            cout << endl;
//        }
//        cout << endl;
//    }
//
//    const char* data = "Callback function called";
//    char *zErrMsg = 0;
//    int rc;
//    char *sql;
//    sqlite3* db;
//    int res = sqlite3_open("databaseName.db", &db);
//    if(res)
//        //database failed to open
//        cout << "Database failed to open" << endl;
//    else
//    {
//       /* Create SQL statement */
//       sql = "CREATE TABLE COMPANY("  \
//          "ID INT PRIMARY KEY     NOT NULL," \
//          "NAME           TEXT    NOT NULL," \
//          "AGE            INT     NOT NULL," \
//          "ADDRESS        CHAR(50)," \
//          "SALARY         REAL );";
//
//       /* Execute SQL statement */
//       rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//
//       if( rc != SQLITE_OK ){
//          fprintf(stderr, "SQL error: %s\n", zErrMsg);
//          sqlite3_free(zErrMsg);
//       } else {
//          fprintf(stdout, "Table created successfully\n");
//       }
//        //your database code here
//    }
//
//   /* Create SQL statement */
//   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
//         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
//         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
//         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
//         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
//         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
//         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
//         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
//
//   /* Execute SQL statement */
//   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//
//   if( rc != SQLITE_OK ){
//      fprintf(stderr, "SQL error: %s\n", zErrMsg);
//      sqlite3_free(zErrMsg);
//   } else {
//      fprintf(stdout, "Records created successfully\n");
//   }
//   /* Create SQL statement */
//   sql = "SELECT * from COMPANY";
//
//   /* Execute SQL statement */
//   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
//
//   if( rc != SQLITE_OK ) {
//      fprintf(stderr, "SQL error: %s\n", zErrMsg);
//      sqlite3_free(zErrMsg);
//   } else {
//      fprintf(stdout, "Operation done successfully\n");
//   }
//    sqlite3_close(db);

    ///////////////////////////////

    srand (time(NULL));

      setlocale(LC_ALL, "");

//animation();
//exit(10);
//    std::vector<std::string> fontFiles;
//    std::vector<std::string> imagesFiles;
//    std::vector<std::string> dataFiles;
//    std::vector<std::string> logsFiles;
//
//    read_directory("./font", fontFiles);
//    read_directory("./images", imagesFiles);
//    read_directory("./data", dataFiles);
//    read_directory("./logs", logsFiles);
//
//    int fw,fh;
//
//    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
//    {
//        SDL_Log("GetCurrentDirectory failed: %s", errno);
//        return errno;
//    }
//    else
//    {
//        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
//        SDL_Log("The current working directory is %s", cCurrentPath);
//    }

//    countFiles("./data");
//
//    initFileSystem();
//
//    initGame();
//
//    initQuests();
//
//    init_portals("./data/maps/phlan/phlan_portals");
//    init_portals("./data/maps/slums/slums_portals");
//    init_portals("./data/maps/khutos_well/khutos_well_portals");
//    init_portals("./data/maps/podal_plaza/podal_plaza_portals");
//    init_portals("./data/maps/cardona_textile_house/cardona_textile_house_portals");
//    init_portals("./data/maps/kovel_mansion/kovel_mansion_portals");
//    init_portals("./data/maps/mendors_library/mendors_library_portals");
//    init_portals("./data/maps/sokol_keep/sokol_keep_portals");
//    init_portals("./data/maps/stojanov_gate/stojanov_gate_portals");
//    init_portals("./data/maps/vahlingen_graveyard/vahlingen_graveyard_portals");
//    init_portals("./data/maps/valjevo_castle/valjevo_castle_portals");
//    init_portals("./data/maps/wealthy_area/wealthy_area_portals");
//
//    loadPortals();
//
//    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

//    loadItemIcons();
//    initShop();
//    generateSmithShopItems();
//    playerCharacter[0].loadCharacterFace();
//    playerCharacter[1].loadCharacterFace();
//    playerCharacter[2].loadCharacterFace();
//    playerCharacter[3].loadCharacterFace();
//    playerCharacter[4].loadCharacterFace();
//    playerCharacter[5].loadCharacterFace();
//
//    loadPCstatusData();
    //loadMapTextures();
    //MainMenuLoadBackground("./images/menus/menu_backdrop.png");
    //initGameTitleFont("./font/droid-sans-mono/DroidSansMono.ttf", 160);
    //initGameBreadTextFont("./font/droid-sans-mono/DroidSansMono.ttf", 24);
    //exit(0);
    //testInit();

    //std::cout << "Loading finished" << std::endl;

    //struct timeval tv;
       /* Wait up to five seconds. */
    //tv.tv_sec = 5;
    //tv.tv_usec = 0;

    //SDL_Surface *surface = IMG_Load("./icons/cursor_1.png");
    //SDL_Cursor *cursor = SDL_CreateColorCursor(surface,72,20);
    //SDL_SetCursor(cursor);


    //while (!quit)
    while( game.Running() )
    {
//        //clear the socket set
//        FD_ZERO(&readfds);
//
//        //add master socket to set
//        FD_SET(master_socket, &readfds);
//        max_sd = master_socket;
//
//        //add child sockets to set
//        for ( i = 0 ; i < max_clients ; i++)
//        {
//            //socket descriptor
//            sd = client_socket[i];
//
//            //if valid socket descriptor then add to read list
//            if(sd > 0)
//                FD_SET( sd , &readfds);
//
//            //highest file descriptor number, need it for the select function
//            if(sd > max_sd)
//                max_sd = sd;
//        }
//
//        //wait for an activity on one of the sockets , timeout is NULL ,
//        //so wait indefinitely
//        activity = select( max_sd + 1 , &readfds , NULL , NULL , &tv);
//
//        if ((activity < 0) && (errno!=EINTR))
//        {
//            printf("select error");
//        }
//
//        //If something happened on the master socket ,
//        //then its an incoming connection
//        if (FD_ISSET(master_socket, &readfds))
//        {
//            if ((new_socket = accept(master_socket,
//                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
//            {
//                perror("accept");
//                exit(EXIT_FAILURE);
//            }
//
//            //inform user of socket number - used in send and receive commands
//            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
//                  (address.sin_port));
//
//            //send new connection greeting message
//            if( send(new_socket, message, strlen(message), 0) != strlen(message) )
//            {
//                perror("send");
//            }
//
//            puts("Welcome message sent successfully");
//
//            //add new socket to array of sockets
//            for (i = 0; i < max_clients; i++)
//            {
//                //if position is empty
//                if( client_socket[i] == 0 )
//                {
//                    client_socket[i] = new_socket;
//                    printf("Adding to list of sockets as %d\n" , i);
//
//                    break;
//                }
//            }
//        }
//
//        //else its some IO operation on some other socket
//        for (i = 0; i < max_clients; i++)
//        {
//            sd = client_socket[i];
//
//            if (FD_ISSET( sd , &readfds))
//            {
//                //Check if it was for closing , and also read the
//                //incoming message
//                if ((valread = read( sd , buffer, 1024)) == 0)
//                {
//                    //Somebody disconnected , get his details and print
//                    getpeername(sd , (struct sockaddr*)&address , \
//                        (socklen_t*)&addrlen);
//                    printf("Host disconnected , ip %s , port %d \n" ,
//                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
//
//                    //Close the socket and mark as 0 in list for reuse
//                    close( sd );
//                    client_socket[i] = 0;
//                }
//
//                //Echo back the message that came in
//                else
//                {
//
//                    //set the string terminating NULL byte on the end
//                    //of the data read
//                    buffer[valread] = '\0';
//
//                    TITLE = std::string(buffer);
//                    TITLE = TITLE.substr(0, TITLE.size()-2);
//                    //TITLE = convertToString(buffer);
//                    //TITLE.erase(std::find(TITLE.begin(), TITLE.end(), '\0'), TITLE.end());
//                    send(sd , buffer , strlen(buffer) , 0 );
//                }
//            }
//        }

        game.HandleEvents();
        game.Update();
        game.Draw();

        //SDL_RenderPresent(game.renderer);

        //start = high_resolution_clock::now();

        // Control the frame rate
        Uint32 current_time = SDL_GetTicks();

        if (current_time - last_frame_time < frame_time) {
            Uint32 delay_time = frame_time - (current_time - last_frame_time);
            SDL_Delay(delay_time);
        }

        last_frame_time = current_time;

        SDL_RenderPresent(game.renderer);

        //stop = high_resolution_clock::now();
        //auto duration = duration_cast<microseconds>(stop - start);

        //m_uPreviousMouseState=m_uCurrentMouseState;
        //mouseUpdate();
//
//        while (SDL_PollEvent(&event) != 0)
//        {
//            switch (event.type)
//            {
//                case SDL_KEYUP:
//                    switch (event.key.keysym.sym)
//                    {
//                        case SDLK_y:
//                        {
//                            game.ChangeState( CMenuState::Instance() );
//                            if( armsAndarmourShop || trainingHall || tavern )
//                            {
//                                shop = 1;
//                            }
//                            if( generalShop || jewelleryShop || silverShop )
//                            {
//                                shop = 1;
//                            }
//                            if( templeShop )
//                            {
//                                shop = 1;
//                                cureCriticalWounds();
//                                cureSeriousWounds();
//                                cureLightWounds();
//                            };
//                        } break;
//                        case SDLK_ESCAPE:
//                        {
//                            if(activeView == MAIN_MENU)
//                            {
//                                if( SettingsMenu )//                                {
//                                    SettingsMenu = 0;
//                                }
//                                else if( SaveMenu )
//                                {
//                                    SaveMenu = 0;
//                                }
//                                else if( LoadMenu )
//                                {
//                                    LoadMenu = 0;
//                                }
//                                else if( CreateCharacter )
//                                {
//                                    CreateCharacter = 0;
//                                }
//                                else
//                                {
//                                    quit = 1;
//                                }
//                            }
//                            else if(activeView == DUNGEON)
//                            {
//                                activeView = MAIN_MENU;
//                            }
//                        } break;
//                    } break;
//                case SDL_MOUSEBUTTONDOWN:
//                    switch (event.button.button)
//                    {
//                        case SDL_BUTTON_RIGHT:
//                        default:
//                        {
//                            m_uCurrentMouseState=SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);
//                        } break;
//                    } break;
//                case SDL_KEYDOWN:
//                    switch (event.key.keysym.sym)
//                    {
//                        case SDLK_F12:
//                        {
//                            std::cout<<"Fps: "<<fps.get()<<'\n';
//                            teleport(4,4,PlayerCoordinate.x,PlayerCoordinate.y);
//                            playerCharacter[playerCharacterSelected].carriedItems.push_back(createWater());
//                            playerCharacter[playerCharacterSelected].increaseHunger();
//                            playerCharacter[playerCharacterSelected].increaseThirst();
//                        } break;
//                        case SDLK_PLUS:
//                        {
//                            MusicVolume = Mix_VolumeMusic(Mix_VolumeMusic(-1)+1 );
//                        } break;
//                        case SDLK_MINUS:
//                        {
//                            MusicVolume = Mix_VolumeMusic(Mix_VolumeMusic(-1)+1);
//                        } break;
//                        case SDLK_LEFT:
//                        case SDLK_q:
//                        {
//                            if( activeView == DUNGEON )
//                            {
//                                rotateCounterClockWise();
//                                getCompassDirection();
//
//                                LastPlayerCoordinate.x = PlayerCoordinate.x;
//                                LastPlayerCoordinate.y = PlayerCoordinate.y;
//                            }
//                        } break;
//                        case SDLK_RIGHT:
//                        case SDLK_e:
//                        {
//                            if( activeView == DUNGEON )
//                            {
//                                rotateClockWise();
//                                getCompassDirection();
//
//                                LastPlayerCoordinate.x = PlayerCoordinate.x;
//                                LastPlayerCoordinate.y = PlayerCoordinate.y;
//                            }
//                        } break;
//                        case SDLK_UP:
//                        case SDLK_w:
//                            inGameTime++;
//                            currentTimeElapse(true);
//                            if( activeView == DUNGEON )
//                            {
//                                // We are in dungeonMode
//                                switch( worldMap )
//                                {
//                                case 0: // PHLAN
//                                    {
//                                        if( phlan_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 1: // SLUMS
//                                    {
//                                        if( slum_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 2: // KHUTOS WELL
//                                    {
//                                        if( khutos_well_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 3: // PODAL_PLAZA
//                                    {
//                                        if( podal_plaza_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 4: // cardona_textile_house_portal
//                                    {
//                                        if( cardona_textile_house_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 5: // kovel_mansion
//                                    {
//                                        if( kovel_mansion_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 6: // mendors_library
//                                    {
//                                        if( mendors_library_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 7: // sokol_keep
//                                    {
//                                        if( sokol_keep_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 8: // stojanov_gate
//                                    {
//                                        if( stojanov_gate_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 9: // vahlingen_graveyard
//                                    {
//                                        if( vahlingen_graveyard_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 10: // valjevo_castle
//                                    {
//                                        if( valjevo_castle_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                case 11: // wealthy_area
//                                    {
//                                        if( wealthy_area_portal(PlayerCoordinate.x, PlayerCoordinate.y, Rotation) )
//                                        {
//                                            updatePlayerLocation(Rotation);
//                                            updateHungerAndThirst();
//                                        }
//                                    } break;
//                                }
//                                LastPlayerCoordinate.y = PlayerCoordinate.y;
//                                LastPlayerCoordinate.x = PlayerCoordinate.x;
//                            }
//                            break;
//                    } break;
//            }
//        }



//        if( activeView == BATTLE )
//        {
//            battleView();
//        }
//        else if( activeView == MAIN_MENU )
//        {
//            if(TITLE == "switch")
//                renderTemple();
//            else
//                if( SettingsMenu == 1 )
//                {
//                renderSettings();
//                }
//                else if( SaveMenu == 1 )
//                {
//                RenderSaveMenu();
//                }
//                else if( LoadMenu == 1)
//                {
//                RenderLoadMenu();
//                }
//                else if( CreateCharacter == 1)
//                {
//                renderCharacterCreation();
//                }
//            MainMenu();
//        }
//        else if(activeView == DUNGEON)
//        {
//            renderWorldViewA();
//
//            if(shop)
//            {
//                if(templeShop)
//                {
//                    renderTemple();
//                }
//                else if(trainingHall)
//                {
//                    renderTrainer();
//                }
//                else if(armsAndarmourShop)
//                {
//                    renderSmithShop();
//                }
//                else if(jewelleryShop)
//                {
//                    renderJewelleryShop();
//                }
//                else if(generalShop)
//                {
//                    renderGeneralShop();
//                }
//                else if(silverShop)
//                {
//                    renderSilverShop();
//                }
//                else if(tavern)
//                {
//                    renderTavern();
//                }
//            }
//        } // end dungeonView

        //IMG_Quit();
        //fps.update();

        //renderDescription(PlayerCoordinate.x, PlayerCoordinate.y);
        //renderFPS(fps.get());

        //SDL_RenderPresent(renderer);

        //std::cout << "MAIN microseconds: " << duration.count() << endl;
       //SDL_Delay(50);
    }

    //SDL_DestroyTexture(currentViewTexture);
    //SDL_DestroyTexture(backgroundTexture);
    //unloadPCstatusData();

    return 0;
}
