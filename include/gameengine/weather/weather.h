#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <string>
#include <vector>

enum {WINTER,SPRING,SUMMER,FALL};

struct weather_engine
{
    int temperature;
    bool farenheit;
    bool celsius;
    int season;

    weather_engine()
    {
        temperature = 10;
        celsius = true;
        farenheit = false;
        season = WINTER;
        climate(season);
    };

    int get_temperature()
    {
        return temperature;
    };

    std::string get_season()
    {
        if( season == WINTER )
            return " WINTER ";
        if( season == SPRING )
            return " SPRING ";
        if( season == SUMMER )
            return " SUMMER ";
        if( season == FALL )
            return " FALL ";
    }

    void climate( unsigned int in_season)
    {
        season = in_season;

        if( season == WINTER )
        {
            temperature = GenerateNumber(-32, 0);
        }
        if( season == SPRING )
        {
            temperature = GenerateNumber(0, 10);
        }
        if( season == SUMMER )
        {
            temperature = GenerateNumber(10, 36);
        }
        if( season == FALL )
        {
            temperature = GenerateNumber(0, 10);
        }
    };
};
 #endif
