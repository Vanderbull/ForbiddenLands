#ifndef PORTALS_H
#define PORTALS_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include <SDL2/SDL.h>

#include "randomizer.h"

struct Passable
{
    enum {WEST,EAST,SOUTH,NORTH};
    int Direction[4];
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

 #endif
