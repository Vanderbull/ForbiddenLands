#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "actor.h"
#include "ingametime.h"
#include "gameengine.h"

class CGameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(CGameEngine* game) = 0;
	virtual void Update(CGameEngine* game) = 0;
	virtual void Draw(CGameEngine* game) = 0;

	void ChangeState(CGameEngine* game, CGameState* state) {
		game->ChangeState(state);
	}

protected:
	CGameState() { }

	ACTOR SActor;
    InGameTime DateAndTime;

    struct portal2
    {
        bool droppedLoot = false;
        bool encounter;
        std::string rotation;
        enum {WEST,EAST,SOUTH,NORTH};
        std::string compassDirections[4];
        bool directionPassable[4];
        SDL_Point warp = {0, 0};
        int warp_x;
        int warp_y;
        std::string description;

        void setup(bool setDirectionPassable[], std::string setCompassDirections[], SDL_Point in_warp, std::string _description = "")
        {
            for(int i; i < 4; i++)
            {
                directionPassable[i] = setDirectionPassable[i];
                compassDirections[i] = setCompassDirections[i];
            }

            warp = in_warp;
            description = _description;
            encounter = GenerateNumber(0,1);
        };
    };

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
            encounter = GenerateNumber(0,1);
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
            encounter = GenerateNumber(0,1);
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

    portal2 test_portal[16][16];

    portal mapPortal[16][16];
    portal savePortal[16][16];

    portal2 phlan_portal_2[16][16];

    portal kustenstad[16][16];
    portal vallentuna[16][16];
    portal mora[16][16];

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

    void initPortal(std::string _dataFilePath)
    {
        int x,y = 0;
        bool west,east,south,north = false;
        std::string west_map,east_map,south_map,north_map = _dataFilePath;
        int warp_x,warp_y;
        std::string description;

        bool directions[4] = {false,false,false,false};
        std::string directions_map[4] = {_dataFilePath.c_str(),_dataFilePath.c_str(),_dataFilePath.c_str(),_dataFilePath.c_str()};
        SDL_Point warp;

        std::ifstream dataFile (_dataFilePath);

        if(!dataFile)
        {
            SDL_Log("Error: init_portals(): file could not be opened %s",_dataFilePath);
            exit(EXIT_FAILURE);
        }

        do
        {
            dataFile >> x >> y >> west >> east >> south >> north >> west_map >> east_map >> south_map >> north_map >> warp_x >> warp_y >> description;
            mapPortal[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
        }
        while(!dataFile.eof());

        dataFile.close();
    };

    void init_portals(std::string _dataFilePath)
    {
        int x,y = 0;
        bool west,east,south,north = false;
        std::string west_map,east_map,south_map,north_map = _dataFilePath;
        int warp_x,warp_y;
        std::string description;

        bool directions[4] = {false,false,false,false};
        std::string directions_map[4] = {_dataFilePath.c_str(),_dataFilePath.c_str(),_dataFilePath.c_str(),_dataFilePath.c_str()};
        SDL_Point warp;

        std::ifstream dataFile (_dataFilePath);

        if(!dataFile)
        {
            SDL_Log("Error: init_portals(): file could not be opened %s",_dataFilePath);
            exit(EXIT_FAILURE);
        }

        do
        {
            dataFile >> x >> y >> west >> east >> south >> north >> west_map >> east_map >> south_map >> north_map >> warp_x >> warp_y >> description;

            if( _dataFilePath == "./assets/data/maps/kustenstad/kustenstad_portals" )
            {
                kustenstad[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
                phlan_portal_2[x][y].setup(directions,directions_map,warp,description.c_str());
            }
            else if( _dataFilePath == "./assets/data/maps/vallentuna/vallentuna_portals" )
            {
                vallentuna[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
            }
            else if( _dataFilePath == "./assets/data/maps/mora/mora_portals" )
            {
                mora[x][y].setup(west,east,south,north,west_map.c_str(),east_map.c_str(),north_map.c_str(),south_map.c_str(),warp_x,warp_y, description.c_str());
            }
            else
            {
                SDL_Log("Error loading map data: %s", _dataFilePath);
                exit(EXIT_FAILURE);
            }
        }
        while(!dataFile.eof());

        dataFile.close();
    };

    std::string mapActive = "Kustenstad";

    void loadPortals()
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading portals\n");

        if( mapActive == "Kustenstad")
        {
            init_portals("./assets/data/maps/kustenstad/kustenstad_portals");
            for( int y = 0; y < 16; y++)
                for( int x = 0; x < 16; x++)
                    save_portals[x][y].setupStruct(kustenstad[x][y]);
        }
        if( mapActive == "Vallentuna")
        {
            init_portals("./assets/data/maps/vallentuna/vallentuna_portals");
            for( int y = 0; y < 16; y++)
                for( int x = 0; x < 16; x++)
                     save_portals[x][y].setupStruct(vallentuna[x][y]);
        }
        if( mapActive == "Mora")
        {
            init_portals("./assets/data/maps/mora/mora_portals");
            for( int y = 0; y < 16; y++)
                for( int x = 0; x < 16; x++)
                    save_portals[x][y].setupStruct(mora[x][y]);
        }
    };
    int OFFSET = 50;
};

#endif
