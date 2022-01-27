#ifndef MAP_RESOURCE_H
#define MAP_RESOURCE_H

#include "common.h"

using namespace std;

static int done = 0;
struct portal
{
    bool droppedLoot = false;
    bool encounter;
    std::string rotation;
    bool west;
    bool east;
    bool south;
    bool north;
    std::string west_map;
    std::string east_map;
    std::string south_map;
    std::string north_map;

    int warp_x;
    int warp_y;

    std::string description;

    void setup(bool _west, bool _east, bool _south, bool _north, std::string _west_map, std::string _east_map, std::string _south_map, std::string _north_map, int _warp_x = -1, int _warp_y  = -1, std::string _description = "")
    {
        west = _west;
        east = _east;
        south = _south;
        north = _north;
        west_map = _west_map;
        east_map = _east_map;
        south_map = _south_map;
        north_map = _north_map;
        warp_x = _warp_x;
        warp_y = _warp_y;
        description = _description;
        encounter = Generate(0,1);
        std::cout << " We are setting up things" << std::endl;
    };

    void setupStruct(portal in_portal)
    {
        west = in_portal.west;
        east = in_portal.east;
        south = in_portal.south;
        north = in_portal.north;
        west_map = in_portal.west_map;
        east_map = in_portal.east_map;
        south_map = in_portal.south_map;
        north_map = in_portal.north_map;
        warp_x = in_portal.warp_x;
        warp_y = in_portal.warp_y;
        description = in_portal.description;
        encounter = Generate(0,1);
    };

    bool active_portal(std::string _rotation)
    {
        if(_rotation == "W")
            return west;
        if(_rotation == "E")
            return east;
        if(_rotation == "S")
            return south;
        if(_rotation == "N")
            return north;
    }

    std::string getMap(std::string _rotation)
    {
        if(_rotation == "W")
            return west_map;
        if(_rotation == "E")
            return east_map;
        if(_rotation == "S")
            return south_map;
        if(_rotation == "N")
            return north_map;
    }
    int getX()
    {
        return warp_x;
    }

    std::string getDescription()
    {
        return description;
    }
};

portal phlan_portals[16][16];
portal slums_portals[16][16];
portal khutos_well_portals[16][16];
portal podal_plaza_portals[16][16];

portal cardona_textile_house_portals[16][16];
portal kovel_mansion_portals[16][16];
portal mendors_library_portals[16][16];
portal sokol_keep_portals[16][16];
portal stojanov_gate_portals[16][16];
portal vahlingen_graveyard_portals[16][16];
portal valjevo_castle_portals[16][16];
portal wealthy_area_portals[16][16];

portal save_portals[16][16];

void init_portals(std::string _dataFilePath)
{
    int x,y = 0;
    bool west,east,south,north = false;
    std::string west_map,east_map,south_map,north_map = _dataFilePath;
    int warp_x,warp_y;
    std::string description;

    std::ifstream dataFile (_dataFilePath);

	if(!dataFile)			// file couldn't be opened
	{
		cerr << "Error: init_portals(): file could not be opened" << _dataFilePath << endl;
		exit(1);
	}

	do
    {
        dataFile >> x >> y >> west >> east >> south >> north >> west_map >> east_map >> south_map >> north_map >> warp_x >> warp_y >> description;

        if( _dataFilePath == "./data/maps/phlan/phlan_portals" )
        {
            phlan_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/slums/slums_portals" )
        {
            slums_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/khutos_well/khutos_well_portals" )
        {
            khutos_well_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/podal_plaza/podal_plaza_portals" )
        {
            podal_plaza_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/cardona_textile_house/cardona_textile_house_portals" )
        {
            cardona_textile_house_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/kovel_mansion/kovel_mansion_portals" )
        {
            kovel_mansion_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/mendors_library/mendors_library_portals" )
        {
            mendors_library_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/sokol_keep/sokol_keep_portals" )
        {
            sokol_keep_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/stojanov_gate/stojanov_gate_portals" )
        {
            stojanov_gate_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/vahlingen_graveyard/vahlingen_graveyard_portals" )
        {
            vahlingen_graveyard_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/valjevo_castle/valjevo_castle_portals" )
        {
            valjevo_castle_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else if( _dataFilePath == "./data/maps/wealthy_area/wealthy_area_portals" )
        {
            wealthy_area_portals[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        else
        {
            std::cout << "Error loading map data: " << _dataFilePath << std::endl;
            exit(19);
        }
    }
    while(!dataFile.eof());

    dataFile.close();
};

int seed_x, seed_y;

int phlan_loaded = 0;
int slums_loaded = 0;
int khutos_well_loaded = 0;
int podal_plaza_loaded = 0;

void loadPortals()
{
    std::cout << "Loading portals" << mapActive << std::endl;

    if( mapActive == "phlan")
    {
        init_portals("./data/maps/phlan/phlan_portals");
        for( int y = 0; y < 16; y++)
            for( int x = 0; x < 16; x++)
                save_portals[x][y].setupStruct(phlan_portals[x][y]);
                //save_portals[x][y].setup(phlan_portals[x][y].west,phlan_portals[x][y].east,phlan_portals[x][y].south,phlan_portals[x][y].north,phlan_portals[x][y].west_map,phlan_portals[x][y].east_map,phlan_portals[x][y].north_map,phlan_portals[x][y].south_map,phlan_portals[x][y].warp_x,phlan_portals[x][y].warp_y,phlan_portals[x][y].description);
        phlan_loaded = 1;
        slums_loaded = 0;
        khutos_well_loaded = 0;
        podal_plaza_loaded = 0;
    }
    if( mapActive == "slums")
    {
        init_portals("./data/maps/slums/slums_portals");
        for( int y = 0; y < 16; y++)
            for( int x = 0; x < 16; x++)
                 save_portals[x][y].setupStruct(slums_portals[x][y]);
        phlan_loaded = 0;
        slums_loaded = 1;
        khutos_well_loaded = 0;
        podal_plaza_loaded = 0;
    }
    if( mapActive == "khutos_well")
    {
        init_portals("./data/maps/khutos_well/khutos_well_portals");
        for( int y = 0; y < 16; y++)
            for( int x = 0; x < 16; x++)
                save_portals[x][y].setupStruct(khutos_well_portals[x][y]);
        phlan_loaded = 0;
        slums_loaded = 0;
        khutos_well_loaded = 1;
        podal_plaza_loaded = 0;
    }
    if( mapActive == "podal_plaza")
    {
        init_portals("./data/maps/podal_plaza/podal_plaza_portals");
        for( int y = 0; y < 16; y++)
            for( int x = 0; x < 16; x++)
                save_portals[x][y].setupStruct(podal_plaza_portals[x][y]);
        phlan_loaded = 0;
        slums_loaded = 0;
        khutos_well_loaded = 0;
        podal_plaza_loaded = 1;
    }
};

bool generic_portal(int x, int y, std::string rotation)
{
};

bool phlan_portal(int x, int y, std::string rotation)
{
    if( phlan_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = phlan_portals[x][y].getMap(Rotation);
        if(mapActive == "slums")
        {
            worldMap = 1;
            loadPortals();
        }
    }

    if( phlan_portals[x][y].getMap(Rotation) != "phlan" )
    {
        if( phlan_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = phlan_portals[x][y].getX();
    }
    return phlan_portals[x][y].active_portal(rotation);
};

bool slum_portal(int x, int y, std::string rotation)
{
    if( slums_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = slums_portals[x][y].getMap(Rotation);
        if(mapActive == "phlan")
        {
            worldMap = 0;
            loadPortals();
        }
        else if( mapActive == "khutos_well" )
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( slums_portals[x][y].getMap(Rotation) != "slums")
    {
        if( slums_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = slums_portals[x][y].getX();
    }
    return slums_portals[x][y].active_portal(rotation);
};

bool khutos_well_portal(int x, int y, std::string rotation)
{
    if( khutos_well_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = khutos_well_portals[x][y].getMap(Rotation);
        if(mapActive == "slums")
        {
            worldMap = 1;
            loadPortals();
        }
        else if( mapActive == "podal_plaza" )
        {
            worldMap = 3;
            loadPortals();
        }
    }
    if( khutos_well_portals[x][y].getMap(Rotation) != "khutos_well")
    {
        if( khutos_well_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = khutos_well_portals[x][y].getX();
    }
    return khutos_well_portals[x][y].active_portal(rotation);
};

bool podal_plaza_portal(int x, int y, std::string rotation)
{
    if( podal_plaza_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = podal_plaza_portals[x][y].getMap(Rotation);
        if(mapActive == "khutos_well")
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( podal_plaza_portals[x][y].getMap(Rotation) != "podal_plaza")
    {
        if( podal_plaza_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = podal_plaza_portals[x][y].getX();
    }
    return podal_plaza_portals[x][y].active_portal(rotation);
};

bool cardona_textile_house_portal(int x, int y, std::string rotation)
{
    if( cardona_textile_house_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = cardona_textile_house_portals[x][y].getMap(Rotation);
        if(mapActive == "khutos_well")
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( cardona_textile_house_portals[x][y].getMap(Rotation) != "podal_plaza")
    {
        if( cardona_textile_house_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = cardona_textile_house_portals[x][y].getX();
    }
    return cardona_textile_house_portals[x][y].active_portal(rotation);
};

bool kovel_mansion_portal(int x, int y, std::string rotation)
{
    if( kovel_mansion_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = kovel_mansion_portals[x][y].getMap(Rotation);
        if(mapActive == "khutos_well")
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( kovel_mansion_portals[x][y].getMap(Rotation) != "podal_plaza")
    {
        if( kovel_mansion_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = kovel_mansion_portals[x][y].getX();
    }
    return kovel_mansion_portals[x][y].active_portal(rotation);
};

bool mendors_library_portal(int x, int y, std::string rotation)
{
    if( mendors_library_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = mendors_library_portals[x][y].getMap(Rotation);
        if(mapActive == "khutos_well")
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( mendors_library_portals[x][y].getMap(Rotation) != "podal_plaza")
    {
        if( mendors_library_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = mendors_library_portals[x][y].getX();
    }
    return mendors_library_portals[x][y].active_portal(rotation);
};

bool sokol_keep_portal(int x, int y, std::string rotation)
{
    if( sokol_keep_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = sokol_keep_portals[x][y].getMap(Rotation);
        if(mapActive == "khutos_well")
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( sokol_keep_portals[x][y].getMap(Rotation) != "podal_plaza")
    {
        if( sokol_keep_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = sokol_keep_portals[x][y].getX();
    }
    return sokol_keep_portals[x][y].active_portal(rotation);
};

bool stojanov_gate_portal(int x, int y, std::string rotation)
{
    if( stojanov_gate_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = stojanov_gate_portals[x][y].getMap(Rotation);
        if(mapActive == "khutos_well")
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( stojanov_gate_portals[x][y].getMap(Rotation) != "podal_plaza")
    {
        if( stojanov_gate_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = stojanov_gate_portals[x][y].getX();
    }
    return stojanov_gate_portals[x][y].active_portal(rotation);
};

bool vahlingen_graveyard_portal(int x, int y, std::string rotation)
{
    if( vahlingen_graveyard_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = vahlingen_graveyard_portals[x][y].getMap(Rotation);
        if(mapActive == "khutos_well")
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( vahlingen_graveyard_portals[x][y].getMap(Rotation) != "podal_plaza")
    {
        if( vahlingen_graveyard_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = vahlingen_graveyard_portals[x][y].getX();
    }
    return vahlingen_graveyard_portals[x][y].active_portal(rotation);
};

bool valjevo_castle_portal(int x, int y, std::string rotation)
{
    if( valjevo_castle_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = valjevo_castle_portals[x][y].getMap(Rotation);
        if(mapActive == "khutos_well")
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( valjevo_castle_portals[x][y].getMap(Rotation) != "podal_plaza")
    {
        if( valjevo_castle_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = valjevo_castle_portals[x][y].getX();
    }
    return valjevo_castle_portals[x][y].active_portal(rotation);
};

bool wealthy_area_portal(int x, int y, std::string rotation)
{
    if( wealthy_area_portals[x][y].getMap(Rotation) != "")
    {
        mapActive = wealthy_area_portals[x][y].getMap(Rotation);
        if(mapActive == "khutos_well")
        {
            worldMap = 2;
            loadPortals();
        }
    }
    if( wealthy_area_portals[x][y].getMap(Rotation) != "podal_plaza")
    {
        if( wealthy_area_portals[x][y].getX() != -1 )
            PlayerCoordinate.x = wealthy_area_portals[x][y].getX();
    }
    return wealthy_area_portals[x][y].active_portal(rotation);
};

void renderCompass()
{
    square = {current.w / 2 - 90, 20, 180, 60};
    SDL_Rect needle = {current.w / 2, 10, 2, 10};
    SDL_Rect needleLeft = {current.w / 2 - 90, 10, 2, 5};
    SDL_Rect needleRight = {current.w / 2 + 90, 10, 2, 5};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &square);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &square);
    SDL_RenderFillRect(renderer, &needleLeft);
    SDL_RenderFillRect(renderer, &needle);
    SDL_RenderFillRect(renderer, &needleRight);

    xcoord = std::to_string(PlayerCoordinate.x);
    ycoord = std::to_string(PlayerCoordinate.y);

    rotationString = "";
    coordinateString = " ( " + xcoord + "," + ycoord + " ) ";

    rotationString += Rotation.c_str();
    RenderText2(rotationString.c_str(),Black,current.w / 2,40,20);
    RenderText2(coordinateString.c_str(),Black, current.w / 2, 60,20);
};

int npc_location_x = 0;
int npc_location_y = 0;

int simulatePlayerRenderDelay = 30;
int simulatePlayerRenderDelayCounter = 0;
SDL_Rect SimulatePlayer[10];

void renderMinimap(std::string mapFile, std::string mapName)
{
    if( !std::experimental::filesystem::exists("./data/maps/phlan/phlan.png") )
    {
        std::cout << "renderDescription 1" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/slums/slums.png") )
    {
        std::cout << "renderDescription 2" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/khutos_well/khutos_well.png") )
    {
        std::cout << "renderDescription 3" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/podal_plaza/podal_plaza.png") )
    {
        std::cout << "renderDescription 4" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/cardona_textile_house/cardona_textile_house.png") )
    {
        std::cout << "renderDescription 5" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/kovel_mansion/kovel_mansion.png") )
    {
        std::cout << "renderDescription 6" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/mendors_library/mendors_library.png") )
    {
        std::cout << "renderDescription 7" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/sokol_keep/sokol_keep.png") )
    {
        std::cout << "renderDescription 8" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/stojanov_gate/stojanov_gate.png") )
    {
        std::cout << "renderDescription 9" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/vahlingen_graveyard/vahlingen_graveyard.png") )
    {
        std::cout << "renderDescription 10" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/valjevo_castle/valjevo_castle.png") )
    {
        std::cout << "renderDescription 11" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/maps/wealthy_area/wealthy_area.png") )
    {
        std::cout << "renderDescription 12" << std::endl;
        exit(99);
    }

    if( mapName == "phlan")
    {
        gTexture = LoadTexture("./data/maps/phlan/phlan.png",255);
    }
    else if( mapName == "slums")
    {
        gTexture = LoadTexture("./data/maps/slums/slums.png",255);
    }
    else if( mapName == "khutos_well")
    {
        gTexture = LoadTexture("./data/maps/khutos_well/khutos_well.png",255);
    }
    else if( mapName == "podal_plaza")
    {
        gTexture = LoadTexture("./data/maps/podal_plaza/podal_plaza.png",255);
    }
    else if( mapName == "cardona_textile_house")
        gTexture = LoadTexture("./data/maps/cardona_textile_house/cardona_textile_house.png",255);
    else if( mapName == "kovel_mansion")
        gTexture = LoadTexture("./data/maps/kovel_mansion/kovel_mansion.png",255);
    else if( mapName == "mendors_library")
        gTexture = LoadTexture("./data/maps/mendors_library/mendors_library.png",255);
    else if( mapName == "sokol_keep")
        gTexture = LoadTexture("./data/maps/sokol_keep/sokol_keep.png",255);
    else if( mapName == "stojanov_gate")
        gTexture = LoadTexture("./data/maps/stojanov_gate/stojanov_gate.png",255);
    else if( mapName == "vahlingen_graveyard")
        gTexture = LoadTexture("./data/maps/vahlingen_graveyard/vahlingen_graveyard.png",255);
    else if( mapName == "valjevo_castle")
        gTexture = LoadTexture("./data/maps/valjevo_castle/valjevo_castle.png",255);
    else if( mapName == "wealthy_area")
        gTexture = LoadTexture("./data/maps/wealthy_area/wealthy_area.png",255);

    SDL_Rect imageSize = {0, 0,256,256};
    SDL_Rect renderLocation = {50, 50,256,256};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderCopy(renderer, gTexture, &imageSize, &renderLocation);
    SDL_DestroyTexture(gTexture);
}

std::string Proclamations( int _ID )
{
    std::ifstream dataFile ("./data/proclamations");

    std::string line;
    std::string proclamation;

    int counter = 0;

    while(std::getline(dataFile, line))
    {
        if (line.length() == 0 || line[0] == '#')
        {
            //cout << "IGNORE LINE\n";
            counter++;
        }
        else
        {
            if( counter == _ID )
            {
                proclamation += "|";
                proclamation += line;
            }

            if( counter > _ID )
                return proclamation;
        }
    }
}

std::string renderDescription(int x, int y)
{
    int skip_return = 0;
    std::ifstream dataFile;

    if( !std::experimental::filesystem::exists("./data/render_descriptions") )
    {
        std::cout << "renderDescription 1" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_slums") )
    {
        std::cout << "renderDescription 2" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_khutos_well") )
    {
        std::cout << "renderDescription 3" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_podal_plaza") )
    {
        std::cout << "renderDescription 4" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_cardona_textile_house") )
    {
        std::cout << "renderDescription 5" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_kovel_mansion") )
    {
        std::cout << "renderDescription 6" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_mendors_library") )
    {
        std::cout << "renderDescription 7" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_sokol_keep") )
    {
        std::cout << "renderDescription 8" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_stojanov_gate") )
    {
        std::cout << "renderDescription 9" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_vahlingen_graveyard") )
    {
        std::cout << "renderDescription 10" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_valjevo_castle") )
    {
        std::cout << "renderDescription 11" << std::endl;
        exit(99);
    }
    if( !std::experimental::filesystem::exists("./data/render_descriptions_wealthy_area") )
    {
        std::cout << "renderDescription 12" << std::endl;
        exit(99);
    }

    if( mapActive == "phlan")
        dataFile.open("./data/render_descriptions");
    else
    if( mapActive == "slums")
        dataFile.open("./data/render_descriptions_slums");
    else
    if( mapActive == "khutos_well")
        dataFile.open("./data/render_descriptions_khutos_well");
    else
    if( mapActive == "podal_plaza")
        dataFile.open("./data/render_descriptions_podal_plaza");
    else
    if( mapActive == "cardona_textile_house")
        dataFile.open("./data/render_descriptions_cardona_textile_house");
    else
    if( mapActive == "kovel_mansion")
        dataFile.open("./data/render_descriptions_kovel_mansion");
    else
    if( mapActive == "mendors_library")
        dataFile.open("./data/render_descriptions_mendors_library");
    else
    if( mapActive == "sokol_keep")
        dataFile.open("./data/render_descriptions_sokol_keep");
    else
    if( mapActive == "stojanov_gate")
        dataFile.open("./data/render_descriptions_stojanov_gate");
    else
    if( mapActive == "vahlingen_graveyard")
        dataFile.open("./data/render_descriptions_vahlingen_graveyard");
    else
    if( mapActive == "valjevo_castle")
        dataFile.open("./data/render_descriptions_valjevo_castle");
    else
    if( mapActive == "wealthy_area")
        dataFile.open("./data/render_descriptions_wealthy_area");

    std::string line;
    std::string descriptions;

    int counter = 0;

    while(std::getline(dataFile, line))
    {
        if (line.length() == 0 || line[0] == '#')
        {
            //cout << "IGNORE LINE\n";
            counter++;
        }
        else
        {
            // cache the line
            std::istringstream tokenizer(line);

            std::getline(tokenizer, phlanTourCoordinateN[0], ','); // then get the tokens from it
            std::getline(tokenizer, phlanTourCoordinateN[1], ','); // then get the tokens from it
            std::getline(tokenizer, phlanTourCoordinateN[2]); // last token: get the remainder of the line.

            if(tokenizer)
            {
                if(phlanTourCoordinateN[0] == std::to_string(x))
                {
                    if(phlanTourCoordinateN[1] == std::to_string(y))
                    {
                        if( phlanTourCoordinateN[2] == "TRAINING_HALL")
                        {
                            if( currentTimeElapse() == day )
                            {
                                trainingHall = 1;
                                skip_return = 1;
                                RenderText("There is a traininghall here, do you want to enter?",Red,100,0,48);
                            }
                        }
                        if( phlanTourCoordinateN[2] == "ARMS_ARMOUR")
                        {
                            if( currentTimeElapse() == day )
                            {
                                armsAndarmourShop = 1;
                                skip_return = 1;
                                RenderText("There is a Armory here, do you want to enter?",Red,100,0,48);
                            }
                        }
                        if( phlanTourCoordinateN[2] == "TAVERN_TALES")
                        {
                            if( currentTimeElapse() == day )
                            {
                                tavern = 1;
                                skip_return = 1;
                                RenderText("There is a tavern here, do you want to enter?",Red,100,0,48);
                            }
                        }
                        if( phlanTourCoordinateN[2] == "GENERAL_SHOP")
                        {
                            if( currentTimeElapse() == day )
                            {
                                generalShop = 1;
                                skip_return = 1;
                                RenderText("There is a general shop here, do you want to enter?",Red,100,0,48);
                            }
                        }
                        if( phlanTourCoordinateN[2] == "JEWELERY_SHOP")
                        {
                            if( currentTimeElapse() == day )
                            {
                                jewelleryShop = 1;
                                skip_return = 1;
                                RenderText("There is a jewellery shop here, do you want to enter?",Red,100,0,48);
                            }
                        }
                        if( phlanTourCoordinateN[2] == "PROCLAMATIONS")
                        {
                            std::cout << Proclamations( (rand()%19 + 1) ) << std::endl;
                            skip_return = 1;
                            RenderText(Proclamations( (rand()%19 + 1) ),Red,100,0,48);
                        }
                        if( phlanTourCoordinateN[2] == "PRIESTHOOD")
                        {
                            if( currentTimeElapse() == day )
                            {
                                templeShop = 1;
                                skip_return = 1;
                                RenderText("There is a priesthood here, do you want to enter?",Red,100,0,48);
                            }
                        }
                        if( phlanTourCoordinateN[2] == "SILVER_SHOP")
                        {
                            if( currentTimeElapse() == day )
                            {
                                silverShop = 1;
                                skip_return = 1;
                                RenderText("There is a silver shop here, do you want to enter?",Red,100,0,48);
                            }
                        }
                        if( phlanTourCoordinateN[2] == "ROLF")
                        {
                            rolf = 1;
                            skip_return = 1;
                            RenderText("Rolf is here, do you want to take a tour?",Red,100,0,48);
                        }
                        phlanTourCoordinateN[2] += phlanTourCoordinateN[0];
                        phlanTourCoordinateN[2] += phlanTourCoordinateN[1];

                        if( skip_return == 0 )
                            return phlanTourCoordinateN[2];
                        skip_return = 0;
                    }
                }
                // success!
            }
            else
            {
               return "There were fewer than one commas in the line";
            }
        }
    }
    dataFile.close();
};

#endif // MAP_RESOURCE_H
